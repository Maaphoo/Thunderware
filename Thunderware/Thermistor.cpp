//Thermistor

// For Arduino 1.0 and earlier
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Thermistor.h"



Thermistor::Thermistor(int tPin, long tNominal, int tTempNominal, int numSamples, int bCoefficient, int seriesResistor)
{
    _tPin = tPin; //The analog pin connected to the thermistor
    _tNominal = tNominal;//The nominal resistance of the thermistor
    _tTempNominal = tTempNominal;//The nominal temperature of the thermistor
    _numSamples = numSamples;//The number of samples to average
    _bCoefficient = bCoefficient; //The beta coefficient of the thermistor
    _seriesResistor = seriesResistor; //The value of the series resistor
    _vApplied = 5.0;
    _adcRange = 1024;
    _measureTime = millis();
  
	
	
}


void Thermistor:: sampleTemp(){

  _now = millis();
  if (_now>_measureTime){

    _sampleSum +=  analogRead(_tPin);
  if (_sampleCounter == _numSamples-1){

    //get Average measurement
    float average = (float)_sampleSum/(float)_numSamples;

    //Reset _sampleSum and _sampeleCounter
    _sampleCounter = 0;
    _sampleSum = 0.0;
    
    // convert the value to resistance
    average = 1023.0 / average - 1.0;
    average = _seriesResistor / average;

    _avgTemp;
    _avgTemp = average / (float)_tNominal; // (R/Ro)
    _avgTemp = log(_avgTemp); // ln(R/Ro)
    _avgTemp /= (float)_bCoefficient; // 1/B * ln(R/Ro)
    _avgTemp += 1.0 / ((float)_tTempNominal + 273.15); // + (1/To)
    _avgTemp = 1.0 / _avgTemp; // Invert
    _avgTemp -= 273.15; // convert to C
  }else{
  _sampleCounter++;
  }
  _measureTime = _now+20;

  }
}

float Thermistor::getTemp(){ return _avgTemp;}
