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

  //Untuk kalibrasi
  Relay relay(16, 17);
  relay.phase.setClosedCircuit();
  relay.neutral.setClosedCircuit();
  //------------------------------------------

  sensor.begin(cfPin, cf1Pin, selPin, currentMode, false, pulseTimeout);
  sensor.setResistors(currentResistor, voltageResistorUpstream, voltageResistorDownstream);

  
  sensor.getActivePower();

  sensor.setMode(MODE_CURRENT);
  unblockingDelay(2000);
  sensor.getCurrent();

  sensor.setMode(MODE_VOLTAGE);
  unblockingDelay(2000);
  sensor.getVoltage();

  //Untuk kalibrasi
  // Calibrate using a 60W bulb (pure resistive) on a 230V line
  sensor.expectedActivePower(14.0);
  sensor.expectedVoltage(194.0);
  sensor.expectedCurrent(14.0 / 194.0);
  Serial.begin(9600);

  Serial.print("[HLW] New current multiplier : "); Serial.println(sensor.getCurrentMultiplier());
  Serial.print("[HLW] New voltage multiplier : "); Serial.println(sensor.getVoltageMultiplier());
  Serial.print("[HLW] New power multiplier   : "); Serial.println(sensor.getPowerMultiplier());
  Serial.println();
  //-----------------------------------------------------

  //Setelah dilakukan kalibrasi agar nilai kalibrasi tersimpan
  //sensor.setCurrentMultiplier(0.0);
  //sensor.setVoltageMultiplier(0.0);
  //sensor.setPowerMultiplier(0.0);
  //-----------------------------------------------------
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