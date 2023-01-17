/**
 * @file sgEncodeSVR.c
 * @author Riley Barnes (riley.barnes@sagetech.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-16
 * 
 * @copyright Copyright (c) 2022 Sagetech, Inc. All rights reserved.
 * 
 */

#include "sg.h"
#include <string.h>
#include <sgUtil.h> // remember to switch this back to "



                                        // airborne surface
                                        // -------- --------
#define SV_PARAM_TOA_EPOS     (1 << 3)  // x
#define SV_PARAM_TOA_POS      (1 << 2)  // x        x
#define SV_PARAM_TOA_VEL      (1 << 1)  // x        x
#define SV_PARAM_LATLON       (1 << 0)  // x        x

#define SV_PARAM_GEOALT       (1 << 7)  // x
#define SV_PARAM_VEL          (1 << 6)  // x
#define SV_PARAM_SURF_GS      (1 << 5)  //          x
#define SV_PARAM_SURF_HEAD    (1 << 4)  //          x
#define SV_PARAM_BAROALT      (1 << 3)  // x
#define SV_PARAM_VRATE        (1 << 2)  // x
#define SV_PARAM_NIC          (1 << 1)  // x        x
#define SV_PARAM_ESTLAT       (1 << 0)  // x

#define SV_PARAM_ESTLON       (1 << 7)  // x
#define SV_PARAM_ESTNVEL      (1 << 6)
#define SV_PARAM_ESTEVAL      (1 << 5)
#define SV_PARAM_SURV         (1 << 4)  // x        x
#define SV_PARAM_REPORT       (1 << 3)  // x        x



/**
 * Documented in the header file.
 * 
 */
bool sgEncodeSVR(uint8_t *buffer, sg_svr_t *svr, uint8_t msgId  )
{

    buffer[0] = SG_MSG_START_BYTE;
    buffer[1] = 0x91;
    buffer[2] = msgId;

    // payload length a the end

    int ofs = 4 ;


    if(svr->type == svrAirborne)
    {
    	buffer[ ofs ] = 0x1F;

    	buffer[ ofs + 1 ] = 0xCF;

    	buffer[ ofs + 2 ] = 0x98;

    	ofs += 3;
    }
    if(svr->type == svrSurface) // surf
    {

    	buffer[ ofs ] = 0x17;

    	buffer[ ofs + 1 ] = 0x32;

    	buffer[ ofs + 2 ] = 0x18;

    	ofs += 3;
    }
    // validity flags


    buffer[ ofs ] = svr->flags;


    buffer[ ofs + 1 ] = svr->eflags;

    ofs += 2;

    icao2Buf(&buffer[ ofs ] , svr->addr);

    ofs += 3;

    buffer[ ofs ] = svr->addrType;

    ofs += 1;

    //toa
    if(buffer[ 4 ] & SV_PARAM_TOA_EPOS)
    {
    	toa2Buf(&buffer[ ofs ], svr->toaEst);
    	ofs += 2;
    }



    if(buffer[ 4 ] & SV_PARAM_TOA_POS)
    {
    	toa2Buf(&buffer[ ofs ], svr->toaPosition);
    	ofs += 2;
    }



    if(buffer[ 4 ] & SV_PARAM_TOA_VEL)
    {
    	toa2Buf(&buffer[ ofs ], svr->toaSpeed);
    	ofs += 2;
    }



     // lat lon wgs
    if(buffer[ 4 ] & SV_PARAM_LATLON)
    {

    	//lat
    	latLon2Buf(&buffer[ ofs ], svr->lat);

    	ofs += 3;

    	//lon
    	latLon2Buf(&buffer[ ofs ], svr->lon);

    	ofs += 3;

    }

    //geoalt
    if(buffer[ 5 ] & SV_PARAM_GEOALT)
    {
    	alt2Buf(&buffer[ ofs ], svr->airborne.geoAlt);

    	ofs+= 3;
    }

    //ns ew vel
   if(buffer[ 5 ] & SV_PARAM_VEL)
   {
	   //nvel
	   vel2Buf(&buffer[ ofs ] ,svr->airborne.velNS);

	   ofs += 2;

	   //evel
	   vel2Buf(&buffer[ ofs ],svr->airborne.velEW);

	   ofs += 2;
   }

   //grd speed surf
   if(buffer[ 5 ] & SV_PARAM_SURF_GS)
   {

	   gs2Buf(&buffer[ ofs ], svr->surface.speed, 1);

	   ofs += 1;
   }

   //heading surf
   if(buffer[ 5 ] & SV_PARAM_SURF_HEAD)
   {
	   heading2Buf(&buffer[ ofs ], svr->surface.heading);
	   ofs += 1;
   }


   //baro alt
   if(buffer[ 5 ] & SV_PARAM_BAROALT)
   {
	   alt2Buf(&buffer[ ofs ], svr->airborne.baroAlt);
	   ofs += 3;
   }

   // vert rate
   if( buffer[ 5 ] & SV_PARAM_VRATE )
   {
	   uint162Buf(&buffer[ ofs ], svr->airborne.vrate);
	   ofs += 2;

   }

   //nic
   if(buffer[ 5 ] & SV_PARAM_NIC)
   {
	   buffer[ ofs ] = svr->nic;
	   ofs += 1;

   }

   //elat
   if(buffer[ 5 ] & SV_PARAM_ESTLAT)
   {
	   latLon2Buf(&buffer[ ofs ], svr->airborne.estLat);
	   ofs += 3;

   }

   //elon
   if(buffer[6] & SV_PARAM_ESTLON)
   {
	   latLon2Buf(&buffer[ ofs ], svr->airborne.estLon);
	   ofs += 3;

   }

   //envel eevel these are not used by mxs

   //surv

   if(buffer[ 6 ] & SV_PARAM_SURV )
   {

	   buffer[ ofs ] = svr->survStatus;

	   ofs += 1;

   }

   //mode
   if(buffer[ 6 ] & SV_PARAM_REPORT)
   {
	   buffer[ ofs ] = svr->mode;
	   ofs += 1;

   }


   buffer[3] = ofs-4;
   //checksum
   appendChecksum(buffer, ofs +1);

    return true;
}


