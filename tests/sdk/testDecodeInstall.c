/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testDecodeInstall.c
 * @author Jacob.Garrison
 *
 * @date Mar 9, 2021
 *      
 */

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <mocha.h>

#include "sg.h"
#include "testSgMessages.h"

/*
 * First set of conditions
 */
static int testDecodeInstall1(void)
{
   // Test data.
   //    Install Reply message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x81, 0x01, 0x24,
      // 0     1     2     3
      //|----icao----|  |----------------reg-------------------|  |--rsvd--|
      0xAB, 0xC1, 0x23, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x5A, 0x00, 0x00,
      // 4     5     6     7     8     9    10    11    12    13    14    15
      //com0 com1 |-----ip address-----|  |------net mask------|  |--port--|
      0x07, 0x00, 0x64, 0x32, 0x19, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0x0B, 0xB9,
      //16    17    18    19    20    21    22    23    24    25    26    27
      //gps emitc emitt size   spd  |-alt ofs-| |---rsvd--|  cfg  |--rsvd--|
      0x13, 0x01, 0x06, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0xA9, 0x00, 0x00,
      //28    29    30    31    32    33    34    35    36    37    38    39
      //cks
      0x5F
      //40
   };
   sg_install_t stl;

   // Test function:
   sgDecodeInstall(buffer, &stl);

   // Test results:
   expect(stl.icao                   == 0x00ABC123);
   expect(strcmp(stl.reg, "123456Z") == 0);
   expect(stl.com0                   == baud230400);
   expect(stl.com1                   == baud38400);
   expect(stl.eth.ipAddress          == 1681004801);
   expect(stl.eth.subnetMask         == 4294901760);
   expect(stl.eth.portNumber         == 3001);
   expect(stl.sil                    == silLow);
   expect(stl.sda                    == sdaHazardous);
   expect(stl.emitter                == bUAV);
   expect(stl.size                   == sizeUnknown);
   expect(stl.maxSpeed               == speedGreater);
   expect(stl.altOffset              == 0);
   expect(stl.antenna                == antBottom);
   expect(stl.altRes100              == true);
   expect(stl.hdgTrueNorth           == false);
   expect(stl.airspeedTrue           == true);
   expect(stl.heater                 == false);
   expect(stl.wowConnected           == true);

   return 0;
}

/*
 * Second set of conditions
 */
static int testDecodeInstall2(void)
{
   // Test data.
   //    Install Reply message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x81, 0x01, 0x24,
      // 0     1     2     3
      //|----icao----|  |----------------reg-------------------|  |--rsvd--|
      0x00, 0x00, 0x01, 0x39, 0x30, 0x41, 0x5A, 0x20, 0x20, 0x20, 0x00, 0x00,
      // 4     5     6     7     8     9    10    11    12    13    14    15
      //com0 com1 |-----ip address-----|  |------net mask------|  |--port--|
      0x04, 0x0A, 0x0A, 0x00, 0x01, 0x02, 0xFF, 0xFF, 0xFE, 0x00, 0x32, 0xC8,
      //16    17    18    19    20    21    22    23    24    25    26    27
      //gps emitc emitt size   spd  |-alt ofs-| |---rsvd--|  cfg  |--rsvd--|
      0x30, 0x00, 0x00, 0x0F, 0x00, 0x7F, 0xFF, 0x00, 0x00, 0xC3, 0x00, 0x00,
      //28    29    30    31    32    33    34    35    36    37    38    39
      //cks
      0x5F
      //40
   };
   sg_install_t stl;

   // Test function:
   sgDecodeInstall(buffer, &stl);

   // Test results:
   expect(stl.icao                   == 0x00000001);
   expect(strcmp(stl.reg, "90AZ   ") == 0);
   expect(stl.com0                   == baud28800);
   expect(stl.com1                   == baud921600);
   expect(stl.eth.ipAddress          == 167772418);
   expect(stl.eth.subnetMask         == 4294966784);
   expect(stl.eth.portNumber         == 13000);
   expect(stl.sil                    == silHigh);
   expect(stl.sda                    == sdaUnknown);
   expect(stl.emitter                == aUnknown);
   expect(stl.size                   == sizeL85W90);
   expect(stl.maxSpeed               == speedUnknown);
   expect(stl.altOffset              == 32767);
   expect(stl.antenna                == antBoth);
   expect(stl.altRes100              == false);
   expect(stl.hdgTrueNorth           == false);
   expect(stl.airspeedTrue           == false);
   expect(stl.heater                 == true);
   expect(stl.wowConnected           == true);

   return 0;
}

/*
 * Third set of conditions
 */
static int testDecodeInstall3(void)
{
   // Test data.
   //    Install Reply message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x81, 0x01, 0x24,
      // 0     1     2     3
      //|----icao----|  |----------------reg-------------------|  |--rsvd--|
      0xFF, 0xFF, 0xFE, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00,
      // 4     5     6     7     8     9    10    11    12    13    14    15
      //com0 com1 |-----ip address-----|  |------net mask------|  |--port--|
      0x07, 0x01, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01,
      //16    17    18    19    20    21    22    23    24    25    26    27
      //gps emitc emitt size   spd  |-alt ofs-| |---rsvd--|  cfg  |--rsvd--|
      0x02, 0x03, 0x00, 0x04, 0x01, 0x80, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00,
      //28    29    30    31    32    33    34    35    36    37    38    39
      //cks
      0x6E
      //40
   };
   sg_install_t stl;

   // Test function:
   sgDecodeInstall(buffer, &stl);

   // Test results:
   expect(stl.icao                   == 0x00FFFFFE);
   expect(strcmp(stl.reg, "       ") == 0);
   expect(stl.com0                   == baud230400);
   expect(stl.com1                   == baud600);
   expect(stl.eth.ipAddress          == 16776960);
   expect(stl.eth.subnetMask         == 1);
   expect(stl.eth.portNumber         == 1);
   expect(stl.sil                    == silUnknown);
   expect(stl.sda                    == sdaMajor);
   expect(stl.emitter                == dUnknown);
   expect(stl.size                   == sizeL35W33);
   expect(stl.maxSpeed               == speed75kt);
   expect(stl.altOffset              == -32768);
   expect(stl.antenna                == antBottom);
   expect(stl.altRes100              == false);
   expect(stl.hdgTrueNorth           == true);
   expect(stl.airspeedTrue           == true);
   expect(stl.heater                 == false);
   expect(stl.wowConnected           == false);

   return 0;
}

/*
 * Documented in the header file.
 */
int testDecodeInstall(void)
{
   int res1 = testDecodeInstall1();
   int res2 = testDecodeInstall2();
   int res3 = testDecodeInstall3();

   return res1 || res2 || res3;
}
