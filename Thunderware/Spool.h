#include <math.h>


unsigned long previousTime;//previous time length of filament was calculated


float rss;//Radius of the spooled filament

void calcFilamentExtruded();

//Spooling Functions

//Find Spool RPM
void calcSpoolRPM(){
  calcFilamentExtruded();// First update the the mm of filament extruded.

  rss = pow(c2*diaSetPoint*diaSetPoint*mmExtruded+c3,0.5);
//  spoolSPS = sf*c1*1000000/(oStepInterval*rss);
//  sStepInterval = 1000000/spoolSPS;//not needed
  spoolRPM = ro*rsc1/(rss*rsm)*outfeedRPM;
//  spoolRPM = spoolSPS*60.0/(200.0*spoolStepMode);
}

long nowFE;
long previousTimeFE;

void calcFilamentExtruded(){
  nowFE = millis();
  if (resetFE){
    previousTimeFE=nowFE;
    mmExtruded = 0;
    resetFE = false;
  }
  mmExtruded += c4*(1000000.0/(double)oStepInterval)*(double)(nowFE-previousTimeFE)/1000.0;
  previousTimeFE = nowFE;
}


