/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file sgEncodeMode.c
 * @author Jacob.Garrison
 *
 * @date Mar 1, 2021
 *      
 * This file receives a mode message struct and
 * converts it into a mode message buffer.
 */

#include <stdbool.h>

#include "sg.h"
#include "sgUtil.h"

#define SG_PAYLOAD_LEN_MODE  SG_MSG_LEN_MODE - 5  /// the payload length.

#define PBASE                4   /// the payload offset.
#define OFFSET_MDE0          0   /// the mode settings first-byte offset in the payload.
#define OFFSET_MDE1          1   /// the mode settings second-byte offset in the payload.
#define OFFSET_RSVD          2   /// the reserved offset in the payload.

#define LEN_RSVD             3   /// the number of reserved bytes.

/*
 * Documented in the header file.
 */
bool sgEncodeMode(uint8_t *buffer, sg_mode_t *mode, uint8_t msgId)
{
   // populate header
   buffer[0]       = SG_MSG_START_BYTE;
   buffer[1]       = SG_MSG_TYPE_HOST_MODE;
   buffer[2]       = msgId;
   buffer[3]       = SG_PAYLOAD_LEN_MODE;

   // populate mode settings
   buffer[PBASE + OFFSET_MDE0] = 0;
   buffer[PBASE + OFFSET_MDE1] = mode->reboot << 5;

   // populate reserved fields
   for (int i = 0; i < LEN_RSVD; ++i)
   {
      buffer[PBASE + OFFSET_RSVD + i] = 0;
   }

   // populate checksum
   appendChecksum(buffer, SG_MSG_LEN_MODE);

   return true;
}
