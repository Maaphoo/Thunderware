/*
  Caliper.cpp - Library for interpreting data
    recorded from the caliper. The caliper's 
    sensor is a 5mm phototransistor slot sensor.
 
 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */


#include "Arduino.h"
#include <Wire.h>
#include "Caliper.h"

Caliper::Caliper(Configuration* configuration) 
{
 _slope = &configuration->physical.slope;
 _yIntercept = &configuration->physical.yIntercept;
// _pin = 2;//Analog pin 2
}

void Caliper::sample(){
  _now = micros();
  if (_now>_previousTime+_minTimeInterval){
      _sampleSum += analogRead(_pin);
      _sampleNum++;
      _previousTime = _now;
  }
  
  if (_sampleNum==*_numSamplesToTake-1){
    _dia = *_slope*((float)_sampleSum/(float)*_numSamplesToTake)+ *_yIntercept;
    dia = _dia;
    _sampleSum = 0;
    _sampleNum =0;
  }
}

/* 
getRawADC() is used to get an average adc value
from the slave arduino located near the caliper
*/
float Caliper::getRawADC()
{ 
  Wire.requestFrom(2,4);
  int i=0;
  while(Wire.available()){
    _rawADC._byte[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();
  
  return _rawADC._float;
}


  

  
