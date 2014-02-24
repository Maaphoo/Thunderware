#ifndef config_h
#define config_h

static const int timeBase = 2000;

//Auger
static const float augerStepMode = 32.0;
static const float gearRatio = 3.0;
static const int augerDir = 0;

// Outfeed
static const float outfeedStepMode = 16.0;
static const int outfeedDir = 1;
static const float outfeedRollerDia = 11.9538; // Effective Diameter of the ourfeed roller. Determine emperically (mm)

// Spool Stepper
static const float spoolStepMode = 16.0;
static const int spoolDir = 1;

// calipers
static const int CAL_CLK = 2;
static const int CAL_DATA = 3;

//Spool Parameters
static const float ro = 5.9769; // Efective radius of outfeed roller
static const float rsc1 = 72.85; // Inner radius of spool core
static const float rsc2 = 75.96; // Outer radius of spool core
static const float rsm = 9.19; // radius of spool stepper motor roller
static const float ts = 56.0; // Traverse Length in mm

//Constants
static const float c1 = (ro*rsc1*spoolStepMode/(rsm*outfeedStepMode));
static const float c2 = (1.0/(PI*ts));
static const float c3 = (rsc2*rsc2);
static const float c4 = (PI*ro/((double)outfeedStepMode*100.0));

//Safety
static const int maxExtruderTemp = 250;

//StarveFeeder

static const float stepMode = 16.0;

static const int enablePin = 48;
static const int stepPin = 46; //PINL 3
static const int directionPin = 44;


#endif // config_h
