/*
  Outfeed.cpp - Library for controlling the outfeed process.
      It consists of a PID controller, DiameterSensor, and a 
      StepperMotor.
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Outfeed.h"

Outfeed::Outfeed(Configuration* configuration) 
        :  _motor(configuration, configuration->physical.outfeedPinSet),
           _caliper(configuration),
           _pid(&_caliper.dia, 
                &_rpm,
                &configuration->profile.diaSetPoint,
                configuration->profile.outfeedKp,
                configuration->profile.outfeedKi,
                configuration->profile.outfeedKd,
                REVERSE)
    
{
  _configuration = configuration;
  _computeInterval = &configuration->profile.outfeedComputeInterval;
 }


//revise so that the outfeed reports mm/s
float Outfeed::getRPM(){ return _motor.getRPM();}

double Outfeed::getDia(){ return _caliper.dia;}

double Outfeed::getRawADC(){return _caliper.getRawADC();}

void Outfeed::linReg(float *slope, float *yIntercept, float *xVals, float *yVals, int *n)
{
 _caliper.linReg(slope, yIntercept, xVals, yVals, n);
}

void Outfeed::setRPM(float rpm)
{
  activate();
  _motor.setRPM(rpm);
} 

void Outfeed::setMode(int mode){ _pid.SetMode(mode);}

int Outfeed::getMode(){ return _pid.GetMode();}

void Outfeed::setTunings(){ _pid.SetTunings(_configuration->profile.outfeedKp,
                                           _configuration->profile.outfeedKi,
                                           _configuration->profile.outfeedKd);}

void Outfeed::disable(){  _motor.disable();}

void Outfeed::enable(){  _motor.enable();}

float Outfeed::getMmExtruded()
{ 
  return _mmExtruded;
}

double Outfeed::getMPerMin()
{
  return getRPM()*2.0*PI*_configuration->physical.outfeedRollerRadius*0.001;
}

double Outfeed::getFtPerMin()
{
  return getRPM()*2.0*PI*_configuration->physical.outfeedRollerRadius*0.00328;
}

void Outfeed::reset()
{ 
  _mmExtruded = 0.0;
  _previousTime = millis();
}

//Idea: set update to call sample until a sample is ready. Reset sampleNum after the pid is computed
// put the mmExtruded into the compute time part. So then update can be called as rapidly as possible
void Outfeed::activate()
{
  _now = millis();
  _mmExtruded += ro*_motor.getRPM()*2.0*PI/60.0*(_now-_previousTime)/1000.0;
  
  if (_now >= _computeTime){
    _caliper.update();
    _pid.Compute();
    if (_pid.GetMode() == AUTOMATIC) {_motor.setRPM(_rpm);}
    _computeTime = _now + (long)*_computeInterval;
  }
  _previousTime = _now;
}


