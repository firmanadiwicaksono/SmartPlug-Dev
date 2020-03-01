#include "Relay.h"
#include <Arduino.h>

//Public
Relay::Relay(int pinPhase, int pinNeutral){
  /*
  Spesifikasi :
  - Constructor ini digunakan untuk inisialisasi objek kelas Switch phase dan neutral. 
  */
 
  phase.setPin(pinPhase);
  neutral.setPin(pinNeutral);
}
//------------------------------------------------------------------------------
