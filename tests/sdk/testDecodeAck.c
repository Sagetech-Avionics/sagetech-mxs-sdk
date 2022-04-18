/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testDecodeAck.c
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
static int testDecodeAck1(void)
{
   // Test data.
   //    ACK message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x80, 0x01, 0x06,
      // 0     1     2     3
      //type id    sys   alt               cks
      0x05, 0x01, 0x36, 0x80, 0x00, 0x00, 0xED
      // 4     5     6     7     8     9    10
   };
   sg_ack_t ack;

   // Test function:
   sgDecodeAck(buffer, &ack);

   // Test results:
   expect(ack.ackType == 5);
   expect(ack.ackId == 1);
   expect(!ack.failXpdr);
   expect(ack.failSystem);
   expect(ack.failCrypto);
   expect(!ack.wow);
   expect(ack.maint);
   expect(ack.isHostAlt);
   expect(ack.opMode == modeOff);
   expect(ack.alt == 0);
   expect(!ack.altValid);

   return 0;
}

/*
 * Second set of conditions
 */
static int testDecodeAck2(void)
{
   // Test data.
   //    ACK message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x80, 0x15, 0x06,
      // 0     1     2     3
      //type id    sys   alt               cks
      0x03, 0x15, 0xE9, 0xFF, 0xFB, 0x69, 0xAE
      // 4     5     6     7     8     9    10
   };
   sg_ack_t ack;

   // Test function:
   sgDecodeAck(buffer, &ack);

   // Test results:
   expect(ack.ackType == 3);
   expect(ack.ackId == 0x15);
   expect(ack.failXpdr);
   expect(!ack.failSystem);
   expect(!ack.failCrypto);
   expect(ack.wow);
   expect(!ack.maint);
   expect(ack.isHostAlt);
   expect(ack.opMode == modeAlt);
   expect(ack.alt == -1175);
   expect(ack.altValid);

   return 0;
}

/*
 * Third set of conditions
 */
static int testDecodeAck3(void)
{
   // Test data.
   //    ACK message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x80, 0x70, 0x06,
      // 0     1     2     3
      //type id    sys   alt               cks
      0x03, 0x70, 0x8E, 0x00, 0x00, 0x76, 0x57
      // 4     5     6     7     8     9    10
   };
   sg_ack_t ack;

   // Test function:
   sgDecodeAck(buffer, &ack);

   // Test results:
   expect(ack.ackType == 3);
   expect(ack.ackId == 0x70);
   expect(!ack.failXpdr);
   expect(ack.failSystem);
   expect(ack.failCrypto);
   expect(ack.wow);
   expect(!ack.maint);
   expect(!ack.isHostAlt);
   expect(ack.opMode == modeStby);
   expect(ack.alt == 118);
   expect(ack.altValid);

   return 0;
}

/*
 * Documented in the header file.
 */
int testDecodeAck(void)
{
   int res1 = testDecodeAck1();
   int res2 = testDecodeAck2();
   int res3 = testDecodeAck3();

   return res1 || res2 || res3;
}
