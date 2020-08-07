#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include "../lib/MQTT/PubSubClient.h"
#include "UpdateFirmwareViaSDCard/FirmwareCrypt/FirmwareCrypt.h"
#include "PengaturanPerangkat/HTMLForm/HTMLForm.h"
#include "PengaturanPerangkat/EEPROMData/EEPROMData.h"
#include "Sensor/DigitalSensor/DigitalSensor.h"
#include "Aktuator/LedRGB/LedRGB.h"
#include "Aktuator/Relay/Relay.h"

const char *ap_ssid = "Smart_Plug_Device";
const char *ap_password = "";

WebServer server(80);
HTMLForm form;
EEPROMData pengaturan;

WiFiClient espClient;
PubSubClient MQTT(espClient);

FirmwareCrypt firmware_update;
TaskHandle_t firmware_crypt_task;

DigitalSensor jumper(34);
Relay relay(16, 17);
LedRGB led(26, 27, 13, 0, 1, 2);

bool can_restart;
bool execute_main;
bool interrupt_update;

String session;

//Web Server
String generateSession(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk membuat nama session secara random dengan panjang 100 digit.
  - Keluaran fungsi berupa objek kelas String.
  */

  String char_set = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
  String str = "HOME_AUTOMATION_SESSION=";
  for(int i = 0; i < 100; i++){
    str += char_set[random(char_set.length())];
  }
  return str;
}

bool is_authentified() {
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk mengecek apakah pengguna telah login atau telah logout.
  - Keluaran fungsi berupa tipe data boolean.
  - true = apabila user telah login.
  - false = apabila user telah logout.
  */

  Serial.println("Enter is_authentified");
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
    if (cookie.indexOf(session) != -1) {
      Serial.println("Authentification Successful");
      return true;
    }
  }
  Serial.println("Authentification Failed");
  return false;
}

void handleLogin() {
  /*
  Spesifikasi :
  - Apabila pengguna belum login server akan memanggil prosedur ini, sehingga pengguna
    diminta untuk login terlebih dahulu sebelum masuk ke halaman pengaturan.
  */

  String message = "";
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
  }
  if (server.hasArg("disconnect")) {
    session = generateSession();
    Serial.println("Disconnection");
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  if (server.hasArg(form.getArg(ARG_USERNAME)) && server.hasArg(form.getArg(ARG_PASSWORD))) {
    if ((server.arg(form.getArg(ARG_USERNAME)) == pengaturan.readUsername()) && (server.arg(form.getArg(ARG_PASSWORD)) == pengaturan.readPassword())) {
      session = generateSession();
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", session);
      server.send(301);
      Serial.println("Log in Successful");
      return;
    }
    message = "Username atau password salah.";
    Serial.println("Log in Failed");
  }
  server.send(200, "text/html", form.login("/login", message));
}

void handleKoneksi() {
  /*
  Spesifikasi :
  - Apabila pengguna telah login server membuka halaman / server akan memanggil prosedur ini,
    sehingga pengguna dapat masuk ke halaman pengaturan koneksi.
  - Apabila pengguna belum login server akan memanggil prosedur handleLogin(),
    sehingga pengguna diminta untuk login terlebih dahulu sebelum masuk ke halaman ini.
  */

  String message = "";
  if (!is_authentified()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }

  if(server.hasArg(form.getArg(ARG_WIFI_SSID)) && server.hasArg(form.getArg(ARG_WIFI_PASSWORD)) && server.hasArg(form.getArg(ARG_MQTT_BROKER)) && server.hasArg(form.getArg(ARG_MQTT_USERNAME)) && server.hasArg(form.getArg(ARG_MQTT_PASSWORD))){
    String error_message = "";
    if(server.arg(form.getArg(ARG_WIFI_SSID)) == ""){
      error_message += "Wi-Fi SSID tidak boleh kosong.\\n";
    }

    if(server.arg(form.getArg(ARG_WIFI_PASSWORD)) == ""){
      error_message += "Wi-Fi Password tidak boleh kosong.\\n";
    }

    if(server.arg(form.getArg(ARG_MQTT_BROKER)) == ""){
      error_message += "MQTT Broker tidak boleh kosong.\\n";
    }

    if(server.arg(form.getArg(ARG_MQTT_USERNAME)) == ""){
      error_message += "MQTT Username tidak boleh kosong.\\n";
    }

    if(server.arg(form.getArg(ARG_MQTT_PASSWORD)) == ""){
      error_message += "MQTT Password tidak boleh kosong.\\n";
    }

    if(error_message == ""){
      if(pengaturan.readWifiSSID() != server.arg(form.getArg(ARG_WIFI_SSID))){
        pengaturan.writeWifiSSID(server.arg(form.getArg(ARG_WIFI_SSID)));
      }

      if(pengaturan.readWifiPassword() != server.arg(form.getArg(ARG_WIFI_PASSWORD))){
        pengaturan.writeWifiPassword(server.arg(form.getArg(ARG_WIFI_PASSWORD)));
      }

      if(pengaturan.readMQTTBroker() != server.arg(form.getArg(ARG_MQTT_BROKER))){
        pengaturan.writeMQTTBroker(server.arg(form.getArg(ARG_MQTT_BROKER)));
      }

      if(pengaturan.readMQTTUsername() != server.arg(form.getArg(ARG_MQTT_USERNAME))){
        pengaturan.writeMQTTUsername(server.arg(form.getArg(ARG_MQTT_USERNAME)));
      }

      if(pengaturan.readMQTTPassword() != server.arg(form.getArg(ARG_MQTT_PASSWORD))){
        pengaturan.writeMQTTPassword(server.arg(form.getArg(ARG_MQTT_PASSWORD)));
      }

      message = "Pengaturan koneksi telah tersimpan.";
    }else{
      message = error_message;
    }
  }
  server.send(200, "text/html", form.pengaturanKoneksi("/", message, "/", "/pengguna", "/firmware", "/login?disconnect=1", pengaturan.readWifiSSID(), pengaturan.readWifiPassword(), pengaturan.readMQTTBroker(), pengaturan.readMQTTUsername(), pengaturan.readMQTTPassword()));
}

void handlePengguna() {
  /*
  Spesifikasi :
  - Apabila pengguna telah login server membuka halaman /pengguna server akan memanggil prosedur ini,
    sehingga pengguna dapat masuk ke halaman pengaturan pengguna.
  - Apabila pengguna belum login server akan memanggil prosedur handleLogin(),
    sehingga pengguna diminta untuk login terlebih dahulu sebelum masuk ke halaman ini.
  */

  String message = "";
  if (!is_authentified()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }

  if (server.hasArg(form.getArg(ARG_USERNAME)) && server.hasArg(form.getArg(ARG_PASSWORD)) && server.hasArg(form.getArg(ARG_KONFIRMASI_PASSWORD))) {
    String error_message = "";
    if(server.arg(form.getArg(ARG_USERNAME)) == ""){
      error_message += "Username tidak boleh kosong.\\n";
    }

    if(server.arg(form.getArg(ARG_PASSWORD)) == ""){
      error_message += "Password tidak boleh kosong.\\n";
    }

    if(server.arg(form.getArg(ARG_KONFIRMASI_PASSWORD)) == ""){
      error_message += "Konfirmasi password tidak boleh kosong.\\n";
    }

    if(server.arg(form.getArg(ARG_PASSWORD)) != server.arg(form.getArg(ARG_KONFIRMASI_PASSWORD))){
      error_message += "Konfirmasi password tidak sesuai.\\n";
    }

    if(error_message == ""){
      if(pengaturan.readUsername() != server.arg(form.getArg(ARG_USERNAME))){
        pengaturan.writeUsername(server.arg(form.getArg(ARG_USERNAME)));
      }

      if(pengaturan.readPassword() != server.arg(form.getArg(ARG_PASSWORD))){
        pengaturan.writePassword(server.arg(form.getArg(ARG_PASSWORD)));
      }

      message = "Pengaturan pengguna telah tersimpan.";
    }else{
      message = error_message;
    }
  }
  server.send(200, "text/html", form.pengaturanPengguna("/pengguna", message, "/", "/pengguna", "/firmware", "/login?disconnect=1", pengaturan.readUsername(), pengaturan.readPassword(), pengaturan.readPassword()));
}

void handleFirmware() {
  /*
  Spesifikasi :
  - Apabila pengguna telah login server membuka halaman /pengguna server akan memanggil prosedur ini,
    sehingga pengguna dapat masuk ke halaman informasi firmware.
  - Apabila pengguna belum login server akan memanggil prosedur handleLogin(),
    sehingga pengguna diminta untuk login terlebih dahulu sebelum masuk ke halaman ini.
  */

  String message = "";
  if (!is_authentified()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }  

  FIRMWARE_IN informasi_firmware;
  informasi_firmware.firmwareName = firmware_update.getFirmwareName();
  informasi_firmware.firmwareDescription = firmware_update.getFirmwareDescription();
  informasi_firmware.firmwareVersion = firmware_update.getFirmwareVersion();
  informasi_firmware.legalCopyright = firmware_update.getLegalCopyright();
  informasi_firmware.companyName = firmware_update.getCompanyName();
  informasi_firmware.firmwareType = firmware_update.getFirmwareType();
  server.send(200, "text/html", form.informasiFirmware(informasi_firmware, "/", "/pengguna", "/firmware", "/login?disconnect=1"));
}

void handleNotFound() {
  /*
  Spesifikasi :
  - Apabila pengguna membuka halaman selain /login, /, dan /pengaturan server akan menjalankan prosedur ini,
    sehingga akan muncul status "Halaman tida ditemukan." di web browser.
  */

  String message = "Halaman tidak ditemukan.\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
//------------------------------------------------------------------------------

//MQTT
void setup_wifi() {
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk keneksi perangkat ke Wi-Fi.
  */

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(pengaturan.readWifiSSID());

  WiFi.begin(pengaturan.readWifiSSID().c_str(), pengaturan.readWifiPassword().c_str());

  while (WiFi.status() != WL_CONNECTED) {
    if(jumper.read() == LOW){
      if(can_restart == true){
        ESP.restart();
      }
    }
    Serial.print(".");
    if(interrupt_update == false){
      led.rainbow(5);
    }else{
      delay(1000);
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  /*
  Spesifikasi :
  - Prosedur ini akan terpanggil apabila ada perubahan topic yang telah di subscribe perangkat.
  */

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String _topic = "";
  for(int i = 0; i < 2; i++){
    _topic += (char)topic[i];
  }
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == '1') {
    if(_topic == "r"){
      relay.phase.setClosedCircuit();
      relay.neutral.setClosedCircuit();
    }
  } else {
    if(_topic == "r"){
      relay.phase.setOpenCircuit();
      relay.neutral.setOpenCircuit();
    }
  }
}

void reconnect() {
  /*
  Spesifikasi :
  - Apabila koneksi MQTT Broker terputus perangkat akan memanggil prosedur ini. 
  */

  while (!MQTT.connected()) {
    if(jumper.read() == LOW){
      if(can_restart == true){
        ESP.restart();
      }
    }
    
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (MQTT.connect(clientId.c_str(), pengaturan.readMQTTUsername().c_str(), pengaturan.readMQTTPassword().c_str())) {
      Serial.println("connected");
      MQTT.subscribe("r");
    } else {
      Serial.print("failed, rc=");
      Serial.print(MQTT.state());
      Serial.println(" try again in 1 seconds");
      if(interrupt_update == false){
        led.rainbow(14);
      }else{
        delay(5000);
      }
    }
  }
}
//------------------------------------------------------------------------------

//FirmwareCrypt
void callbackUpdateProcess(FIRMWARECRYPT_PROCESS proc_info, FIRMWARECRYPT_PROCESS_MESSAGE proc_message, String message){
  /*
  Spesifikasi :
  - Prosedur ini memberikan informasi proses update firmware via SD Card, sehingga pengguna dapat memantau
    proses update firmware perangkat.
  - SD_CARD_DETECTED = Ketika pengguna memasang SD Card.
  - FIRMWARECRYPT_FILE_EXISTS = Apabila firmware ditemukan di SD Card.
  - FIRMWARECRYPT_FILE_NOT_EXISTS = Apabila firmware tidak ditemukan di SD Card.
  - VALID_FIRMWARECRYPT_FILE = Apabila firmware sesuai.
  - INVALID_FIRMWARECRYPT_FILE = Apabila firmware tidak sesuai.
  - FIRMWARE_TYPE_UPDATE_VERSION = file firmware digunakan untuk update firmware terbaru.
  - FIRMWARE_TYPE_ROLLBACK_VERSION = file firmware digunakan untuk kembali ke versi firmware awal (release 1).
  - VALID_FIRMWARE_HASH = Apabila firmware tidak mengalami corrupt data.
  - INVALID_FIRMWARE_HASH = Apabila firmware mengalami corrupt data.
  - UPDATE_COMPLETE = Apabila proses update telah selesai.
  - WAITING_REMOVE_SDCARD = Menunggu pengguna melepas SD Card.
  */

  if((proc_info == READ_SDCARD) && (proc_message == SD_CARD_DETECTED)){
    if(interrupt_update == false){
      interrupt_update = true;
    }

    led.setBlack();
    delay(100);
    led.rainbow(5);
  }

  if((proc_info == READ_SDCARD) && (proc_message == SD_CARD_NOT_DETECTED)){
    if(interrupt_update == true){
      interrupt_update = false;
    }
  }

  if((proc_info == READ_FIRMWARECRYPT_FILE) && (proc_message == FIRMWARECRYPT_FILE_EXISTS)){
    led.setBlack();
    delay(100);
    led.rainbow(5);
    delay(100);
  }

  if((proc_info == READ_FIRMWARECRYPT_FILE) && (proc_message == FIRMWARECRYPT_FILE_NOT_EXISTS)){
    led.setBlack();
    delay(100);
    led.rainbow(5);
    delay(2000);
  }

  if((proc_info == READ_FIRMWARECRYPT_FILE) && (proc_message == VALID_FIRMWARECRYPT_FILE)){
    led.setBlack();
    delay(100);
    led.rainbow(5);
    delay(100);
  }

  if((proc_info == READ_FIRMWARECRYPT_FILE) && (proc_message == INVALID_FIRMWARECRYPT_FILE)){
    led.setBlack();
    delay(100);
    led.setRed();
    delay(2000);
  }

  if(proc_info == READ_FIRMWARECRYPT_FILE){
    if(proc_message == FIRMWARE_TYPE_UPDATE_VERSION){
      led.setBlack();
      delay(100);
      led.blink(0, 255, 0, 10, 100);
    }else{
      led.setBlack();
      delay(100);
    }
  }

  if((proc_info == DECRYPT_AND_VERIF_HASH) && (proc_message == VALID_FIRMWARE_HASH)){
    led.setBlack();
    delay(100);
    led.setGreen();
    delay(100);
  }

  if((proc_info == DECRYPT_AND_VERIF_HASH) && (proc_message == INVALID_FIRMWARE_HASH)){
    led.setBlack();
    delay(100);
    led.setRed();
    delay(2000);
  }

  if((proc_info == DECRYPT_AND_UPDATE_FIRMWARE) && (proc_message == UPDATE_COMPLETE)){
    led.setBlack();
    delay(100);
    led.setGreen();
    delay(2000);
    led.setBlack();
    delay(100);
  }

  if((proc_info == REMOVE_SDCARD) && (proc_message == WAITING_REMOVE_SDCARD)){
    led.rainbow(10);
    led.blink(0, 255, 0, 10, 100);
  }

  if((proc_info == REMOVE_SDCARD) && (proc_message == SDCARD_REMOVED)){
    led.setBlack();
    delay(1000);
  }
}

void callbackRollbackProcess(FIRMWARECRYPT_PROCESS proc_info, FIRMWARECRYPT_PROCESS_MESSAGE proc_message, String message){
  /*
  Spesifikasi :
  - Prosedur ini memberikan informasi proses rollback firmware via SD Card, sehingga pengguna dapat memantau
    proses update firmware perangkat.
  - SD_CARD_DETECTED = Ketika pengguna memasang SD Card.
  - FIRMWARECRYPT_FILE_EXISTS = Apabila firmware ditemukan di SD Card.
  - FIRMWARECRYPT_FILE_NOT_EXISTS = Apabila firmware tidak ditemukan di SD Card.
  - VALID_FIRMWARECRYPT_FILE = Apabila firmware sesuai.
  - INVALID_FIRMWARECRYPT_FILE = Apabila firmware tidak sesuai.
  - FIRMWARE_TYPE_UPDATE_VERSION = file firmware digunakan untuk update firmware terbaru.
  - FIRMWARE_TYPE_ROLLBACK_VERSION = file firmware digunakan untuk kembali ke versi firmware awal (release 1).
  - VALID_FIRMWARE_HASH = Apabila firmware tidak mengalami corrupt data.
  - INVALID_FIRMWARE_HASH = Apabila firmware mengalami corrupt data.
  - UPDATE_COMPLETE = Apabila proses update telah selesai.
  - WAITING_REMOVE_SDCARD = Menunggu pengguna melepas SD Card.
  */

  if((proc_info == READ_SDCARD) && (proc_message == SD_CARD_DETECTED)){
    if(interrupt_update == false){
      interrupt_update = true;
    }

    led.setBlack();
    delay(100);
    led.rainbow(5);
  }

  if((proc_info == READ_SDCARD) && (proc_message == SD_CARD_NOT_DETECTED)){
    if(interrupt_update == true){
      interrupt_update = false;
    }
  }

  if((proc_info == READ_FIRMWARECRYPT_FILE) && (proc_message == FIRMWARECRYPT_FILE_EXISTS)){
    led.setBlack();
    delay(100);
    led.rainbow(5);
    delay(100);
  }

  if((proc_info == READ_FIRMWARECRYPT_FILE) && (proc_message == FIRMWARECRYPT_FILE_NOT_EXISTS)){
    led.setBlack();
    delay(100);
    led.rainbow(5);
    delay(2000);
  }

  if((proc_info == READ_FIRMWARECRYPT_FILE) && (proc_message == VALID_FIRMWARECRYPT_FILE)){
    led.setBlack();
    delay(100);
    led.rainbow(5);
    delay(100);
  }

  if((proc_info == READ_FIRMWARECRYPT_FILE) && (proc_message == INVALID_FIRMWARECRYPT_FILE)){
    led.setBlack();
    delay(100);
    led.setRed();
    delay(2000);
  }

  if(proc_info == READ_FIRMWARECRYPT_FILE){
    if(proc_message == FIRMWARE_TYPE_ROLLBACK_VERSION){
      led.setBlack();
      delay(100);
      led.blink(0, 0, 255, 10, 100);
    }else{
      led.setBlack();
      delay(100);
    }
  }

  if((proc_info == DECRYPT_AND_VERIF_HASH) && (proc_message == VALID_FIRMWARE_HASH)){
    led.setBlack();
    delay(100);
    led.setBlue();
    delay(100);
  }

  if((proc_info == DECRYPT_AND_VERIF_HASH) && (proc_message == INVALID_FIRMWARE_HASH)){
    led.setBlack();
    delay(100);
    led.setRed();
    delay(2000);
  }

  if((proc_info == DECRYPT_AND_UPDATE_FIRMWARE) && (proc_message == UPDATE_COMPLETE)){
    led.setBlack();
    delay(100);
    led.setBlue();
    delay(2000);
    led.setBlack();
    delay(100);
  }

  if((proc_info == REMOVE_SDCARD) && (proc_message == WAITING_REMOVE_SDCARD)){
    led.rainbow(10);
    led.blink(0, 0, 255, 10, 100);
  }

  if((proc_info == REMOVE_SDCARD) && (proc_message == SDCARD_REMOVED)){
    led.setBlack();
    delay(1000);
  }
}

void firmwareCryptTask(void * pvParameters){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menangani proses update firmware via SD Card. 
  - Prosedur ini dieksekusi secara terus-menerus dengan interval 1000 milli detik.
  */

  while(true){
    can_restart = false;
    Serial.println("Update");
    firmware_update.handleUpdate();
    Serial.println("Rollback");
    firmware_update.handleRollback();
    can_restart = true;
    delay(1000);
  }
}
//------------------------------------------------------------------------------

//Setup
void setup() {
  /*
  Spesifikasi :
   - Prosedur ini dipanggil sebelum prosedur firmwareCryptTask(void * pvParameters) dan prosedur loop().
   - Prosedur ini digunakan untuk konfigurasi Input/Output perangkat.
  */
 
  led.rainbow(10);
  Serial.begin(9600);

  interrupt_update = false;

  randomSeed(micros()); //Inisialisasi random

  pengaturan.begin();
  if(pengaturan.readUsername() == ""){
    pengaturan.writeUsername("admin");
  }
  if(pengaturan.readPassword() == ""){
    pengaturan.writePassword("admin");
  }

  firmware_update.setCallbackProcess(callbackUpdateProcess, callbackRollbackProcess); 
  xTaskCreatePinnedToCore(firmwareCryptTask, "firmware_crypt_task", 10000, NULL, 1, &firmware_crypt_task, 1);
  
  if(jumper.read() == HIGH){
    setup_wifi();
    IPAddress mqtt_server;
    mqtt_server.fromString(pengaturan.readMQTTBroker());
    MQTT.setServer(mqtt_server, 1883);
    MQTT.setCallback(callback);
    led.blink(0, 255, 0, 10, 100);
    execute_main = true;
  }else{
    led.blink(125, 0, 125, 10, 100);
    WiFi.softAP(ap_ssid, ap_password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    session = generateSession();
    server.on("/", handleKoneksi);
    server.on("/pengguna", handlePengguna);
    server.on("/firmware", handleFirmware);
    server.on("/login", handleLogin);
    server.onNotFound(handleNotFound);

    const char * headerkeys[] = {"User-Agent", "Cookie"} ;
    size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
    server.collectHeaders(headerkeys, headerkeyssize);
    server.begin();
    Serial.println("HTTP server started");
    led.blink(0, 0, 255, 10, 100);
    execute_main = false;
  }
}
//------------------------------------------------------------------------------

//Main Program
void loop(){
  /*
  Spesifikasi :
  - Prosedur ini adalah program utama.
  - Prosedur ini dieksekusi secara terus-menerus dengan interval 10 milli detik.
  */

  if(execute_main == true){
    while(true){
      if (!MQTT.connected()) {
        reconnect();
      }
    
      MQTT.loop();

      if(jumper.read() == LOW){
        if(can_restart == true){
          ESP.restart();
        }
      }
      delay(10);  
    }
  }else{
    while(true){
      server.handleClient();

      if(jumper.read() == HIGH){
        if(can_restart == true){
          ESP.restart();
        }
      }
    }
  }
}
//------------------------------------------------------------------------------
