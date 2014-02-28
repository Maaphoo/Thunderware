/*
  Outfeed.cpp - Library for controlling the outfeed process.
      It consists of a PID controller, DiameterSensor, and a 
      StepperMotor.
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Outfeed.h"

Outfeed::Outfeed(StepperMotor::PinSet pinSet, int timer) : _motor(pinSet, timer)
{

 }


//revise so that the outfeed reports mm/s
float Outfeed::getRPM(){ return _motor.getRPM();}

void Outfeed::setRPM(float rpm)
{
  update();
  _motor.setRPM(rpm);
} 

void Outfeed::disable(){  _motor.disable();}
void Outfeed::enable(){  _motor.enable();}
float Outfeed::getMmExtruded()
{ 
  update();
  return _mmExtruded;
}

void Outfeed::reset()
{ 
  _mmExtruded = 0.0;
  _previousTime = millis();
}

void Outfeed::update()
{
  _now = millis();
  _mmExtruded += ro*_motor.getRPM()*2.0*PI/60.0*(_now-_previousTime)/1000.0;
  _previousTime = _now;
}
