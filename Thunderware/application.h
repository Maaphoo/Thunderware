#ifndef application_h
#define application_h

class Thermistor;

class Application {
 public:
  Application();

  Thermistor* nozzleThermistor() { return _nozzleTh; }
  Thermistor* barrelThermistor() { return _barrelTh; }
 protected:
  Thermistor* _nozzleTh;
  Thermistor* _barrelTh;
};

#endif // application_h
