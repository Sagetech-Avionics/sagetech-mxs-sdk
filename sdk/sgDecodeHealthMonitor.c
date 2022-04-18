/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file sgDecodeHealthMonitor.c
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
   int8_t   socTemp;
   int8_t   rfTemp;
   int8_t   ptTemp;
   uint8_t  checksum;
} health_t;

/*
 * Documented in the header file.
 */
bool sgDecodeHealthMonitor(uint8_t *buffer, sg_healthmonitor_t *hlt)
{
   health_t sgHlt;
   memcpy(&sgHlt, buffer, sizeof(health_t));

   hlt->socTemp   = sgHlt.socTemp;
   hlt->rfTemp    = sgHlt.rfTemp;
   hlt->ptTemp    = sgHlt.ptTemp;

   return true;
}
