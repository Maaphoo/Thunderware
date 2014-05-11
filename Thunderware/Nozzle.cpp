/*
  Nozzle.h - Library for controlling the nozzle heater. The
         nozzle heater is a 12 v 5.8 ohm heating element that is switched
         using a tip120 darlington transistor. A PWM signal is used to vary
         the output of the heater.Nozzle
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Nozzle.h"

Nozzle::Nozzle(Configuration* configuration) 
        : _thermistor(0, //This is the thermistor pin. Should this be set in physical configuration?
                       configuration->physical.nozzleTRNom,
                       configuration->physical.nozzleTTNom,
                       configuration->physical.nozzleTNumSamples,
                       configuration->physical.nozzleTBCoefficient,
                       configuration->physical.nozzleTSeriesResistor), 
          _pid( &_thermistor.temp, 
                &_dutyCycle,
                &configuration->profile.nozzleTemp,
                configuration->physical.nozzleKp,
                configuration->physical.nozzleKi,
                configuration->physical.nozzleKd,
                DIRECT), 

           _pin(configuration->physical.nozzlePin)
                       
{
  _config = configuration;
  _sampleTime = &configuration->physical.nozzleSampleTime;
  _temp = &_thermistor.temp;
  _pid.SetSampleTime(*_sampleTime);
  _pid.SetTunings(configuration->physical.nozzleKp,
                  configuration->physical.nozzleKi,
                  configuration->physical.nozzleKd);

  _pid.SetOutputLimits(configuration->physical.nozzleMin, 
                       configuration->physical.nozzleMax);
  _pid.SetMode(AUTOMATIC);
  pinMode(_pin, OUTPUT);//Set the nozzle pin to output. The pin should be defined somewhere else?
}

void Nozzle::activate()
{
  
 //variables
 static unsigned long _now;
 static unsigned long _endPeriod;

//Get the time
 _now = millis();
 _thermistor.sampleTemp();//Always sample temp so that the PID gets a good input
 if (_now>_endPeriod){
   _pid.Compute();
   analogWrite(_pin, _dutyCycle);
   _endPeriod = _now+*_sampleTime;//This won't be as exact(shouldn't matter), but it avoids the problem of setting the start time caused by += _sampleTime.
 }
}

// sampleTemp is used for states where the heater should be inactive. 
void Nozzle::sampleTemp()
{
   _thermistor.sampleTemp();
}
  

void Nozzle::setDutyCycle(float dutyCycle)
{
  if (_pid.GetMode() == AUTOMATIC){
    _pid.SetMode(MANUAL);
  }
  //Validate the duty cycle
  if (dutyCycle<0){dutyCycle = 0.0;}
  if (dutyCycle>100){dutyCycle = 100.0;}
  
  _dutyCycle = dutyCycle;
}

void Nozzle::setMode(int mode){ _pid.SetMode(mode);}
int Nozzle::getMode(){return _pid.GetMode();}

void Nozzle::off()
{
  _dutyCycle = 0;
 analogWrite(_pin, 0); 
}

double Nozzle::getDutyCycle(){return _dutyCycle;}

float Nozzle::getTemp(){return _thermistor.temp;}



