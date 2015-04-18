/*
	Thunder Head Filament Extruder Firmware

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
//#include "StateMachine.h"
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
//#include <MemoryFree.h>

Application app;
Configuration configuration;

//Setup Finite State Machine
enum ExtruderStates {
  SELECT_PROFILE,
  PREHEAT,
  SOAK,
  BEGIN_EXTRUDE,
  LOAD_FILAMENT,
  EXTRUDE,
  TEST,
  CALIBRATE_CALIPERS
} currentState;

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
void (*state_table[])() = {
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
const byte ROWS = 4;
const byte COLS = 4;

//Membrane Kpd initialize keypad pins

byte colPins[ROWS] = {29, 27, 25, 23};
byte rowPins[COLS] = {37, 35, 33, 31};

//Keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
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
//StateMachine stateMachine;

Buzzer buzzer;

Nozzle nozzle(&configuration);

Barrel barrel(&configuration);

//StarveFeeder starveFeeder(&configuration);

StepperMotor auger(&configuration, configuration.physical.augerPinSet);

Outfeed outfeed(&configuration);

Spooler spooler(&configuration, &outfeed);

Safety safety(&configuration, &barrel, &nozzle);


MenuItem root;

MenuItem mainMenu[3];
int mainMenuSize = 3;

MenuItem selectProfileMenu[11];
int selectProfileSize = 11;
MenuItem calibrate[10];
int calibrateSize = 10;
MenuItem auxiliary[2];
int auxiliarySize = 2;

MenuItem profile[20 ];
int profileSize = 20;

MenuItem caliperConfig[1];
int caliperConfigSize = 1;
MenuItem augerConfig[6];
int augerConfigSize = 6;
MenuItem barrelConfig [12];
int barrelConfigSize = 12;
MenuItem nozzleConfig [13];
int nozzleConfigSize = 13;
MenuItem outfeedConfig [8];
int outfeedConfigSize = 8;
MenuItem spoolerConfig[11];
int spoolerConfigSize = 11;
MenuItem  starveFeederConfig[14];
int  starveFeederConfigSize = 14;


Menu menu(&root, &lcd, &kpd);

#include "Extrude.h"
#include "FSM.h"
#include "Preheat.h"
#include "Safety.h"
#include "TestReporting.h"
#include "test.h"
#include "strings.h"

void setup()
{
  Serial.begin(115200);
  while (!Serial); // while the serial stream is not open, do nothing:
  Wire.begin();
  lcd.begin(20, 4); //Start up LCD
  lcd.clear();


  buzzer.setMsg(Buzzer::POWER_ON);
  //  stateMachine.setState(StateMachine::SELECT_PROFILE);

  // currentState = TEST;
  //  currentState = EXTRUDE_AUTOMATIC;

  makeChild (&root, mainMenu, mainMenuSize);

  wireMenu(mainMenu, mainMenuSize);

  wireMenu(selectProfileMenu, selectProfileSize);
  wireMenu(calibrate, calibrateSize);
  wireMenu(auxiliary, auxiliarySize);

  wireMenu(profile, profileSize);

  wireMenu(starveFeederConfig, starveFeederConfigSize);
  wireMenu(augerConfig, augerConfigSize);
  wireMenu(barrelConfig, barrelConfigSize);
  wireMenu(nozzleConfig, nozzleConfigSize);
  wireMenu(outfeedConfig, outfeedConfigSize);
  wireMenu(spoolerConfig, spoolerConfigSize);

  makeChild(&mainMenu[0], selectProfileMenu, selectProfileSize);
  makeChild(&mainMenu[1], calibrate, calibrateSize);
  makeChild(&mainMenu[2], auxiliary, auxiliarySize);

  for (int i = 0; i < 10; i++) {
    makeChild(&selectProfileMenu[i], profile, profileSize);//should be all 10
  }

  makeChild(&calibrate[1], starveFeederConfig, starveFeederConfigSize);
  makeChild(&calibrate[2], augerConfig, augerConfigSize);
  makeChild(&calibrate[3], barrelConfig, barrelConfigSize);
  makeChild(&calibrate[4], nozzleConfig, nozzleConfigSize);
  makeChild(&calibrate[5], outfeedConfig, outfeedConfigSize);
  makeChild(&calibrate[6], spoolerConfig, spoolerConfigSize);
  
  root.setText("Main Menu");

  mainMenu[0].setText("Select Profile");
  mainMenu[1].setText("Calibrate");
  mainMenu[2].setText("Auxiliry");

  //Load the profile titles and link them to their data stored in EEPROM
  for (int i = 0; i < 10; i++) {
    configuration.loadProfileName(configuration.profileNames[i], i);
    selectProfileMenu[i].setText(configuration.profileNames[i]);
    selectProfileMenu[i].setDoActionOnSelect(true);
  }

  //Not sure how to do the following as part of the above loop or use one function (loadProfile) easily
  selectProfileMenu[0].setAction(&loadProfile0);
  selectProfileMenu[1].setAction(&loadProfile1);
  selectProfileMenu[2].setAction(&loadProfile2);
  selectProfileMenu[3].setAction(&loadProfile3);
  selectProfileMenu[4].setAction(&loadProfile4);
  selectProfileMenu[5].setAction(&loadProfile5);
  selectProfileMenu[6].setAction(&loadProfile6);
  selectProfileMenu[7].setAction(&loadProfile7);
  selectProfileMenu[8].setAction(&loadProfile8);
  selectProfileMenu[9].setAction(&loadProfile9);

  //  selectProfileMenu[0].setText("1.85mm PET");
  //  selectProfileMenu[0].setDoActionOnSelect(true);
  //  selectProfileMenu[0].setAction(&loadProfile1);

  selectProfileMenu[10].setText("Default Profile");
  selectProfileMenu[10].setDoActionOnSelect(true);
  selectProfileMenu[10].setAction(&loaddDefaultProfile);

  profile[0].setText("Extrude");
  profile[0].setAction(&extrude1);
  profile[1].setText("Save Current Setngs");
  profile[1].setAction(&saveCurrentSettings1);
  profile[1].setType(MenuItem::ACTION);
  profile[2].setText("Name");
  profile[2].setType(MenuItem::STRING);
  profile[3].setupVal("Dia Set Point",
                      MenuItem::DOUBLE,
                      &configuration.profile.diaSetPoint,
                      2);
  profile[4].setupVal("Tolerance",
                      MenuItem::FLOAT,
                      &configuration.profile.tolerance,
                      3);

  profile[5].setupVal("Grams Per Min",
                      MenuItem::FLOAT,
                      &configuration.profile.starveFeederTargetFeedRate,
                      2);

  profile[6].setupVal("Auger RPM",
                      MenuItem::FLOAT,
                      &configuration.profile.augerRPM,
                      2);

  profile[7].setupVal("Outfeed RPM",
                      MenuItem::DOUBLE,
                      &configuration.profile.outfeedRPM,
                      2);

  profile[8].setupVal("Outfeed Ki",
                      MenuItem::DOUBLE,
                      &configuration.profile.outfeedKi,
                      2);

  profile[9].setupVal("Outfeed Kp",
                      MenuItem::DOUBLE,
                      &configuration.profile.outfeedKp,
                      2);

  profile[10].setupVal("Outfeed Kd",
                       MenuItem::DOUBLE,
                       &configuration.profile.outfeedKd,
                       2);

  profile[11].setupVal("OutfeedMaxRPM",
                       MenuItem::DOUBLE,
                       &configuration.profile.outfeedMaxRPM,
                       2);

  profile[12].setupVal("OutfeedMinRPM",
                       MenuItem::DOUBLE,
                       &configuration.profile.outfeedMinRPM,
                       2);

  profile[13].setupVal("OF Comp Int",
                       MenuItem::INT,
                       &configuration.profile.outfeedComputeInterval
                      );

  profile[14].setupVal("Soak Time",
                       MenuItem::DOUBLE,
                       &configuration.profile.soakTime
                      );

  profile[15].setupVal("Barrel Temp",
                       MenuItem::DOUBLE,
                       &configuration.profile.barrelTemp
                      );

  profile[16].setupVal("Nozzle Temp",
                       MenuItem::DOUBLE,
                       &configuration.profile.nozzleTemp
                      );

  profile[17].setupVal("Min Temp",
                       MenuItem::DOUBLE,
                       &configuration.profile.minExtrudeTemp
                      );

  profile[18].setupVal("Max Temp",
                       MenuItem::DOUBLE,
                       &configuration.profile.maxTemp
                      );

  profile[19].setupVal("Max Preheat Time",
                       MenuItem::UNSIGNED_LONG,
                       &configuration.profile.maxPreheatTime
                      );



  calibrate[0].setText("Calipers");
  calibrate[1].setText("Starve Feeder");
  calibrate[2].setText("Auger");
  calibrate[3].setText("Barrel");
  calibrate[4].setText("Nozzle");
  calibrate[5].setText("Outfeed");
  calibrate[6].setText("Spooler");
  calibrate[7].setText("Load Default Config");
  calibrate[7].setAction(&loadDefaultConfig);
  calibrate[7].setType(MenuItem::ACTION);
  calibrate[8].setText("Load Saved Config"); //done at startup
  calibrate[8].setAction(&loadConfig);
  calibrate[8].setType(MenuItem::ACTION);
  calibrate[9].setText("Save Current Config");
  calibrate[9].setAction(&saveConfig);
  calibrate[9].setType(MenuItem::ACTION);

  //  calibrate[0].setAction(&testCalipers);
  //  calibrate[1].setAction(&testStarveFeeder);
  //  calibrate[2].setAction(&testAuger);
  //  calibrate[3].setAction(&testBarrel);
  //  calibrate[4].setAction(&testNozzle);
  //  calibrate[5].setAction(&testOutfeed);

  augerConfig[0].setText("Test Auger");
  augerConfig[0].setAction(&testAuger);
  augerConfig[1].setupVal("Pin Set",
                          MenuItem::INT,
                          &configuration.physical.augerPinSet
                         );

  augerConfig[2].setupVal("Step Mode",
                          MenuItem::INT,
                          &configuration.physical.augerStepMode
                         );

  augerConfig[3].setupVal("Direction",
                          MenuItem::BOOLEAN,
                          &configuration.physical.augerDirection
                         );

  augerConfig[4].setupVal("Enable",
                          MenuItem::BOOLEAN,
                          &configuration.physical.augerEnable
                         );

  augerConfig[5].setupVal("Gear Ratio",
                          MenuItem::FLOAT,
                          &configuration.physical.augerGearRatio,
                          2);




  barrelConfig[0].setText("Test Barrel");
  barrelConfig[0].setAction(&testBarrel);

  barrelConfig[1].setupVal("TimeBase",
                           MenuItem::INT,
                           &configuration.physical.timeBase
                          );

  barrelConfig[2].setupVal("Max DutyCycle",
                           MenuItem::DOUBLE,
                           &configuration.physical.barrelMax,
                           2);

  barrelConfig[3].setupVal("Min DutyCycle",
                           MenuItem::DOUBLE,
                           &configuration.physical.barrelMin,
                           2);

  barrelConfig[4].setupVal("Ki",
                           MenuItem::DOUBLE,
                           &configuration.physical.barrelKi,
                           2);

  barrelConfig[5].setupVal("Kp",
                           MenuItem::DOUBLE,
                           &configuration.physical.barrelKp,
                           2);

  barrelConfig[6].setupVal("Kd",
                           MenuItem::DOUBLE,
                           &configuration.physical.barrelKd,
                           2);

  barrelConfig[7].setupVal("Nom Resistance",
                           MenuItem::INT,
                           &configuration.physical.barrelTRNom
                          );

  barrelConfig[8].setupVal("Nom Temp",
                           MenuItem::INT,
                           &configuration.physical.barrelTTNom
                          );

  barrelConfig[9].setupVal("Num Samples",
                           MenuItem::INT,
                           &configuration.physical.barrelTNumSamples
                          );

  barrelConfig[10].setupVal("B Coef",
                            MenuItem::INT,
                            &configuration.physical.barrelTBCoefficient
                           );

  barrelConfig[11].setupVal("Series R",
                            MenuItem::INT,
                            &configuration.physical.barrelTSeriesResistor
                           );



  nozzleConfig[0].setText("Test nozzle");
  nozzleConfig[0].setAction(&testNozzle);

  nozzleConfig[1].setupVal("Pin",
                           MenuItem::INT,
                           &configuration.physical.nozzlePin
                          );
  nozzleConfig[2].setupVal("SampleTime",
                           MenuItem::INT,
                           &configuration.physical.nozzleSampleTime
                          );

  nozzleConfig[3].setupVal("Max DutyCycle",
                           MenuItem::DOUBLE,
                           &configuration.physical.nozzleMax,
                           2);

  nozzleConfig[4].setupVal("Min DutyCycle",
                           MenuItem::DOUBLE,
                           &configuration.physical.nozzleMin,
                           2);

  nozzleConfig[5].setupVal("Ki",
                           MenuItem::DOUBLE,
                           &configuration.physical.nozzleKi,
                           2);

  nozzleConfig[6].setupVal("Kp",
                           MenuItem::DOUBLE,
                           &configuration.physical.nozzleKp,
                           2);

  nozzleConfig[7].setupVal("Kd",
                           MenuItem::DOUBLE,
                           &configuration.physical.nozzleKd,
                           2);

  nozzleConfig[8].setupVal("Nom Resistance",
                           MenuItem::INT,
                           &configuration.physical.nozzleTRNom
                          );

  nozzleConfig[9].setupVal("Nom Temp",
                           MenuItem::INT,
                           &configuration.physical.nozzleTTNom
                          );

  nozzleConfig[10].setupVal("Num Samples",
                            MenuItem::INT,
                            &configuration.physical.nozzleTNumSamples
                           );

  nozzleConfig[11].setupVal("B Coef",
                            MenuItem::INT,
                            &configuration.physical.nozzleTBCoefficient
                           );

  nozzleConfig[12].setupVal("Series R",
                            MenuItem::INT,
                            &configuration.physical.nozzleTSeriesResistor
                           );




  outfeedConfig[0].setText("Test Outfeed");
  outfeedConfig[0].setAction(&testOutfeed);

  outfeedConfig[1].setupVal("Pin Set",
                            MenuItem::INT,
                            &configuration.physical.outfeedPinSet
                           );

  outfeedConfig[2].setupVal("Step Mode",
                            MenuItem::INT,
                            &configuration.physical.outfeedStepMode
                           );

  outfeedConfig[3].setupVal("Direction",
                            MenuItem::BOOLEAN,
                            &configuration.physical.outfeedDirection
                           );

  outfeedConfig[4].setupVal("Enable",
                            MenuItem::BOOLEAN,
                            &configuration.physical.outfeedEnable
                           );

  outfeedConfig[5].setupVal("Roller Rad",
                            MenuItem::DOUBLE,
                            &configuration.physical.outfeedRollerRadius,
                            2);

  outfeedConfig[6].setupVal("Max RPM",
                            MenuItem::DOUBLE,
                            &configuration.physical.outfeedMaxRPM,
                            2);

  outfeedConfig[7].setupVal("Min RPM",
                            MenuItem::DOUBLE,
                            &configuration.physical.outfeedMinRPM,
                            2);





  starveFeederConfig[0].setText("Test Starve Feeder");
  starveFeederConfig[0].setAction(&testStarveFeeder);
  starveFeederConfig[1].setupVal("Lump Mass",
                                 MenuItem::FLOAT,
                                 &configuration.physical.starveFeederLumpMass,
                                 2);

  starveFeederConfig[2].setupVal("DumpPosition",
                                 MenuItem::INT,
                                 &configuration.physical.starveFeederDumpPosition
                                );

  starveFeederConfig[3].setupVal("Step Delay",
                                 MenuItem::INT,
                                 &configuration.physical.starveFeederStepDelay
                                );

  starveFeederConfig[4].setupVal("Home Delay",
                                 MenuItem::INT,
                                 &configuration.physical.starveFeederHomeDelay
                                );

  starveFeederConfig[5].setupVal("Over Rotation",
                                 MenuItem::INT,
                                 &configuration.physical.starveFeederOverRotation
                                );

  starveFeederConfig[6].setupVal("Direction",
                                 MenuItem::BOOLEAN,
                                 &configuration.physical.starveFeederDirection
                                );

  starveFeederConfig[7].setupVal("Max DutyCycle",
                                 MenuItem::INT,
                                 &configuration.physical.starveFeederMaxDutyCycle
                                );

  starveFeederConfig[8].setupVal("Min DutyCycle",
                                 MenuItem::INT,
                                 &configuration.physical.starveFeederMinDutyCycle
                                );

  starveFeederConfig[9].setupVal("Sensor Pin",
                                 MenuItem::INT,
                                 &configuration.physical.starveFeederSensorPin
                                );

  starveFeederConfig[10].setupVal("Direction Pin",
                                  MenuItem::INT,
                                  &configuration.physical.starveFeederDirectionPin
                                 );

  starveFeederConfig[11].setupVal("Step Pin",
                                  MenuItem::INT,
                                  &configuration.physical.starveFeederStepPin
                                 );

  starveFeederConfig[12].setupVal("Enable Pin",
                                  MenuItem::INT,
                                  &configuration.physical.starveFeederEnablePin
                                 );

  starveFeederConfig[13].setupVal("Vib Pin",
                                  MenuItem::INT,
                                  &configuration.physical.starveFeederVibPin
                                 );

  //Spooler config menu
  spoolerConfig[0].setText("Test Spooler");
  spoolerConfig[0].setAction(&testSpooler);

  spoolerConfig[1].setupVal("PIN SET",
                            MenuItem::INT,
                            &configuration.physical.spoolerPinSet
                           );

  spoolerConfig[2].setupVal("Step Mode",
                            MenuItem::INT,
                            &configuration.physical.spoolerStepMode
                           );

  spoolerConfig[3].setupVal("Direction",
                            MenuItem::BOOLEAN,
                            &configuration.physical.spoolerDirection
                           );

  spoolerConfig[4].setupVal("Enable",
                            MenuItem::BOOLEAN,
                            &configuration.physical.spoolerEnable
                           );

  spoolerConfig[5].setupVal("Disk Radius",
                            MenuItem::FLOAT,
                            &configuration.physical.spoolerDiskRadius,
                            1);

  spoolerConfig[6].setupVal("Core Radius",
                            MenuItem::FLOAT,
                            &configuration.physical.spoolerCoreRadius,
                            1);

  spoolerConfig[7].setupVal("Traverse Len",
                            MenuItem::FLOAT,
                            &configuration.physical.spoolerTraverseLength,
                            1);

  spoolerConfig[8].setupVal("Traverse Len",
                            MenuItem::FLOAT,
                            &configuration.physical.spoolerTraverseLength,
                            1);

  spoolerConfig[9].setupVal("Roller Raduis",
                            MenuItem::FLOAT,
                            &configuration.physical.spoolerMotorRollerRaduis,
                            1);

  spoolerConfig[10].setupVal("Traverse Len",
                             MenuItem::FLOAT,
                             &configuration.physical.spoolerTraverseLength,
                             1);

  auxiliary[0].setText("Measure Filament");
  auxiliary[1].setText("Reset EEPROM");
  auxiliary[1].setType(MenuItem::ACTION);
  auxiliary[1].setAction(&resetEEPROM);

  //  starveFeederConfig[1].setupVal("MinFillTime",
  //                                 MenuItem::INT,
  //                                 &testInt
  //                                 );
  //  starveFeederConfig[2].setupVal("maxFillTime",
  //                                 MenuItem::INT,
  //                                 &testLong
  //                                 );
  //  starveFeederConfig[3].setupVal("StartupTime",
  //                                 MenuItem::INT,
  //                                 &testFloat
  //                                 );
  //  starveFeederConfig[8].setupVal("Startup DCyc",
  //                                 MenuItem::INT,
  //                                 &testDouble
  //                                 );
  //  starveFeederConfig[9].setupVal("DutyCycle",
  //                                 MenuItem::INT,
  //                                 &testDouble
  //                                 );
  //  starveFeederConfig[4].setupVal("debounceTime",
  //                                 MenuItem::INT,
  //                                 &testDouble
  //                                 );


  menu.reset();
}

void loop() {

  //Allow for keyboard input as well
  key = kpd.getKey();
  if (Serial.available() > 0) {
    key = (char)Serial.read();
  }
  //  if (key) {
  //    Serial.print("freeMemory()=");
  //    Serial.println(freeMemory());
  //  }
  switch (key) {
    case '1':
      menu.up();
      break;
    case '2':
      menu.down();
      break;

    case '3':
      menu.select();
      break;
    case '4':
      menu.back();
      break;
    case '5':
      menu.printSelected();
      break;
  }
//  state_table[currentState]();
}


void wireMenu(MenuItem* menuItem, int size) {
  for (int i = 0; i < size - 1; i++) {
    menuItem[i].setNext(&menuItem[i + 1]);
    menuItem[i + 1].setPrevious(&menuItem[i]);
  }
}

void makeChild(MenuItem* parent, MenuItem* child, int childSize) {

  for (int i = 0; i < childSize; i++) {
    child[i].setParent(parent);
  }
  parent->setChild(child);//Set child of parent to be the first entry in the menu
}


//Wrapper functions for menu items whos actions are member fucntions of other classes

void loadDefaultConfig() {
  configuration.loadDefaultConfig();
  lcd.clear();
  lcd.print(F("Configuration Loaded"));
  delay(2000);
  menu.display();
}

void loadConfig() {
  lcd.clear();
  lcd.print(F("Loading..."));
  delay(500);
  configuration.loadConfig();
  lcd.clear();
  lcd.print(F("Configuration Loaded"));
  delay(2000);
  menu.display();
}

void saveConfig() {
  lcd.clear();
  lcd.print(F("Saving..."));
  delay(500);
  configuration.saveConfig();
  lcd.clear();
  lcd.print(F("Configuration Saved"));
  delay(2000);
  menu.display();
}


void loadProfile0() {
  configuration.loadProfile(0);
  profile[2]._value1 = configuration.profileNames[0];
}
void loadProfile1() {
  configuration.loadProfile(1);
  profile[2]._value1 = configuration.profileNames[1];
}
void loadProfile2() {
  configuration.loadProfile(2);
  profile[2]._value1 = configuration.profileNames[2];
}
void loadProfile3() {
  configuration.loadProfile(3);
  profile[2]._value1 = configuration.profileNames[3];
}
void loadProfile4() {
  configuration.loadProfile(4);
  profile[2]._value1 = configuration.profileNames[4];
}
void loadProfile5() {
  configuration.loadProfile(5);
  profile[2]._value1 = configuration.profileNames[5];
}
void loadProfile6() {
  configuration.loadProfile(6);
  profile[2]._value1 = configuration.profileNames[6];
}
void loadProfile7() {
  configuration.loadProfile(7);
  profile[2]._value1 = configuration.profileNames[7];
}
void loadProfile8() {
  configuration.loadProfile(8);
  profile[2]._value1 = configuration.profileNames[8];
}
void loadProfile9() {
  configuration.loadProfile(9);
  profile[2]._value1 = configuration.profileNames[9];
}

void loaddDefaultProfile() {
  configuration.loadDefaultProfile();
}
void extrude1() {

}


void saveCurrentSettings1() {
  Serial.print("Saving Settings for profile number: ");
  Serial.println(configuration.profile.profileNumber);
  configuration.saveProfile();
}
void resetEEPROM() {
  Serial.println(F("WARNING: This action will overwirte all stored profiles with the default Settings."));
  lcd.clear();
  lcd.print(F("WARNING: This action"));
  lcd.print(F("will overwrite all "));
  lcd.print(F("stored profiles with"));
  lcd.print(F("the default settings"));
  delay (5000);
  Serial.println(F("Would you like to proceed? y or n"));
  lcd.clear();
  lcd.print(F("Would you like to proceed?"));
  lcd.print(F("  y or n"));

  boolean waitForResponse = true;
  while (waitForResponse) {
    key = kpd.getKey();

    //Allow for keyboard input as well
    if (Serial.available() > 0) {
      key = (char)Serial.read();
    }

    if (key == 'y') {
      Serial.println(F("Resetting the EEPROM..."));
      lcd.clear();
      lcd.print(F("Resetting EEPROM..."));
      configuration.loadDefaultProfile();
      for (int i = 0; i < 10; i++) {
        configuration.profile.profileNumber = i;
        selectProfileMenu[i].setText(configuration.profileNames[i]);//The names have been reset. This will reflect the change
        configuration.saveProfile();
      }
      waitForResponse = false;
    }

    if (key == 'n') {
      waitForResponse = false;
    }
  }
  menu.display();
}



