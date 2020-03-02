#ifndef EnergySensor_h
#define EnergySensor_h

#include <Arduino.h>
#include "../lib/HLW8012/HLW8012.h"

class EnergySensor{
private:
  HLW8012 sensor;
  const int currentMode = HIGH;
  const double currentResistor = 0.001;
  const double voltageResistorUpstream = 2350000;
  const double voltageResistorDownstream = 1000;
  const int pulseTimeout = 500000;
  int activePower;
  int voltage;
  int current;
  double apparentPower;
  double powerFactor;
  void unblockingDelay(int mseconds);
public:
  EnergySensor(int cfPin, int cf1Pin, int selPin);
  void calibrate(int expectedActivePower, int expectedVoltage);
  void read();
  int getActivePower(); //W
  int getVoltage(); //V
  double getCurrent(); //A
  int getApparentPower(); //VA
  double getPowerFactor();
};

#endif
