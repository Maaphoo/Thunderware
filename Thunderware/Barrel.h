/*
  Barrel.h - Library for activating the the barrel heater.
 The barrel heater is a 120 v 130 w heating element powered
 by an electro-mechanical relay. The relay coil is optically 
 isolated from the logic circuits and is activated by pin 7.
 
 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */
#ifndef Barrel_h
#define Barrel_h

#include "Arduino.h"
#include "Thermistor.h"
#include <PID_v1.h>
#include "Configuration.h"

class Thermistor;
class PID;
class Configuration;

class Barrel
{
public:

  Barrel(Configuration* configuration);//constructor
  void activate();
  void setDutyCycle(float dutyCycle);
  void sampleTemp();
  float getTemp();
  void off();
  void setMode(int mode);

private:

  Thermistor       _thermistor;
  PID              _pid;
  //  Configuration*   _config;
  int*             _timeBase;
  double           _dutyCycle;
  double*          _temp;

};

#endif

