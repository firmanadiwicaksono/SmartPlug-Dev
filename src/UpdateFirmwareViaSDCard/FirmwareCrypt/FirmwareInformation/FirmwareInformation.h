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

#ifndef FirmwareInformation_h
#define FirmwareInformation_h

#include <Arduino.h>

const byte encrypt_key[32] = {178, 26, 136, 14, 74, 132, 143, 207, 162, 50, 238, 62, 25, 249, 213, 40, 170, 237, 210, 207, 90, 245, 234, 81, 132, 47, 228, 50, 204, 161, 81, 186};
const byte encrypt_iv[16] = {129, 125, 236, 132, 188, 136, 57, 75, 97, 238, 108, 103, 181, 202, 222, 149};
const String buffer_check = "E66CAF78B29353B6C006A2BA3DC32802CB4EF43B748096F3DA8E7418F29E92DC";
const String firmware_name = "Blink 200ms";
const String firmware_description = "Blink 200ms";
const String firmware_version = "1.0.0.0";
const String legal_copyright = "Copyright (c) 2020 Firman Adi Wicaksono";
const String company_name = "Firman Adi Wicaksono";

#endif
