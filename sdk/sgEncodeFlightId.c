/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file sgEncodeFlightId.c
 * @author Jacob.Garrison
 *
 * @date Feb 25, 2021
 *      
 */

#ifndef NDEBUG
#include <assert.h>
#endif
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "sg.h"
#include "sgUtil.h"

#define SG_PAYLOAD_LEN_FLIGHT  SG_MSG_LEN_FLIGHT - 5  /// the payload length.

#define PBASE               4   /// the payload offset.
#define OFFSET_ID           0   /// the flight id offset in the payload.
#define OFFSET_RSVD         8   /// the reserved field offset in the payload.

#define ID_LEN              8   /// the length of the flight identification field.

#ifndef NDEBUG
/**
 * Validate all input parameters prior to bufferizing data. Function is
 * used during development in debug mode, only.
 *
 * @param id The populated flight identification message struct.
 *
 * no return value, an error code is thrown if any data is invalid
 */
static void checkIdInputs(sg_flightid_t *id)
{
   bool pad = false;  // Flag when a space is encountered
   for (int i = 0; i < ID_LEN; ++i)
   {
      assert(
            (id->flightId[i] == 0x20 ||
            (0x30 <= id->flightId[i] && id->flightId[i] <= 0x39) ||
            (0x41 <= toupper(id->flightId[i]) && toupper(id->flightId[i]) <= 0x5A)) &&
            "Registration character is invalid");

      if (pad)
      {
         assert(
               id->flightId[i] == 0x20 &&
               "Spaces are valid for right-padding, only.");
      }
      else if (id->flightId[i] == 0x20)
      {
         pad = true;
      }
   }
   assert(
         id->flightId[ID_LEN] == '\0' &&
         "The final flight id field character must be the null terminator");
}
#endif


/*
 * Documented in the header file.
 */
bool sgEncodeFlightId(uint8_t *buffer, sg_flightid_t *id, uint8_t msgId)
{
#ifndef NDEBUG
   // Validate all data inputs (debug mode, only)
   checkIdInputs(id);
#endif

   // populate header
   buffer[0]       = SG_MSG_START_BYTE;
   buffer[1]       = SG_MSG_TYPE_HOST_FLIGHT;
   buffer[2]       = msgId;
   buffer[3]       = SG_PAYLOAD_LEN_FLIGHT;

   // populate flight identification
   charArray2Buf(&buffer[PBASE + OFFSET_ID], id->flightId, ID_LEN);

   // populate reserved field
   uint322Buf(&buffer[PBASE + OFFSET_RSVD], 0);

   // populate checksum
   appendChecksum(buffer, SG_MSG_LEN_FLIGHT);

   return true;
}
