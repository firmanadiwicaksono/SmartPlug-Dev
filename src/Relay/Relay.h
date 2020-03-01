#ifndef Relay_h
#define Relay_h

#include <Arduino.h>
#include "Switch/Switch.h"

class Relay{
public:
  Relay(int pinPhase, int pinNeutral);
  Switch phase;
  Switch neutral;
};

#endif
