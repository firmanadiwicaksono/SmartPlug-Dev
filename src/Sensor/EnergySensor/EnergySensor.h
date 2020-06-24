#ifndef EnergySensor_h
#define EnergySensor_h

#include <Arduino.h>
#include "../lib/HLW8012/HLW8012.h"

//Untuk Kalibrasi
#include "Aktuator/Relay/Relay.h"
//------------------------------------------

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
  double current;
  double apparentPower;
  double powerFactor;
  void unblockingDelay(int mseconds);
public:
  EnergySensor(int cfPin, int cf1Pin, int selPin);
  void read();
  int getActivePower();
  int getVoltage();
  double getCurrent();
  int getApparentPower();
  double getPowerFactor();
};

#endif
