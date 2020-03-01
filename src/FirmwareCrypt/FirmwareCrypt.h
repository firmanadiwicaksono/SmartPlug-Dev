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
 
#ifndef FirmwareCrypt_h
#define FirmwareCrypt_h

#include <Arduino.h>
#include "FirmwareInfoParser/FirmwareInfoParser.h"

enum FIRMWARECRYPT_PROCESS{
  WAITING_PROCESS,
  READ_SDCARD,
  READ_FIRMWARECRYPT_FILE,
  DECRYPT_AND_VERIF_HASH,
  DECRYPT_AND_UPDATE_FIRMWARE,
  REMOVE_SDCARD,
  RESTART_DEVICE
};

enum FIRMWARECRYPT_PROCESS_MESSAGE{
  WAITING_PROCESS_MESSAGE,

  SD_CARD_DETECTED,
  SD_CARD_NOT_DETECTED,

  FIRMWARECRYPT_FILE_NOT_EXISTS,
  FIRMWARECRYPT_FILE_EXISTS,
  VALID_FIRMWARECRYPT_FILE,
  INVALID_FIRMWARECRYPT_FILE,

  VALID_FIRMWARE_HASH,
  INVALID_FIRMWARE_HASH,

  UPDATE_COMPLETE,
  UPDATE_FAILED,
  
  WAITING_REMOVE_SDCARD,
  SDCARD_REMOVED
};

#define FIRMWARECRYPT_CALLBACK_SIGNATURE void (*callback)(FIRMWARECRYPT_PROCESS proc_info, FIRMWARECRYPT_PROCESS_MESSAGE proc_message, String message)

class FirmwareCrypt{
private:
  const String firmware_info_filename = "/firmware.firmwarecrypt";
  const String firmware_filename = "/firmware.firmwarecrypt_";
  const int aes_block_size = 64;
  bool debug_mode;
  FIRMWARECRYPT_CALLBACK_SIGNATURE;
  String partFile(int part);
  void AES256Decrypt(byte* cipher, byte* plain, const byte* key, const byte* iv);
    
public:
  FirmwareInfoParser info;
  FirmwareCrypt();
  String getFirmwareName(); 
  String getFirmwareDecription();
  String getFirmwareVersion();
  String getLegalCopyright();
  String getCompanyName();
  void setDebugMode(bool debug_mode);
  void setCallbackProcess(FIRMWARECRYPT_CALLBACK_SIGNATURE);
  void handleUpdate();
};

#endif
