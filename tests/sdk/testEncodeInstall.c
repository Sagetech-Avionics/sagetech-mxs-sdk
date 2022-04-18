/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testEncodeInstall.c
 * @author Jacob.Garrison
 *
 * @date Feb 25, 2021
 *      
 */


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <mocha.h>

#include "sg.h"
#include "testSgMessages.h"

/*
 * First set of conditions
 */
static int testEncodeInstall1(void)
{
   // Test data.
   //    Installation message data
   sg_install_t stl;
   stl.icao = 0xABC123;
   strcpy(stl.reg, "123456Z");
   stl.com0 = baud230400;
   stl.com1 = baud38400;
   stl.eth.ipAddress = 1681004801;   // 100.50.25.1
   stl.eth.subnetMask = 4294901760;  // 255.255.0.0
   stl.eth.portNumber = 3001;
   stl.sil = silLow;
   stl.sda = sdaHazardous;
   stl.emitter = bUAV;
   stl.size = sizeUnknown;
   stl.maxSpeed = speedGreater;
   stl.altOffset = 0;
   stl.antenna = antBottom;
   stl.altRes100 = true;
   stl.hdgTrueNorth = false;
   stl.airspeedTrue = true;
   stl.heater = false;
   stl.wowConnected = true;

   //    Message ID
   uint8_t msgId = 0xBA;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_INSTALL];
   sgEncodeInstall(buffer, &stl, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_INSTALL); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_INSTALL - 5);   // Payload length
   expect(buffer[4] == 0xAB);                     // ICAO
   expect(buffer[5] == 0xC1);                     // ICAO
   expect(buffer[6] == 0x23);                     // ICAO
   expect(buffer[7] == 0x31);                     // Reg
   expect(buffer[8] == 0x32);                     // Reg
   expect(buffer[9] == 0x33);                     // Reg
   expect(buffer[10] == 0x34);                    // Reg
   expect(buffer[11] == 0x35);                    // Reg
   expect(buffer[12] == 0x36);                    // Reg
   expect(buffer[13] == 0x5A);                    // Reg
   expect(buffer[14] == 0);                       // Rsvd
   expect(buffer[15] == 0);                       // Rsvd
   expect(buffer[16] == 7);                       // COM0
   expect(buffer[17] == 0);                       // COM1
   expect(buffer[18] == 100);                     // IP
   expect(buffer[19] == 50);                      // IP
   expect(buffer[20] == 25);                      // IP
   expect(buffer[21] == 1);                       // IP
   expect(buffer[22] == 255);                     // Mask
   expect(buffer[23] == 255);                     // Mask
   expect(buffer[24] == 0);                       // Mask
   expect(buffer[25] == 0);                       // Mask
   expect(buffer[26] == 0x0B);                    // Port
   expect(buffer[27] == 0xB9);                    // Port
   expect(buffer[28] == 0x13);                    // GPS Integrity
   expect(buffer[29] == 1);                       // Emitter Set
   expect(buffer[30] == 6);                       // Emitter Type
   expect(buffer[31] == 0);                       // Size
   expect(buffer[32] == 6);                       // Max Speed
   expect(buffer[33] == 0);                       // Alt Offset
   expect(buffer[34] == 0);                       // Alt Offset
   expect(buffer[35] == 0);                       // Rsvd
   expect(buffer[36] == 0);                       // Rsvd
   expect(buffer[37] == 0xA9);                    // Config
   expect(buffer[38] == 0);                       // Rsvd
   expect(buffer[39] == 0);                       // Rsvd
   expect(buffer[40] == 0xE9);                    // Checksum

   return 0;
}

/*
 * Second set of conditions
 */
static int testEncodeInstall2(void)
{
   // Test data.
   //    Installation message data
   sg_install_t stl;
   stl.icao = 0x000001;
   strcpy(stl.reg, "90AZ   ");
   stl.com0 = baud28800;
   stl.com1 = baud921600;
   stl.eth.ipAddress = 167772418;    // 100.0.1.2
   stl.eth.subnetMask = 4294966784;  // 255.255.254.0
   stl.eth.portNumber = 13000;
   stl.sil = silHigh;
   stl.sda = sdaUnknown;
   stl.emitter = aUnknown;
   stl.size = sizeL85W90;
   stl.maxSpeed = speedUnknown;
   stl.altOffset = 32767;
   stl.antenna = antBoth;
   stl.altRes100 = false;
   stl.hdgTrueNorth = false;
   stl.airspeedTrue = false;
   stl.heater = true;
   stl.wowConnected = true;

   //    Message ID
   uint8_t msgId = 0x9A;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_INSTALL];
   sgEncodeInstall(buffer, &stl, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_INSTALL); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_INSTALL - 5);   // Payload length
   expect(buffer[4] == 0x00);                     // ICAO
   expect(buffer[5] == 0x00);                     // ICAO
   expect(buffer[6] == 0x01);                     // ICAO
   expect(buffer[7] == 0x39);                     // Reg
   expect(buffer[8] == 0x30);                     // Reg
   expect(buffer[9] == 0x41);                     // Reg
   expect(buffer[10] == 0x5A);                    // Reg
   expect(buffer[11] == 0x20);                    // Reg
   expect(buffer[12] == 0x20);                    // Reg
   expect(buffer[13] == 0x20);                    // Reg
   expect(buffer[14] == 0);                       // Rsvd
   expect(buffer[15] == 0);                       // Rsvd
   expect(buffer[16] == 4);                       // COM0
   expect(buffer[17] == 10);                      // COM1
   expect(buffer[18] == 10);                      // IP
   expect(buffer[19] == 0);                       // IP
   expect(buffer[20] == 1);                       // IP
   expect(buffer[21] == 2);                       // IP
   expect(buffer[22] == 255);                     // Mask
   expect(buffer[23] == 255);                     // Mask
   expect(buffer[24] == 254);                     // Mask
   expect(buffer[25] == 0);                       // Mask
   expect(buffer[26] == 0x32);                    // Port
   expect(buffer[27] == 0xC8);                    // Port
   expect(buffer[28] == 0x30);                    // GPS Integrity
   expect(buffer[29] == 0);                       // Emitter Set
   expect(buffer[30] == 0x00);                    // Emitter Type
   expect(buffer[31] == 0x0F);                    // Size
   expect(buffer[32] == 0);                       // Max Speed
   expect(buffer[33] == 0x7F);                    // Alt Offset
   expect(buffer[34] == 0xFF);                    // Alt Offset
   expect(buffer[35] == 0);                       // Rsvd
   expect(buffer[36] == 0);                       // Rsvd
   expect(buffer[37] == 0xC3);                    // Config
   expect(buffer[38] == 0);                       // Rsvd
   expect(buffer[39] == 0);                       // Rsvd
   expect(buffer[40] == 0x5F);                    // Checksum

   return 0;
}

/*
 * Third set of conditions
 */
static int testEncodeInstall3(void)
{
   // Test data.
   //    Installation message data
   sg_install_t stl;
   stl.icao = 0xFFFFFE;
   strcpy(stl.reg, "       ");
   stl.com0 = baud230400;
   stl.com1 = baud600;
   stl.eth.ipAddress = 16776960;   // 0.255.255.0
   stl.eth.subnetMask = 1;         // 0.0.0.1
   stl.eth.portNumber = 1;
   stl.sil = silUnknown;
   stl.sda = sdaMajor;
   stl.emitter = dUnknown;
   stl.size = sizeL35W33;
   stl.maxSpeed = speed75kt;
   stl.altOffset = -32768;
   stl.antenna = antBottom;
   stl.altRes100 = false;
   stl.hdgTrueNorth = true;
   stl.airspeedTrue = true;
   stl.heater = false;
   stl.wowConnected = false;

   //    Message ID
   uint8_t msgId = 0x00;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_INSTALL];
   sgEncodeInstall(buffer, &stl, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_INSTALL); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_INSTALL - 5);   // Payload length
   expect(buffer[4] == 0xFF);                     // ICAO
   expect(buffer[5] == 0xFF);                     // ICAO
   expect(buffer[6] == 0xFE);                     // ICAO
   expect(buffer[7] == 0x20);                     // Reg
   expect(buffer[8] == 0x20);                     // Reg
   expect(buffer[9] == 0x20);                     // Reg
   expect(buffer[10] == 0x20);                    // Reg
   expect(buffer[11] == 0x20);                    // Reg
   expect(buffer[12] == 0x20);                    // Reg
   expect(buffer[13] == 0x20);                    // Reg
   expect(buffer[14] == 0);                       // Rsvd
   expect(buffer[15] == 0);                       // Rsvd
   expect(buffer[16] == 7);                       // COM0
   expect(buffer[17] == 1);                       // COM1
   expect(buffer[18] == 0);                       // IP
   expect(buffer[19] == 255);                     // IP
   expect(buffer[20] == 255);                     // IP
   expect(buffer[21] == 0);                       // IP
   expect(buffer[22] == 0);                       // Mask
   expect(buffer[23] == 0);                       // Mask
   expect(buffer[24] == 0);                       // Mask
   expect(buffer[25] == 1);                       // Mask
   expect(buffer[26] == 0x00);                    // Port
   expect(buffer[27] == 0x01);                    // Port
   expect(buffer[28] == 0x02);                    // GPS Integrity
   expect(buffer[29] == 3);                       // Emitter Set
   expect(buffer[30] == 0);                       // Emitter Type
   expect(buffer[31] == 4);                       // Size
   expect(buffer[32] == 1);                       // Max Speed
   expect(buffer[33] == 0x80);                    // Alt Offset
   expect(buffer[34] == 0x00);                    // Alt Offset
   expect(buffer[35] == 0);                       // Rsvd
   expect(buffer[36] == 0);                       // Rsvd
   expect(buffer[37] == 0x31);                    // Config
   expect(buffer[38] == 0);                       // Rsvd
   expect(buffer[39] == 0);                       // Rsvd
   expect(buffer[40] == 0x6E);                    // Checksum

   return 0;
}

/*
 * Documented in the header file.
 */
int testEncodeInstall(void)
{
    int res1 = testEncodeInstall1();
    int res2 = testEncodeInstall2();
    int res3 = testEncodeInstall3();

    return res1 || res2 || res3;
}
