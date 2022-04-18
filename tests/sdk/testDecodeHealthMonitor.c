/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testDecodeHealthMonitor.c
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
static int testDecodeHealthMonitor1(void)
{
   // Test data.
   //    Health Monitor message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x8D, 0x00, 0x03,
      // 0     1     2     3
      //soc   rf    pt   cks
      0x3E, 0x35, 0x34, 0xE1,
      // 4     5     6     7
   };
   sg_healthmonitor_t hlt;

   // Test function:
   sgDecodeHealthMonitor(buffer, &hlt);

   // Test results:
   expect(hlt.socTemp == 62);
   expect(hlt.rfTemp  == 53);
   expect(hlt.ptTemp  == 52);

   return 0;
}

/*
 * Second set of conditions
 */
static int testDecodeHealthMonitor2(void)
{
   // Test data.
   //    Health Monitor message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x8D, 0xCE, 0x03,
      // 0     1     2     3
      //soc   rf    pt   cks
      0x80, 0x7F, 0x00, 0x86,
      // 4     5     6     7
   };
   sg_healthmonitor_t hlt;

   // Test function:
   sgDecodeHealthMonitor(buffer, &hlt);

   // Test results:
   expect(hlt.socTemp == -128);
   expect(hlt.rfTemp  == 127);
   expect(hlt.ptTemp  == 0);

   return 0;
}

/*
 * Third set of conditions
 */
static int testDecodeHealthMonitor3(void)
{
   // Test data.
   //    Health Monitor message raw data capture
   uint8_t buffer[] =
   {
      0xAA, 0x8D, 0x00, 0x03,
      // 0     1     2     3
      //soc   rf    pt   cks
      0xFF, 0x00, 0x29, 0xE1,
      // 4     5     6     7
   };
   sg_healthmonitor_t hlt;

   // Test function:
   sgDecodeHealthMonitor(buffer, &hlt);

   // Test results:
   expect(hlt.socTemp == -1);
   expect(hlt.rfTemp  == 0);
   expect(hlt.ptTemp  == 41);

   return 0;
}

/*
 * Documented in the header file.
 */
int testDecodeHealthMonitor(void)
{
   int res1 = testDecodeHealthMonitor1();
   int res2 = testDecodeHealthMonitor2();
   int res3 = testDecodeHealthMonitor3();

   return res1 || res2 || res3;
}
