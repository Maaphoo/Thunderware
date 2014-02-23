/*
  NozzleHeater.h - Library for controlling the nozzle heater. The
         nozzle heater is a 12 v 5.8 ohm heating element that is switched
         using a tip120 darlington transistor. A PWM signal is used to vary
         the output of the heater.
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/
#ifndef NozzleHeater_h
#define NozzleHeater_h

#include "Arduino.h"

class NozzleHeater
{
  public:
    #define nozzleHeaterPin 5//Set the nozzle heater pin to pin 5
    
    NozzleHeater();//constructor
    void setPWM(int dutyCycle);
    void off();
    int getDutyCycle();
    
  private:
   int _dutyCycle;
};

#endif
