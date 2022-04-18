/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testEncodeDataReq.c
 * @author Jacob.Garrison
 *
 * @date Feb 23, 2021
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
static int testEncodeDataReq1(void)
{
   // Test data.
   //    Data request message data
   sg_datareq_t data;
   data.reqType = dataInstall;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_DATAREQ];
   sgEncodeDataReq(buffer, &data, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_DATAREQ); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_DATAREQ - 5);   // Payload length
   expect(buffer[4] == 0x81);                     // Data type
   expect(buffer[5] == 0x00);                     // Reserved
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x35);                     // Checksum

   return 0;
}

/*
 * Second set of conditions
 */
static int testEncodeDataReq2(void)
{
   // Test data.
   //    Data request message data
   sg_datareq_t data;
   data.reqType = dataFlightID;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_DATAREQ];
   sgEncodeDataReq(buffer, &data, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_DATAREQ); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_DATAREQ - 5);   // Payload length
   expect(buffer[4] == 0x82);                     // Data type
   expect(buffer[5] == 0x00);                     // Reserved
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x36);                     // Checksum

   return 0;
}

/*
 * Third set of conditions
 */
static int testEncodeDataReq3(void)
{
   // Test data.
   //    Data request message data
   sg_datareq_t data;
   data.reqType = dataStatus;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_DATAREQ];
   sgEncodeDataReq(buffer, &data, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_DATAREQ); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_DATAREQ - 5);   // Payload length
   expect(buffer[4] == 0x83);                     // Data type
   expect(buffer[5] == 0x00);                     // Reserved
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x37);                     // Checksum

   return 0;
}

/*
 * Fourth set of conditions
 */
static int testEncodeDataReq4(void)
{
   // Test data.
   //    Data request message data
   sg_datareq_t data;
   data.reqType = dataMode;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_DATAREQ];
   sgEncodeDataReq(buffer, &data, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_DATAREQ); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_DATAREQ - 5);   // Payload length
   expect(buffer[4] == 0x8C);                     // Data type
   expect(buffer[5] == 0x00);                     // Reserved
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x40);                     // Checksum

   return 0;
}

/*
 * Fifth set of conditions
 */
static int testEncodeDataReq5(void)
{
   // Test data.
   //    Data request message data
   sg_datareq_t data;
   data.reqType = dataHealth;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_DATAREQ];
   sgEncodeDataReq(buffer, &data, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_DATAREQ); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_DATAREQ - 5);   // Payload length
   expect(buffer[4] == 0x8D);                     // Data type
   expect(buffer[5] == 0x00);                     // Reserved
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x41);                     // Checksum

   return 0;
}

/*
 * Sixth set of conditions
 */
static int testEncodeDataReq6(void)
{
   // Test data.
   //    Data request message data
   sg_datareq_t data;
   data.reqType = dataVersion;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_DATAREQ];
   sgEncodeDataReq(buffer, &data, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_DATAREQ); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_DATAREQ - 5);   // Payload length
   expect(buffer[4] == 0x8E);                     // Data type
   expect(buffer[5] == 0x00);                     // Reserved
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x42);                     // Checksum

   return 0;
}

/*
 * Seventh set of conditions
 */
static int testEncodeDataReq7(void)
{
   // Test data.
   //    Data request message data
   sg_datareq_t data;
   data.reqType = dataSerialNum;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_DATAREQ];
   sgEncodeDataReq(buffer, &data, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_DATAREQ); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_DATAREQ - 5);   // Payload length
   expect(buffer[4] == 0x8F);                     // Data type
   expect(buffer[5] == 0x00);                     // Reserved
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x43);                     // Checksum

   return 0;
}

/*
 * Eighth set of conditions
 */
static int testEncodeDataReq8(void)
{
   // Test data.
   //    Data request message data
   sg_datareq_t data;
   data.reqType = dataTOD;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_DATAREQ];
   sgEncodeDataReq(buffer, &data, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_DATAREQ); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_DATAREQ - 5);   // Payload length
   expect(buffer[4] == 0xD2);                     // Data type
   expect(buffer[5] == 0x00);                     // Reserved
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x86);                     // Checksum

   return 0;
}

/*
 * Ninth set of conditions
 */
static int testEncodeDataReq9(void)
{
   // Test data.
   //    Data request message data
   sg_datareq_t data;
   data.reqType = dataMode5;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_DATAREQ];
   sgEncodeDataReq(buffer, &data, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_DATAREQ); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_DATAREQ - 5);   // Payload length
   expect(buffer[4] == 0xD3);                     // Data type
   expect(buffer[5] == 0x00);                     // Reserved
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x87);                     // Checksum

   return 0;
}

/*
 * Tenth set of conditions
 */
static int testEncodeDataReq10(void)
{
   // Test data.
   //    Data request message data
   sg_datareq_t data;
   data.reqType = dataCrypto;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_DATAREQ];
   sgEncodeDataReq(buffer, &data, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_DATAREQ); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_DATAREQ - 5);   // Payload length
   expect(buffer[4] == 0xD4);                     // Data type
   expect(buffer[5] == 0x00);                     // Reserved
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x88);                     // Checksum

   return 0;
}

/*
 * Eleventh set of conditions
 */
static int testEncodeDataReq11(void)
{
   // Test data.
   //    Data request message data
   sg_datareq_t data;
   data.reqType = dataMilSettings;

   //    Message ID
   uint8_t msgId = 0x01;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_DATAREQ];
   sgEncodeDataReq(buffer, &data, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_DATAREQ); // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_DATAREQ - 5);   // Payload length
   expect(buffer[4] == 0xD7);                     // Data type
   expect(buffer[5] == 0x00);                     // Reserved
   expect(buffer[6] == 0x00);                     // Reserved
   expect(buffer[7] == 0x00);                     // Reserved
   expect(buffer[8] == 0x8B);                     // Checksum

   return 0;
}

/*
 * Documented in the header file.
 */
int testEncodeDataReq(void)
{
    int res1 = testEncodeDataReq1();
    int res2 = testEncodeDataReq2();
    int res3 = testEncodeDataReq3();
    int res4 = testEncodeDataReq4();
    int res5 = testEncodeDataReq5();
    int res6 = testEncodeDataReq6();
    int res7 = testEncodeDataReq7();
    int res8 = testEncodeDataReq8();
    int res9 = testEncodeDataReq9();
    int res10 = testEncodeDataReq10();
    int res11 = testEncodeDataReq11();

    return res1 || res2 || res3 || res4 || res5 || res6 ||
           res7 || res8 || res9 || res10 || res11;
}
