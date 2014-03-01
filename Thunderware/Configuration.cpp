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

Configuration::Configuration()
{
  EEPROM_readAnything(0,currentConfig.configStored);
  if (currentConfig.configStored){
    //Read the stored profile from the EEPROM
    EEPROM_readAnything(0,currentConfig);
  } else {
    
  //load the currentConfig with the default parameters.
  //auger
  currentConfig.augerStepMode = 32;
  currentConfig.augerDirection = 0;
  currentConfig.augerGearRatio = 3.0;
  
  //Outfeed
  currentConfig.outfeedStepMode = 16;
  currentConfig.outfeedDirection = 1;
  currentConfig.outfeedRollerRadius = 5.9769; // Efective radius of outfeed roller32;
  currentConfig.outfeedMaxRPM = 200.0;
  currentConfig.outfeedMinRPM = 0.0;
  
  //Spooler
  currentConfig.spoolerStepMode = 16;
  currentConfig.spoolerDirection = 1;
  currentConfig.rsc1 = 72.85; // Inner radius of spool core
  currentConfig.rsc2 = 75.96; // Outer radius of spool core
  currentConfig.rsm = 9.19; // radius of spool stepper motor roller
  currentConfig.ts = 56.0; // Traverse Length in mm

  //StarveFeeder
  currentConfig.starveFeederStepMode = 16;
  
  //Barrel 
  currentConfig.timeBase = 2000;//Time base in milliseconds
  currentConfig.barrelMaxDS = 80;//The max dutyCycle for the barrel
  currentConfig.barrelMinDs = 0;//The min dutyCycle for the barrel
  currentConfig.barrelKp = 3.4; 
  currentConfig.barrelKi = 0.15;
  currentConfig.barrelkd = 0.0;
  currentConfig.barrelTRNom = 100000;
  currentConfig.barrelTTNom = 25;
  currentConfig.barrelTNumSamples = 20;
  currentConfig.barrelTBCoefficient = 4092;
  currentConfig.barrelTSeriesResistor = 9890;

  //nozzle
  currentConfig.nozzleMaxDS = 255;//The max dutyCycle for the nozzle
  currentConfig.nozzleMinDs = 0;//The min dutyCycle for the nozzle
  currentConfig.nozzleKp = 3.5;
  currentConfig.nozzleKi = 0.15;
  currentConfig.nozzlekd = 0.0;
  currentConfig.nozzleSampleTime = 1000;
  currentConfig.nozzleTRNom = 100000;
  currentConfig.nozzleTTNom = 25;
  currentConfig.nozzleTNumSamples = 20;
  currentConfig.nozzleTBCoefficient = 4092;
  currentConfig.nozzleTSeriesResistor = 9910;
  
  //Diameter Sensor
  currentConfig.slope = 0.00045405 ;
  currentConfig.yIntercept = 1.5635;
  }

  

  
  
}

void Configuration::saveConfig()
{
  currentConfig.configStored = true;//Make sure that the config is marked as stored
  EEPROM_writeAnything(0,currentConfig);//Write to EEPROM
}
void Configuration::deleteConfig()
{
  currentConfig.configStored = false;//Mark config as not stored
  EEPROM_writeAnything(0,currentConfig.configStored);//Just update the configStored variable the rest is irrelevant
}

boolean Configuration::loadConfig()
{
  EEPROM_readAnything(0,currentConfig.configStored);
  if (currentConfig.configStored){
    //Read the stored profile from the EEPROM
    EEPROM_readAnything(0,currentConfig);
    return true;
  } else {
    return false;
  }
}

//ProfileNum is zero indexed
boolean Configuration::saveProfile()
{
  for (int i=0;i<numProfiles;i++){
    boolean isStored = EEPROM_readAnything(calculateOffset(i),isStored);
    if (!isStored){
      EEPROM_writeAnything(calculateOffset(i),currentProfile);
      return true;
    }
  }
  return false;
}

void Configuration::deleteProfile(int profileNum)
{
  EEPROM_writeAnything(calculateOffset(profileNum),false);//Sets the selected profile to not stored.
}

boolean Configuration::loadProfile(int profileNum)
{
  boolean isStored = EEPROM_readAnything(calculateOffset(profileNum),isStored);
  if (isStored){
    EEPROM_readAnything(calculateOffset(profileNum),currentProfile);
    return true;
  }else{
    return false;
  }
}

char* Configuration::getTitle(int profileNum)
{
  boolean isStored = EEPROM_readAnything(calculateOffset(profileNum),isStored);
  if (isStored){
    char name[20];
    EEPROM_readAnything(calculateOffset(profileNum)+sizeof(boolean),name);
    return name;
  }
  return '\0';//Return the null character if the profile doesn't exist
}

int Configuration::calculateOffset(int profileNum)
{
  return sizeof(PhysicalConfig)+profileNum*sizeof(Profile);
}
