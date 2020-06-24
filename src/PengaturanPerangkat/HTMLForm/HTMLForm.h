#ifndef HTMLForm_h
#define HTMLForm_h

#include <Arduino.h>

enum HTML_FORM_ARG{
  ARG_USERNAME,
  ARG_PASSWORD,
  ARG_KONFIRMASI_PASSWORD,
  ARG_WIFI_SSID,
  ARG_WIFI_PASSWORD,
  ARG_MQTT_BROKER,
  ARG_MQTT_USERNAME,
  ARG_MQTT_PASSWORD
};

typedef struct{
  String firmwareName;
  String firmwareDescription;
  String firmwareVersion;
  String legalCopyright;
  String companyName;
  String firmwareType;
}FIRMWARE_IN;

class HTMLForm{
private:
  String htmlFormArg[8] = {
    "username",
    "password",
    "konfirmasi_password",
    "wifi_ssid",
    "wifi_password",
    "mqtt_broker",
    "mqtt_username",
    "mqtt_password"
  };

public:
  String login(String target,  String message);
  String pengaturanKoneksi(String target, String message, String link_pengaturan_koneksi, String link_pengaturan_pengguna, String link_informasi_firmware, String link_logout, String wifi_ssid, String wifi_password, String mqtt_broker, String mqtt_username, String mqtt_password);
  String pengaturanPengguna(String target, String message, String link_pengaturan_koneksi, String link_pengaturan_pengguna, String link_informasi_firmware, String link_logout, String username, String password, String konfirmasi_password);
  String informasiFirmware(FIRMWARE_IN informasi_firmware, String link_pengaturan_koneksi, String link_pengaturan_pengguna, String link_informasi_firmware, String link_logout);
  String getArg(HTML_FORM_ARG arg);
};

#endif
