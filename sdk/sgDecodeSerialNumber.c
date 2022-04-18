/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file sgDecodeSerialNumber.c
 * @author Jacob.Garrison
 *
 * @date Mar 10, 2021
 *      
 */

#include <string.h>
#include <stdbool.h>

#include "sg.h"
#include "sgUtil.h"

#define SG_SN_LEN    32     // The number of bytes in each Serial Number message field

typedef struct __attribute__((packed))
{
   uint8_t  start;
   uint8_t  type;
   uint8_t  id;
   uint8_t  payloadLen;
   char     ifSN[SG_SN_LEN];
   char     rfSN[SG_SN_LEN];
   char     xpndrSN[SG_SN_LEN];
   uint8_t  checksum;
} serialnumber_t;

/*
 * Documented in the header file.
 */
bool sgDecodeSerialNumber(uint8_t *buffer, sg_serialnumber_t *sn)
{
   serialnumber_t sgSn;
   memcpy(&sgSn, buffer, sizeof(serialnumber_t));

   strcpy(sn->ifSN,    sgSn.ifSN);
   strcpy(sn->rfSN,    sgSn.rfSN);
   strcpy(sn->xpndrSN, sgSn.xpndrSN);

   // Ensure char arrays are null-terminated
   memset(&sn->ifSN[SG_SN_LEN],    '\0', 1);
   memset(&sn->rfSN[SG_SN_LEN],    '\0', 1);
   memset(&sn->xpndrSN[SG_SN_LEN], '\0', 1);

   return true;
}
