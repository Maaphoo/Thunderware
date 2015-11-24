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
    //    enum PinSet {
    //      SET_3_14_8 = 0,// wired to auger motor, pins: step->3, dir->14, enable->8
    //      SET_11_15_12,//wired to outfeed motor, pins: step->11, dir->15, enable->12
    //      SET_10_16_9,//wired to spool motor, pins: step->10, dir->16, enable->9
    //      //STARVE_FEEDER,
    //    };

    struct Profile {
      //General
      int profileNumber;
      char name[20];
      double diaSetPoint;//mm
	  float density; //g/cm3
      float tolerance;//mm

      //Starve Feeder
      float gramsPerMin;


      //Auger
      float augerRPM;

      //Outfeed
      double outfeedRPM;
      double outfeedKi;
      double outfeedKp;
      double outfeedKd;
      double outfeedMaxRPM;
      double outfeedMinRPM;
      int outfeedComputeInterval;

      //Barrel
      double soakTime;
      double barrelTemp;

      //nozzle
      double nozzleTemp;

      //Safety parameters
      double minExtrudeTemp;
      double maxTemp; //The maximum temp allowed for barrel or nozzle
      unsigned long maxPreheatTime;
    } profile, tempProfile;


    /*The physicalConfig struct holds information describing *
     *the physical setup of the extruder.                    */

    struct PhysicalConfig {
      //variables that help with storage
      boolean configStored;
      boolean loadAutomatically;

      //StarveFeeder
      int starveFeederSlaveAddress;
      float starveFeederLumpMass;
      int starveFeederHomePosition;
      int starveFeederDumpPosition;
      int starveFeederStepDelay;
      int starveFeederHomingStepDelay;
      int starveFeederOverRotation;
      boolean starveFeederDirection;
      int starveFeederVibDutyCycle;
      int starveFeederStartupDutyCycle;
      int starveFeederMaxDutyCycle;
      int starveFeederMinDutyCycle;
      int starveFeederMinFillTime;
      int starveFeederMaxFillTime;
      int starveFeederStartupTime;
      int starveFeederDebounceTime;


      //Auger
      int augerPinSet;
      int augerStepMode;
      boolean augerDirection;
      boolean augerEnable;
      float augerGearRatio;

      //Outfeed
      int outfeedPinSet;
      int outfeedStepMode;
      boolean outfeedDirection;
      boolean outfeedEnable;
      float outfeedRollerRadius;
      double outfeedMaxRPM;
      double outfeedMinRPM;


      //Spooler
      int spoolerPinSet;
      int spoolerStepMode;
      boolean spoolerDirection;
      boolean spoolerEnable;
      float spoolerDiskRadius;
      float spoolerCoreRadius;
      float spoolerTraverseLength;
      float spoolerMotorRollerRadius;

//       float rsc1; // Inner radius of spool core
//       float rsc2; // Outer radius of spool core
//       float rsm; // radius of spool stepper motor roller
//       float ts; // Traverse Length in mm


      //Barrel
      int timeBase;//Time base in milliseconds
      double barrelMax;//The max dutyCycle for the barrel
      double barrelMin;//The min dutyCycle for the barrel
      double barrelKp, barrelKi, barrelKd;
      long barrelTRNom;
      int barrelTTNom;
      int barrelTNumSamples;
      int barrelTBCoefficient;
      int barrelTSeriesResistor;

      //nozzle
      int nozzlePin;
      double nozzleMax;//The max dutyCycle for the nozzle
      double nozzleMin;//The min dutyCycle for the nozzle
      double nozzleKp, nozzleKi, nozzleKd;
      int nozzleSampleTime;
      long nozzleTRNom;
      int nozzleTTNom;
      int nozzleTNumSamples;
      int nozzleTBCoefficient;
      int nozzleTSeriesResistor;

      //Diameter Sensor
      float slope;
      float yIntercept;

      //Parameters for the different states
      double maxTemp;
      unsigned long loadFilamentTime; //The number of minutes allowed for loading the filament.

    } physical;

    char profileNames[10][20];
    char name0[20];
    void loadProfileName(char* namePtr, int profile);//Used for menus.
    void loadProfileNames();
    Configuration();//constructor
    void saveConfig();
    void deleteConfig();
    void loadConfig();//returns true if successfull
    void loadDefaultConfig();
    void saveProfile();//Saves profile in designated position.
    boolean loadProfile(int profileNum);
    void loadDefaultProfile();
    void deleteProfile(int profileNum);

    //returns a pointer to the name of the indicated profile
    char *getName(int profileNum);


  private:
    int calculateOffset(int profileNum);//determines the address of a profile
    int numProfiles;//The number of allowed profiles
};

#endif


