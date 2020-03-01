#ifndef LedPWM_h
#define LedPWM_h

#include <Arduino.h>

class LedPWM{
private:
  int channel;

public:
  void begin(int pin, int channel, int freq, int resolution);
  void setDutyCycle(int val);
};

#endif
