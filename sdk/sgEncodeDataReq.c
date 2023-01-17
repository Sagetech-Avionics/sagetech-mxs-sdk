/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file sgEncodeDataReq.c
 * @author Jacob.Garrison
 *
 * @date Feb 23, 2021
 *      
 * This file receives a populated data request struct and
 * converts it into a data request message buffer.
 */

#ifndef NDEBUG
#include <assert.h>
#endif
#include <stdbool.h>
#include <stdlib.h>

#include "sg.h"
#include "sgUtil.h"

#define SG_PAYLOAD_LEN_DATAREQ  SG_MSG_LEN_DATAREQ - 5  /// the payload length.

#define PBASE                 4   /// the payload offset.

#define OFFSET_REQ_TYPE       0   /// the requested response message type
#define OFFSET_RSVD_1         1   /// a reserved field
#define OFFSET_RSVD_2         2   /// a reserved field
#define OFFSET_RSVD_3         3   /// a reserved field

#ifndef NDEBUG
/**
 * Validate all input parameters prior to bufferizing data. Function is
 * used during development in debug mode, only.
 *
 * @param data The populated target request message struct.
 *
 * no return value, an error code is thrown if any data is invalid
 */
static void checkDataReqInputs(sg_datareq_t *data)
{
   /* TODO: Separate civil and military functionality into different source files */

   assert(
         ((dataInstall <= data->reqType && data->reqType <= dataStatus) ||
         (dataMode <= data->reqType && data->reqType <= dataSerialNum) ||
         (dataTOD <= data->reqType && data->reqType <= dataCrypto) ||
         data->reqType == dataMilSettings) &&
         "Selected report type is not an enumerated value");
}
#endif

/*
 * Documented in the header file.
 */
bool sgEncodeDataReq(uint8_t *buffer, sg_datareq_t *data, uint8_t msgId)
{
#ifndef NDEBUG
   // Validate all data inputs (debug mode, only)
   checkDataReqInputs(data);
#endif

   // populate header
   buffer[0]       = SG_MSG_START_BYTE;
   buffer[1]       = SG_MSG_TYPE_HOST_DATAREQ;
   buffer[2]       = msgId;
   buffer[3]       = SG_PAYLOAD_LEN_DATAREQ;

   // populate Request Type
   buffer[PBASE + OFFSET_REQ_TYPE] = data->reqType;

   // populate Reserved fields
   buffer[PBASE + OFFSET_RSVD_1] = 0;
   buffer[PBASE + OFFSET_RSVD_2] = 0;
   buffer[PBASE + OFFSET_RSVD_3] = 0;

   // populate checksum
   appendChecksum(buffer, SG_MSG_LEN_DATAREQ);

   return true;
}
