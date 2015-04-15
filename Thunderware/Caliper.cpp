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

Caliper::Caliper(Configuration* configuration) 
{
 _slope = &configuration->physical.slope;
 _yIntercept = &configuration->physical.yIntercept;
// _pin = 2;//Analog pin 2
}

void Caliper::update(){
    dia = *_slope * (getRawADC()) + *_yIntercept;
}

/* 
getRawADC() is used to get an average adc value
from the slave arduino located near the caliper
*/
float Caliper::getRawADC()
{ 
  Wire.requestFrom(2,4);
  int i=0;
  while(Wire.available()){
    _rawADC._byte[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();
  
  return _rawADC._float;
}

void Caliper::linReg(float *slope, float *yIntercept, float *xVals, float *yVals, int *n){
  //Variables
  float sumX = 0.0, sumY=0.0, sumXY=0.0, sumXX=0.0, sumYY=0.0;
  float sXY, sXX;
 
  //Find Sums
  for (int i=0; i<*n; i++) {   
    sumX = sumX + *(xVals + i);
    sumY = sumY + *(yVals + i);
    sumXY = sumXY + *(xVals + i)* *(yVals + i);
    sumXX = sumXX + *(xVals + i)* *(xVals + i);
    sumYY = sumYY + *(yVals + i)* *(yVals + i);
  }
  
  //Debug  
//  Serial.println(sumX);
//  Serial.println(sumY);
//  Serial.println(sumXY);
//  Serial.println(sumXX);  
//  Serial.println(sumYY);  
  
  //Compute slope and intercept
  sXY = sumXY-sumX*sumY/ *n;
  sXX = sumXX-sumX*sumX / *n;
  
  /*
  There is an error here or in the variables used. I can't find it.
  
  
  *slope = sXY/sXX;
  *yIntercept = sumY/ *n - *slope*sumX / *n;

  */
  //Debug
//  Serial.println(sXY);
//  Serial.println(sXX);
//  Serial.println(*slope,6);
//  Serial.println(*yIntercept,6);  

}

  

  
