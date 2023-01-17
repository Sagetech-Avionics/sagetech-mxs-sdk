/**
 * @file sgEncodeMSR.c
 * @author Riley Barnes (riley.barnes@sagetech.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022 Sagetech, Inc. All rights reserved.
 * 
 */



#include "sg.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "sgUtil.h"
#include <stdio.h>







#define MS_PARAM_TOA          (1 << 3)
#define MS_PARAM_ADSBVER      (1 << 2)
#define MS_PARAM_CALLSIGN     (1 << 1)
#define MS_PARAM_CATEMITTER   (1 << 0)

#define MS_PARAM_AVLEN        (1 << 7)
#define MS_PARAM_PRIORITY     (1 << 6)
#define MS_PARAM_CAPCODES     (1 << 5)
#define MS_PARAM_OPMODE       (1 << 4)
#define MS_PARAM_NACP         (1 << 3)
#define MS_PARAM_NACV         (1 << 2)
#define MS_PARAM_SDA          (1 << 1)
#define MS_PARAM_GVA          (1 << 0)

#define MS_PARAM_NIC          (1 << 7)
#define MS_PARAM_HEADING      (1 << 6)
#define MS_PARAM_VRATE        (1 << 5)




/**
 * Documented in the header file. 
 */
bool sgEncodeMSR(uint8_t *buffer, sg_msr_t *msr, uint8_t msgId)
{

    //traditional aa message header

    buffer[0] = SG_MSG_START_BYTE;
    buffer[1] = 0x92; 
    buffer[2] = msgId;
    
    int ofs = 4;

    if(msr->type == msrTypeV0)
    {
    	buffer[ ofs ] = 0x2F;

    	buffer[ ofs + 1 ] = 0x6E;

    	buffer[ ofs + 2 ] = 0x60;

    }

    if(msr->type == msrTypeV1Airborne)
    {
    	buffer[ ofs ] = 0x2F;

    	buffer[ ofs + 1 ] = 0x7E;

    	buffer[ ofs + 2 ] = 0xE0;
    }

    if(msr->type == msrTypeV1Surface)
    {
    	buffer[ ofs ] = 0x2F;

    	buffer[ ofs + 1 ] = 0xFE;

    	buffer[ ofs + 2 ] = 0xE0;
    }

    if(msr->type == msrTypeV2Airborne)
    {
    	buffer[ ofs ] = 0x2F;

    	buffer[ ofs + 1 ] = 0x7F;

    	buffer[ ofs + 2 ] = 0xE0;
    }

    if(msr->type == msrTypeV2Surface)
    {
    	buffer[ ofs ] = 0x2F;

    	buffer[ ofs + 1 ] = 0xFF;

    	buffer[ ofs + 2 ] = 0xE0;
    }

    ofs += 3;

    buffer [ ofs ] = msr->flags;

    ofs += 1;

    icao2Buf(&buffer[ ofs ], msr->addr );

    ofs += 3;

    buffer[ ofs ] = msr->addrType;

    ofs += 1;

    //toa
    if(buffer[ 4 ] & MS_PARAM_TOA)
    {
    	toa2Buf(&buffer[ ofs ], msr->toa);

    	ofs += 2;
    }

    //adsb ver
    if(buffer[ 4 ] & MS_PARAM_ADSBVER)
    {
    	buffer[ ofs ] = msr->version;
    	ofs += 1;
    }

    //callsign
    if(buffer[ 4 ] & MS_PARAM_CALLSIGN)
    {

    	charArray2Buf(&buffer[ ofs ], msr->callsign, 8);
    	ofs += 8;
    }

    //emitter
    if(buffer[ 4 ] & MS_PARAM_CATEMITTER)
    {
    	buffer[ ofs ] = msr->emitter;
    	ofs += 1;
    }

    // length width
    if(buffer[ 5 ] & MS_PARAM_AVLEN)
    {
    	buffer[ ofs ] = msr->size;
    	ofs += 1;
    }

    //priority
    if(buffer[ 5 ] & MS_PARAM_PRIORITY)
    {
    	buffer[ ofs ] = msr->priority;
    	ofs += 1;
    }

    //cap
    if(buffer[ 5 ] & MS_PARAM_CAPCODES)
    {
    	 buffer[ ofs ] = msr->capability.b2low << 3 ;

    	 buffer[ ofs + 1 ] = msr->capability.tcas << 7 |
    	                     msr->capability.adsb << 6 |
    	                     msr->capability.arv  << 5 |
    	                     msr->capability.tsr  << 4 |
    	                     msr->capability.tcr  << 3 |
    	                     msr->capability.uat  << 1 ;

    	 //the next byte is reserved skip but still keep empty

    	ofs += 3;
    }

    //opmode
    if(buffer[ 5 ] & MS_PARAM_OPMODE)
    {
    	buffer[ ofs ] = msr->opMode.tcasRA       << 5 |
    	                msr->opMode.ident        << 4 |
    	                msr->opMode.singleAnt    << 2 ;

    	buffer[ ofs + 1 ] = msr->opMode.gpsLatOfs    << 5 |
    	                    msr->opMode.gpsLonOfs;

    	ofs += 2;
    }

    //nacp
    if(buffer[ 5 ] & MS_PARAM_NACP)
    {
    	buffer[ ofs ] = msr->svQuality.nacp;
    	ofs += 1;
    }

    //nacv
    if(buffer[ 5 ] & MS_PARAM_NACV)
    {
    	buffer[ ofs ] = msr->svQuality.nacv;
    	ofs += 1;
    }

    //sil
    if(buffer[ 5 ] & MS_PARAM_SDA)
    {
    	buffer[ ofs ] = msr->svQuality.sda       << 3 |
    	                              msr->svQuality.silSupp   << 2 |
    	                              msr->svQuality.sil;
    	ofs += 1;
    }

    //gva
    if(buffer[ 5 ] & MS_PARAM_GVA)
    {
    	buffer[ ofs ] = msr->svQuality.gva;
    	ofs += 1;
    }

    //nic
    if(buffer[ 6 ] & MS_PARAM_NIC)
    {
    	buffer[ ofs ] = msr->svQuality.nicBaro;
    	ofs += 1;
    }

    //hrd
    if(buffer[ 6 ] & MS_PARAM_HEADING )
    {
    	buffer[ ofs ] = msr->trackHeading;
    	ofs += 1;
    }

    //vertrate type
    if(buffer[ 6 ] & MS_PARAM_VRATE)
    {
    	buffer[ ofs ] = msr->vrateType;
    	ofs += 1;
    }

    //payload length
    buffer[ 3 ] = ofs - 4;

    //checksum
    appendChecksum(buffer, ofs + 1 );

    return true;
}



