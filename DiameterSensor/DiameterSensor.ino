#include <Wire.h>
int CalliperSlaveAddress = 3;

int count=0;
//Time Related Vars
unsigned long now;
unsigned long measurementTime;
int interval = 100;
float avgMeasurement;
float avgADCVal;
volatile byte* INPUT1FloatPtr;
long analogMeasurement;
float measurement;
void setup()
{
  Wire.begin(CalliperSlaveAddress);    // join i2c bus with address #3
  Wire.onRequest(requestEvent);        // register event
//  Serial.begin(115200);                // start serial for debug output

}

void loop()
{
  now = millis();
  
  if (now>= measurementTime){
    avgADCVal = getMeasurement();
    measurementTime = now+interval;
  }
}


float getMeasurement(){
  for (int i=0;i<500;i++){
    analogMeasurement += analogRead(0);
    delayMicroseconds(100); 
  }
  measurement = (float)analogMeasurement/500.0;
  analogMeasurement = 0;
  measurement = measurement;

  return measurement;
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  byte Data[4];
  INPUT1FloatPtr = (byte*) &avgADCVal;
  Data[0] = INPUT1FloatPtr[0]; 
  Data[1] = INPUT1FloatPtr[1]; 
  Data[2] = INPUT1FloatPtr[2]; 
  Data[3] = INPUT1FloatPtr[3]; 
  Wire.write(Data,4);
//  Serial.println(avgADCVal);
//  Serial.println(Data[0]);
//  Serial.println(Data[1]);
//  Serial.println(Data[2]);
//  Serial.println(Data[3]);
//  Serial.println();
}
