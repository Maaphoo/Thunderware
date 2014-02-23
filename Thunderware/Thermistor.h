/*

 */

#ifndef Thermistor_h
#define Thermistor_h

#include <inttypes.h>

class Thermistor
{

public:
    Thermistor(int tPin, long tNominal, int tTempNominal, int numSamples, int bCoefficient, int seriesResistor);
    void sampleTemp();
    float getTemp();

protected:
    int _tPin;
    int _numSamples;
    long _tNominal; 
    long _sampleSum;
    int _tTempNominal;
    int _sampleCounter;
    int _bCoefficient;
    int _seriesResistor;
    float _vApplied;
    float _avgTemp;
    int _adcRange;
    unsigned long _now;
    unsigned long _measureTime;
	

};

#endif
