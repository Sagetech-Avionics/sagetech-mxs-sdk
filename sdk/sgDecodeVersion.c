/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file sgDecodeVersion.c
 * @author Jacob.Garrison
 *
 * @date Mar 10, 2021
 *      
 */

#include <string.h>
#include <stdbool.h>

#include "sg.h"
#include "sgUtil.h"

typedef struct __attribute__((packed))
{
   uint8_t  start;
   uint8_t  type;
   uint8_t  id;
   uint8_t  payloadLen;
   uint8_t  swVsn;
   uint8_t  fwVsn;
   uint8_t  swSvnRev[2];
   uint8_t  fwSvnRev[2];
   uint8_t  checksum;
} version_t;

/*
 * Documented in the header file.
 */
bool sgDecodeVersion(uint8_t *buffer, sg_version_t *vsn)
{
   version_t sgVsn;
   memcpy(&sgVsn, buffer, sizeof(version_t));

   vsn->swVersion      = sgVsn.swVsn;
   vsn->fwVersion      = sgVsn.fwVsn;
   vsn->swSvnRevision  = toUint16(sgVsn.swSvnRev);
   vsn->fwSvnRevision  = toUint16(sgVsn.fwSvnRev);

   return true;
}
