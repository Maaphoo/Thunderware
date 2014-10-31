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

Changes that need to be made for Quito

  1) Add logic and config for enable/disable so it can be switched easily
  2) check that code works with buzzer logic
  3) Re write Spooler code so that it works with new geometry
  4) Test keypad
  5) test LCD
  6) Verify the correct logic on the nozzle/barrel heaters.
  
Genneral additions:
  Indicator LED for nozzle and barrel heaters.
  

*/

  #include <LiquidCrystal.h>
  #include <Keypad.h>
  #include <PID_v1.h>
  #include <EEPROM.h>
  #include <Wire.h>
  #include "EEPROMAnything.h"
  #include "Thermistor.h"
  #include <stdio.h>
  #include <string.h>
  #include "application.h"
  #include "StateMachine.h"
  #include "Configuration.h"
  #include "config.h"
  #include "Buzzer.h"
  #include "Nozzle.h"
  #include "Barrel.h"
  #include "StepperMotor.h"
  #include "FastPWM.h"
  #include "Spooler.h"
  #include "StarveFeeder.h"
  #include "Caliper.h"
  #include "OMMenuMgr.h"
  #include "Safety.h"

Application app;
Configuration configuration;

//Setup Finite State Machine

void selectProfile();
void customProfile();
void preheat();
void soak();
void beginExtrude();
void loadFilament();
void extrude();
void test();
void calibrateCalipers();

//Pointers to State functios
void (*state_table[])()={
  selectProfile,
  preheat,
  soak,
  beginExtrude,
  loadFilament,
  extrude,
  test,
  calibrateCalipers
};

// lcd pins
const byte LCD_RS  = 22;
const byte LCD_EN  = 24;
const byte LCD_D4  = 26;
const byte LCD_D5  = 28;
const byte LCD_D6  = 30;
const byte LCD_D7  = 32;


const byte LCD_ROWS = 4;
const byte LCD_COLS = 20;

//initialize library with LCD interface pins
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

 //Keypad Rows and Columns
 const byte ROWS=4;
 const byte COLS=4;
 
 //Membrane Kpd initialize keypad pins

 byte colPins[ROWS]={29, 27, 25, 23};
 byte rowPins[COLS]={37, 35, 33, 31};
 
 //Keymap
 char keys[ROWS][COLS]={
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
 };
 
//  //Black Kpd initialize keypad pins
//
// byte colPins[ROWS]={23,25,27,29};
// byte rowPins[COLS]={31,33,35,37};
// 
// //Keymap
// char keys[ROWS][COLS]={
// {'1','2','3','A'},
// {'4','5','6','B'},
// {'7','8','9','C'},
// {'*','0','#','D'}
// };
 
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char key;//The key that is pressed

//Initialize objects
StateMachine stateMachine;

Buzzer buzzer;

Nozzle nozzle(&configuration);

Barrel barrel(&configuration);

StarveFeeder starveFeeder(&configuration);

StepperMotor auger(&configuration, configuration.physical.augerPinSet);

Outfeed outfeed(&configuration);

Spooler spooler(&configuration, &outfeed);

Safety safety(&configuration, &barrel, &nozzle, &stateMachine);



#include "Extrude.h"
#include "FSM.h"
#include "Preheat.h"
#include "Safety.h"
#include "TestReporting.h"
#include "test.h"


void setup()
{
  Serial.begin(115200);
  Wire.begin();
  lcd.begin(20, 4); //Start up LCD

  stateMachine.setState(StateMachine::SELECT_PROFILE);
// currentState = TEST;
//  currentState = EXTRUDE_AUTOMATIC;


}

  void loop(){
   state_table[stateMachine.getState()]();
 }





