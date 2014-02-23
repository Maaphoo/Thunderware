/*
  NozzleHeater.h - Library for controlling the nozzle heater. The
         nozzle heater is a 12 v 5.8 ohm heating element that is switched
         using a tip120 darlington transistor. A PWM signal is used to vary
         the output of the heater.
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "NozzleHeater.h"


NozzleHeater::NozzleHeater()
{
  pinMode(nozzleHeaterPin, OUTPUT); 
 }


void NozzleHeater::setPWM(int dutyCycle)
{
 analogWrite(nozzleHeaterPin, dutyCycle); 
 _dutyCycle = dutyCycle;

}

void NozzleHeater::off()
{
  _dutyCycle = 0;
 analogWrite(nozzleHeaterPin, 0); 
}

int NozzleHeater::getDutyCycle(){ return _dutyCycle;}

