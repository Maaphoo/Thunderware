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
    profile.isStored = 0;
    strcpy(profile.name, "(Default) 1.75 ABS");
    profile.diaSetPoint = 1.75;
    profile.tolerance = 0.05;

    //Starve Feeder
    profile.feedRate = 7.5;

    //Auger
    profile.augerRPM = 40.0;

    //Outfeed
    profile.outfeedKi = 3.0;
    profile.outfeedKp = 0.0;
    profile.outfeedKd = 0.0;
    profile.outfeedMaxRPM = 200.0;
    profile.outfeedMinRPM = 0.0;
    profile.outfeedSampleTime = 2000;
    

    //buzzer
    profile.buzzerActive = true;

    //Barrel
    profile.barrelTemp = 220.0;

    //nozzle
    profile.nozzleTemp = 220.0;
}


void Configuration::loadDefaultConfig()
{
      
  //load the physical with the default parameters.
  //auger
  physical.augerStepMode = 32;
  physical.augerDirection = 0;
  physical.augerGearRatio = 3.0;
  
  //Outfeed
  physical.outfeedStepMode = 16;
  physical.outfeedDirection = 1;
  physical.outfeedRollerRadius = 5.9769; // Efective radius of outfeed roller32;
  physical.outfeedMaxRPM = 200.0;
  physical.outfeedMinRPM = 0.0;
  
  //Spooler
  physical.spoolerStepMode = 16;
  physical.spoolerDirection = 1;
  physical.rsc1 = 72.85; // Inner radius of spool core
  physical.rsc2 = 75.96; // Outer radius of spool core
  physical.rsm = 9.19; // radius of spool stepper motor roller
  physical.ts = 56.0; // Traverse Length in mm

  //StarveFeeder
  physical.starveFeederStepMode = 16;
  
  //Barrel 
  physical.timeBase = 2000;//Time base in milliseconds
  physical.barrelMaxDS = 80;//The max dutyCycle for the barrel
  physical.barrelMinDs = 0;//The min dutyCycle for the barrel
  physical.barrelKp = 3.4; 
  physical.barrelKi = 0.15;
  physical.barrelkd = 0.0;
  physical.barrelTRNom = 100000;
  physical.barrelTTNom = 25;
  physical.barrelTNumSamples = 20;
  physical.barrelTBCoefficient = 4092;
  physical.barrelTSeriesResistor = 9890;

  //nozzle
  physical.nozzleMaxDS = 255;//The max dutyCycle for the nozzle
  physical.nozzleMinDs = 0;//The min dutyCycle for the nozzle
  physical.nozzleKp = 3.5;
  physical.nozzleKi = 0.15;
  physical.nozzlekd = 0.0;
  physical.nozzleSampleTime = 1000;
  physical.nozzleTRNom = 100000;
  physical.nozzleTTNom = 25;
  physical.nozzleTNumSamples = 20;
  physical.nozzleTBCoefficient = 4092;
  physical.nozzleTSeriesResistor = 9910;
  
  //Diameter Sensor
  physical.slope = 0.00045405 ;
  physical.yIntercept = 1.5635;
}

Configuration::Configuration()
{
  EEPROM_readAnything(0,physical.configStored);
  if (physical.configStored){
    //Read the stored profile from the EEPROM
    EEPROM_readAnything(0,physical);
  } else {
    loadDefaultConfig();
  }
}

void Configuration::saveConfig()
{
  physical.configStored = true;//Make sure that the config is marked as stored
  EEPROM_writeAnything(0,physical);//Write to EEPROM
}
void Configuration::deleteConfig()
{
  physical.configStored = false;//Mark config as not stored
  EEPROM_writeAnything(0,physical.configStored);//Just update the configStored variable the rest is irrelevant
}

boolean Configuration::loadConfig()
{
  EEPROM_readAnything(0,physical.configStored);
  if (physical.configStored){
    //Read the stored profile from the EEPROM
    EEPROM_readAnything(0,physical);
    return true;
  } else {
    return false;
  }
}

//ProfileNum is zero indexed
boolean Configuration::saveProfile()
{
  for (int i=0;i<numProfiles;i++){
    EEPROM_readAnything(calculateOffset(i),tempProfile);
    if (!tempProfile.isStored){
      EEPROM_writeAnything(calculateOffset(i),profile);
      return true;
    }
  }
  return false;
}

void Configuration::saveProfile(int profileNum)
{
  EEPROM_writeAnything(calculateOffset(profileNum),profile);
}

void Configuration::deleteProfile(int profileNum)
{
  tempProfile.isStored = false;
  EEPROM_writeAnything(calculateOffset(profileNum),tempProfile);//Sets the selected profile to not stored.
}

boolean Configuration::loadProfile(int profileNum)
{
    EEPROM_readAnything(calculateOffset(profileNum),tempProfile);
    if (tempProfile.isStored){
      EEPROM_readAnything(calculateOffset(profileNum),profile);    
      return true;
  }else{
    return false;
  }
}

char* Configuration::getName(int profileNum)
{
    EEPROM_readAnything(calculateOffset(profileNum), tempProfile);
    return tempProfile.name;
}

int Configuration::calculateOffset(int profileNum)
{
  return sizeof(PhysicalConfig)+profileNum*sizeof(Profile)-1;//Will padding in the struct cause problems with this?
}
