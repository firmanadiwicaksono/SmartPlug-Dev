#include "Switch.h"
#include <Arduino.h>

//Public
void Switch::setPin(int pin){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk inisialisasi pin switch.
  */
 
  this->pin = pin;
  pinMode(this->pin, OUTPUT); 
  digitalWrite(this->pin, LOW);
}

void Switch::setClosedCircuit(){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk membuat switch mengeluarkan keluaran HIGH.
  */

  digitalWrite(pin, HIGH);
}

void Switch::setOpenCircuit(){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk membuat switch mengeluarkan keluaran LOW.
  */

  digitalWrite(pin, LOW);
}
//------------------------------------------------------------------------------
