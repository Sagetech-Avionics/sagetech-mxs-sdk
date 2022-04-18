/**
 * @copyright Copyright (c) 2020 Sagetech, Inc. All rights reserved.
 *
 * @file testDecodeMSR.c
 * @author jim billmeyer
 *
 * @date Mar 23, 2021
 */


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <mocha.h>

#include "sg.h"
#include "testSgMessages.h"


int testDecodeMsr(void)
{
   uint8_t buffer[] =
   {
      0xAA, 0x92, 0xDB, 0x21,
    //0     1     2     3     4     5     6     7
    //type              vflag icao              qual
      0x2F, 0x7F, 0xE0, 0xFC, 0xAC, 0x82, 0xEC, 0x01,
    //toa         ver   callsign
      0xBE, 0xAB, 0x02, 0x4E, 0x39, 0x37, 0x38, 0x43,
    //                  ecat  pri   cap codes
      0x50, 0x20, 0x20, 0x01, 0x00, 0x00, 0xB0, 0x00,
    //omode       nacp  nacv  sil   gva   nic   hrd
      0x00, 0x20, 0x0A, 0x02, 0x1B, 0x02, 0x01, 0x00,
    //vrate cks
      0x01, 0xCE
   };

   sg_msr_t msr;

   sgDecodeMSR(buffer, &msr);

   expect(msr.type == msrTypeV2Airborne);

   expect(msr.validity.priority);
   expect(msr.validity.sil);
   expect(msr.validity.nacv);
   expect(msr.validity.nacp);
   expect(msr.validity.opmode);
   expect(msr.validity.capcodes);

   expect(msr.addr              == 0xAC82EC);
   expect(msr.addrType          == svrAdrNonIcaoUnknown);
   expect(((uint32_t) (msr.toa * 1000.0 + 0.5)) == 381336);
   expect(msr.version           == adsbVerDO260B);
   expect(strcmp(msr.callsign, "N978CP  ") == 0);
   expect(msr.emitter           == adsbLight);
   expect(msr.size              == 0);
   expect(msr.priority          == priNone);

   expect(msr.capability.b2low  == false);
   expect(msr.capability.uat    == false);
   expect(msr.capability.arv    == true);
   expect(msr.capability.tsr    == true);
   expect(msr.capability.adsb   == false);
   expect(msr.capability.tcas   == true);
   expect(msr.capability.tcr    == tcrNone);

   expect(msr.opMode.gpsLatFmt  == true);
   expect(msr.opMode.gpsLatOfs  == gpslatLeft2m);
   expect(msr.opMode.gpsLonFmt  == true);
   expect(msr.opMode.gpsLonOfs  == gpsLonNodata);
   expect(msr.opMode.tcasRA     == false);
   expect(msr.opMode.ident      == false);
   expect(msr.opMode.singleAnt  == false);

   expect(msr.svQuality.nacp    == nacp10);
   expect(msr.svQuality.nacv    == nacv3dot0);
   expect(msr.svQuality.sda     == sdaHazardous);
   expect(msr.svQuality.silSupp == false);
   expect(msr.svQuality.sil     == svsilPow7);
   expect(msr.svQuality.gva     == gvaLT45m);
   expect(msr.svQuality.nicBaro == nicNonGilham);

   expect(msr.trackHeading      == trackTrueNorth);
   expect(msr.vrateType         == vrateGeoAlt);

   return 0;
}


