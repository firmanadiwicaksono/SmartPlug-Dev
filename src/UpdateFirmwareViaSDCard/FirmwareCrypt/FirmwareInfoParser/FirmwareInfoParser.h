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

#ifndef FirmwareInfoParser_h
#define FirmwareInfoParser_h

#include <Arduino.h>

class FirmwareInfoParser{
private:
  String buffer_check;
  String hash;
  String firmware_name;
  String firmware_description;
  String firmware_version;
  String legal_copyright;
  String company_name;
  String firmware_type;
  bool verif(String firmware_info);

public:
  FirmwareInfoParser();
  bool parse(String firmware_info);
  String getBufferCheck();
  String getHash();
  String getFirmwareName();
  String getFirmwareDescription();
  String getFirmwareVersion();
  String getLegalCopyright();
  String getCompanyName();
  String getFirmwareType();
};

#endif
