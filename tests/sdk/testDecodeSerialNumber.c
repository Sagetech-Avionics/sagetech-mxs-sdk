/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testDecodeSerialNumber.c
 * @author Jacob.Garrison
 *
 * @date Mar 10, 2021
 *      
 */

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <mocha.h>

#include "sg.h"
#include "testSgMessages.h"

/*
 * Documented in the header file.
 */
int testDecodeSerialNumber(void)
{
   // Test data.
   //    Serial Number message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x8F, 0x9D, 0x60,
      // 0     1     2     3
      //|-----------------IF SN--------------------|
      0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
      // 4     5     6     7     8     9    10    11
      //|-----------------IF SN--------------------|
      0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
      //12    13    14    15    16    17    18    19
      //|-----------------IF SN--------------------|
      0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
      //20    21    22    23    24    25    26    27
      //|-----------------IF SN--------------------|
      0x59, 0x5A, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
      //28    29    30    31    32    33    34    35
      //|-----------------RF SN--------------------|
      0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
      //36    37    38    39    40    41    42    43
      //|-----------------RF SN--------------------|
      0x30, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
      //44    45    46    47    48    49    50    51
      //|-----------------RF SN--------------------|
      0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
      //52    53    54    55    56    57    58    59
      //|-----------------RF SN--------------------|
      0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
      //60    61    62    63    64    65    66    67
      //|----------------XPNDR SN------------------|
      0x37, 0x38, 0x39, 0x30, 0x41, 0x42, 0x43, 0x44,
      //68    69    70    71    72    73    74    75
      //|----------------XPNDR SN------------------|
      0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C,
      //76    77    78    79    80    81    82    83
      //|----------------XPNDR SN------------------|
      0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54,
      //84    85    86    87    88    89    90    91
      //|----------------XPNDR SN------------------|
      0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x30, 0x31,
      //92    93    94    95    96    97    98    99
      //cks
      0x12
   };
   sg_serialnumber_t sn;

   // Test function:
   sgDecodeSerialNumber(buffer, &sn);

   // Test results:
   expect(strcmp(sn.ifSN,    "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456") == 0);
   expect(strcmp(sn.rfSN,    "234567890ABCDEFGHIJKLMNOPQRSTUVW") == 0);
   expect(strcmp(sn.xpndrSN, "7890ABCDEFGHIJKLMNOPQRSTUVWXYZ01") == 0);

   return 0;
}
