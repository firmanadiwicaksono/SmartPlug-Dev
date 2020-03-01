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

#include "FirmwareInfoParser.h"
#include <Arduino.h>

//Private
bool FirmwareInfoParser::verif(String firmware_info){
  int n = 0;
  for(int i = 0; i < firmware_info.length(); i++){
    if(firmware_info[i] == ';'){
      n++;
    }
  }

  if(n == 7)
    return true;
  else
    return false;
}
//------------------------------------------------------------------------------

//Public
FirmwareInfoParser::FirmwareInfoParser(){
  buffer_check = "";
  hash = "";
  firmware_name = "";
  firmware_description = "";
  firmware_version = "";
  legal_copyright = "";
  company_name = "";
}

bool FirmwareInfoParser::parse(String firmware_info){
  if(verif(firmware_info) == true){
    int pos_begin = 0;
    int pos_end = 0;
    
    pos_end = firmware_info.indexOf(';', pos_begin);
    buffer_check = firmware_info.substring(pos_begin, pos_end); 
    pos_begin = pos_end + 1;

    pos_end = firmware_info.indexOf(';', pos_begin);
    hash = firmware_info.substring(pos_begin, pos_end); 
    pos_begin = pos_end + 1;

    pos_end = firmware_info.indexOf(';', pos_begin);
    firmware_name = firmware_info.substring(pos_begin, pos_end); 
    pos_begin = pos_end + 1;

    pos_end = firmware_info.indexOf(';', pos_begin);
    firmware_description = firmware_info.substring(pos_begin, pos_end); 
    pos_begin = pos_end + 1;

    pos_end = firmware_info.indexOf(';', pos_begin);
    firmware_version = firmware_info.substring(pos_begin, pos_end); 
    pos_begin = pos_end + 1;

    pos_end = firmware_info.indexOf(';', pos_begin);
    legal_copyright = firmware_info.substring(pos_begin, pos_end); 
    pos_begin = pos_end + 1;

    pos_end = firmware_info.indexOf(';', pos_begin);
    company_name = firmware_info.substring(pos_begin, pos_end); 
    pos_begin = pos_end + 1;

    return true;
  }else{
    buffer_check = "";
    hash = "";
    firmware_name = "";
    firmware_description = "";
    firmware_version = "";
    legal_copyright = "";
    company_name = "";
    return false;
  }
}

String FirmwareInfoParser::getBufferCheck(){
  return buffer_check;  
}

String FirmwareInfoParser::getHash(){
  return hash;
}

String FirmwareInfoParser::getFirmwareName(){
  return firmware_name;
}

String FirmwareInfoParser::getFirmwareDescription(){
  return firmware_description;
}

String FirmwareInfoParser::getFirmwareVersion(){
  return firmware_version;
}

String FirmwareInfoParser::getLegalCopyright(){
  return legal_copyright;
}

String FirmwareInfoParser::getCompanyName(){
  return company_name;
}
//------------------------------------------------------------------------------
