/*
  Configuration.h - Library for saving, loading,
 and deleting the various configurations both
 for the active profile and the physical setup
 of the extruder.
 
 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */
#ifndef Configuration_h
#define Configuration_h

#include "Arduino.h"

class Configuration
{
public:
  struct Profile {
    //General
    boolean isStored;
    char name[20];
    float diaSetPoint;
    float tolerance;

    //Starve Feeder
    float feedRate;

    //Auger
    float augerRPM;

    //Outfeed
    double outfeedKi;
    double outfeedKp;
    double outfeedKd;
    double outfeedMaxRPM;
    double outfeedMinRPM;
    double outfeedSampleTime;
    

    //buzzer
    boolean buzzerActive;

    //Barrel
    float barrelTemp;

    //nozzle
    float nozzleTemp;
  } currentProfile;

  struct PhysicalConfig{
    //variables that help with storage
    boolean configStored;
    
    //Auger
    int augerStepMode;
    boolean augerDirection;
    float augerGearRatio;

    //Outfeed
    int outfeedStepMode;
    boolean outfeedDirection;
    float outfeedRollerRadius;
    double outfeedMaxRPM;
    double outfeedMinRPM;


    //Spooler
    int spoolerStepMode;
    boolean spoolerDirection;
    float rsc1; // Inner radius of spool core
    float rsc2; // Outer radius of spool core
    float rsm; // radius of spool stepper motor roller
    float ts; // Traverse Length in mm 

    //StarveFeeder
    int starveFeederStepMode;

    //Barrel
    int timeBase;//Time base in milliseconds
    double barrelMaxDS;//The max dutyCycle for the barrel
    double barrelMinDs;//The min dutyCycle for the barrel
    double barrelKp, barrelKi, barrelkd;
    int barrelTRNom;
    int barrelTTNom;
    int barrelTNumSamples;
    int barrelTBCoefficient;
    int barrelTSeriesResistor;

    //nozzle
    double nozzleMaxDS;//The max dutyCycle for the nozzle
    double nozzleMinDs;//The min dutyCycle for the nozzle
    double nozzleKp, nozzleKi, nozzlekd;
    int nozzleSampleTime;
    int nozzleTRNom;
    int nozzleTTNom;
    int nozzleTNumSamples;
    int nozzleTBCoefficient;
    int nozzleTSeriesResistor;
    
    //Diameter Sensor
    float slope;
    float yIntercept;
  }currentConfig;


  Configuration();//constructor
  //The default configs are used unless there is a config file stored in the EEPROM
  void saveConfig();
  void deleteConfig();
  boolean loadConfig();//returns true if successfull
  
  //Profile is left empty unless one is selected or default is used. 
  boolean saveProfile();//Saves profile in first available position. Returns true on success. 
  boolean saveProfile(int profileNum);//Saves profile in designated position. Returns true on success
  boolean loadProfile(int profileNum);
  void deleteProfile(int profileNum);
  
  //returns a pointer to the title of the indicated profile
  char *getTitle(int profileNum);
  

private:
  int calculateOffset(int profileNum);//determines the address of a profile
  int numProfiles;//The number of allowed profiles
};

#endif


