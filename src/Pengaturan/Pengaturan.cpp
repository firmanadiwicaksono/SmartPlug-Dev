#include "Pengaturan.h"
#include <Arduino.h>
#include <EEPROM.h>

//Private
  String Pengaturan::readData(int start, int length){
    /*
    Spesifikasi :
    - Fungsi ini digunakan untuk membaca data dari EPROM
    - Keluaran dari fungsi ini berupa objek kelas String.
    */

    String data = "";
    for(int i = 0; i < length; i++){
      byte x = EEPROM.read(start + i);
      if(x != 0){
        data += (char)x;
      }
    }
    return data;
  }

  void Pengaturan::writeData(String data, int start, int length){
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
void Pengaturan::begin(){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk inisialisasi EPROM sebelum dilakukan pembacaan dan penulisan data.
  */

  EEPROM.begin(1000);
}

String Pengaturan::readWifiSSID(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca Wi-Fi SSID.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 0), data_length);
}

String Pengaturan::readWifiPassword(){ 
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca Wi-Fi Password.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 1), data_length);
}

String Pengaturan::readMQTTBroker(){ 
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca alamat MQQT Broker.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 2), data_length);
}

String Pengaturan::readMQTTUsername(){ 
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca alamat MQQT Username.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 3), data_length);
}

String Pengaturan::readMQTTPassword(){ 
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca alamat MQQT Password.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 4), data_length);
}

String Pengaturan::readUsername(){ 
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca Username.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 5), data_length);
}

String Pengaturan::readPassword(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membaca Password.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  return readData(start_index + (data_length * 6), data_length);
}

void Pengaturan::writeWifiSSID(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis Wi-Fi SSID ke EPROM.
  */

  return writeData(data, start_index + (data_length * 0), data_length);
}

void Pengaturan::writeWifiPassword(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis Wi-Fi Password ke EPROM.
  */

  return writeData(data, start_index + (data_length * 1), data_length);
}

void Pengaturan::writeMQTTBroker(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis alamat MQTT Broker ke EPROM.
  */

  return writeData(data, start_index + (data_length * 2), data_length);
}

void Pengaturan::writeMQTTUsername(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis MQTT Username ke EPROM.
  */

  return writeData(data, start_index + (data_length * 3), data_length);
}

void Pengaturan::writeMQTTPassword(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis MQTT Password ke EPROM.
  */

  return writeData(data, start_index + (data_length * 4), data_length);
}

void Pengaturan::writeUsername(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis Username ke EPROM.
  */

  return writeData(data, start_index + (data_length * 5), data_length);
}

void Pengaturan::writePassword(String data){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menulis Password ke EPROM.
  */

  return writeData(data, start_index + (data_length * 6), data_length);
}
//------------------------------------------------------------------------------