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
  #include "Safety.h"
  #include "MenuItem.h"
  #include "Menu.h"

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


MenuItem root;
MenuItem mainMenu[3];
int mainMenuSize = 3;
MenuItem selectProfileMenu[10];
int selectProfileSize = 10;
MenuItem calibrate[2];
int calibrateSize = 2;
MenuItem auxiliary[1];
int auxiliarySize = 1;


Menu menu(&root, &lcd, &kpd);

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

//  makeChild (&root, mainMenu, mainMenuSize);
//  wireMenu(mainMenu, mainMenuSize);
//  wireMenu(selectProfileMenu, selectProfileSize);
//  wireMenu(calibrate, calibrateSize);
//  wireMenu(auxiliary, auxiliarySize);
//
//  makeChild(&mainMenu[0], selectProfileMenu, selectProfileSize);
//  makeChild(&mainMenu[1], calibrate, calibrateSize);
//  makeChild(&mainMenu[2], auxiliary, auxiliarySize);
//
//  root.setText("Main Menu");
//
//  mainMenu[0].setText("Select Profile");
//  mainMenu[1].setText("Calibrate");
//  mainMenu[2].setText("Auxiliry");
//
//  selectProfileMenu[0].setText("ABS");
//  selectProfileMenu[0].setAction(&sayHello);
//  selectProfileMenu[1].setText("PLA");
//  selectProfileMenu[1].setValue(23.453);
//  selectProfileMenu[1].setPrecision(3);
//  selectProfileMenu[1].itemType = MenuItem::VALUE;
//
//  calibrate[0].setText("Calipers");
//  calibrate[1].setText("Starve Feeder");
//  calibrate[2].setText("Auger Motor");
//  calibrate[3].setText("Barrel");
//  calibrate[4].setText("Nozzle");
//  calibrate[5].setText("Outfeed Motor");
//  calibrate[6].setText("Spooler Motor");
//
//  calibrate[0].setAction(&testCalipers);
//  calibrate[1].setAction(&testStarveFeeder);
//  calibrate[2].setAction(&testAuger);
//  calibrate[3].setAction(&testBarrel);
//  calibrate[4].setAction(&testNozzle);
//
//  
////  menu.reset();


}

  void loop(){
    
//      //Allow for keyboard input as well
//  key = kpd.getKey();
//  if (Serial.available() > 0) {
//    key = (char)Serial.read();
//  }
//  switch(key){
//  case '1':
//    menu.up();
//    break;
//  case '2':
//    menu.down();
//    break;
//    
//  case '3':
//    menu.select();
//    break;
//  case '4':
//    menu.back();
//    break;
//  }
   state_table[stateMachine.getState()]();
 }


void wireMenu(MenuItem* menuItem,int size){
  for (int i=0;i<size-1;i++){
    menuItem[i].setNext(&menuItem[i+1]);
    menuItem[i+1].setPrevious(&menuItem[i]);
  }
}

void makeChild(MenuItem* parent, MenuItem* child, int childSize){

  for (int i=0;i<childSize;i++){
    child[i].setParent(parent);
  }
  parent->setChild(child);//Set child of parent to be the first entry in the menu
}

void sayHello() {}
void testCalipers() {}
void testStarveFeeder() {}
void testAuger() {}
void testBarrel() {}
void testNozzle() {}
