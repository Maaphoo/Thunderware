/*
Outfeed.cpp - Library for controlling the outfeed process.
It consists of a PID controller, DiameterSensor, and a
StepperMotor.

Created by Matthew P. Rogge, Februrary 12, 2014.
Released into the public domain.
*/

#include "Arduino.h"
#include "Outfeed.h"

Outfeed::Outfeed(Configuration* configuration)
:  _motor(configuration, configuration->physical.outfeedPinSet),
_caliper2(configuration, 4),
_caliper1(configuration, 3),
_pid(&_caliper1.dia,
&_motor._rpm,
&configuration->profile.diaSetPoint,
configuration->profile.outfeedKp,
configuration->profile.outfeedKi,
configuration->profile.outfeedKd,
REVERSE)

{
	_configuration = configuration;
	_computeInterval = &configuration->profile.outfeedComputeInterval;
}


//revise so that the outfeed reports mm/s
float Outfeed::getRPM(){ return _motor.getRPM();}

double Outfeed::getDia(){ 
  _caliper2.update();
  return _caliper2.dia;
}

double Outfeed::getRawADC(int sensorNum){
	switch(sensorNum){
		case 1:
			return _caliper1.getRawADC();
		case 2:
			return _caliper2.getRawADC();
	}	
}

void Outfeed::linReg(float slopeAndIntercept[], float *xVals, float *yVals, int *n)
{
	_caliper2.linReg(slopeAndIntercept, xVals, yVals, n);
}

void Outfeed::setRPM(float rpm)
{
	/*activate();*/
	_motor.setRPM(rpm);
}

void Outfeed::setMode(int mode){ _pid.SetMode(mode);}

int Outfeed::getMode(){ return _pid.GetMode();}

void Outfeed::setTunings(){
	_pid.SetTunings(_configuration->profile.outfeedKp,
	_configuration->profile.outfeedKi,
	_configuration->profile.outfeedKd);
}

double Outfeed::getKp(){return _pid.GetKp();}

void Outfeed::setKp(double kp){ _pid.SetTunings(kp, _pid.GetKi(), _pid.GetKd());}

double Outfeed::getKi(){return _pid.GetKi();}

void Outfeed::setKi(double ki){ _pid.SetTunings(_pid.GetKp(), ki, _pid.GetKd());}

double Outfeed::getKd(){return _pid.GetKd();}

void Outfeed::setKd(double kd){ _pid.SetTunings(_pid.GetKp(), _pid.GetKi(), kd);}

void Outfeed::disable(){  _motor.disable();}

void Outfeed::enable(){  _motor.enable();}

float Outfeed::getMmExtruded()
{
	return _mmExtruded;
}

double Outfeed::getMPerMin()
{
	return getRPM()*2.0*PI*_configuration->physical.outfeedRollerRadius*0.001;
}

double Outfeed::getFtPerMin()
{
	return getRPM()*2.0*PI*_configuration->physical.outfeedRollerRadius*0.00328;
}

void Outfeed::reset()
{
	_mmExtruded = 0.0;
	_previousTime = millis();
}

//Idea: set update to call sample until a sample is ready. Reset sampleNum after the pid is computed
// put the mmExtruded into the compute time part. So then update can be called as rapidly as possible
void Outfeed::activate()
{
	_now = millis();
	_mmExtruded += _configuration->physical.outfeedRollerRadius*_motor.getRPM()*2.0*PI/60.0*(_now-_previousTime)/1000.0;

	if (_now >= _computeTime){
		//_caliper.update();
		if (_pid.GetMode() == AUTOMATIC) {
			_pid.Compute();
			_motor.setRPM(_motor._rpm);
		}
		_computeTime = _now + (long)*_computeInterval;
	}
	_previousTime = _now;
}

void Outfeed::setDirection(){_motor.setDirection();}


