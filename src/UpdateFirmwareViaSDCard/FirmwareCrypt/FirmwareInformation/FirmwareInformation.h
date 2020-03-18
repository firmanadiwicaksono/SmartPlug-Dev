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

const byte firmwarecrypt_encrypt_key[32] = {146, 71, 185, 19, 71, 24, 115, 81, 226, 28, 15, 219, 137, 146, 157, 208, 120, 123, 169, 2, 243, 4, 226, 242, 108, 175, 112, 20, 248, 62, 151, 83};
const byte firmwarecrypt_encrypt_iv[16] = {165, 238, 159, 48, 143, 49, 79, 235, 169, 126, 93, 221, 208, 47, 12, 57};
const byte update_encrypt_key[32] = {249, 102, 46, 124, 156, 197, 92, 66, 91, 82, 6, 86, 23, 153, 77, 59, 124, 24, 118, 67, 53, 121, 120, 165, 34, 83, 2, 78, 87, 99, 220, 237};
const byte update_encrypt_iv[16] = {132, 230, 200, 193, 154, 41, 195, 157, 93, 163, 211, 63, 232, 58, 112, 17};
const byte rollback_encrypt_key[32] = {166, 158, 165, 184, 59, 213, 59, 128, 242, 176, 212, 185, 74, 210, 74, 235, 247, 21, 200, 93, 250, 54, 212, 63, 163, 19, 83, 121, 182, 230, 141, 106};
const byte rollback_encrypt_iv[16] = {58, 156, 103, 55, 81, 70, 211, 236, 152, 83, 157, 222, 151, 213, 152, 133};
const String buffer_check = "E66CAF78B29353B6C006A2BA3DC32802CB4EF43B748096F3DA8E7418F29E92DC";
const String firmware_name = "Smart Plug";
const String firmware_description = "Home Automation Untuk Monitoring Penggunaan Energi";
const String firmware_version = "0.0.1";
const String legal_copyright = "Copyright (c) Firman Adi Wicaksono 2020";
const String company_name = "FirmanDev";
const String firmware_type = "Rollback Version";

#endif
