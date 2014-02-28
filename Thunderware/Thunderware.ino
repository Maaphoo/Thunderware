/*
	Thunder Head Filament Extruder Firmware

	Describe what it does in layman's terms.  Refer to the components
	attached to the various pins.

        The Thunder Head extruder is a small scale filament extruder
        that employs feedback control to improve production rate while
        maintaining good filament tolerances.

        Hardware components controlled by the firmware:

        Drive Motor: A 1200 oz in stepper motor for driving the auger

        Outfeed Motor: A NEMA17 stepper common to many 3D printers for
                pulling the filament out of the extruder

        Spool Motor: A NEMA17 stepper common to many 3D printers for
                turning the spool as filament is produced.

        Starve Feeder Motor: A NEMA17 stepper common to many 3D printers for
                feeding plastic pellets into the extruder.

        Barrel Heater: A electro-mechanical relay activated AC 130 W
                heating element used to head the Barrel of the extruder

        Nozzle Heater: A darlington transistor (TIP120) activated 12 v 5.8 ohm
                heater used to maintain the nozzle temperature

        LCD Screen: A 20x4 (ie 2004) LCD screen used to display  extruder status

        Buzzer: A ??? buzzer used for audio indication of extruder state changes and errors

        Sensors used by the firmware:

        Barrel Thermistor: A 100K EPCOS thermistor used for monitoring the barrel
                temperature.

        Nozzle Thermistor: A 100K EPCOS thermistor used for monitoring the nozzle
                temperature.

        Diameter Sensor: A 5mm optical slot sensor (transistor type) used for sensing
                the diameter of the filament.

        Key Pad: A 4x4 numeric key pad for obtaining user input.

	Created 02/12/2014
	By Matthew Rogge

*/

/*Change log:
FEB 12 Began documentation/organization of code.
      Currently the nozzleHeater is using a global variable to pass around the pwm value, perhaps this should be changed.

Jan_12 updated starve feeder for the new starve feeder design.

       added sei() to pellet interrupt because he lcd had started freaking out w/ strange symbols all over the place.
       Interrupts causing it?

12/7 - had a melt plug due to ground up pellets caused by over feeding. ground out top of barrel
       and recalibrated feeder while attached as normal. This way any noise is taken into account.
       ß
12/6 rewrote/calibrated Starve feeder. Works differently now. DEC_6_2works well still trying to improve


12/5 - Re calibrated starve feeder.


12/3
added lcd.begin() in 'D' for soak and preheat in '*' for extrude. looks like there are interrupt problems?


12/2
Added control over starve feeder feed rate.
Added independent heater at nozzle pin 5 PWM
moved buzzer to pin 1

*/

  #include <LiquidCrystal.h>
  #include <Keypad.h>
  #include <PID_v1.h>
  #include <EEPROM.h>
  #include "EEPROMAnything.h"
  #include "Thermistor.h"
  #include <stdio.h>
  #include <string.h>
  #include "application.h"
  #include "config.h"
  #include "Buzzer.h"
  #include "NozzleHeater.h"
  #include "BarrelHeater.h"
  #include "StepperMotor.h"
  #include "FastPWM.h"
  #include "Spooler.h"

//Finite State Machine for controlling the state of the extruder.

//Names of States
enum ExtruderState {
  SELECT_PROFILE,
  CUSTOM_PROFILE,
  PREHEAT,
  SOAK,
  EXTRUDE_MANUAL,
  EXTRUDE_AUTOMATIC,
  EXTRUSION_COMPLETE,
  SAFETY_SHUTDOWN,
  TEST
};
ExtruderState currentState;

Application app;


  //Stepper setup

  //Auger Stepper Setup
  float augerRPM;
  unsigned long augerSPS = augerRPM*gearRatio*augerStepMode*200L/60L;
  unsigned long aStepInterval = 1000000/augerSPS;//microseconds per step


  //outfeed stepper
  double outfeedRPM = 100;
  unsigned long outfeedSPS = outfeedRPM*outfeedStepMode*200L/60L;
  double oStepInterval = 1000000L/outfeedSPS;//microseconds per step

  //Spool Stepper
  unsigned long sStepInterval;//microseconds per step
  float sf = 1;
  float spoolRPM;


  float spoolSPS;


  //calipers
  int flag;
  double diaMeasurements[7];
  double maxDia;
  double minDia;
  double avgDia;
  double diaSum;
  int diaCount;
  double calVariation = 0.15;
  double medianDia;

  //Filament Parameters
  double diaSetPoint = 1.75;//Diameter of filament
  double mmExtruded;//length of filament extruded
  boolean resetFE = true;


  //general variables
  int i;
  int k;
  unsigned long caliperReadingInt;
  double caliperReading;
  int caliperCount = 0;
  volatile unsigned long value;
  long finalValue;
  long finalValueGood;
  long previousValue;
  unsigned long nowCal;
  unsigned long lastInterrupt;
  unsigned long reportValue;
  unsigned long finalValueReport;
  double array[180];

  //Timing
  unsigned long goTime;
  unsigned long now;
  unsigned long durration;
  unsigned long startTime;
  unsigned long stepTime;
  unsigned long reportTime;
  unsigned long computeTime;
  unsigned long startExtrudingTime;



  //Temp Sensors
  // Thermistor nozzleTh(0,100000,25, 20,4092, 9890);
  // Thermistor barrelTh(1,100000,25, 20,4092, 9910);
  boolean alternateThermistors; //Needed to keep analog sensor from heating

  double barrelTemp;
  double barrelSetPoint;

  double nozzleTemp;
  double nozzleSetPoint;

   //barrel Heater
  double barrelDutyCycle;
  unsigned long soakTime;//Time to wait once the extruder has reached temp.

   //nozzle Heater
   double nozzleDutyCycle;



  //Define Variables we'll be connecting to
  double *tempInput;
  double *tempSetPoint;

  //Define the barrel's Tuning Parameters
  double agrKp=10.8, agrKi=.3, agrKd = 20;
  double consKp=3.4, consKi=.15, consKd=0;

  double nozKp=3.5, nozKi=.15, nozKd=0;


  //Barrel Output limits
  int minDutyCycle = 0;
  int maxDutyCycle = 80;

  //nozzle Output limits
  int minNozDutyCycle = 0;
  int maxNozDutyCycle = 250;

  //Setup PID for heater
  PID barrelPID(&barrelTemp, &barrelDutyCycle, &barrelSetPoint, consKp, consKi, consKd, DIRECT);
  PID nozzlePID(&nozzleTemp, &nozzleDutyCycle, &nozzleSetPoint, nozKp, nozKi, nozKd, DIRECT);


  //Setup PID for outfeed motor
  double diaKp=3, diaKi=0, diaKd=0;
  PID outfeedPID(&medianDia, &outfeedRPM, &diaSetPoint, diaKp, diaKi, diaKd, REVERSE);


//Setup Finite State Machine

void selectProfile();
void customProfile();
void preheat();
void soak();
void extrudeManual();
void extrudeAutomatic();
void extrudeComplete();
void safetyShutdown();
void test();

//Pointers to State functios
void (*state_table[])()={
  selectProfile,
  customProfile,
  preheat,
  soak,
  extrudeManual,
  extrudeAutomatic,
  extrudeComplete,
  safetyShutdown,
  test
};

//initialize library with LCD interface pins
LiquidCrystal lcd(26,24,22,37,35,33,31,29,27,25,23);

//Keypad Rows and Columns
const byte ROWS=4;
const byte COLS=4;

//initialize keypad pins
byte rowPins[ROWS]={45,43,41,39};
byte colPins[COLS]={53,51,49,47};

//Keymap
char keys[ROWS][COLS]={
    {'1','4','7','*'},
    {'2','5','8','0'},
    {'3','6','9','#'},
    {'A','B','C','D'}
};

//Initialize Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char key;//The key that is pressed

//initialize buzzer
Buzzer buzzer;

//Initialize nozzle heater
NozzleHeater nozzleHeater;

//Initialize Barrel heater
BarrelHeater barrelHeater;

//Initialize Stepper Motors
StepperMotor auger(StepperMotor::SET_3_14_8, 4);

Outfeed outfeed(StepperMotor::SET_11_15_12, 1);
Spooler spool(outfeed, StepperMotor::SET_10_16_9, 2);

//Initialize FastPWM timers
//FastPWM timer1(1);
//FastPWM timer2(2);
//FastPWM timer4(4);

#include "Calipers.h"
#include "Extrude.h"
#include "FSM.h"
#include "Preheat.h"
#include "Safety.h"
#include "StarveFeeder.h"
#include "TestReporting.h"
#include "test.h"


void setup()
{
  Serial.begin(115200);
//  buzzer.setMsg(2);
//  for (int i=0;i<20000;i++){
//    delay(10);
//    buzzer.activate();
//  }
  initializeCalipers();
  initializeStarveFeeder();
  lcd.begin(20, 4); //Start up LCD

 //turn the PID on
  barrelPID.SetSampleTime(2000);
  barrelPID.SetTunings(consKp, consKi, consKd);
  barrelPID.SetOutputLimits(minDutyCycle, maxDutyCycle);
  barrelPID.SetMode(AUTOMATIC);

  nozzlePID.SetSampleTime(2000);
  nozzlePID.SetTunings(nozKp, nozKi, nozKd);
  nozzlePID.SetOutputLimits(minNozDutyCycle, maxNozDutyCycle);
  nozzlePID.SetMode(AUTOMATIC);

  //put the outfeed PID is in manual
  outfeedPID.SetSampleTime(2000);
  outfeedPID.SetTunings(diaKp, diaKi, diaKd);
  outfeedPID.SetMode(MANUAL);
  outfeedPID.SetOutputLimits(0,200);

//  currentState = SELECT_PROFILE;
  currentState = TEST;
//  currentState = EXTRUDE_AUTOMATIC;
}

  void loop(){
   state_table[currentState]();
 }












