#ifndef Pengaturan_h
#define Pengaturan_h

#include <Arduino.h>

class Pengaturan{
private:
  const int start_index = 0;
  const int data_length = 32;
  String readData(int start, int length);
  void writeData(String data, int start, int length);
public:
  void begin();
  String readWifiSSID();
  String readWifiPassword();
  String readMQTTBroker();
  String readMQTTUsername();
  String readMQTTPassword();
  String readUsername();
  String readPassword();
  void writeWifiSSID(String data);
  void writeWifiPassword(String data);
  void writeMQTTBroker(String data);
  void writeMQTTUsername(String data);
  void writeMQTTPassword(String data);
  void writeUsername(String data);
  void writePassword(String data);
};

#endif
