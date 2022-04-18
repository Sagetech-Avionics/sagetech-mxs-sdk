/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testDecodeVersion.c
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
static int testDecodeVersion1(void)
{
   // Test data.
   //    Version message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x8E, 0x05, 0x06,
      // 0     1     2     3
      //sw    fw  |-sw svn-|  |-fw svn-|   cks
      0x09, 0x09, 0x30, 0x4F, 0x30, 0x19, 0x1D
      // 4     5     6     7     8     9    10
   };
   sg_version_t vsn;

   // Test function:
   sgDecodeVersion(buffer, &vsn);

   // Test results:
   expect(vsn.swVersion      == 9);
   expect(vsn.fwVersion      == 9);
   expect(vsn.swSvnRevision  == 12367);
   expect(vsn.fwSvnRevision  == 12313);

   return 0;
}

/*
 * Second set of conditions
 */
static int testDecodeVersion2(void)
{
   // Test data.
   //    Version message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x8E, 0xF2, 0x06,
      // 0     1     2     3
      //sw    fw  |-sw svn-|  |-fw svn-|   cks
      0x07, 0x0A, 0xFE, 0x70, 0x00, 0x04, 0xB3
      // 4     5     6     7     8     9    10
   };
   sg_version_t vsn;

   // Test function:
   sgDecodeVersion(buffer, &vsn);

   // Test results:
   expect(vsn.swVersion      == 7);
   expect(vsn.fwVersion      == 10);
   expect(vsn.swSvnRevision  == 65136);
   expect(vsn.fwSvnRevision  == 4);

   return 0;
}

/*
 * Third set of conditions
 */
static int testDecodeVersion3(void)
{
   // Test data.
   //    Version message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x8E, 0x9B, 0x06,
      // 0     1     2     3
      //sw    fw  |-sw svn-|  |-fw svn-|   cks
      0x12, 0x1B, 0x8B, 0x02, 0xA0, 0x00, 0x33
      // 4     5     6     7     8     9    10
   };
   sg_version_t vsn;

   // Test function:
   sgDecodeVersion(buffer, &vsn);

   // Test results:
   expect(vsn.swVersion      == 18);
   expect(vsn.fwVersion      == 27);
   expect(vsn.swSvnRevision  == 35586);
   expect(vsn.fwSvnRevision  == 40960);

   return 0;
}

/*
 * Documented in the header file.
 */
int testDecodeVersion(void)
{
   int res1 = testDecodeVersion1();
   int res2 = testDecodeVersion2();
   int res3 = testDecodeVersion3();

   return res1 || res2 || res3;
}
