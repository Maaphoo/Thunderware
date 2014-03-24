/*
  Caliper.h - Library for interpreting data
    recorded from the caliper. The caliper's 
    sensor is a 5mm phototransistor slot sensor.
 
 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */
#ifndef Caliper_h
#define Caliper_h

#include "Arduino.h"
#include "Configuration.h"
class Configuration;

class Caliper
{
public:

  Caliper(Configuration* configuration);//constructor
  void sample();
  float getRawADC();
  double dia;

private:
  void linReg(float* slope, float *yIntercept, float *xVals, float *yVals, int *n);
  
  union RawADC {byte _byte[4]; float _float;} _rawADC;
  int _pin;
  int*  _numSamplesToTake;
  float* _slope;
  float* _yIntercept;
  unsigned long _previousTime;
  unsigned long _minTimeInterval;
  unsigned long _now;
  unsigned int _sampleNum;
  unsigned int _sampleSum;
  float _dia;
  

};

#endif

