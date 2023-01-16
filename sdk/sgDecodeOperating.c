/**
 * @copyright Copyright (c) 2022 Sagetech, Inc. All rights reserved.
 *
 * @file sgDecodeOperating.c
 * @author Justin.LeFever
 *
 * @date Feb 28, 2022
 *
 */

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "sg.h"
#include "sgUtil.h"

#define SG_PAYLOAD_LEN_OPMSG  SG_MSG_LEN_OPMSG - 5  /// the payload length.

#define PBASE                 4   /// the payload offset.
#define OFFSET_SQUAWK         0   /// the squawk code offset in the payload.
#define OFFSET_CONFIG         2   /// the mode/config offset in the payload.
#define OFFSET_EMRG_ID        3   /// the emergency flag offset in the payload.
#define OFFSET_ALT            4   /// the altitude offset in the payload.
#define OFFSET_RATE           6   /// the climb rate offset in the payload.
#define OFFSET_HEADING        8   /// the heading offset in the payload.
#define OFFSET_AIRSPEED       10  /// the airspeed offset in the payload.

typedef struct __attribute__((packed))
{
   uint8_t  start;
   uint8_t  type;
   uint8_t  id;
   uint8_t  payloadLen;
   uint8_t  squawk[2];
   uint8_t  modeConfig;
   uint8_t  emergencyIdent;
   uint8_t  altitude[2];
   uint8_t  altitudeRate[2];
   uint8_t  heading[2];
   uint8_t  airspeed[2];
} stl_t;

/*
 * Documented in the header file.
 */
bool sgDecodeOperating(uint8_t *buffer, operating_struct *stl)
{
   stl_t sgStl;
   memcpy(&sgStl, buffer, sizeof(stl_t));

   // Squawk Code
   uint8_t temp        = sgStl.squawk[0];
   sgStl.squawk[0]     = sgStl.squawk[1];
   sgStl.squawk[1]     = temp;
   stl->squawk         = toUint16(sgStl.squawk) & 0x0fff;

   // Mode/Configuration
   stl->opMode         = (op_mode_struct) sgStl.modeConfig & 0x03; // Bit 1-0 of Mode/Configuration field
   stl->savePowerUp    = sgStl.modeConfig & 0x04; // Bit 2 of Mode/Configuration field
   stl->enableSqt      = sgStl.modeConfig & 0x08; // Bit 3 of Mode/Configuration field
   stl->enableXBit     = sgStl.modeConfig & 0x10; // Bit 4 of Mode/Configuration field
   stl->milEmergency   = sgStl.modeConfig & 0x20; // Bit 5 of Mode/Configuration field

   // Emergency/Ident
   stl->emergcType     = (emergency_struct) sgStl.emergencyIdent & 0x07; // Bit 2-0 of Emergency/Ident field
   stl->identOn        = sgStl.emergencyIdent & 0x08; // Bit 3 of Emergency/Ident field

   // Altitude
   stl->altUseIntrnl   = toInt16(sgStl.altitude) & 0x8000; // Bit 15 of Altitude field
   stl->altHostAvlbl   = toInt16(sgStl.altitude) & 0x4000; // Bit 14 of Altitude field
   stl->altitude       = toInt16(sgStl.altitude) & 0x3fff; // Bit 13-0 of Altitude field

   // Altitude Rate
   stl->climbValid     = (toInt16(sgStl.altitudeRate) == 0x8000) ? 0 : 1; // If alt rate = 0x8000, then alt rate is not available
   stl->climbRate      = toInt16(sgStl.altitudeRate) & 0xffff; // Bit 15-0 of Altitude Rate field

   // Heading
   stl->headingValid   = toUint16(sgStl.heading) & 0x8000; // Bit 15 of Heading field
   stl->heading        = toUint16(sgStl.heading) & 0x7fff; // Bit 14-0 of Heading field

   // Airspeed
   stl->airspdValid    = toUint16(sgStl.airspeed) & 0x8000; // Bit 15 of Airspeed field
   stl->airspd         = toUint16(sgStl.airspeed) & 0x7fff; // Bit 14-0 of Airspeed field

   return true;
}
