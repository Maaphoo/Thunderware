/*
  BarrelHeater.h - Library for activating the the barrel heater.
          The barrel heater is a 120 v 130 w heating element powered
          by an electro-mechanical relay. The relay coil is optically 
          isolated from the logic circuits and is activated by pin 7.
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/
#ifndef BarrelHeater_h
#define BarrelHeater_h

#include "Arduino.h"

class BarrelHeater
{
  public:

    BarrelHeater();//constructor
    void activate();
    void setDutyCycle(float dutyCycle);
    void off();
    
  private:
  int _timeBase;
  float _dutyCycle;
};

#endif
