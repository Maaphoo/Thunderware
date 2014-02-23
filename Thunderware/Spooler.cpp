/*
  Spooler.cpp - Library for controlling the spooling mechanism. A stepper
      motor turns the spool. Its speed is determined by the geometry
      of the spool, the distance from the center of the spool to the surface
      of the filament and the rate at which filament is being extruded. 
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Spooler.h"
#include "config.h"

Spooler::Spooler(StepperMotor *outfeed, int motor, int timer) : _motor(motor, timer)
{
  _outfeed = outfeed;
}



void Spooler::setRPM()
{
  calcLengthExtruded();// First update the the mm of filament extruded.
  _filamentSurfaceRaduis = pow(c2*diaSetPoint*diaSetPoint*mmExtruded+c3,0.5);
  spoolRPM = ro*rsc1/(rss*rsm)*outfeedRPM;
}

void Spooler::calcLengthExtruded()
{
  
}


