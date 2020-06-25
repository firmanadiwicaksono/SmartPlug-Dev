/*
 * -----------------------------------------------------------------------------
 * Firmware Crypt Framework for Update Firmware Via SD Card With Encryption
 * Advanced Encryption Standard 256 Bit Cipher Block Chaining (AES 256-Bit CBC)
 * Copyright (c) 2020 Firman Adi Wicaksono. All rights reserved.
 * 
 * LICENSE TERMS
 * 
 * The redistribution and use of this software (with or without changes)
 * is allowed without the payment of fees or royalties provided that:
 * 
 *  1. source code distributions include the above copyright notice, this
 *     list of conditions and the following disclaimer;
 *    
 *  2. binary distributions include the above copyright notice, this list
 *     of conditions and the following disclaimer in their documentation;
 * 
 *  3. the name of the copyright holder is not used to endorse products
 *     built using this software without specific written permission.
 *     
 * DISCLAIMER
 * 
 * This software is provided 'as is' with no explicit or implied warranties
 * in respect of its properties, including, but not limited to, correctness
 * and/or fitness for purpose.
 * -----------------------------------------------------------------------------
 */

#include "FirmwareCrypt.h"
#include "FirmwareInformation/FirmwareInformation.h"
#include "../lib/AES/AES.h"
#include "../lib/SHA256/sha256.h"
#include <Arduino.h>
#include <Update.h>
#include <SD.h>
#include <SPI.h>

//Private
String FirmwareCrypt::partFile(int part){
  /*
  Spesifikasi : 
  - Fungsi ini dugunakan untuk membuat part filename firmware.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  String str_filename = firmware_filename;
  String str_part = "000";  
  String str_number = "";
  str_number += part;
  if(str_number.length() <= 3 ){  
    str_part = str_part.substring(0, 3 - str_number.length());
    str_part += str_number;  
  }else{
    str_part = str_number; 
  }

  str_filename += str_part;

  return str_filename;
}

void FirmwareCrypt::AES256Decrypt(byte* cipher, byte* plain, const byte* key, const byte* iv)
{
  /*
  Spesifikasi : 
  - prosedur ini digunakan untuk mendekripsi file firmware yang terenkripsi.
  */

    AES aes;
    byte tmp_key[32];
    byte tmp_iv[16];

    for(int i = 0; i < 32; i++)
        tmp_key[i] = key[i];
        
    for(int i = 0; i < 16; i++)
        tmp_iv[i] = iv[i];
        
    aes.set_key (tmp_key, 256);
    aes.cbc_decrypt (cipher, plain, 4, tmp_iv) ;
}
//------------------------------------------------------------------------------

//Public
FirmwareCrypt::FirmwareCrypt(){
  /*
  Spesifikasi :
  - Constructor ini digukanan untuk inisialiasi kelas.
  */

  debug_mode = true;
  setCallbackProcess(NULL, NULL);
}

String FirmwareCrypt::getFirmwareName(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk menampilkan Firmware Name.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  if(debug_mode == true){
    Serial.print("Debug --> Firmware Name : ");
    Serial.println(firmware_name);
  }
  
  return firmware_name;
}

String FirmwareCrypt::getFirmwareDescription(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk menampilkan Firmware Description.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  if(debug_mode == true){
    Serial.print("Debug --> Firmware Description : ");
    Serial.println(firmware_description);
  }
  
  return firmware_description;
}

String FirmwareCrypt::getFirmwareVersion(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk menampilkan Firmware Version.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  if(debug_mode == true){
    Serial.print("Debug --> Firmware Version : ");
    Serial.println(firmware_version);
  }
  
  return firmware_version;
}

String FirmwareCrypt::getLegalCopyright(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk menampilkan Legal Copyright.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  if(debug_mode == true){
    Serial.print("Debug --> Legal Copyright : ");
    Serial.println(legal_copyright);
  }
  
  return legal_copyright;
}

String FirmwareCrypt::getCompanyName(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk menampilkan Company Name.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  if(debug_mode == true){
    Serial.print("Debug --> Company Name : ");
    Serial.println(company_name);
  }
  
  return company_name;
}

String FirmwareCrypt::getFirmwareType(){
  /*
  Spesifikasi :
  - Fungsi ini digunakan untuk menampilkan Firmware Type.
  - Keluaran dari fungsi ini berupa objek kelas String.
  */

  if(debug_mode == true){
    Serial.print("Debug --> Firmware Type : ");
    Serial.println(firmware_type);
  }
  
  return firmware_type;
}

void FirmwareCrypt::setCallbackProcess(FIRMWARECRYPT_CALLBACK_UPDATE_SIGNATURE, FIRMWARECRYPT_CALLBACK_ROLLBACK_SIGNATURE){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menginisialisasi pointer prosedur FIRMWARECRYPT_CALLBACK_UPDATE_SIGNATURE
    dan FIRMWARECRYPT_ROLLBACK_UPDATE_SIGNATURE.
  */

  this->callbackUpdate = callbackUpdate;
  this->callbackRollback = callbackRollback;
}

void FirmwareCrypt::handleUpdate(){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menangani proses update firmware via SD Card.
  */
 
  if(debug_mode == true){
    Serial.println("Debug --> Read SD Card...");
  }
  
  if(callbackUpdate != NULL){ 
    callbackUpdate(WAITING_PROCESS, WAITING_PROCESS_MESSAGE, "");
  }
  
  if (SD.begin()) {
    if(debug_mode == true){
      Serial.println("Debug --> SD Card detected...");
    }
    
    if(callbackUpdate != NULL){ 
      callbackUpdate(READ_SDCARD, SD_CARD_DETECTED, "");
    }

    if(callbackUpdate != NULL){ 
      callbackUpdate(READ_FIRMWARECRYPT_FILE, WAITING_PROCESS_MESSAGE, "");
    }
    
    if(SD.exists(firmware_info_filename) == true){
      if(callbackUpdate != NULL){ 
        callbackUpdate(READ_FIRMWARECRYPT_FILE, FIRMWARECRYPT_FILE_EXISTS, "");
      }
    
      File firmware_info = SD.open(firmware_info_filename); 
      
      firmware_info.seek(firmware_info.size() - 1);
      byte last_byte_length[1];
      firmware_info.read(last_byte_length, 1);

      firmware_info.seek(0);
      String firmware_info_str = "";
      int count = firmware_info.available() - 1;
      while (count > 0) {
        byte buffer_firmware_info[aes_block_size], buffer_decrypt[aes_block_size];
        firmware_info.read(buffer_firmware_info, sizeof(buffer_firmware_info)); 
        AES256Decrypt(buffer_firmware_info, buffer_decrypt, firmwarecrypt_encrypt_key, firmwarecrypt_encrypt_iv);

        int buffer_length = 0;
        if(count > sizeof(buffer_firmware_info)){
          buffer_length = sizeof(buffer_firmware_info); 
        }else{
          buffer_length = last_byte_length[0];
        }

        for(int i = 0; i < buffer_length; i++){
          firmware_info_str += (char)buffer_decrypt[i];
        }

        count -= sizeof(buffer_firmware_info);
      }

      if(debug_mode == true){
        Serial.print("Debug --> firmware_info_str : ");
        Serial.println(firmware_info_str);
      }

      if(info.parse(firmware_info_str) == true){
        if(debug_mode == true){
          Serial.println("Debug --> Parse firmware_info_str complete...");
          Serial.print("Debug --> Buffer Check : ");
          Serial.println(info.getBufferCheck());
          Serial.print("Debug --> Hash : ");
          Serial.println(info.getHash());
          Serial.print("Debug --> Firmware Name : ");
          Serial.println(info.getFirmwareName());
          Serial.print("Debug --> Firmware Description : ");
          Serial.println(info.getFirmwareDescription());
          Serial.print("Debug --> Firmware Version : ");
          Serial.println(info.getFirmwareVersion());
          Serial.print("Debug --> Legal Copyright : ");
          Serial.println(info.getLegalCopyright());
          Serial.print("Debug --> Company Name : ");
          Serial.println(info.getCompanyName());
          Serial.print("Debug --> Firmware Type : ");
          Serial.println(info.getFirmwareType());

          String str_buffer_check = info.getBufferCheck();
          int n = 0;
          for(int i = 0; i < buffer_check.length(); i++){
            if(str_buffer_check[i] == buffer_check[i]){
              n++;
            }
          }

          if(n == buffer_check.length()){
            if(debug_mode == true){
              Serial.println("Debug --> Valid firmwarecrypt file...");   
            }

            if(callbackUpdate != NULL){ 
              callbackUpdate(READ_FIRMWARECRYPT_FILE, VALID_FIRMWARECRYPT_FILE, "");
            }

            if(info.getFirmwareType() == "Update Version"){
              if(debug_mode == true){
                Serial.println("Debug --> Firmware type is update version...");   
              }

              if(callbackUpdate != NULL){ 
                callbackUpdate(READ_FIRMWARECRYPT_FILE, FIRMWARE_TYPE_UPDATE_VERSION, "");
              }

              if(debug_mode == true){
                Serial.println("Debug --> Verif firmware hash...");   
              }
              
              if(callbackUpdate != NULL){ 
                callbackUpdate(DECRYPT_AND_VERIF_HASH, WAITING_PROCESS_MESSAGE, "");
              }

              Sha256* sha256Instance=new Sha256();
              BYTE hash[SHA256_BLOCK_SIZE];
              char texthash[2*SHA256_BLOCK_SIZE+1];
              
              int file_number = 1;
              while(SD.exists(partFile(file_number)) == true){
                if(debug_mode == true){
                  Serial.print("Debug --> Verif firmware hash : "); 
                  Serial.println(partFile(file_number));  
                }

                if(callbackUpdate != NULL){ 
                  callbackUpdate(DECRYPT_AND_VERIF_HASH, WAITING_PROCESS_MESSAGE, partFile(file_number));
                }
                
                File firmware = SD.open(partFile(file_number)); 
        
                firmware.seek(firmware.size() - 1);
                byte last_byte_length[1];
                firmware.read(last_byte_length, 1);
          
                firmware.seek(0);
                int count = firmware.available() - 1;
                while (count > 0) {
                  byte buffer_firmware[aes_block_size], buffer_decrypt[aes_block_size];
                  firmware.read(buffer_firmware, sizeof(buffer_firmware)); 
                  AES256Decrypt(buffer_firmware, buffer_decrypt, update_encrypt_key, update_encrypt_iv);
          
                  int buffer_length = 0;
                  if(count > sizeof(buffer_firmware)){
                    buffer_length = sizeof(buffer_firmware); 
                  }else{
                    buffer_length = last_byte_length[0];
                  }
          
                  sha256Instance->update(buffer_decrypt, buffer_length);
          
                  count -= sizeof(buffer_firmware);
                }
                file_number++;  
              }

              sha256Instance->final(hash);
              for(int i=0; i<SHA256_BLOCK_SIZE; ++i){
                sprintf(texthash+2*i, "%02X", hash[i]);
              }

              if(debug_mode == true){
                Serial.print("Debug --> SHA-256 Hash : "); 
                Serial.println(texthash);  
              }

              String str_hash = info.getHash();
              int n = 0;
              for(int i = 0; i < str_hash.length(); i++){
                if(texthash[i] == str_hash[i]){
                  n++;
                }
              }

              if(n == str_hash.length()){
                if(debug_mode == true){
                  Serial.println("Debug --> Valid firmware hash...");  
                }

                if(callbackUpdate != NULL){ 
                  callbackUpdate(DECRYPT_AND_VERIF_HASH, VALID_FIRMWARE_HASH, str_hash);
                }

                if(debug_mode == true){
                  Serial.println("Debug --> Update firmware...");   
                }
                
                if(callbackUpdate != NULL){ 
                  callbackUpdate(DECRYPT_AND_UPDATE_FIRMWARE, WAITING_PROCESS_MESSAGE, "");
                }
    
                uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
                if(debug_mode == true){
                  Serial.print("Debug --> MAX SKETCH SPACE : ");
                  Serial.println(maxSketchSpace);
                }
                
                if (Update.begin(maxSketchSpace)) {
                  int file_number = 1;
                  while(SD.exists(partFile(file_number)) == true){
                    if(debug_mode == true){
                      Serial.print("Debug --> Update firmware : "); 
                      Serial.println(partFile(file_number));  
                    }
      
                    if(callbackUpdate != NULL){ 
                    callbackUpdate(DECRYPT_AND_UPDATE_FIRMWARE, WAITING_PROCESS_MESSAGE, partFile(file_number));
                    }
                    
                    File firmware = SD.open(partFile(file_number)); 
            
                    firmware.seek(firmware.size() - 1);
                    byte last_byte_length[1];
                    firmware.read(last_byte_length, 1);
              
                    firmware.seek(0);
                    int count = firmware.available() - 1;
                    while (count > 0) {
                      byte buffer_firmware[aes_block_size], buffer_decrypt[aes_block_size];
                      firmware.read(buffer_firmware, sizeof(buffer_firmware)); 
                      AES256Decrypt(buffer_firmware, buffer_decrypt, update_encrypt_key, update_encrypt_iv);
              
                      int buffer_length = 0;
                      if(count > sizeof(buffer_firmware)){
                        buffer_length = sizeof(buffer_firmware); 
                      }else{
                        buffer_length = last_byte_length[0];
                      }
              
                      Update.write(buffer_decrypt, buffer_length);
              
                      count -= sizeof(buffer_firmware);
                    }
                    file_number++;  
                  }
      
                  if(Update.end(true) == true){
                    if(debug_mode == true){
                      Serial.println("Debug --> Update complete...");   
                    }
                      
                    if(callbackUpdate != NULL){ 
                      callbackUpdate(DECRYPT_AND_UPDATE_FIRMWARE, UPDATE_COMPLETE, "");
                    }
      
                    if(SD.begin()){
                      if(debug_mode == true){
                        Serial.println("Debug --> Waiting Remove SD Card...");   
                      }
                        
                      if(callbackUpdate != NULL){ 
                        callbackUpdate(REMOVE_SDCARD, WAITING_REMOVE_SDCARD, "");
                      }
    
                      SD.end();
                    }
      
                    while(SD.begin()){
                      if(debug_mode == true){
                        Serial.print(".");
                      }

                      if(callbackUpdate != NULL){ 
                        callbackUpdate(REMOVE_SDCARD, WAITING_REMOVE_SDCARD, "");
                      }
                      
                      SD.end();
                      delay(1000);
                    }
      
                    if(debug_mode == true){
                      Serial.println("Debug --> SD Card Removed...");   
                    }
                        
                    if(callbackUpdate != NULL){ 
                      callbackUpdate(REMOVE_SDCARD, SDCARD_REMOVED, "");
                    }
      
                    if(debug_mode == true){
                      Serial.println("Debug --> Restart Device...");   
                    }
                        
                    if(callbackUpdate != NULL){ 
                      callbackUpdate(RESTART_DEVICE, WAITING_PROCESS_MESSAGE, "");
                    }
      
                    ESP.restart();
                    
                  }else{
                    if(debug_mode == true){
                      Serial.println("Debug --> Update failed...");   
                    }
                      
                    if(callbackUpdate != NULL){ 
                      callbackUpdate(DECRYPT_AND_UPDATE_FIRMWARE, UPDATE_FAILED, "");
                    }
    
                    SD.end();
                  }
                }else{
                  if(debug_mode == true){
                    Serial.println("Debug --> ERROR BEGIN UPDATE...");
                  }

                  SD.end();
                }
              }else{
                if(debug_mode == true){
                  Serial.println("Debug --> Invalid firmware hash...");  
                }

                if(callbackUpdate != NULL){ 
                  callbackUpdate(DECRYPT_AND_VERIF_HASH, INVALID_FIRMWARE_HASH, "");
                }

                SD.end();
              }
            }else{
              if(debug_mode == true){
                Serial.println("Debug --> Firmware type is not update version...");   
              }

              if(callbackUpdate != NULL){ 
                callbackUpdate(READ_FIRMWARECRYPT_FILE, FIRMWARE_TYPE_ROLLBACK_VERSION, "");
              }
            }
          }else{
            if(debug_mode == true){
              Serial.println("Debug --> Invalid firmwarecrypt file...");    
            }
            
            if(callbackUpdate != NULL){ 
              callbackUpdate(READ_FIRMWARECRYPT_FILE, INVALID_FIRMWARECRYPT_FILE, "");
            }

            SD.end();
          }
        }
      }else{
        if(debug_mode == true){
          Serial.println("Debug --> Parse firmware_info_str failed...");
          Serial.println("Debug --> Invalid firmwarecrypt file...");
        }

        if(callbackUpdate != NULL){ 
          callbackUpdate(READ_FIRMWARECRYPT_FILE, INVALID_FIRMWARECRYPT_FILE, "");
        }

        SD.end();
      }
    }else{
      if(debug_mode == true){
        Serial.println("Debug --> Firmwarecrypt file not exists...");
      }
        
      if(callbackUpdate != NULL){ 
        callbackUpdate(READ_FIRMWARECRYPT_FILE, FIRMWARECRYPT_FILE_NOT_EXISTS, "");
      }

      SD.end();
    }
  }else{
    if(debug_mode == true){
      Serial.println("Debug --> SD Card not detected...");
    }
    
    if(callbackUpdate != NULL){ 
      callbackUpdate(READ_SDCARD, SD_CARD_NOT_DETECTED, "");
    }
  }
}

void FirmwareCrypt::handleRollback(){
  /*
  Spesifikasi :
  - Prosedur ini digunakan untuk menangani proses rollback firmware via SD Card.
  */
 
  if(debug_mode == true){
    Serial.println("Debug --> Read SD Card...");
  }
  
  if(callbackRollback != NULL){ 
    callbackRollback(WAITING_PROCESS, WAITING_PROCESS_MESSAGE, "");
  }
  
  if (SD.begin()) {
    if(debug_mode == true){
      Serial.println("Debug --> SD Card detected...");
    }
    
    if(callbackRollback != NULL){ 
      callbackRollback(READ_SDCARD, SD_CARD_DETECTED, "");
    }

    if(callbackRollback != NULL){ 
      callbackRollback(READ_FIRMWARECRYPT_FILE, WAITING_PROCESS_MESSAGE, "");
    }
    
    if(SD.exists(firmware_info_filename) == true){
      if(callbackRollback != NULL){ 
        callbackRollback(READ_FIRMWARECRYPT_FILE, FIRMWARECRYPT_FILE_EXISTS, "");
      }
    
      File firmware_info = SD.open(firmware_info_filename); 
      
      firmware_info.seek(firmware_info.size() - 1);
      byte last_byte_length[1];
      firmware_info.read(last_byte_length, 1);

      firmware_info.seek(0);
      String firmware_info_str = "";
      int count = firmware_info.available() - 1;
      while (count > 0) {
        byte buffer_firmware_info[aes_block_size], buffer_decrypt[aes_block_size];
        firmware_info.read(buffer_firmware_info, sizeof(buffer_firmware_info)); 
        AES256Decrypt(buffer_firmware_info, buffer_decrypt, firmwarecrypt_encrypt_key, firmwarecrypt_encrypt_iv);

        int buffer_length = 0;
        if(count > sizeof(buffer_firmware_info)){
          buffer_length = sizeof(buffer_firmware_info); 
        }else{
          buffer_length = last_byte_length[0];
        }

        for(int i = 0; i < buffer_length; i++){
          firmware_info_str += (char)buffer_decrypt[i];
        }

        count -= sizeof(buffer_firmware_info);
      }

      if(debug_mode == true){
        Serial.print("Debug --> firmware_info_str : ");
        Serial.println(firmware_info_str);
      }

      if(info.parse(firmware_info_str) == true){
        if(debug_mode == true){
          Serial.println("Debug --> Parse firmware_info_str complete...");
          Serial.print("Debug --> Buffer Check : ");
          Serial.println(info.getBufferCheck());
          Serial.print("Debug --> Hash : ");
          Serial.println(info.getHash());
          Serial.print("Debug --> Firmware Name : ");
          Serial.println(info.getFirmwareName());
          Serial.print("Debug --> Firmware Description : ");
          Serial.println(info.getFirmwareDescription());
          Serial.print("Debug --> Firmware Version : ");
          Serial.println(info.getFirmwareVersion());
          Serial.print("Debug --> Legal Copyright : ");
          Serial.println(info.getLegalCopyright());
          Serial.print("Debug --> Company Name : ");
          Serial.println(info.getCompanyName());
          Serial.print("Debug --> Firmware Type : ");
          Serial.println(info.getFirmwareType());

          String str_buffer_check = info.getBufferCheck();
          int n = 0;
          for(int i = 0; i < buffer_check.length(); i++){
            if(str_buffer_check[i] == buffer_check[i]){
              n++;
            }
          }

          if(n == buffer_check.length()){
            if(debug_mode == true){
              Serial.println("Debug --> Valid firmwarecrypt file...");   
            }

            if(callbackRollback != NULL){ 
              callbackRollback(READ_FIRMWARECRYPT_FILE, VALID_FIRMWARECRYPT_FILE, "");
            }

            if(info.getFirmwareType() == "Rollback Version"){
              if(debug_mode == true){
                Serial.println("Debug --> Firmware type is rollback version...");   
              }

              if(callbackRollback != NULL){ 
                callbackRollback(READ_FIRMWARECRYPT_FILE, FIRMWARE_TYPE_ROLLBACK_VERSION, "");
              }

              if(debug_mode == true){
                Serial.println("Debug --> Verif firmware hash...");   
              }
              
              if(callbackRollback != NULL){ 
                callbackRollback(DECRYPT_AND_VERIF_HASH, WAITING_PROCESS_MESSAGE, "");
              }

              Sha256* sha256Instance=new Sha256();
              BYTE hash[SHA256_BLOCK_SIZE];
              char texthash[2*SHA256_BLOCK_SIZE+1];
              
              int file_number = 1;
              while(SD.exists(partFile(file_number)) == true){
                if(debug_mode == true){
                  Serial.print("Debug --> Verif firmware hash : "); 
                  Serial.println(partFile(file_number));  
                }

                if(callbackRollback != NULL){ 
                  callbackRollback(DECRYPT_AND_VERIF_HASH, WAITING_PROCESS_MESSAGE, partFile(file_number));
                }
                
                File firmware = SD.open(partFile(file_number)); 
        
                firmware.seek(firmware.size() - 1);
                byte last_byte_length[1];
                firmware.read(last_byte_length, 1);
          
                firmware.seek(0);
                int count = firmware.available() - 1;
                while (count > 0) {
                  byte buffer_firmware[aes_block_size], buffer_decrypt[aes_block_size];
                  firmware.read(buffer_firmware, sizeof(buffer_firmware)); 
                  AES256Decrypt(buffer_firmware, buffer_decrypt, rollback_encrypt_key, rollback_encrypt_iv);
          
                  int buffer_length = 0;
                  if(count > sizeof(buffer_firmware)){
                    buffer_length = sizeof(buffer_firmware); 
                  }else{
                    buffer_length = last_byte_length[0];
                  }
          
                  sha256Instance->update(buffer_decrypt, buffer_length);
          
                  count -= sizeof(buffer_firmware);
                }
                file_number++;  
              }

              sha256Instance->final(hash);
              for(int i=0; i<SHA256_BLOCK_SIZE; ++i){
                sprintf(texthash+2*i, "%02X", hash[i]);
              }

              if(debug_mode == true){
                Serial.print("Debug --> SHA-256 Hash : "); 
                Serial.println(texthash);  
              }

              String str_hash = info.getHash();
              int n = 0;
              for(int i = 0; i < str_hash.length(); i++){
                if(texthash[i] == str_hash[i]){
                  n++;
                }
              }

              if(n == str_hash.length()){
                if(debug_mode == true){
                  Serial.println("Debug --> Valid firmware hash...");  
                }

                if(callbackRollback != NULL){ 
                  callbackRollback(DECRYPT_AND_VERIF_HASH, VALID_FIRMWARE_HASH, str_hash);
                }

                if(debug_mode == true){
                  Serial.println("Debug --> Update firmware...");   
                }
                
                if(callbackRollback != NULL){ 
                  callbackRollback(DECRYPT_AND_UPDATE_FIRMWARE, WAITING_PROCESS_MESSAGE, "");
                }
    
                uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
                if(debug_mode == true){
                  Serial.print("Debug --> MAX SKETCH SPACE : ");
                  Serial.println(maxSketchSpace);
                }
                
                if (Update.begin(maxSketchSpace)) {
                  int file_number = 1;
                  while(SD.exists(partFile(file_number)) == true){
                    if(debug_mode == true){
                      Serial.print("Debug --> Update firmware : "); 
                      Serial.println(partFile(file_number));  
                    }
      
                    if(callbackRollback != NULL){ 
                    callbackRollback(DECRYPT_AND_UPDATE_FIRMWARE, WAITING_PROCESS_MESSAGE, partFile(file_number));
                    }
                    
                    File firmware = SD.open(partFile(file_number)); 
            
                    firmware.seek(firmware.size() - 1);
                    byte last_byte_length[1];
                    firmware.read(last_byte_length, 1);
              
                    firmware.seek(0);
                    int count = firmware.available() - 1;
                    while (count > 0) {
                      byte buffer_firmware[aes_block_size], buffer_decrypt[aes_block_size];
                      firmware.read(buffer_firmware, sizeof(buffer_firmware)); 
                      AES256Decrypt(buffer_firmware, buffer_decrypt, rollback_encrypt_key, rollback_encrypt_iv);
              
                      int buffer_length = 0;
                      if(count > sizeof(buffer_firmware)){
                        buffer_length = sizeof(buffer_firmware); 
                      }else{
                        buffer_length = last_byte_length[0];
                      }
              
                      Update.write(buffer_decrypt, buffer_length);
              
                      count -= sizeof(buffer_firmware);
                    }
                    file_number++;  
                  }
      
                  if(Update.end(true) == true){
                    if(debug_mode == true){
                      Serial.println("Debug --> Update complete...");   
                    }
                      
                    if(callbackRollback != NULL){ 
                      callbackRollback(DECRYPT_AND_UPDATE_FIRMWARE, UPDATE_COMPLETE, "");
                    }
      
                    if(SD.begin()){
                      if(debug_mode == true){
                        Serial.println("Debug --> Waiting Remove SD Card...");   
                      }
                        
                      if(callbackRollback != NULL){ 
                        callbackRollback(REMOVE_SDCARD, WAITING_REMOVE_SDCARD, "");
                      }
    
                      SD.end();
                    }
      
                    while(SD.begin()){
                      if(debug_mode == true){
                        Serial.print(".");
                      }

                      if(callbackRollback != NULL){ 
                        callbackRollback(REMOVE_SDCARD, WAITING_REMOVE_SDCARD, "");
                      }
                      
                      SD.end();
                      delay(1000);
                    }
      
                    if(debug_mode == true){
                      Serial.println("Debug --> SD Card Removed...");   
                    }
                        
                    if(callbackRollback != NULL){ 
                      callbackRollback(REMOVE_SDCARD, SDCARD_REMOVED, "");
                    }
      
                    if(debug_mode == true){
                      Serial.println("Debug --> Restart Device...");   
                    }
                        
                    if(callbackRollback != NULL){ 
                      callbackRollback(RESTART_DEVICE, WAITING_PROCESS_MESSAGE, "");
                    }
      
                    ESP.restart();
                    
                  }else{
                    if(debug_mode == true){
                      Serial.println("Debug --> Update failed...");   
                    }
                      
                    if(callbackRollback != NULL){ 
                      callbackRollback(DECRYPT_AND_UPDATE_FIRMWARE, UPDATE_FAILED, "");
                    }
    
                    SD.end();
                  }
                }else{
                  if(debug_mode == true){
                    Serial.println("Debug --> ERROR BEGIN UPDATE...");
                  }

                  SD.end();
                }
              }else{
                if(debug_mode == true){
                  Serial.println("Debug --> Invalid firmware hash...");  
                }

                if(callbackRollback != NULL){ 
                  callbackRollback(DECRYPT_AND_VERIF_HASH, INVALID_FIRMWARE_HASH, "");
                }

                SD.end();
              }
            }else{
              if(debug_mode == true){
                Serial.println("Debug --> Firmware type is not rollback version...");   
              }

              if(callbackRollback != NULL){ 
                callbackRollback(READ_FIRMWARECRYPT_FILE, FIRMWARE_TYPE_UPDATE_VERSION, "");
              }
            }
          }else{
            if(debug_mode == true){
              Serial.println("Debug --> Invalid firmwarecrypt file...");    
            }
            
            if(callbackRollback != NULL){ 
              callbackRollback(READ_FIRMWARECRYPT_FILE, INVALID_FIRMWARECRYPT_FILE, "");
            }

            SD.end();
          }
        }
      }else{
        if(debug_mode == true){
          Serial.println("Debug --> Parse firmware_info_str failed...");
          Serial.println("Debug --> Invalid firmwarecrypt file...");
        }

        if(callbackRollback != NULL){ 
          callbackRollback(READ_FIRMWARECRYPT_FILE, INVALID_FIRMWARECRYPT_FILE, "");
        }

        SD.end();
      }
    }else{
      if(debug_mode == true){
        Serial.println("Debug --> Firmwarecrypt file not exists...");
      }
        
      if(callbackRollback != NULL){ 
        callbackRollback(READ_FIRMWARECRYPT_FILE, FIRMWARECRYPT_FILE_NOT_EXISTS, "");
      }

      SD.end();
    }
  }else{
    if(debug_mode == true){
      Serial.println("Debug --> SD Card not detected...");
    }
    
    if(callbackRollback != NULL){ 
      callbackRollback(READ_SDCARD, SD_CARD_NOT_DETECTED, "");
    }
  }
}
//------------------------------------------------------------------------------
