#ifndef LedRGB_h
#define LedRGB_h

#include <Arduino.h>
#include "LedPWM/LedPWM.h"

class LedRGB{
private:
  const int freq = 20000;
  const int resolution = 8;
  LedPWM R;
  LedPWM G;
  LedPWM B;
  void HSVtoRGB(float inH, float inS, float inV, float& outR, float& outG, float& outB);
public:
  LedRGB(int pinR, int pinG, int pinB, int channelR, int channelG, int channelB);
  void setRGB(int valR, int valG, int valB);
  void setBlack();
  void setRed();
  void setGreen();
  void setBlue();
  void blink(int valR, int valG, int valB, int count, int delayStep);
  void rainbow(int delayStep);
};

#endif
