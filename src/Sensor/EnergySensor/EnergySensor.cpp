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
  return sensor.getPowerMultiplier();
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
//------------------------------------------------------------------------------