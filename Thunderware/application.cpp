#include "application.h"

#include <stdio.h>
#include "Thermistor.h"

Application::Application():
    _nozzleTh(NULL),
    _barrelTh(NULL) {

  _nozzleTh = new Thermistor(0,100000,25, 20,4092, 9890);
  _barrelTh = new Thermistor(1,100000,25, 20,4092, 9910);
}
