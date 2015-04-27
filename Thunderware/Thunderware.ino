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
#include <avr/pgmspace.h>
#include "EEPROMAnything.h"
#include "Thermistor.h"
#include <stdio.h>
#include <string.h>
#include "application.h"
//#include "StateMachine.h"
#include "Configuration.h"
//#include "config.h"
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
#include "test.h"



//MenuItem Text strings
const char root[] PROGMEM = "Main Menu";
const char selectProfile[] PROGMEM = "Select Profile";
const char calibrate[] PROGMEM = "Calibrate";
const char auxiliary[] PROGMEM = "Auxiliary";
const char profile0[] PROGMEM = "1)";
const char profile1[] PROGMEM = "2)";
const char profile2[] PROGMEM = "3)";
const char profile3[] PROGMEM = "4)";
const char profile4[] PROGMEM = "5)";
const char profile5[] PROGMEM = "6)";
const char profile6[] PROGMEM = "7)";
const char profile7[] PROGMEM = "8)";
const char profile8[] PROGMEM = "9)";
const char profile9[] PROGMEM = "10)";
const char defaultProfile[] PROGMEM = "Default";
const char extrudeStr[] PROGMEM = "Extrude";
const char saveProfile[] PROGMEM = "Save Profile";
const char profileName[] PROGMEM = "Name";
const char diaSetPoint[] PROGMEM = "Diameter";
const char tolerance[] PROGMEM = "Tolerance";
const char gramsPerMin[] PROGMEM = "GramsPerMin";
const char augerRPM[] PROGMEM = "Auger RPM";
const char outfeedRPM[] PROGMEM = "Outfeed RPM";
const char outfeedKp[] PROGMEM = "Outfeed Kp";
const char outfeedKi[] PROGMEM = "Outfeed Ki";
const char outfeedKd[] PROGMEM = "Outfeed Kp";
const char soakTime[] PROGMEM = "Soak Time";
const char barrelTempStr[] PROGMEM = "Barrel Temp";
const char nozzleTempStr[] PROGMEM = "Nozzle Temp";
const char barrelSetTemp[] PROGMEM = "Barrel Temp";
const char nozzleSetTemp[] PROGMEM = "Nozzle Temp";
const char minTemp[] PROGMEM = "Min Temp";
const char maxTemp[] PROGMEM = "Max Temp";
const char maxPreheatTime[] PROGMEM = "MaxPreheatTime";
const char starveFeederConfig[] PROGMEM = "Starve Feeder";
const char augerConfig[] PROGMEM = "Auger";
const char barrelConfig[] PROGMEM = "Barrel";
const char nozzleConfig[] PROGMEM = "Nozzle";
const char outfeedConfig[] PROGMEM = "Outfeed";
const char spoolerConfig[] PROGMEM = "Spooler";
const char testStarveFeederStr[] PROGMEM = "Test Starve Feeder";
const char testAugerStr[] PROGMEM = "Test Auger";
const char augerPinSet[] PROGMEM = "Pin Set";
const char augerStepMode[] PROGMEM = "Step Mode";
const char augerDirection[] PROGMEM = "Direction";
const char augerEnable[] PROGMEM = "Enable";
const char augerGearRatio[] PROGMEM = "Gear Ratio";
const char testBarrelStr[] PROGMEM = "Test Barrel";
const char timeBase[] PROGMEM = "Time Base";
const char barrelMaxDutyCycle[] PROGMEM = "Max Duty Cycle";
const char barrelMinDutyCycle[] PROGMEM = "Min Duty Cycle";
const char barrelKp[] PROGMEM = "Kp";
const char barrelKi[] PROGMEM = "Ki";
const char barrelKd[] PROGMEM = "Kd";
const char barrelTRNom[] PROGMEM = "Ther Resist Nom";
const char barrelTTNom[] PROGMEM = "Ther Temp Nom";
const char barrelTNumSamples[] PROGMEM = "Ther Num Samples";
const char barrelTBCoefficient[] PROGMEM = "Ther B Coef";
const char barrelTSeriesResistor[] PROGMEM = "Ther S Resist";
const char testNozzleStr[] PROGMEM = "Test Nozzle";
const char nozzlePin[] PROGMEM = "Pin";
const char nozzleMaxDutyCycle[] PROGMEM = "Max Duty Cycle";
const char nozzleMinDutyCycle[] PROGMEM = "Min Duty Cycle";
const char nozzleKp[] PROGMEM = "Kp";
const char nozzleKi[] PROGMEM = "Ki";
const char nozzleKd[] PROGMEM = "Kd";
const char nozzleSampleTime[] PROGMEM = "Sample Time";
const char nozzleTRNom[] PROGMEM = "Ther Resist Nom";
const char nozzleTTNom[] PROGMEM = "Ther Temp Nom";
const char nozzleTNumSamples[] PROGMEM = "Ther Num Samples";
const char nozzleTBCoefficient[] PROGMEM = "Ther B Coef";
const char nozzleTSeriesResistor[] PROGMEM = "Ther S Resist";
const char testOutfeedStr[] PROGMEM = "Test Outfeed";
const char outfeedPinSet[] PROGMEM = "Pin Set";
const char outfeedStepMode[] PROGMEM = "Step Mode";
const char outfeedDirection[] PROGMEM = "Direction";
const char outfeedEnable[] PROGMEM = "Enable";
const char outfeedRollerRadius[] PROGMEM = "Roller Radius";
const char outfeedMaxRPM[] PROGMEM = "Max RPM";
const char outfeedMinRPM[] PROGMEM = "Min RPM";
const char testSpoolerStr[] PROGMEM = "Test Spooler";
const char spoolerPinSet[] PROGMEM = "Pin Set";
const char spoolerStepMode[] PROGMEM = "Step Mode";
const char spoolerDirection[] PROGMEM = "Direction";
const char spoolerEnable[] PROGMEM = "Enable";
const char spoolerDiskRadius[] PROGMEM = "Disk Radius";
const char spoolerCoreRadius[] PROGMEM = "Core Radius";
const char spoolerTraverseLength[] PROGMEM = "Traverse Length";
const char spoolerMotorRollerRadius[] PROGMEM = "Roller Radius";
const char preheatRoot[] PROGMEM = "Preheating...";
const char soakRoot[] PROGMEM = "Soaking...";
const char soakTimeRemainingStr[] PROGMEM = "Soak Time Left";
const char increaseSoakTimeStr[] PROGMEM = "Increase Soak Time";
const char decreaseSoakTimeStr[] PROGMEM = "Decrease Soak Time";
const char skipSoakStr[] PROGMEM = "Skip Soak";
const char loadFilamentRoot[] PROGMEM = "Load Filament...";
const char loadFilamentRemainingTime[] PROGMEM = "Time Remaining";
const char filamentLoadedStr[] PROGMEM = "Filament Loaded";
const char loadFilamentAddTimeStr[] PROGMEM = "Add Time";
const char starveFeederMode[] PROGMEM = "Starve Feeder";
const char extrudeRoot[] PROGMEM = "Extruding...";
const char filamentDiameter[] PROGMEM = "Diameter";
const char gramsExtrudedStr[] PROGMEM = "Grams Extruded";


//Variables for hoding menu values
double barrelTemp;
double nozzleTemp;
char loadFilamentTimeRemaining[6];
char starveFeederModeStr[3];
char soakTimeRemaining[6];
int gramsExtruded;

//Menu Action methods
void starveFeederChangeMode(){}
void filamentLoaded(){}
void increaseSoakTime(){}
void decreaseSoakTime(){}
void skipSoak(){}
void loadFilamentAddTime(){}





Configuration configuration;

const Menu::MenuItem mainItems[] PROGMEM =
{
{root, -1, 1, NULL, 0, Menu::TITLE, NULL},
{selectProfile, 0, 4, NULL, 0, Menu::TITLE, NULL},
{calibrate, 0, 32, NULL, 0, Menu::TITLE, NULL},
{auxiliary, 0, -1, NULL, 0, Menu::TITLE, NULL},
{profile0, 1, 15, &configuration.profileNames[0], 0, Menu::TITLE_STRING, &loadProfile0},
{profile1, 1, 15, &configuration.profileNames[1], 0, Menu::TITLE_STRING, &loadProfile1},
{profile2, 1, 15, &configuration.profileNames[2], 0, Menu::TITLE_STRING, &loadProfile2},
{profile3, 1, 15, &configuration.profileNames[3], 0, Menu::TITLE_STRING, &loadProfile3},
{profile4, 1, 15, &configuration.profileNames[4], 0, Menu::TITLE_STRING, &loadProfile4},
{profile5, 1, 15, &configuration.profileNames[5], 0, Menu::TITLE_STRING, &loadProfile5},
{profile6, 1, 15, &configuration.profileNames[6], 0, Menu::TITLE_STRING, &loadProfile6},
{profile7, 1, 15, &configuration.profileNames[7], 0, Menu::TITLE_STRING, &loadProfile7},
{profile8, 1, 15, &configuration.profileNames[8], 0, Menu::TITLE_STRING, &loadProfile8},
{profile9, 1, 15, &configuration.profileNames[9], 0, Menu::TITLE_STRING, &loadProfile9},
{defaultProfile, 1, 15, NULL, 0, Menu::TITLE, &loadDefaultProfile},
{extrudeStr, 4, -1, NULL, 0, Menu::TITLE, &actionExtrude},
{saveProfile, 4, -1, NULL, 0, Menu::TITLE, &saveCurrentProfile},
{profileName, 4, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
{diaSetPoint, 4, -1, &configuration.profile.diaSetPoint, 2, Menu::DOUBLE, NULL},
{tolerance, 4, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
{gramsPerMin, 4, -1, &configuration.profile.starveFeederTargetFeedRate, 2, Menu::FLOAT, NULL},
{augerRPM, 4, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, NULL},
{outfeedRPM, 4, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, NULL},
{outfeedKp, 4, -1, &configuration.profile.outfeedKp, 2, Menu::DOUBLE, NULL},
{outfeedKi, 4, -1, &configuration.profile.outfeedKi, 2, Menu::DOUBLE, NULL},
{outfeedKd, 4, -1, &configuration.profile.outfeedKd, 2, Menu::DOUBLE, NULL},
{soakTime, 4, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL},
{barrelSetTemp, 4, -1, &configuration.profile.barrelTemp, 0, Menu::DOUBLE, NULL},
{nozzleSetTemp, 4, -1, &configuration.profile.nozzleTemp, 0, Menu::DOUBLE, NULL},
{minTemp, 4, -1, &configuration.profile.minExtrudeTemp, 0, Menu::DOUBLE, NULL},
{maxTemp, 4, -1, &configuration.profile.maxTemp, 0, Menu::DOUBLE, NULL},
{maxPreheatTime, 4, -1, &configuration.profile.maxPreheatTime, 0, Menu::UNSIGNED_LONG, NULL},
{starveFeederConfig, 2, 38, NULL, 0, Menu::TITLE, NULL},
{augerConfig, 2, 39, NULL, 0, Menu::TITLE, NULL},
{barrelConfig, 2, 45, NULL, 0, Menu::TITLE, NULL},
{nozzleConfig, 2, 57, NULL, 0, Menu::TITLE, NULL},
{outfeedConfig, 2, 70, NULL, 0, Menu::TITLE, NULL},
{spoolerConfig, 2, 78, NULL, 0, Menu::TITLE, NULL},
{testStarveFeederStr, 32, -1, NULL, 0, Menu::ACTION, NULL},
{testAugerStr, 33, -1, NULL, 0, Menu::ACTION, &testAuger},
{augerPinSet, 33, -1, &configuration.physical.augerPinSet, 0, Menu::INT, NULL},
{augerStepMode, 33, -1, &configuration.physical.augerStepMode, 0, Menu::INT, NULL},
{augerDirection, 33, -1, &configuration.physical.augerDirection, 0, Menu::BOOLEAN, NULL},
{augerEnable, 33, -1, &configuration.physical.augerEnable, 0, Menu::BOOLEAN, NULL},
{augerGearRatio, 33, -1, &configuration.physical.augerGearRatio, 2, Menu::FLOAT, NULL},
{testBarrelStr, 34, -1, NULL, 0, Menu::ACTION, &testBarrel},
{timeBase, 34, -1, &configuration.physical.timeBase, 0, Menu::INT, NULL},
{barrelMaxDutyCycle, 34, -1, &configuration.physical.barrelMax, 0, Menu::DOUBLE, NULL},
{barrelMinDutyCycle, 34, -1, &configuration.physical.barrelMin, 0, Menu::DOUBLE, NULL},
{barrelKp, 34, -1, &configuration.physical.barrelKp, 2, Menu::DOUBLE, NULL},
{barrelKi, 34, -1, &configuration.physical.barrelKi, 2, Menu::DOUBLE, NULL},
{barrelKd, 34, -1, &configuration.physical.barrelKd, 2, Menu::DOUBLE, NULL},
{barrelTRNom, 34, -1, &configuration.physical.barrelTRNom, 0, Menu::UNSIGNED_LONG, NULL},
{barrelTTNom, 34, -1, &configuration.physical.barrelTTNom, 0, Menu::INT, NULL},
{barrelTNumSamples, 34, -1, &configuration.physical.barrelTNumSamples, 0, Menu::INT, NULL},
{barrelTBCoefficient, 34, -1, &configuration.physical.barrelTBCoefficient, 0, Menu::INT, NULL},
{barrelTSeriesResistor, 34, -1, &configuration.physical.barrelTSeriesResistor, 0, Menu::INT, NULL},
{testNozzleStr, 35, -1, NULL, 0, Menu::ACTION, &testNozzle},
{nozzlePin, 35, -1, &configuration.physical.nozzlePin, 0, Menu::INT, },
{nozzleMaxDutyCycle, 35, -1, &configuration.physical.nozzleMax, 0, Menu::DOUBLE, NULL},
{nozzleMinDutyCycle, 35, -1, &configuration.physical.nozzleMin, 0, Menu::DOUBLE, NULL},
{nozzleKp, 35, -1, &configuration.physical.nozzleKp, 2, Menu::DOUBLE, NULL},
{nozzleKi, 35, -1, &configuration.physical.nozzleKi, 2, Menu::DOUBLE, NULL},
{nozzleKd, 35, -1, &configuration.physical.nozzleKd, 2, Menu::DOUBLE, NULL},
{nozzleSampleTime, 35, -1, &configuration.physical.nozzleSampleTime, 0, Menu::INT, NULL},
{nozzleTRNom, 35, -1, &configuration.physical.nozzleTRNom, 0, Menu::UNSIGNED_LONG, NULL},
{nozzleTTNom, 35, -1, &configuration.physical.nozzleTTNom, 0, Menu::INT, NULL},
{nozzleTNumSamples, 35, -1, & configuration.physical.nozzleTNumSamples, 0, Menu::INT, NULL},
{nozzleTBCoefficient, 35, -1, &configuration.physical.nozzleTBCoefficient, 0, Menu::INT, NULL},
{nozzleTSeriesResistor, 35, -1,  &configuration.physical.nozzleTSeriesResistor, 0, Menu::INT, NULL},
{testOutfeedStr, 36, -1, NULL, 0, Menu::ACTION, &testOutfeed},
{outfeedPinSet, 36, -1, &configuration.physical.outfeedPinSet, 0, Menu::INT, NULL},
{outfeedStepMode, 36, -1, &configuration.physical.outfeedStepMode, 0, Menu::INT, NULL},
{outfeedDirection, 36, -1, &configuration.physical.outfeedDirection, 0, Menu::BOOLEAN, NULL},
{outfeedEnable, 36, -1, &configuration.physical.outfeedEnable, 0, Menu::BOOLEAN, NULL},
{outfeedRollerRadius, 36, -1, &configuration.physical.outfeedRollerRadius, 2, Menu::FLOAT, NULL},
{outfeedMaxRPM, 36, -1, &configuration.physical.outfeedMaxRPM, 2, Menu::DOUBLE, NULL},
{outfeedMinRPM, 36, -1, &configuration.physical.outfeedMinRPM, 2, Menu::DOUBLE, NULL},
{testSpoolerStr, 37, -1, NULL, 0, Menu::ACTION, &testSpooler},
{spoolerPinSet, 37, -1, &configuration.physical.spoolerPinSet, 0, Menu::INT, NULL},
{spoolerStepMode, 37, -1, &configuration.physical.spoolerStepMode, 0, Menu::INT, NULL},
{spoolerDirection, 37, -1, &configuration.physical.spoolerDirection, 0, Menu::BOOLEAN, NULL},
{spoolerEnable, 37, -1, &configuration.physical.spoolerEnable, 0, Menu::BOOLEAN, NULL},
{spoolerDiskRadius, 37, -1, &configuration.physical.spoolerDiskRadius, 2, Menu::FLOAT, NULL},
{spoolerCoreRadius, 37, -1, &configuration.physical.spoolerCoreRadius, 2, Menu::FLOAT, NULL},
{spoolerTraverseLength, 37, -1, &configuration.physical.spoolerTraverseLength, 2, Menu::FLOAT, NULL},
{spoolerMotorRollerRadius, 37, -1, &configuration.physical.spoolerMotorRollerRadius, 2, Menu::FLOAT, NULL}
};

const Menu::MenuItem preheatItems[] PROGMEM =
{
{preheatRoot, -1, 1, NULL, 0, Menu::TITLE, NULL},
{barrelTempStr, 0, -1, &barrelTemp, 0, Menu::DOUBLE_LOCKED,NULL},
{nozzleTempStr, 0, -1, &nozzleTemp, 0, Menu::DOUBLE_LOCKED,NULL},
{barrelSetTemp, 0, -1, &configuration.profile.barrelTemp, 0, Menu::DOUBLE, NULL},
{nozzleSetTemp, 0, -1, &configuration.profile.nozzleTemp, 0, Menu::DOUBLE, NULL},
{profileName, 0, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
{diaSetPoint, 0, -1, &configuration.profile.diaSetPoint, 2, Menu::DOUBLE, NULL},
{tolerance, 0, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
{gramsPerMin, 0, -1, &configuration.profile.starveFeederTargetFeedRate, 2, Menu::FLOAT, NULL},
{augerRPM, 0, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, NULL},
{outfeedRPM, 0, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, NULL},
{outfeedKp, 0, -1, &configuration.profile.outfeedKp, 2, Menu::DOUBLE, NULL},
{outfeedKi, 0, -1, &configuration.profile.outfeedKi, 2, Menu::DOUBLE, NULL},
{outfeedKd, 0, -1, &configuration.profile.outfeedKd, 2, Menu::DOUBLE, NULL},
{soakTime, 0, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL},
{minTemp, 0, -1, &configuration.profile.minExtrudeTemp, 0, Menu::DOUBLE, NULL},
{maxTemp, 0, -1, &configuration.profile.maxTemp, 0, Menu::DOUBLE, NULL},
{maxPreheatTime, 0, -1, &configuration.profile.maxPreheatTime, 0, Menu::UNSIGNED_LONG, NULL}
};

const Menu::MenuItem soakItems[] PROGMEM =
{
{soakRoot, -1, 1, NULL, 0, Menu::TITLE, NULL},
{soakTimeRemainingStr, 0, -1, &soakTimeRemaining, 0, Menu::STRING_LOCKED, NULL},
{barrelTempStr, 0, -1, &barrelTemp, 0, Menu::DOUBLE_LOCKED, NULL},
{nozzleTempStr, 0, -1, &nozzleTemp, 0, Menu::DOUBLE_LOCKED, NULL},
{increaseSoakTimeStr, 0, -1, NULL, 0, Menu::ACTION, &increaseSoakTime},
{decreaseSoakTimeStr, 0, -1, NULL, 0, Menu::ACTION, &decreaseSoakTime},
{skipSoakStr, 0, -1, NULL, 0, Menu::ACTION, &skipSoak},
{barrelSetTemp, 0, -1, &configuration.profile.barrelTemp, 0, Menu::DOUBLE, NULL},
{nozzleSetTemp, 0, -1, &configuration.profile.nozzleTemp, 0, Menu::DOUBLE, NULL},
{profileName, 0, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
{diaSetPoint, 0, -1, &configuration.profile.diaSetPoint, 2, Menu::DOUBLE, NULL},
{tolerance, 0, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
{gramsPerMin, 0, -1, &configuration.profile.starveFeederTargetFeedRate, 2, Menu::FLOAT, NULL},
{augerRPM, 0, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, NULL},
{outfeedRPM, 0, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, NULL},
{outfeedKp, 0, -1, &configuration.profile.outfeedKp, 2, Menu::DOUBLE, NULL},
{outfeedKi, 0, -1, &configuration.profile.outfeedKi, 2, Menu::DOUBLE, NULL},
{outfeedKd, 0, -1, &configuration.profile.outfeedKd, 2, Menu::DOUBLE, NULL},
{soakTime, 0, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL},
{minTemp, 0, -1, &configuration.profile.minExtrudeTemp, 0, Menu::DOUBLE, NULL},
{maxTemp, 0, -1, &configuration.profile.maxTemp, 0, Menu::DOUBLE, NULL},
{maxPreheatTime, 0, -1, &configuration.profile.maxPreheatTime, 0, Menu::UNSIGNED_LONG, NULL}
};

const Menu::MenuItem loadFilamentItems[] PROGMEM =
{
{loadFilamentRoot, -1, 1, NULL, 0, Menu::TITLE, NULL},
{loadFilamentRemainingTime, 0, -1, &loadFilamentTimeRemaining, 0, Menu::STRING_LOCKED, NULL},
{filamentLoadedStr, 0, -1, NULL, 0, Menu::ACTION, &filamentLoaded},
{loadFilamentAddTimeStr, 0, 0, NULL, 0, Menu::ACTION, &loadFilamentAddTime},
{starveFeederMode, 0, 1, &starveFeederModeStr, 0, Menu::STRING, &starveFeederChangeMode},
{barrelSetTemp, 0, -1, &configuration.profile.barrelTemp, 0, Menu::DOUBLE, NULL},
{nozzleSetTemp, 0, -1, &configuration.profile.nozzleTemp, 0, Menu::DOUBLE, NULL},
{profileName, 0, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
{diaSetPoint, 0, -1, &configuration.profile.diaSetPoint, 2, Menu::DOUBLE, NULL},
{tolerance, 0, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
{gramsPerMin, 0, -1, &configuration.profile.starveFeederTargetFeedRate, 2, Menu::FLOAT, NULL},
{augerRPM, 0, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, NULL},
{outfeedRPM, 0, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, NULL},
{outfeedKp, 0, -1, &configuration.profile.outfeedKp, 2, Menu::DOUBLE, NULL},
{outfeedKi, 0, -1, &configuration.profile.outfeedKi, 2, Menu::DOUBLE, NULL},
{outfeedKd, 0, -1, &configuration.profile.outfeedKd, 2, Menu::DOUBLE, NULL},
{soakTime, 0, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL},
{minTemp, 0, -1, &configuration.profile.minExtrudeTemp, 0, Menu::DOUBLE, NULL},
{maxTemp, 0, -1, &configuration.profile.maxTemp, 0, Menu::DOUBLE, NULL},
{maxPreheatTime, 0, -1, &configuration.profile.maxPreheatTime, 0, Menu::UNSIGNED_LONG, NULL},
};

const Menu::MenuItem extrudeItems[] PROGMEM =
{
{extrudeRoot, -1, 1, NULL, 0, Menu::TITLE, NULL},
{filamentDiameter, 0, -1, &loadFilamentTimeRemaining, 0, Menu::STRING_LOCKED, NULL},
{gramsPerMin, 0, -1, &configuration.profile.starveFeederTargetFeedRate, 2, Menu::FLOAT, NULL},
{gramsExtrudedStr, 0, 0, &gramsExtruded, 0, Menu::INT_LOCKED, NULL},
{barrelTempStr, 0, -1, &barrelTemp, 0, Menu::DOUBLE_LOCKED, NULL},
{nozzleTempStr, 0, -1, &nozzleTemp, 0, Menu::DOUBLE_LOCKED, NULL},
{augerRPM, 0, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, NULL},
{outfeedRPM, 0, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, NULL},
{starveFeederMode, 0, 1, &starveFeederModeStr, 0, Menu::STRING, &starveFeederChangeMode},
{barrelSetTemp, 0, -1, &configuration.profile.barrelTemp, 0, Menu::DOUBLE, NULL},
{nozzleSetTemp, 0, -1, &configuration.profile.nozzleTemp, 0, Menu::DOUBLE, NULL},
{profileName, 0, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
{diaSetPoint, 0, -1, &configuration.profile.diaSetPoint, 2, Menu::DOUBLE, NULL},
{tolerance, 0, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
{outfeedKp, 0, -1, &configuration.profile.outfeedKp, 2, Menu::DOUBLE, NULL},
{outfeedKi, 0, -1, &configuration.profile.outfeedKi, 2, Menu::DOUBLE, NULL},
{outfeedKd, 0, -1, &configuration.profile.outfeedKd, 2, Menu::DOUBLE, NULL},
{soakTime, 0, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL},
{minTemp, 0, -1, &configuration.profile.minExtrudeTemp, 0, Menu::DOUBLE, NULL},
{maxTemp, 0, -1, &configuration.profile.maxTemp, 0, Menu::DOUBLE, NULL},
{maxPreheatTime, 0, -1, &configuration.profile.maxPreheatTime, 0, Menu::UNSIGNED_LONG, NULL},
};




Application app;

//Setup Finite State Machine
enum ExtruderStates {
  //  SELECT_PROFILE,
  PREHEAT,
  SOAK,
  BEGIN_EXTRUDE,
  LOAD_FILAMENT,
  EXTRUDE,
  TEST,
  CALIBRATE_CALIPERS
} currentState;

//void selectProfile();
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
  //  selectProfile,
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

Menu mainMenu(mainItems, sizeof(mainItems) / sizeof(mainItems[0]), &lcd, &kpd);
Menu preheatMenu(preheatItems, sizeof(preheatItems) / sizeof(preheatItems[0]), &lcd, &kpd);
Menu soakMenu(soakItems, sizeof(soakItems) / sizeof(soakItems[0]), &lcd, &kpd);
Menu loadFilamentMenu(loadFilamentItems, sizeof(loadFilamentItems) / sizeof(loadFilamentItems[0]), &lcd, &kpd);
Menu extrudeMenu(extrudeItems, sizeof(extrudeItems) / sizeof(extrudeItems[0]), &lcd, &kpd);
Menu* activeMenu;

#include "Extrude.h"
#include "FSM.h"
#include "Preheat.h"
#include "Safety.h"
#include "TestReporting.h"
#include "strings.h"

void setup()
{
  Serial.begin(115200);
  while (!Serial); // while the serial stream is not open, do nothing:
  Wire.begin();
  lcd.begin(20, 4); //Start up LCD
  lcd.clear();
  activeMenu = &mainMenu;
  buzzer.setMsg(Buzzer::POWER_ON);
  //  stateMachine.setState(StateMachine::SELECT_PROFILE);

  // currentState = TEST;
  //  currentState = EXTRUDE_AUTOMATIC;
  activeMenu = &mainMenu;

  activeMenu->reset();
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
      activeMenu->up();
      break;
    case '2':
      activeMenu->down();
      break;

    case '3':
      activeMenu->select();
      break;
    case '4':
      activeMenu->back();
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
  mainMenu.display();
}

void loadConfig() {
  lcd.clear();
  lcd.print(F("Loading..."));
  delay(500);
  configuration.loadConfig();
  lcd.clear();
  lcd.print(F("Configuration Loaded"));
  delay(2000);
  mainMenu.display();
}

void saveConfig() {
  lcd.clear();
  lcd.print(F("Saving..."));
  delay(500);
  configuration.saveConfig();
  lcd.clear();
  lcd.print(F("Configuration Saved"));
  delay(2000);
  mainMenu.display();
}


void loadProfile0() {
  Serial.println("Loading Profile 0");
  configuration.loadProfile(0);
}
void loadProfile1() {
  configuration.loadProfile(1);
}
void loadProfile2() {
  configuration.loadProfile(2);
}
void loadProfile3() {
  configuration.loadProfile(3);
}
void loadProfile4() {
  configuration.loadProfile(4);
}
void loadProfile5() {
  configuration.loadProfile(5);
}
void loadProfile6() {
  configuration.loadProfile(6);
}
void loadProfile7() {
  configuration.loadProfile(7);
}
void loadProfile8() {
  configuration.loadProfile(8);
}
void loadProfile9() {
  configuration.loadProfile(9);
}

void loadDefaultProfile() {
  configuration.loadDefaultProfile();
}
void extrude1() {

}


void saveCurrentProfile() {
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
        //        selectProfileMenu[i].setText(configuration.profileNames[i]);//The names have been reset. This will reflect the change
        configuration.saveProfile();
      }
      waitForResponse = false;
    }

    if (key == 'n') {
      waitForResponse = false;
    }
  }
  mainMenu.display();
}

void actionExtrude() {
  Serial.println("Extruding...");
  activeMenu = &preheatMenu;
  activeMenu->reset();
}


