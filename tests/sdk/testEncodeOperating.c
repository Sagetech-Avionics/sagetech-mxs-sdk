/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file   testEncodeOperating.c
 * @author Jacob.Garrison
 *
 * @date Feb 17, 2021
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
static int testEncodeOperating1(void)
{
   // Test data.
   //    Operating message data
   sg_operating_t op;
   op.squawk = 01200;
   op.opMode = modeOn;
   op.savePowerUp = false;
   op.enableSqt = false;
   op.enableXBit = false;
   op.milEmergency = false;
   op.emergcType = emergcNone;
   op.identOn = false;
   op.altUseIntrnl = true;
   op.altitude = -600;
   op.altHostAvlbl = false;
   op.altRes25 = false;
   op.climbValid = false;
   op.climbRate = 256;
   op.heading = 0;
   op.headingValid = true;
   op.airspd = 0;
   op.airspdValid = true;

   //    Message ID
   uint8_t msgId = 0xFF;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_OPMSG];
   sgEncodeOperating(buffer, &op, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);      // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_OPMSG); // Msg Type
   expect(buffer[2] == msgId);                  // Msg ID
   expect(buffer[3] == SG_MSG_LEN_OPMSG - 5);   // Payload length
   expect(buffer[4] == 0x02);                   // Squawk
   expect(buffer[5] == 0x80);                   // Squawk
   expect(buffer[6] == 0x01);                   // Mode/Config
   expect(buffer[7] == 0x00);                   // Emergc/Ident
   expect(buffer[8] == 0x80);                   // Altitude
   expect(buffer[9] == 0x00);                   // Altitude
   expect(buffer[10] == 0x80);                  // Altitude Rate
   expect(buffer[11] == 0x00);                  // Altitude Rate
   expect(buffer[12] == 0x80);                  // Heading
   expect(buffer[13] == 0x00);                  // Heading
   expect(buffer[14] == 0x80);                  // Airspeed
   expect(buffer[15] == 0x00);                  // Airspeed
   expect(buffer[16] == 0x3B);                  // Checksum

   return 0;
}

/*
 * Second set of conditions
 */
static int testEncodeOperating2(void)
{
   // Test data.
   //    Operating message data
   sg_operating_t op;
   op.squawk = 07600;
   op.opMode = modeStby;
   op.savePowerUp = false;
   op.enableSqt = true;
   op.enableXBit = true;
   op.milEmergency = false;
   op.emergcType = emergcComm;
   op.identOn = true;
   op.altUseIntrnl = false;
   op.altitude = -1100;
   op.altHostAvlbl = true;
   op.altRes25 = false;
   op.climbValid = true;
   op.climbRate = 256;
   op.heading = 135;
   op.headingValid = false;
   op.airspd = 137;
   op.airspdValid = false;

   //    Message ID
   uint8_t msgId = 0x2B;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_OPMSG];
   sgEncodeOperating(buffer, &op, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);      // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_OPMSG); // Msg Type
   expect(buffer[2] == msgId);                  // Msg ID
   expect(buffer[3] == SG_MSG_LEN_OPMSG - 5);   // Payload length
   expect(buffer[4] == 0x0F);                   // Squawk
   expect(buffer[5] == 0x80);                   // Squawk
   expect(buffer[6] == 0x1A);                   // Mode/Config
   expect(buffer[7] == 0x0C);                   // Emergc/Ident
   expect(buffer[8] == 0x40);                   // Altitude
   expect(buffer[9] == 0x01);                   // Altitude
   expect(buffer[10] == 0x00);                  // Altitude Rate
   expect(buffer[11] == 0x04);                  // Altitude Rate
   expect(buffer[12] == 0x30);                  // Heading
   expect(buffer[13] == 0x00);                  // Heading
   expect(buffer[14] == 0x00);                  // Airspeed
   expect(buffer[15] == 0x89);                  // Airspeed
   expect(buffer[16] == 0x97);                  // Checksum

   return 0;
}

/*
 * Third set of conditions
 */
static int testEncodeOperating3(void)
{
   // Test data.
   //    Operating message data
   sg_operating_t op;
   op.squawk = 03333;
   op.opMode = modeOff;
   op.savePowerUp = true;
   op.enableSqt = false;
   op.enableXBit = false;
   op.milEmergency = true;
   op.emergcType = emergcMed;
   op.identOn = false;
   op.altUseIntrnl = false;
   op.altitude = 25000;
   op.altHostAvlbl = false;
   op.altRes25 = false;
   op.climbValid = true;
   op.climbRate = -6400;
   op.heading = 358;
   op.headingValid = true;
   op.airspd = 1024;
   op.airspdValid = true;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_OPMSG];
   sgEncodeOperating(buffer, &op, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);      // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_OPMSG); // Msg Type
   expect(buffer[2] == msgId);                  // Msg ID
   expect(buffer[3] == SG_MSG_LEN_OPMSG - 5);   // Payload length
   expect(buffer[4] == 0x06);                   // Squawk
   expect(buffer[5] == 0xDB);                   // Squawk
   expect(buffer[6] == 0x24);                   // Mode/Config
   expect(buffer[7] == 0x02);                   // Emergc/Ident
   expect(buffer[8] == 0x00);                   // Altitude
   expect(buffer[9] == 0x00);                   // Altitude
   expect(buffer[10] == 0xFF);                  // Altitude Rate
   expect(buffer[11] == 0x9C);                  // Altitude Rate
   expect(buffer[12] == 0xFF);                  // Heading
   expect(                                      // Heading
         0x49 <= buffer[13] &&
         buffer[13] <= 0x4A);
   expect(buffer[14] == 0x84);                  // Airspeed
   expect(buffer[15] == 0x00);                  // Airspeed
   expect(buffer[16] == 0x28);                  // Checksum

   return 0;
}

/*
 * Documented in the header file.
 */
int testEncodeOperating(void)
{
    int res1 = testEncodeOperating1();
    int res2 = testEncodeOperating2();
    int res3 = testEncodeOperating3();

    return res1 || res2 || res3;
}
