/*
  Configuration.cpp - Library for saving, loading,
     and deleting the various configurations both
     for the active profile and the physical setup
     of the extruder.

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "EEPROMAnything.h"
#include "Configuration.h"

void Configuration::loadDefaultProfile()
{
  //General
  profile.profileNumber = -1;
  strcpy(profile.name, "Default 1.75 ABS");
  profile.diaSetPoint = 1.75;
  profile.tolerance = 0.05;

  //Starve Feeder
  profile.gramsPerMin = 10.0;

  //Auger
  profile.augerRPM = 40.0;

  //Outfeed
  profile.outfeedRPM = 60;
  profile.outfeedKp = 0.0;
  profile.outfeedKi = 3.0;
  profile.outfeedKd = 0.0;
  profile.outfeedMaxRPM = 200.0;
  profile.outfeedMinRPM = 0.0;
  profile.outfeedComputeInterval = 2000;


  //Barrel
  profile.soakTime = 8.0;// minutes for barrel to remain at setpoint before extruding
  profile.barrelTemp = 200.0;

  //nozzle
  profile.nozzleTemp = 200.0;

  //Safety parameters
  profile.minExtrudeTemp = 180; //The minimum temp allowed for extrusion
  profile.maxTemp = 240; //The max temp allowed for the barrel or the nozzle.
  profile.maxPreheatTime = 10; // The max number of minutes allowed for the preheat state.
}


void Configuration::loadDefaultConfig()
{

  //load the physical with the default parameters.
  //EEPROM storage
  physical.loadAutomatically = false;

  //StarveFeeder
  physical.starveFeederSlaveAddress = 2;
  physical.starveFeederLumpMass = 7.6;
  physical.starveFeederMinFillTime = 1000;
  physical.starveFeederMaxFillTime = 10000;
  physical.starveFeederStartupTime = 1200;
  physical.starveFeederDebounceTime = 80;
  physical.starveFeederHomePosition = 100;
  physical.starveFeederDumpPosition = 1600;
  physical.starveFeederStepDelay = 75;
  physical.starveFeederHomingStepDelay = 2000;
  physical.starveFeederOverRotation = 90;
  physical.starveFeederDirection = 0;
  physical.starveFeederVibDutyCycle = 85;
  physical.starveFeederMaxDutyCycle = 160;
  physical.starveFeederStartupDutyCycle = 120;

  //auger
  physical.augerPinSet = 0;
  physical.augerStepMode = 16;
  physical.augerDirection = 1;
  physical.augerEnable = 1;
  physical.augerGearRatio = 3.0;

  //Outfeed
  physical.outfeedPinSet = 1;
  physical.outfeedStepMode = 16;
  physical.outfeedDirection = 0;
  physical.outfeedEnable = 0;
  physical.outfeedRollerRadius = 5.465; //
  physical.outfeedMaxRPM = 200.0;
  physical.outfeedMinRPM = 0.0;

  //Spooler
  physical.spoolerPinSet = 2;
  physical.spoolerStepMode = 16;
  physical.spoolerDirection = 0;
  physical.spoolerEnable = 0;
  physical.spoolerDiskRadius = 276.6 / 2.0; //Radius of wooden disk
  physical.spoolerCoreRadius = 94.0 / 2.0; //Radius of spool core
  physical.spoolerTraverseLength = 62.5 / 2.0;
  physical.spoolerMotorRollerRadius = 15.0 / 2.0;

  physical.rsc1 = 73.15; // Inner radius of spool core
  physical.rsc2 = 75.93; // Outer radius of spool core
  physical.rsm = 14.25; // radius of spool stepper motor roller
  physical.ts = 56.8; // Traverse Length in mm


  //Barrel
  physical.timeBase = 2000;//Time base in milliseconds
  physical.barrelMax = 100;//The max dutyCycle for the barrel
  physical.barrelMin = 0;//The min dutyCycle for the barrel
  physical.barrelKp = 3.4;
  physical.barrelKi = 0.15;
  physical.barrelKd = 0.0;
  physical.barrelTRNom = 100000;
  physical.barrelTTNom = 25;
  physical.barrelTNumSamples = 20;
  physical.barrelTBCoefficient = 4092;
  physical.barrelTSeriesResistor = 9890;

  //nozzle
  physical.nozzlePin = 5;
  physical.nozzleMax = 255;//The max dutyCycle for the nozzle
  physical.nozzleMin = 0;//The min dutyCycle for the nozzle
  physical.nozzleKp = 3.5;
  physical.nozzleKi = 0.15;
  physical.nozzleKd = 0.0;
  physical.nozzleSampleTime = 2000;
  physical.nozzleTRNom = 100000;
  physical.nozzleTTNom = 25;
  physical.nozzleTNumSamples = 20;
  physical.nozzleTBCoefficient = 4092;
  physical.nozzleTSeriesResistor = 9910;

  //Diameter Sensor
  physical.slope = 0.0005656 ;
  physical.yIntercept = 1.5519;

  //Safety Parameters for the different states
  physical.maxTemp = 250;//the max temp the barrel or nozzle are allowed to achieve.
  physical.loadFilamentTime = 2; //The number of minutes allowed for loading the filament.

}

Configuration::Configuration()
{
  loadProfileNames();
  loadConfig();
}


void Configuration::saveConfig()
{
	Serial.println(F("Saving Config."));
  physical.configStored = true;//Make sure that the config is marked as stored
  EEPROM_writeAnything(0, physical); //Write to EEPROM
}


void Configuration::deleteConfig()
{
  physical.configStored = false;//Mark config as not stored
  EEPROM_writeAnything(0, physical.configStored); //Just update the configStored variable the rest is irrelevant
}


void Configuration::loadConfig()
{
    EEPROM_readAnything(0, physical);
}


void Configuration::saveProfile()
{
  EEPROM_writeAnything(calculateOffset(profile.profileNumber), profile);
}

void Configuration::deleteProfile(int profileNum)
{
}

boolean Configuration::loadProfile(int profileNum)
{
  EEPROM_readAnything(calculateOffset(profileNum), profile);
}

int Configuration::calculateOffset(int profileNum)
{
  return sizeof(PhysicalConfig) + profileNum * sizeof(Profile); //Will padding in the struct cause problems with this?
}

void Configuration::loadProfileName(char* namePtr, int profile) {
  EEPROM_readAnything(calculateOffset(profile), tempProfile);
  strcpy(namePtr, tempProfile.name);
}

void Configuration::loadProfileNames() {
  for (int i = 0; i < 10; i++) {
    loadProfileName(profileNames[i], i);
  }
}


