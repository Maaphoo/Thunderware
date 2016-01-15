 /*
 Spooler.cpp - Library for controlling the spooling mechanism. A stepper
 motor turns the spool. Its speed is determined by the geometry
 of the spool, the distance from the center of the spool to the surface
 of the filament and the rate at which filament is being extruded.

 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */

 #include "Arduino.h"
 #include <Wire.h>
 #include "Spooler.h"

 Spooler::Spooler(Configuration* configuration)
 :   _motor(configuration, configuration->physical.spoolerPinSet),
 _pid(&_rawADCInput,
 &_motorRPM,
 &_pidSetpoint,
 0.01,
 0.0,
 0.0,
 DIRECT)

 {
	 _wireAddress = 5;
	 _interval = 500;
	 _pid.SetSampleTime(_interval);
	 _pid.SetMode(MANUAL);

 }


 void Spooler::setRPM() // Call every 1000ms to update the speed of the spooler based on the PID output
 {
	 _now = millis();
	 if (_now >= _previousTime){
		 Wire.requestFrom(_wireAddress,4);
		 int i=0;
		 while(Wire.available()){
			 _rawADC._byte[i] = Wire.read();
			 i++;
		 }
		 Wire.endTransmission();
		 _rawADCInput = _rawADC._float;
		 if (_pid.GetMode() == MANUAL){
			 _pid.SetMode(AUTOMATIC);
		 }
		 _pid.Compute();
		 _motor.setRPM(_motorRPM);
		 _previousTime = _now+_interval;
	 }
 }

 float Spooler::getRPM(){return _motor.getRPM();}
 
 float Spooler::getRawADC(){
	 Wire.requestFrom(_wireAddress,4);
	 int i=0;
	 while(Wire.available()){
		 _rawADC._byte[i] = Wire.read();
		 i++;
	 }
	 Wire.endTransmission();
	 _rawADCInput = _rawADC._float;
	 return _rawADCInput;
 }



 void Spooler::setRPM(float rpm)
 {
	 if (_pid.GetMode() == AUTOMATIC){
		 _pid.SetMode(MANUAL);
	 }
	 _motor.setRPM(rpm);
 }

 //Instead of using the following, should I have a public pointer to _motor and then use someting like spooler.motor->enable()?
 void Spooler::enable(){ _motor.enable();}
 void Spooler::disable(){ _motor.disable();}

 void Spooler::setDirection(){ _motor.setDirection();}





