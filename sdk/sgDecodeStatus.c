/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file   sgDecodeStatus.c
 * @author jimb
 *
 * @date   Feb 10, 2021
 *
 * This file receives a raw Status Response message buffer and
 * parses the payload into a data struct.
 */

#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "sg.h"
#include "sgUtil.h"

/// built-in-test bit locations.
#define SG_STATUS_POWERUP    (1 << 7)
#define SG_STATUS_CONTINUOUS (1 << 6)
#define SG_STATUS_PROCESSOR  (1 << 4)
#define SG_STATUS_CRC        (1 << 3)
#define SG_STATUS_MEMORY     (1 << 2)
#define SG_STATUS_CALIBRATE  (1 << 1)
#define SG_STATUS_RECEIVER   (1 << 7)
#define SG_STATUS_POWER53V   (1 << 6)
#define SG_STATUS_ADC        (1 << 5)
#define SG_STATUS_PRESSURE   (1 << 4)
#define SG_STATUS_FPGA       (1 << 3)
#define SG_STATUS_RXLOCK     (1 << 2)
#define SG_STATUS_TXLOCK     (1 << 1)
#define SG_STATUS_SUPPRESS   (1 << 0)
#define SG_STATUS_TEMP       (1 << 7)
#define SG_STATUS_SQMONITOR  (1 << 6)
#define SG_STATUS_TXRATE     (1 << 5)
#define SG_STATUS_LATENCY    (1 << 4)
#define SG_STATUS_TXPOWER    (1 << 3)
#define SG_STATUS_VOLTAGE    (1 << 7)
#define SG_STATUS_ICAO       (1 << 6)
#define SG_STATUS_GPS        (1 << 5)

typedef struct __attribute__((packed))
{
   uint8_t  start;
   uint8_t  type;
   uint8_t  id;
   uint8_t  payloadLen;
   uint8_t  versionSW;
   uint8_t  versionFW;
   uint8_t  crc[4];
   uint8_t  bit[4];
   uint8_t  checksum;
} status_t;

/*
 * Documented in the header file.
 */
bool sgDecodeStatus(uint8_t *buffer, sg_status_t *status)
{
   status_t sgStatus;
   memcpy(&sgStatus, buffer, sizeof(status_t));
   
   status->crc        = toUint32(sgStatus.crc);
   status->versionSW  = sgStatus.versionSW;
   status->versionFW  = sgStatus.versionFW;
   status->powerUp    = sgStatus.bit[0] & SG_STATUS_POWERUP;
   status->continuous = sgStatus.bit[0] & SG_STATUS_CONTINUOUS;
   status->processor  = sgStatus.bit[0] & SG_STATUS_PROCESSOR;
   status->crcValid   = sgStatus.bit[0] & SG_STATUS_CRC;
   status->memory     = sgStatus.bit[0] & SG_STATUS_MEMORY;
   status->calibrated = sgStatus.bit[0] & SG_STATUS_CALIBRATE;
   status->receiver   = sgStatus.bit[1] & SG_STATUS_RECEIVER;
   status->power53v   = sgStatus.bit[1] & SG_STATUS_POWER53V;
   status->adc        = sgStatus.bit[1] & SG_STATUS_ADC;
   status->pressure   = sgStatus.bit[1] & SG_STATUS_PRESSURE;
   status->fpga       = sgStatus.bit[1] & SG_STATUS_FPGA;
   status->rxLock     = sgStatus.bit[1] & SG_STATUS_RXLOCK;
   status->txLock     = sgStatus.bit[1] & SG_STATUS_TXLOCK;
   status->mtSuppress = sgStatus.bit[1] & SG_STATUS_SUPPRESS;
   status->temp       = sgStatus.bit[2] & SG_STATUS_TEMP;
   status->sqMonitor  = sgStatus.bit[2] & SG_STATUS_SQMONITOR;
   status->txRate     = sgStatus.bit[2] & SG_STATUS_TXRATE;
   status->sysLatency = sgStatus.bit[2] & SG_STATUS_LATENCY;
   status->txPower    = sgStatus.bit[2] & SG_STATUS_TXPOWER;
   status->voltageIn  = sgStatus.bit[3] & SG_STATUS_VOLTAGE;
   status->icao       = sgStatus.bit[3] & SG_STATUS_ICAO;
   status->gps        = sgStatus.bit[3] & SG_STATUS_GPS;

   return true;
}
