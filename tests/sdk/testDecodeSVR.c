/**
 * @copyright Copyright (c) 2020 Sagetech, Inc. All rights reserved.
 *
 * @file testDecodeSVR.c
 * @author jimb
 *
 * @date Feb 15, 2021
 */

#include <stdint.h>
#include <stdbool.h>
#include <mocha.h>

#include "sg.h"
#include "testSgMessages.h"

/*
 * Documented in the header file.
 */
int testDecodeSvrAirborne(void)
{
   // Test data.
   //    Airborne state vector report raw buffer data capture.
   uint8_t buffer[] =
   {
      0xAA, 0x91, 0xB2, 0x2A,
      // 0     1     2     3     4     5     6     7
      //type            vflags      icao
      0x1F, 0xCF, 0x98, 0xA4, 0x80, 0xAB, 0xC1, 0x23,
      // 8     9    10    11    12    13    14    15
      //aq  toa                                 lat
      0x02, 0xEE, 0xDA, 0xEE, 0xB7, 0xEE, 0xDA, 0x20,
      //16    17    18    19    20    21    22    23
      //          lon               galt
      0x84, 0x6B, 0xA9, 0x9C, 0x42, 0x00, 0x00, 0x00,
      //24    25    26    27    28    29    30    31
      //nvel      evel        balt              vrate
      0xFC, 0xE8, 0x00, 0x00, 0x01, 0xE7, 0x80, 0x00,
      //32    33    34    35    36    37    38    39
      //    nic   elat              elon
      0x00, 0x00, 0x20, 0x84, 0x65, 0xA9, 0x9C, 0x42,
      //40    41    42
      //srv mode  cks
      0x00, 0x02, 0xFB
   };

   sg_svr_t svr;

   // Test function:
   sgDecodeSVR(buffer, &svr);

   // Test results:
   expect(svr.type == svrAirborne);

   expect(svr.validity.airSpeed);
   expect(svr.validity.baroAlt);
   expect(!svr.validity.baroVRate);
   expect(!svr.validity.geoAlt);
   expect(!svr.validity.geoVRate);
   expect(svr.validity.position);
   expect(!svr.validity.surfHeading);
   expect(!svr.validity.surfSpeed);

   expect(svr.evalidity.estPosition);
   expect(!svr.evalidity.estSpeed);

   expect(svr.addr == 0xABC123);
   expect(svr.addrType == svrAdrIcao);

   expect(((long) (svr.toaEst * 1000.0)) == 477703);
   expect(((long) (svr.toaPosition * 1000.0)) == 477429);
   expect(((long) (svr.toaSpeed * 1000.0)) == 477703);

   expect(((long) (svr.lat * 1000.0)) == 45727);
   expect(((long) (svr.lon * 1000.0)) == -121485);

   expect(svr.airborne.speed   == 99);
   expect(svr.airborne.heading == 179);
   expect(svr.airborne.velNS   == -99);
   expect(svr.airborne.velEW   == 0);
   expect(svr.airborne.geoAlt  == 0);
   expect(svr.airborne.baroAlt == 1950);
   expect(svr.airborne.vrate   == 0);
   expect(((long) (svr.airborne.estLat * 1000.0)) == 45727);
   expect(((long) (svr.airborne.estLon * 1000.0)) == -121485)

   expect(svr.survStatus == 0);
   expect(svr.mode == 2);
   expect(svr.nic == 0);

   return 0;
}

/*
 * Documented in the header file.
 */
int testDecodeSvrSurface(void)
{
   // Test data:
   //    Surface state vector report raw buffer data capture.
   uint8_t buffer[] =
   {
      0xAA, 0x91, 0x59, 0x18,
      // 0     1     2     3     4     5     6     7
      //type            vflags      icao
      0x17, 0x32, 0x18, 0x98, 0x00, 0xAB, 0xC1, 0x23,
      // 8     9    10    11    12    13    14    15
      //aq  toa                     lat
      0x02, 0x75, 0xDF, 0x75, 0xDF, 0x20, 0x84, 0x75,
      //16    17    18    19    20    21    22    23
      //lon             vel   hdg   nic   srv   mode
      0xA9, 0x9C, 0x42, 0x30, 0x80, 0x00, 0x00, 0x02,
      //24
      //cks
      0x30,
   };

   sg_svr_t svr;

   // Test function:
   sgDecodeSVR(buffer, &svr);

   // Test results:
   expect(svr.type == svrSurface);

   expect(!svr.validity.airSpeed);
   expect(!svr.validity.baroAlt);
   expect(!svr.validity.baroVRate);
   expect(!svr.validity.geoAlt);
   expect(!svr.validity.geoVRate);
   expect(svr.validity.position);
   expect(svr.validity.surfHeading);
   expect(svr.validity.surfSpeed);

   expect(!svr.evalidity.estPosition);
   expect(!svr.evalidity.estSpeed);

   expect(svr.addr == 0xABC123);
   expect(svr.addrType == svrAdrIcao);

   expect(((long) (svr.toaEst * 1000.0)) == 0);
   expect(((long) (svr.toaPosition * 1000.0)) == 235742);
   expect(((long) (svr.toaSpeed * 1000.0)) == 235742);

   expect(((long) (svr.lat * 1000.0)) == 45727);
   expect(((long) (svr.lon * 1000.0)) == -121485);

   expect(svr.surface.speed == 24);
   expect(svr.surface.heading == 180);

   expect(svr.survStatus == 0);
   expect(svr.mode == 2);
   expect(svr.nic == 0);

   return 0;
}
