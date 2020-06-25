#include "EnergySensor.h"
#include <Arduino.h>

//Private
void EnergySensor::unblockingDelay(int mseconds) {
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk memberikan delay pada saat kalibrasi sensor energi.
  */

  unsigned long timeout = millis();
  while ((millis() - timeout) < mseconds) delay(1);
}
//------------------------------------------------------------------------------

//Public
EnergySensor::EnergySensor(int cfPin, int cf1Pin, int selPin){
  /*
  Spesifikasi :
  - Constructor ini digunakan untuk konfigurasi awal sensor energi.
  */

  sensor.begin(cfPin, cf1Pin, selPin, currentMode, false, pulseTimeout);
  sensor.setResistors(currentResistor, voltageResistorUpstream, voltageResistorDownstream);
}

void EnergySensor::calibrate(int expectedActivePower, int expectedVoltage){
  sensor.getActivePower();

  sensor.setMode(MODE_CURRENT);
  unblockingDelay(2000);
  sensor.getCurrent();

  sensor.setMode(MODE_VOLTAGE);
  unblockingDelay(2000);
  sensor.getVoltage();

  sensor.expectedActivePower(expectedActivePower);
  sensor.expectedVoltage(expectedVoltage);
  sensor.expectedCurrent((double)expectedActivePower / (double)expectedVoltage);
  
  _current_multiplier = sensor.getCurrentMultiplier();
  _voltage_multiplier = sensor.getVoltageMultiplier();
  _power_multiplier = sensor.getPowerMultiplier();
}

double EnergySensor::getCurrentMultiplier(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk mendapatkan nilai kalibrasi arus
  */
  return sensor.getCurrentMultiplier();
}

double EnergySensor::getVoltageMultiplier(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk mendapatkan nilai kalibrasi tegangan
  */

  return sensor.getVoltageMultiplier();
}

double EnergySensor::getPowerMultiplier(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk mendapatkan nilai kalibrasi daya
  */
  return getPowerMultiplier();
}

void EnergySensor::setCalibrate(double currentMultiplier, double voltageMultiplier, double powerMultiplier){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk set nilai kalibrasi
  */

  sensor.setCurrentMultiplier(currentMultiplier);
  sensor.setVoltageMultiplier(voltageMultiplier);
  sensor.setPowerMultiplier(powerMultiplier);
}

void EnergySensor::read(){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk membaca nilai sensor energi.
  */
  //static unsigned long last = millis();
  //if ((millis() - last) > 2000) {
    activePower = sensor.getActivePower();
    voltage = sensor.getVoltage();
    current = sensor.getCurrent();
    
    apparentPower = voltage * current;
    powerFactor = activePower / apparentPower;
    sensor.toggleMode();
  //}

}

int EnergySensor::getActivePower(){
  /*
  - Fungsi ini digunakan untuk mendapatkan daya aktif (W).
  - Keluaran dari fungsi ini adalah tipe data integer.
  - Daya dengan satuan Joule/detik  atau  watt disebut sebagai daya aktif. Simbolnya adalah P.
    Daya aktif adalah daya sebenarnya yang dibutuhkan oleh beban. Daya aktif dihitung dengan rumus:
    P = |V| × |I| × cos φ
  */

  return activePower;
}

int EnergySensor::getVoltage(){
  /*
  - Fungsi ini digunakan untuk mendapatkan nilai tegangan (V).
  - Keluaran dari fungsi ini adalah tipe data integer.
  */

  return voltage;    
}

double EnergySensor::getCurrent(){
  /*
  - Fungsi ini digunakan untuk mendapatkan nilai arus (A).
  - Keluaran dari fungsi ini adalah tipe data double.
  */

  return current;    
}

int EnergySensor::getApparentPower(){
  /*
  - Fungsi ini digunakan untuk mendapatkan daya semu (VA).
  - Keluaran dari fungsi ini adalah tipe data double.
  - Daya semu atau daya total (S), ataupun juga dikenal dalam Bahasa Inggris Apparent Power,
    adalah hasil perkalian antara tegangan efektif (Vrms) dengan arus efektif (Irms).
  */

  return apparentPower;    
}

double EnergySensor::getPowerFactor(){
  /*
  - Fungsi ini digunakan untuk mendapatkan faktor daya (0.0-1.0).
  - Keluaran dari fungsi ini adalah tipe data double.
  */

  return powerFactor;    
}
//------------------------------------------------------------------------------