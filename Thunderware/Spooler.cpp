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
  _diaSetPoint = _configuration->profile.diaSetPoint;
  _configuration = configuration;
 c1 = (_configuration->physical.outfeedRollerRadius
       *_configuration->physical.spoolerDiskRadius
       *_configuration->physical.spoolerStepMode
       /(_configuration->physical.spoolerMotorRollerRaduis
       *_configuration->physical.outfeedStepMode));
 c2 = (_configuration->profile.diaSetPoint/(PI*_configuration->physical.spoolerTraverseLength));
 c3 = (_configuration->physical.spoolerCoreRadius*_configuration->physical.spoolerCoreRadius);
 c4 = (PI*_configuration->physical.outfeedRollerRadius/((double)configuration->physical.outfeedStepMode*100.0));
}


void Spooler::setRPM()
{

  _filamentSurfaceRaduis = pow(c2*c2*_outfeed->getMmExtruded()+c3,0.5);
  _motorRPM = _configuration->physical.outfeedRollerRadius
             *_configuration->physical.spoolerDiskRadius
             /(_filamentSurfaceRaduis*_configuration->physical.spoolerMotorRollerRaduis)
             *_outfeed->getRPM();
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






