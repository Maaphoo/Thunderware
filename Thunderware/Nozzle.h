/*Nozzle.h - Library for controlling the nozzle heater. The
         nozzle heater is a 12 v 5.8 ohm heating element that is switched
         using a tip120 darlington transistor. A PWM signal is used to vary
         the output of the heater.
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#ifndef Nozzle_H
#define Nozzle_h

#include "Arduino.h"
#include "Thermistor.h"
#include <PID_v1.h>
#include "Configuration.h"

class Thermistor;
class PID;
class Configuration;

class Nozzle
{
public:
  Nozzle(Configuration* configuration);//constructor
  void activate();
  void sampleTemp();
  void setDutyCycle(float dutyCycle);
  void setMode(int mode);
  int getMode();
  double getDutyCycle();
  void off();
  float getTemp();

private:
  Thermistor       _thermistor;
  PID              _pid;
  Configuration*   _config;
  int*             _sampleTime;
  double           _dutyCycle;
  double*           _temp;
  const int        _pin;
  
};


#endif
