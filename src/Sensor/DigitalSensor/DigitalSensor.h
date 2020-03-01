#ifndef DigitalSensor_h
#define DigitalSensor_h

#include <Arduino.h>

class DigitalSensor{
private:
  int pin;

public:
  DigitalSensor(int pin);
  bool read();
};

#endif
