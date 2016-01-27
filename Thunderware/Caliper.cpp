/*
Caliper.cpp - Library for interpreting data
recorded from the caliper. The caliper's
sensor is a 5mm phototransistor slot sensor.

Created by Matthew P. Rogge, Februrary 12, 2014.
Released into the public domain.
*/


#include "Arduino.h"
#include <Wire.h>
#include "Caliper.h"

Caliper::Caliper(Configuration* configuration, int wireAddress)
{
	_slope = &configuration->physical.slope;
	_yIntercept = &configuration->physical.yIntercept;
	// _pin = 2;//Analog pin 2
	_wireAddress = wireAddress;
}

void Caliper::update(){
	dia = *_slope * (1024.0-getRawADC()) + *_yIntercept;
}

/*
getRawADC() is used to get an average adc value
from the slave arduino located near the caliper
*/
float Caliper::getRawADC()
{
	Wire.requestFrom(_wireAddress,4);
	int i=0;
	while(Wire.available()){
		_rawADC._byte[i] = Wire.read();
//		Serial.println(_rawADC._byte[i]);
		i++;
	}
//	Serial.println();
	Wire.endTransmission();
	rawADC = _rawADC._float;
	return _rawADC._float;
}

void  Caliper::linReg(float slopeAndInt[], float *xVals, float *yVals, int *n) {
	//Variables
	float sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumXX = 0.0, sumYY = 0.0;
	float sXY, sXX;



	//Find Sums
	for (int i = 0; i < *n; i++) {
		sumX = sumX + *(xVals + i);
		sumY = sumY + *(yVals + i);
		sumXY = sumXY + *(xVals + i) * *(yVals + i);
		sumXX = sumXX + *(xVals + i) * *(xVals + i);
		sumYY = sumYY + *(yVals + i) * *(yVals + i);
	}

	//Compute slope and intercept
	sXY = sumXY - sumX * sumY / *n;
	sXX = sumXX - sumX * sumX / *n;
	slopeAndInt[0] = sXY / sXX;
	slopeAndInt[1] = sumY / *n - slopeAndInt[0] * (sumX / *n);

	//Debug
	Serial.println("Data (x,y):");
	for (int i = 0; i < *n; i++) {
		Serial.print(xVals[i]);
		Serial.print(", ");
		Serial.println(yVals[i]);
	}
	Serial.println();

	Serial.print("sumX: ");
	Serial.println(sumX);
	Serial.print("sumY: ");
	Serial.println(sumY);
	Serial.print("sumXY: ");
	Serial.println(sumXY);
	Serial.print("sumXX: ");
	Serial.println(sumXX);
	Serial.print("sumYY: ");
	Serial.println(sumYY);
	Serial.println();

	Serial.print("sXY: ");
	Serial.println(sXY);
	Serial.print("sXX: ");
	Serial.println(sXX);
	Serial.print("slope: ");
	Serial.println(slopeAndInt[0], 6);
	Serial.print("Intercept: ");
	Serial.println(slopeAndInt[1], 6);
}

// void Caliper::linReg(float *slope, float *yIntercept, float *xVals, float *yVals, int *n){
	////Variables
	//float sumX = 0.0, sumY=0.0, sumXY=0.0, sumXX=0.0, sumYY=0.0;
	//float sXY, sXX;
	//
	////Find Sums
	//for (int i=0; i<*n; i++) {
		//sumX = sumX + *(xVals + i);
		//sumY = sumY + *(yVals + i);
		//sumXY = sumXY + *(xVals + i)* *(yVals + i);
		//sumXX = sumXX + *(xVals + i)* *(xVals + i);
		//sumYY = sumYY + *(yVals + i)* *(yVals + i);
		//}
//
////Compute slope and intercept
	//sXY = *n * sumXY-sumX*sumY;
	//sXX = *n * sumXX-sumX*sumX;
	//
	////Compute slope and intercept
	//
	//float slope1 = sXY/sXX;
	//float yIntercept1 = (sumY - slope1 * sumX) / *n;
	
// 	//Variables
	// 	float sumX = 0.0, sumY=0.0, sumXY=0.0, sumXX=0.0, sumYY=0.0;
	// 	float sXY, sXX;
	// 	
	// 		//Find Sums
	// 		for (int i=0; i<n; i++) {
	// 		sumX = sumX + *(xVals + i);
	// 		sumY = sumY + *(yVals + i);
	// 		sumXY = sumXY + *(xVals + i)* *(yVals + i);
	// 		sumXX = sumXX + *(xVals + i)* *(xVals + i);
	// 		sumYY = sumYY + *(yVals + i)* *(yVals + i);
	// 		}
	// 	//Compute slope and intercept
	// 	sXY = n * sumXY-sumX*sumY;
	// 	sXX = n1 * sumXX-sumX*sumX;
	// 
	// 	*slope = sXY;
	// 	}
