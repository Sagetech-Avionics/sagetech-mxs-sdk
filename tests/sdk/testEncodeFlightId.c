/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testEncodeFlightId.c
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
static int testEncodeFlightId1(void)
{
   // Test data.
   //    Flight id message data
   sg_flightid_t id;
   strcpy(id.flightId, "00ZZAA99");

   //    Message ID
   uint8_t msgId = 0xAA;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_FLIGHT];
   sgEncodeFlightId(buffer, &id, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_FLIGHT); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_FLIGHT - 5);   // Payload length
   expect(buffer[4] == 0x30);                     // ID
   expect(buffer[5] == 0x30);                     // ID
   expect(buffer[6] == 0x5A);                     // ID
   expect(buffer[7] == 0x5A);                     // ID
   expect(buffer[8] == 0x41);                     // ID
   expect(buffer[9] == 0x41);                     // ID
   expect(buffer[10] == 0x39);                    // ID
   expect(buffer[11] == 0x39);                    // ID
   expect(buffer[12] == 0);                       // Reserved
   expect(buffer[13] == 0);                       // Reserved
   expect(buffer[14] == 0);                       // Reserved
   expect(buffer[15] == 0);                       // Reserved
   expect(buffer[16] == 0x6A);                    // Checksum

   return 0;
}

/*
 * Second set of conditions
 */
static int testEncodeFlightId2(void)
{
   // Test data.
    //    Flight id message data
    sg_flightid_t id;
    strcpy(id.flightId, "        ");

    //    Message ID
    uint8_t msgId = 0x00;

    // Test function:
    uint8_t buffer[SG_MSG_LEN_FLIGHT];
    sgEncodeFlightId(buffer, &id, msgId);

    // Test results:
    expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
    expect(buffer[1] == SG_MSG_TYPE_HOST_FLIGHT); // Msg Type
    expect(buffer[2] == msgId);                    // Msg ID
    expect(buffer[3] == SG_MSG_LEN_FLIGHT - 5);   // Payload length
    expect(buffer[4] == 0x20);                     // ID
    expect(buffer[5] == 0x20);                     // ID
    expect(buffer[6] == 0x20);                     // ID
    expect(buffer[7] == 0x20);                     // ID
    expect(buffer[8] == 0x20);                     // ID
    expect(buffer[9] == 0x20);                     // ID
    expect(buffer[10] == 0x20);                    // ID
    expect(buffer[11] == 0x20);                    // ID
    expect(buffer[12] == 0);                       // Reserved
    expect(buffer[13] == 0);                       // Reserved
    expect(buffer[14] == 0);                       // Reserved
    expect(buffer[15] == 0);                       // Reserved
    expect(buffer[16] == 0xB8);                    // Checksum

    return 0;
}

/*
 * Third set of conditions
 */
static int testEncodeFlightId3(void)
{
   // Test data.
    //    Flight id message data
    sg_flightid_t id;
    strcpy(id.flightId, "ZA      ");

    //    Message ID
    uint8_t msgId = 0xFF;

    // Test function:
    uint8_t buffer[SG_MSG_LEN_FLIGHT];
    sgEncodeFlightId(buffer, &id, msgId);

    // Test results:
    expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
    expect(buffer[1] == SG_MSG_TYPE_HOST_FLIGHT); // Msg Type
    expect(buffer[2] == msgId);                    // Msg ID
    expect(buffer[3] == SG_MSG_LEN_FLIGHT - 5);   // Payload length
    expect(buffer[4] == 0x5A);                     // ID
    expect(buffer[5] == 0x41);                     // ID
    expect(buffer[6] == 0x20);                     // ID
    expect(buffer[7] == 0x20);                     // ID
    expect(buffer[8] == 0x20);                     // ID
    expect(buffer[9] == 0x20);                     // ID
    expect(buffer[10] == 0x20);                    // ID
    expect(buffer[11] == 0x20);                    // ID
    expect(buffer[12] == 0);                       // Reserved
    expect(buffer[13] == 0);                       // Reserved
    expect(buffer[14] == 0);                       // Reserved
    expect(buffer[15] == 0);                       // Reserved
    expect(buffer[16] == 0x12);                    // Checksum

    return 0;
}

/*
 * Documented in the header file.
 */
int testEncodeFlightId(void)
{
    int res1 = testEncodeFlightId1();
    int res2 = testEncodeFlightId2();
    int res3 = testEncodeFlightId3();

    return res1 || res2 || res3;
}
