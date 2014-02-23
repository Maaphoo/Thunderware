

#define timeBase  2000

//Auger
#define augerStepMode 32.0
#define gearRatio 3.0
#define augerDir 0

//Outfeed
#define outfeedStepMode 16.0
#define outfeedDir 1
#define outfeedRollerDia 11.9538 //Effective Diameter of the ourfeed roller. Determine emperically (mm)

//Spool Stepper
#define spoolStepMode 16.0
#define spoolDir 1

//calipers
#define CAL_CLK 2
#define CAL_DATA 3

//Spool Parameters
#define ro 5.9769 //Efective radius of outfeed roller
#define rsc1  72.85//Inner radius of spool core
#define rsc2 75.96//Outer radius of spool core
#define rsm 9.19//radius of spool stepper motor roller
#define ts 56.0 // Traverse Length in mm

//Constants
#define c1 (ro*rsc1*spoolStepMode/(rsm*outfeedStepMode))
#define c2 (1.0/(PI*ts))
#define c3 (rsc2*rsc2)
#define c4 (PI*ro/((double)outfeedStepMode*100.0))

//Safety
#define maxExtruderTemp 250

//StarveFeeder

#define gearRatio 3
#define stepMode 16.0

#define enablePin 48
#define stepPin 46 //PINL 3
#define directionPin 44


