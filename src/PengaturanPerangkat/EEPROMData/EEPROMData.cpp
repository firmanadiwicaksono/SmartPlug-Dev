#include "EEPROMData.h"
#include <Arduino.h>
#include <EEPROM.h>

//Private
  String EEPROMData::readData(int start, int length){
    /*
    Spesifikasi :
    - Fungsi ini digunakan untuk membaca data dari EPROM
    - Keluaran dari fungsi ini berupa objek kelas String.
    */

    String data = "";
    for(int i = 0; i < length; i++){
      byte x = EEPROM.read(start + i);
      if((x != 0) && (x != 255)){
        data += (char)x;
      }
    }
    return data;
  }

  void EEPROMData::writeData(String data, int start, int length){
    /*
    Spesifikasi :
    - Prosedur ini digunakan untuk menulis data ke EPROM.
    */

    byte buffer[length];
    for(int i = 0; i < length; i++){
      buffer[i] = 0;
    }
    for(int i = 0; i < data.length(); i++){
      buffer[i] = data[i];
    }
    for(int i = 0; i < length; i++){
      EEPROM.write(start + i, buffer[i]);
    }
    EEPROM.commit();
  }
//------------------------------------------------------------------------------

//Public
void EEPROMData::begin(){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk inisialisasi EPROM sebelum dilakukan pembacaan dan penulisan data.
  */

  EEPROM.begin(1000);
}

String EEPROMData::readWifiSSID(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca Wi-Fi SSID.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 0), data_length);
}

String EEPROMData::readWifiPassword(){ 
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca Wi-Fi Password.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 1), data_length);
}

String EEPROMData::readMQTTBroker(){ 
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca alamat MQQT Broker.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 2), data_length);
}

String EEPROMData::readMQTTUsername(){ 
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca alamat MQQT Username.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 3), data_length);
}

String EEPROMData::readMQTTPassword(){ 
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca alamat MQQT Password.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 4), data_length);
}

String EEPROMData::readUsername(){ 
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca Username.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 5), data_length);
}

String EEPROMData::readPassword(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca Password.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 6), data_length);
}

void EEPROMData::writeWifiSSID(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis Wi-Fi SSID ke EPROM.
  */

  return writeData(data, start_index + (data_length * 0), data_length);
}

void EEPROMData::writeWifiPassword(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis Wi-Fi Password ke EPROM.
  */

  return writeData(data, start_index + (data_length * 1), data_length);
}

void EEPROMData::writeMQTTBroker(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis alamat MQTT Broker ke EPROM.
  */

  return writeData(data, start_index + (data_length * 2), data_length);
}

void EEPROMData::writeMQTTUsername(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis MQTT Username ke EPROM.
  */

  return writeData(data, start_index + (data_length * 3), data_length);
}

void EEPROMData::writeMQTTPassword(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis MQTT Password ke EPROM.
  */

  return writeData(data, start_index + (data_length * 4), data_length);
}

void EEPROMData::writeUsername(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis Username ke EPROM.
  */

  return writeData(data, start_index + (data_length * 5), data_length);
}

void EEPROMData::writePassword(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis Password ke EPROM.
  */

  return writeData(data, start_index + (data_length * 6), data_length);
}
//------------------------------------------------------------------------------