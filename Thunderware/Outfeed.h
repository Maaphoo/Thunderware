/*
  Outfeed.h - Library for activating the the barrel heater.
          The barrel heater is a 120 v 130 w heating element powered
          by an electro-mechanical relay. The relay coil is optically 
          isolated from the logic circuits and is activated by pin 7.
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/
#ifndef Outfeed_h
#define Outfeed_h

#include "Arduino.h"
#include "config.h"
#include "StepperMotor.h"

class StepperMotor;

class Outfeed
{
  public:

    Outfeed(StepperMotor::PinSet pinSet, int timer);//constructor
    float getRPM();
    void setRPM(float rpm);
    void disable();
    void enable();
    void reset();
    float getMmExtruded();
    void update();
    
  private:
    StepperMotor _motor;
    float _mmExtruded;
    unsigned long _now;
    unsigned long _previousTime;

};

#endif
