/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testDecodeStatus.c
 * @author Jacob.Garrison
 *
 * @date Feb 16, 2021
 *      
 */

#include <stdint.h>
#include <stdbool.h>
#include <mocha.h>

#include "sg.h"
#include "testSgMessages.h"

/*
 * First set of conditions
 */
static int testDecodeStatus1(void)
{
   // Test data.
   //    Status message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x83, 0x05, 0x0A,
      // 0     1     2     3
      //sw    fw   crc
      0x09, 0x09, 0x55, 0xC9, 0x1E, 0x2C,
      // 4     5     6     7     8     9
      //bit                    cks
      0xDF, 0xFF, 0xF8, 0xE0, 0x64
      //10    11    12    13    14
   };
   sg_status_t status;

   // Test function:
   sgDecodeStatus(buffer, &status);

   // Test results:
   expect(status.versionSW == 9);
   expect(status.versionFW == 9);
   expect(status.crc == 0x55C91E2C);
   expect(status.powerUp);
   expect(status.continuous);
   expect(status.processor);
   expect(status.crcValid);
   expect(status.memory);
   expect(status.calibrated);
   expect(status.receiver);
   expect(status.power53v);
   expect(status.adc);
   expect(status.pressure);
   expect(status.fpga);
   expect(status.rxLock);
   expect(status.txLock);
   expect(status.mtSuppress);
   expect(status.temp);
   expect(status.sqMonitor);
   expect(status.txRate);
   expect(status.sysLatency);
   expect(status.txPower);
   expect(status.voltageIn);
   expect(status.icao);
   expect(status.gps);

   return 0;
}

/*
 * Second set of conditions
 */
static int testDecodeStatus2(void)
{
   // Test data.
   //    Status message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x83, 0x05, 0x0A,
      // 0     1     2     3
      //sw    fw   crc
      0x0B, 0x0C, 0xF0, 0x0B, 0xD2, 0xFF,
      // 4     5     6     7     8     9
      //bit                    cks
      0x94, 0x5E, 0x10, 0x20, 0x64
      //10    11    12    13    14
   };
   sg_status_t status;

   // Test function:
   sgDecodeStatus(buffer, &status);

   // Test results:
   expect(status.versionSW == 11);
   expect(status.versionFW == 12);
   expect(status.crc == 0xF00BD2FF);
   expect(status.powerUp);
   expect(!status.continuous);
   expect(status.processor);
   expect(!status.crcValid);
   expect(status.memory);
   expect(!status.calibrated);
   expect(!status.receiver);
   expect(status.power53v);
   expect(!status.adc);
   expect(status.pressure);
   expect(status.fpga);
   expect(status.rxLock);
   expect(status.txLock);
   expect(!status.mtSuppress);
   expect(!status.temp);
   expect(!status.sqMonitor);
   expect(!status.txRate);
   expect(status.sysLatency);
   expect(!status.txPower);
   expect(!status.voltageIn);
   expect(!status.icao);
   expect(status.gps);

   return 0;
}

/*
 * Third set of conditions
 */
static int testDecodeStatus3(void)
{
   // Test data.
   //    Status message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x83, 0x05, 0x0A,
      // 0     1     2     3
      //sw    fw   crc
      0x00, 0x02, 0x0F, 0xFF, 0xFF, 0xF0,
      // 4     5     6     7     8     9
      //bit                    cks
      0xDF, 0xFF, 0xF8, 0xE0, 0x64
      //10    11    12    13    14
   };
   sg_status_t status;

   // Test function:
   sgDecodeStatus(buffer, &status);

   // Test results:
   expect(status.versionSW == 0);
   expect(status.versionFW == 2);
   expect(status.crc == 0x0FFFFFF0);
   expect(status.powerUp);
   expect(status.continuous);
   expect(status.processor);
   expect(status.crcValid);
   expect(status.memory);
   expect(status.calibrated);
   expect(status.receiver);
   expect(status.power53v);
   expect(status.adc);
   expect(status.pressure);
   expect(status.fpga);
   expect(status.rxLock);
   expect(status.txLock);
   expect(status.mtSuppress);
   expect(status.temp);
   expect(status.sqMonitor);
   expect(status.txRate);
   expect(status.sysLatency);
   expect(status.txPower);
   expect(status.voltageIn);
   expect(status.icao);
   expect(status.gps);

   return 0;
}

/*
 * Documented in the header file.
 */
int testDecodeStatus(void)
{
   int res1 = testDecodeStatus1();
   int res2 = testDecodeStatus2();
   int res3 = testDecodeStatus3();

   return res1 || res2 || res3;
}
