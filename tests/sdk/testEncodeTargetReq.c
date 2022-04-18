/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file   testEncodeTargetReq.c
 * @author Jacob.Garrison
 *
 * @date Feb 19, 2021
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
static int testEncodeTargetReq1(void)
{
   // Test data.
   //    Target request message data
   sg_targetreq_t tgt;
   tgt.reqType = reportAuto;
   tgt.transmitPort = transmitSource;
   tgt.maxTargets = 404;
   tgt.icao = 0xF092E4;
   tgt.stateVector = true;
   tgt.modeStatus = false;
   tgt.targetState = true;
   tgt.airRefVel = false;
   tgt.tisb = true;
   tgt.military = false;
   tgt.commA = true;
   tgt.ownship = false;

   //    Message ID
   uint8_t msgId = 0xCD;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_TARGETREQ];
   sgEncodeTargetReq(buffer, &tgt, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);          // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_TARGETREQ); // Msg Type
   expect(buffer[2] == msgId);                      // Msg ID
   expect(buffer[3] == SG_MSG_LEN_TARGETREQ - 5);   // Payload length
   expect(buffer[4] == 0x00);                       // Report type
   expect(buffer[5] == 0x01);                       // Max targets
   expect(buffer[6] == 0x94);                       // Max targets
   expect(buffer[7] == 0xF0);                       // Target ID
   expect(buffer[8] == 0x92);                       // Target ID
   expect(buffer[9] == 0xE4);                       // Target ID
   expect(buffer[10] == 0x55);                      // Requested reports
   expect(buffer[11] == 0xD9);                      // Checksum

   return 0;
}

/*
 * Second set of conditions
 */
static int testEncodeTargetReq2(void)
{
   // Test data.
   //    Target request message data
   sg_targetreq_t tgt;
   tgt.reqType = reportNone;
   tgt.transmitPort = transmitCom1;
   tgt.maxTargets = 90;
   tgt.icao = 0x003421;
   tgt.stateVector = false;
   tgt.modeStatus = false;
   tgt.targetState = true;
   tgt.airRefVel = true;
   tgt.tisb = true;
   tgt.military = true;
   tgt.commA = false;
   tgt.ownship = false;

   //    Message ID
   uint8_t msgId = 0xA0;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_TARGETREQ];
   sgEncodeTargetReq(buffer, &tgt, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);          // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_TARGETREQ); // Msg Type
   expect(buffer[2] == msgId);                      // Msg ID
   expect(buffer[3] == SG_MSG_LEN_TARGETREQ - 5);   // Payload length
   expect(buffer[4] == 0x83);                       // Report type
   expect(buffer[5] == 0x00);                       // Max targets
   expect(buffer[6] == 0x5A);                       // Max targets
   expect(buffer[7] == 0x00);                       // Target ID
   expect(buffer[8] == 0x34);                       // Target ID
   expect(buffer[9] == 0x21);                       // Target ID
   expect(buffer[10] == 0x3C);                      // Requested reports
   expect(buffer[11] == 0xCA);                      // Checksum

   return 0;
}

/*
 * Third set of conditions
 */
static int testEncodeTargetReq3(void)
{
   // Test data.
   //    Target request message data
   sg_targetreq_t tgt;
   tgt.reqType = reportIcao;
   tgt.transmitPort = transmitEth;
   tgt.maxTargets = 01;
   tgt.icao = 0xABC123;
   tgt.stateVector = true;
   tgt.modeStatus = true;
   tgt.targetState = true;
   tgt.airRefVel = false;
   tgt.tisb = false;
   tgt.military = false;
   tgt.commA = false;
   tgt.ownship = false;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_TARGETREQ];
   sgEncodeTargetReq(buffer, &tgt, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);          // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_TARGETREQ); // Msg Type
   expect(buffer[2] == msgId);                      // Msg ID
   expect(buffer[3] == SG_MSG_LEN_TARGETREQ - 5);   // Payload length
   expect(buffer[4] == 0xC2);                       // Report type
   expect(buffer[5] == 0x00);                       // Max targets
   expect(buffer[6] == 0x01);                       // Max targets
   expect(buffer[7] == 0xAB);                       // Target ID
   expect(buffer[8] == 0xC1);                       // Target ID
   expect(buffer[9] == 0x23);                       // Target ID
   expect(buffer[10] == 0x07);                      // Requested reports
   expect(buffer[11] == 0x16);                      // Checksum

   return 0;
}

/*
 * Documented in the header file.
 */
int testEncodeTargetReq(void)
{
    int res1 = testEncodeTargetReq1();
    int res2 = testEncodeTargetReq2();
    int res3 = testEncodeTargetReq3();

    return res1 || res2 || res3;
}
