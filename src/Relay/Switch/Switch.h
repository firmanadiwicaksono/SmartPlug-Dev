#ifndef Switch_h
#define Switch_h

#include <Arduino.h>

class Switch{
private:
  int pin;

public:
  void setPin(int pin);
  void setClosedCircuit();
  void setOpenCircuit();
};

#endif
