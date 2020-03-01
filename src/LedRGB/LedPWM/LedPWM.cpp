#include "LedPWM.h"
#include <Arduino.h>

//Public
void LedPWM::begin(int pin, int channel, int freq, int resolution){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk inisialisasi pin Led dengan keluaran berupa sinyal PWM.
  */

  this->channel = channel;
  ledcSetup(this->channel, freq, resolution);
  ledcAttachPin(pin, this->channel);
}

void LedPWM::setDutyCycle(int val){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk mengatur duty cycle sinyal PWM pada keluaran pin Led.
  */

  ledcWrite(channel, val);
}
//------------------------------------------------------------------------------