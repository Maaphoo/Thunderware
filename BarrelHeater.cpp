/*
  BarrelHeater.cpp - Library for activating the the barrel heater.
          The barrel heater is a 120 v 130 w heating element powered
          by an electro-mechanical relay. The relay coil is optically 
          isolated from the logic circuits and is activated by pin 7.
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "BarrelHeater.h"

BarrelHeater::BarrelHeater()
{
  pinMode(7, OUTPUT); //Set pin 7 as the barrel heater pin.
  _timeBase = 2000;
 }



void BarrelHeater::activate()
{
 //variables
 static unsigned long _now;
 static unsigned long _durration;
 static unsigned long _startTime;

//Get the time
 _now = millis();
  
 //If one timebase has passed start over. Turn the relay on. 
 if (_now >= _timeBase + _startTime){
   _startTime = _now;
   
   // Determine the length of time that the relay should be on
   _durration = ((_timeBase*_dutyCycle)/100L);
   
   if (_dutyCycle>1){ // Only turn on if duty cycle is greater than 1
  // Serial.println("relay On");
      PORTH = PORTH | B00010000;
   }
  }
  
  //If the relay should now be off, turn it off
 if (_now >= _startTime + _durration){
  //    Serial.println("relay OFF");

      PORTH = PORTH & B11101111;
  }
}

void BarrelHeater::setDutyCycle(float dutyCycle)
{
  //Validate the duty cycle
  if (dutyCycle<0){dutyCycle = 0.0;}
  if (dutyCycle>100){dutyCycle = 100.0;}
  
  _dutyCycle = dutyCycle;
}
void BarrelHeater::off()
{
  PORTH = PORTH & B11101111;//turn the relay off
}
