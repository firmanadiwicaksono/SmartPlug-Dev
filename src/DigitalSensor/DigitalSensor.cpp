#include "DigitalSensor.h"
#include <Arduino.h>

//Public
DigitalSensor::DigitalSensor(int pin){
  /*
  Spesifikasi :
  - Constructor ini digunakan untuk konfigurasi pin sensor digital.
  */

  this->pin = pin;
  pinMode(this->pin, INPUT);
}

bool DigitalSensor::read(){
  /*
  Spesifikasi : 
  - fungsi ini digunakan untuk membaca nilai sensor digital.
  - keluaran fungsi ini berupa tipe data boolean.
  - true = apabila keluaran sensor digital HIGH.
  - false = apabila keluaran sensor digital LOW.
  */
 
  return digitalRead(pin);  
}
//------------------------------------------------------------------------------
