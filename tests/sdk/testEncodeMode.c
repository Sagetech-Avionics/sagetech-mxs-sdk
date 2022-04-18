/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testEncodeMode.c
 * @author Jacob.Garrison
 *
 * @date Mar 1, 2021
 *      
 */

#include <stdbool.h>
#include <mocha.h>

#include "sg.h"
#include "testSgMessages.h"

/*
 * First set of conditions
 */
static int testEncodeMode1(void)
{
   // Test data.
   //    Mode message data
   sg_mode_t mode;
   mode.reboot = false;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_MODE];
   sgEncodeMode(buffer, &mode, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_MODE);    // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_MODE - 5);      // Payload length
   expect(buffer[4] == 0x00);                     // MDE0
   expect(buffer[5] == 0x00);                     // MDE1
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x00);                     // Reserved
   expect(buffer[9] == 0xBC);                     // Checksum

   return 0;
}

/*
 * Second set of conditions
 */
static int testEncodeMode2(void)
{
   // Test data.
   //    Mode message data
   sg_mode_t mode;
   mode.reboot = true;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_MODE];
   sgEncodeMode(buffer, &mode, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_MODE);    // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_MODE - 5);      // Payload length
   expect(buffer[4] == 0x00);                     // MDE0
   expect(buffer[5] == 0x20);                     // MDE1
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x00);                     // Reserved
   expect(buffer[9] == 0xDC);                     // Checksum

   return 0;
}

/*
 * Documented in the header file.
 */
int testEncodeMode(void)
{
    int res1 = testEncodeMode1();
    int res2 = testEncodeMode2();

    return res1 || res2;
}

