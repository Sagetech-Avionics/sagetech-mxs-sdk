/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testDecodeFlightId.c
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
 * First set of conditions
 */
static int testDecodeFlightId1(void)
{
   // Test data.
   //    Flight Id Reply message raw data capture
   uint8_t buffer[] =
   {
         0xAA, 0x82, 0x01, 0x0C,
         // 0     1     2     3
         //|------------------flight id---------------|
         0x41, 0x41, 0x31, 0x32, 0x33, 0x34, 0x20, 0x20,
         // 4     5     6     7     8     9    10    11
         //|-------rsvd-------|   cks
         0x00, 0x00, 0x00, 0x00, 0xC6
         //12    13    14    15    16
   };
   sg_flightid_t id;

   // Test function:
   sgDecodeFlightId(buffer, &id);

   // Test results:
   expect(strcmp(id.flightId, "AA1234  ") == 0);

   return 0;
}

/*
 * Second set of conditions
 */
static int testDecodeFlightId2(void)
{
   // Test data.
   //    Flight Id Reply message raw data capture
   uint8_t buffer[] =
   {
         0xAA, 0x82, 0x01, 0x0C,
         // 0     1     2     3
         //|------------------flight id---------------|
         0x30, 0x30, 0x5A, 0x5A, 0x41, 0x41, 0x39, 0x39,
         // 4     5     6     7     8     9    10    11
         //|-------rsvd-------|   cks
         0x00, 0x00, 0x00, 0x00, 0xC6
         //12    13    14    15    16
   };
   sg_flightid_t id;

   // Test function:
   sgDecodeFlightId(buffer, &id);

   // Test results:
   expect(strcmp(id.flightId, "00ZZAA99") == 0);

   return 0;
}

/*
 * Third set of conditions
 */
static int testDecodeFlightId3(void)
{
   // Test data.
   //    Flight Id Reply message raw data capture
   uint8_t buffer[] =
   {
         0xAA, 0x82, 0x01, 0x0C,
         // 0     1     2     3
         //|------------------flight id---------------|
         0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
         // 4     5     6     7     8     9    10    11
         //|-------rsvd-------|   cks
         0x00, 0x00, 0x00, 0x00, 0xC6
         //12    13    14    15    16
   };
   sg_flightid_t id;

   // Test function:
   sgDecodeFlightId(buffer, &id);

   // Test results:
   expect(strcmp(id.flightId, "        ") == 0);

   return 0;
}

/*
 * Documented in the header file.
 */
int testDecodeFlightId(void)
{
   int res1 = testDecodeFlightId1();
   int res2 = testDecodeFlightId2();
   int res3 = testDecodeFlightId3();

   return res1 || res2 || res3;
}
