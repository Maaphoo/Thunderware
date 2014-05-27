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

Spooler::Spooler(Configuration* configuration, Outfeed* outfeed) :   _motor(configuration, configuration->physical.spoolerPinSet)
{
  _outfeed = outfeed;
  _diaSetPoint = 1.75;
}



void Spooler::setRPM()
{

  _filamentSurfaceRaduis = pow(c2*_diaSetPoint*_diaSetPoint*_outfeed->getMmExtruded()+c3,0.5);
  _motorRPM = ro*rsc1/(_filamentSurfaceRaduis*rsm)*_outfeed->getRPM();
  _motor.setRPM(_motorRPM);
}

float Spooler::getRPM(){return _motor.getRPM();}

void Spooler::setRPM(float rpm)
{
  _motor.setRPM(rpm);
}

//Instead of using the following, should I have a public pointer to _motor and then use someting like spooler.motor->enable()?
void Spooler::enable(){ _motor.enable();}
void Spooler::disable(){ _motor.disable();}






