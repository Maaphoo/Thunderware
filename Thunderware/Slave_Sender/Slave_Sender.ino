// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

unsigned long now;
unsigned long measurementTime;
int interval = 100;

float dia;
volatile byte* INPUT1FloatPtr;
long analogMeasurement;
float measurement;
void setup()
{
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onRequest(requestEvent); // register event
 //   Serial.begin(115200);  // start serial for debug output

}

void loop()
{
  now = millis();
  if (now>= measurementTime){
    dia = getMeasurement();
    measurementTime = now+interval;
//    Serial.println(dia);
  }
}


float getMeasurement(){
  for (int i=0;i<20;i++){
    analogMeasurement += analogRead(0);
    delayMicroseconds(30); 
  }
  measurement = (float)analogMeasurement/20.0;
  analogMeasurement = 0;
//  measurement = (measurement-ADC1)/slope+M1;

  return measurement;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  byte* Data;
  INPUT1FloatPtr = (byte*) &dia;
  Data[0] = INPUT1FloatPtr[0]; 
  Data[1] = INPUT1FloatPtr[1]; 
  Data[2] = INPUT1FloatPtr[2]; 
  Data[3] = INPUT1FloatPtr[3]; 
  Wire.write(Data,4);
}

