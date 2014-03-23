/*
  Barrel.cpp - Library for activating the the barrel heater.
          The barrel heater is a 120 v 130 w heating element powered
          by an electro-mechanical relay. The relay coil is optically 
          isolated from the logic circuits and is activated by pin 7.
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Barrel.h"

Barrel::Barrel(Configuration* configuration) 
        : _thermistor(1, //This is the thermistor pin. Should this be set in physical configuration?
                       configuration->physical.barrelTRNom,
                       configuration->physical.barrelTTNom,
                       configuration->physical.barrelTNumSamples,
                       configuration->physical.barrelTBCoefficient,
                       configuration->physical.barrelTSeriesResistor),
          _pid( &_thermistor.temp, 
                &_dutyCycle,
                &configuration->profile.barrelTemp,
                configuration->physical.barrelKp,
                configuration->physical.barrelKi,
                configuration->physical.barrelKd,
                DIRECT)
{
//  _config = configuration;
  _timeBase = &configuration->physical.timeBase;
  _temp = &_thermistor.temp;
  _pid.SetSampleTime(*_timeBase);
  _pid.SetTunings(configuration->physical.barrelKp,
                  configuration->physical.barrelKi,
                  configuration->physical.barrelKd);

  _pid.SetOutputLimits(configuration->physical.barrelMin, 
                       configuration->physical.barrelMax);
  _pid.SetMode(AUTOMATIC);
  
  pinMode(7, OUTPUT); //Set pin 7 as the barrel heater pin. Should this go in physical config?
}



void Barrel::activate()
{
  
 //variables
 static unsigned long _now;
 static unsigned long _durration;
 static unsigned long _startTime;

//Get the time
 _now = millis();
 _thermistor.sampleTemp();//Always sample temp so that the PID gets a good input
  
 //If one timebase has passed start over. Get the new PID setting and turn the relay on. 
 if (_now >= *_timeBase + _startTime){
   _startTime = _now;
   _temp = &_thermistor.temp;
   _pid.Compute();
   Serial.print("Barrel Temp in Barrel: ");
   Serial.println(*_temp);
   Serial.print("Barrel Temp in Barrel Th: ");
   Serial.println(_thermistor.temp);   
   Serial.print("DutyCycle: ");
   Serial.println(_dutyCycle);   
   // Determine the length of time that the relay should be on
   _durration = ((*_timeBase*_dutyCycle)/100L);
   
   if (_dutyCycle>1){ // Only turn on if duty cycle is greater than 1
      PORTH = PORTH | B00010000;//Turn Relay on.
   }
  }
  
  //If the relay should now be off, turn it off
 if (_now >= _startTime + _durration){
      PORTH = PORTH & B11101111;//Turn relay off
  }
}

// sampleTemp is used for states where the heater should be inactive. 
void Barrel::sampleTemp()
{
   _thermistor.sampleTemp();//Always sample temp so that the PID gets a good input
}

void Barrel::setDutyCycle(float dutyCycle)
{
  //Validate the duty cycle
  if (dutyCycle<0){dutyCycle = 0.0;}
  if (dutyCycle>100){dutyCycle = 100.0;}
  
  _dutyCycle = dutyCycle;
}
void Barrel::off()
{
  PORTH = PORTH & B11101111;//turn the relay off
}

void Barrel::setMode(int mode) 
{
  _pid.SetMode(mode);
}
  

float Barrel::getTemp(){return _thermistor.temp;}
