/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testEncodeGPS.c
 * @author Jacob.Garrison
 *
 * @date Mar 1, 2021
 *      
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <mocha.h>

#include "sg.h"
#include "testSgMessages.h"

/*
 * First set of conditions
 */
static int testEncodeGPS1(void)
{
   // Test data.
   //    Gps message data
   sg_gps_t gps;
   strcpy(gps.longitude, "12219.75002");
   strcpy(gps.latitude, "4737.22400");
   strcpy(gps.grdSpeed, "1126.0");
   strcpy(gps.grdTrack, "077.5200");
   gps.latNorth = true;
   gps.lngEast = false;
   gps.fdeFail = true;
   gps.gpsValid = true;
   strcpy(gps.timeOfFix, "223323.000");
   gps.height = -200;
   gps.hpl = 5;
   gps.hfom = 12;
   gps.vfom = 20;
   gps.nacv = nacvUnknown;

   //    Message ID
   uint8_t msgId = 0xAA;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_GPS];
   sgEncodeGPS(buffer, &gps, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_GPS);     // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_GPS - 5);       // Payload length
   expect(buffer[4] == 0x31);                     // Lng
   expect(buffer[5] == 0x32);                     // Lng
   expect(buffer[6] == 0x32);                     // Lng
   expect(buffer[7] == 0x31);                     // Lng
   expect(buffer[8] == 0x39);                     // Lng
   expect(buffer[9] == 0x2E);                     // Lng
   expect(buffer[10] == 0x37);                    // Lng
   expect(buffer[11] == 0x35);                    // Lng
   expect(buffer[12] == 0x30);                    // Lng
   expect(buffer[13] == 0x30);                    // Lng
   expect(buffer[14] == 0x32);                    // Lng
   expect(buffer[15] == 0x34);                    // Lat
   expect(buffer[16] == 0x37);                    // Lat
   expect(buffer[17] == 0x33);                    // Lat
   expect(buffer[18] == 0x37);                    // Lat
   expect(buffer[19] == 0x2E);                    // Lat
   expect(buffer[20] == 0x32);                    // Lat
   expect(buffer[21] == 0x32);                    // Lat
   expect(buffer[22] == 0x34);                    // Lat
   expect(buffer[23] == 0x30);                    // Lat
   expect(buffer[24] == 0x30);                    // Lat
   expect(buffer[25] == 0x31);                    // Speed
   expect(buffer[26] == 0x31);                    // Speed
   expect(buffer[27] == 0x32);                    // Speed
   expect(buffer[28] == 0x36);                    // Speed
   expect(buffer[29] == 0x2E);                    // Speed
   expect(buffer[30] == 0x30);                    // Speed
   expect(buffer[31] == 0x30);                    // Track
   expect(buffer[32] == 0x37);                    // Track
   expect(buffer[33] == 0x37);                    // Track
   expect(buffer[34] == 0x2E);                    // Track
   expect(buffer[35] == 0x35);                    // Track
   expect(buffer[36] == 0x32);                    // Track
   expect(buffer[37] == 0x30);                    // Track
   expect(buffer[38] == 0x30);                    // Track
   expect(buffer[39] == 0x41);                    // Status
   expect(buffer[40] == 0x32);                    // Time
   expect(buffer[41] == 0x32);                    // Time
   expect(buffer[42] == 0x33);                    // Time
   expect(buffer[43] == 0x33);                    // Time
   expect(buffer[44] == 0x32);                    // Time
   expect(buffer[45] == 0x33);                    // Time
   expect(buffer[46] == 0x2E);                    // Time
   expect(buffer[47] == 0x30);                    // Time
   expect(buffer[48] == 0x30);                    // Time
   expect(buffer[49] == 0x30);                    // Time
   expect(buffer[50] == 0x00);                    // Height
   expect(buffer[51] == 0x00);                    // Height
   expect(buffer[52] == 0x48);                    // Height
   expect(buffer[53] == 0xC3);                    // Height
   expect(buffer[54] == 0x00);                    // HPL
   expect(buffer[55] == 0x00);                    // HPL
   expect(buffer[56] == 0xA0);                    // HPL
   expect(buffer[57] == 0x40);                    // HPL
   expect(buffer[58] == 0x00);                    // HFOM
   expect(buffer[59] == 0x00);                    // HFOM
   expect(buffer[60] == 0x40);                    // HFOM
   expect(buffer[61] == 0x41);                    // HFOM
   expect(buffer[62] == 0x00);                    // VFOM
   expect(buffer[63] == 0x00);                    // VFOM
   expect(buffer[64] == 0xA0);                    // VFOM
   expect(buffer[65] == 0x41);                    // VFOM
   expect(buffer[66] == 0x00);                    // NACv
   expect(buffer[67] == 0xF3);                    // Checksum

   return 0;
}

/*
 * Second set of conditions
 */
static int testEncodeGPS2(void)
{
   // Test data.
   //    Gps message data
   sg_gps_t gps;
   strcpy(gps.longitude, "05833.91482");
   strcpy(gps.latitude, "4917.11266");
   strcpy(gps.grdSpeed, "125.80");
   strcpy(gps.grdTrack, "185.2000");
   gps.latNorth = false;
   gps.lngEast = true;
   gps.fdeFail = false;
   gps.gpsValid = false;
   strcpy(gps.timeOfFix, "085601.010");
   gps.height = 15;
   gps.hpl = 60;
   gps.hfom = 176;
   gps.vfom = 75;
   gps.nacv = nacv0dot3;

   //    Message ID
   uint8_t msgId = 0x02;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_GPS];
   sgEncodeGPS(buffer, &gps, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_GPS);     // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_GPS - 5);       // Payload length
   expect(buffer[4] == 0x30);                     // Lng
   expect(buffer[5] == 0x35);                     // Lng
   expect(buffer[6] == 0x38);                     // Lng
   expect(buffer[7] == 0x33);                     // Lng
   expect(buffer[8] == 0x33);                     // Lng
   expect(buffer[9] == 0x2E);                     // Lng
   expect(buffer[10] == 0x39);                    // Lng
   expect(buffer[11] == 0x31);                    // Lng
   expect(buffer[12] == 0x34);                    // Lng
   expect(buffer[13] == 0x38);                    // Lng
   expect(buffer[14] == 0x32);                    // Lng
   expect(buffer[15] == 0x34);                    // Lat
   expect(buffer[16] == 0x39);                    // Lat
   expect(buffer[17] == 0x31);                    // Lat
   expect(buffer[18] == 0x37);                    // Lat
   expect(buffer[19] == 0x2E);                    // Lat
   expect(buffer[20] == 0x31);                    // Lat
   expect(buffer[21] == 0x31);                    // Lat
   expect(buffer[22] == 0x32);                    // Lat
   expect(buffer[23] == 0x36);                    // Lat
   expect(buffer[24] == 0x36);                    // Lat
   expect(buffer[25] == 0x31);                    // Speed
   expect(buffer[26] == 0x32);                    // Speed
   expect(buffer[27] == 0x35);                    // Speed
   expect(buffer[28] == 0x2E);                    // Speed
   expect(buffer[29] == 0x38);                    // Speed
   expect(buffer[30] == 0x30);                    // Speed
   expect(buffer[31] == 0x31);                    // Track
   expect(buffer[32] == 0x38);                    // Track
   expect(buffer[33] == 0x35);                    // Track
   expect(buffer[34] == 0x2E);                    // Track
   expect(buffer[35] == 0x32);                    // Track
   expect(buffer[36] == 0x30);                    // Track
   expect(buffer[37] == 0x30);                    // Track
   expect(buffer[38] == 0x30);                    // Track
   expect(buffer[39] == 0x82);                    // Status
   expect(buffer[40] == 0x30);                    // Time
   expect(buffer[41] == 0x38);                    // Time
   expect(buffer[42] == 0x35);                    // Time
   expect(buffer[43] == 0x36);                    // Time
   expect(buffer[44] == 0x30);                    // Time
   expect(buffer[45] == 0x31);                    // Time
   expect(buffer[46] == 0x2E);                    // Time
   expect(buffer[47] == 0x30);                    // Time
   expect(buffer[48] == 0x31);                    // Time
   expect(buffer[49] == 0x30);                    // Time
   expect(buffer[50] == 0x00);                    // Height
   expect(buffer[51] == 0x00);                    // Height
   expect(buffer[52] == 0x70);                    // Height
   expect(buffer[53] == 0x41);                    // Height
   expect(buffer[54] == 0x00);                    // HPL
   expect(buffer[55] == 0x00);                    // HPL
   expect(buffer[56] == 0x70);                    // HPL
   expect(buffer[57] == 0x42);                    // HPL
   expect(buffer[58] == 0x00);                    // HFOM
   expect(buffer[59] == 0x00);                    // HFOM
   expect(buffer[60] == 0x30);                    // HFOM
   expect(buffer[61] == 0x43);                    // HFOM
   expect(buffer[62] == 0x00);                    // VFOM
   expect(buffer[63] == 0x00);                    // VFOM
   expect(buffer[64] == 0x96);                    // VFOM
   expect(buffer[65] == 0x42);                    // VFOM
   expect(buffer[66] == 0x40);                    // NACv
   expect(buffer[67] == 0x4A);                    // Checksum

   return 0;
}

/*
 * Third set of conditions
 */
static int testEncodeGPS3(void)
{
   // Test data.
   //    Gps message data
   sg_gps_t gps;
   strcpy(gps.longitude, "12220.94600");
   strcpy(gps.latitude, "2759.28336");
   strcpy(gps.grdSpeed, "048.32");
   strcpy(gps.grdTrack, "275.4000");
   gps.latNorth = false;
   gps.lngEast = false;
   gps.fdeFail = false;
   gps.gpsValid = true;
   strcpy(gps.timeOfFix, "      .   ");
   gps.height = 6725;
   gps.hpl = 190;
   gps.hfom = 7410;
   gps.vfom = 200;
   gps.nacv = nacv3dot0;

   //    Message ID
   uint8_t msgId = 0xEE;

   // Test function:
   uint8_t buffer[SG_MSG_LEN_GPS];
   sgEncodeGPS(buffer, &gps, msgId);

   // Test results:
   expect(buffer[0] == SG_MSG_START_BYTE);        // Start byte
   expect(buffer[1] == SG_MSG_TYPE_HOST_GPS);     // Msg Type
   expect(buffer[2] == msgId);                    // Msg ID
   expect(buffer[3] == SG_MSG_LEN_GPS - 5);       // Payload length
   expect(buffer[4] == 0x31);                     // Lng
   expect(buffer[5] == 0x32);                     // Lng
   expect(buffer[6] == 0x32);                     // Lng
   expect(buffer[7] == 0x32);                     // Lng
   expect(buffer[8] == 0x30);                     // Lng
   expect(buffer[9] == 0x2E);                     // Lng
   expect(buffer[10] == 0x39);                    // Lng
   expect(buffer[11] == 0x34);                    // Lng
   expect(buffer[12] == 0x36);                    // Lng
   expect(buffer[13] == 0x30);                    // Lng
   expect(buffer[14] == 0x30);                    // Lng
   expect(buffer[15] == 0x32);                    // Lat
   expect(buffer[16] == 0x37);                    // Lat
   expect(buffer[17] == 0x35);                    // Lat
   expect(buffer[18] == 0x39);                    // Lat
   expect(buffer[19] == 0x2E);                    // Lat
   expect(buffer[20] == 0x32);                    // Lat
   expect(buffer[21] == 0x38);                    // Lat
   expect(buffer[22] == 0x33);                    // Lat
   expect(buffer[23] == 0x33);                    // Lat
   expect(buffer[24] == 0x36);                    // Lat
   expect(buffer[25] == 0x30);                    // Speed
   expect(buffer[26] == 0x34);                    // Speed
   expect(buffer[27] == 0x38);                    // Speed
   expect(buffer[28] == 0x2E);                    // Speed
   expect(buffer[29] == 0x33);                    // Speed
   expect(buffer[30] == 0x32);                    // Speed
   expect(buffer[31] == 0x32);                    // Track
   expect(buffer[32] == 0x37);                    // Track
   expect(buffer[33] == 0x35);                    // Track
   expect(buffer[34] == 0x2E);                    // Track
   expect(buffer[35] == 0x34);                    // Track
   expect(buffer[36] == 0x30);                    // Track
   expect(buffer[37] == 0x30);                    // Track
   expect(buffer[38] == 0x30);                    // Track
   expect(buffer[39] == 0x00);                    // Status
   expect(buffer[40] == 0x20);                    // Time
   expect(buffer[41] == 0x20);                    // Time
   expect(buffer[42] == 0x20);                    // Time
   expect(buffer[43] == 0x20);                    // Time
   expect(buffer[44] == 0x20);                    // Time
   expect(buffer[45] == 0x20);                    // Time
   expect(buffer[46] == 0x2E);                    // Time
   expect(buffer[47] == 0x20);                    // Time
   expect(buffer[48] == 0x20);                    // Time
   expect(buffer[49] == 0x20);                    // Time
   expect(buffer[50] == 0x00);                    // Height
   expect(buffer[51] == 0x28);                    // Height
   expect(buffer[52] == 0xD2);                    // Height
   expect(buffer[53] == 0x45);                    // Height
   expect(buffer[54] == 0x00);                    // HPL
   expect(buffer[55] == 0x00);                    // HPL
   expect(buffer[56] == 0x3E);                    // HPL
   expect(buffer[57] == 0x43);                    // HPL
   expect(buffer[58] == 0x00);                    // HFOM
   expect(buffer[59] == 0x90);                    // HFOM
   expect(buffer[60] == 0xE7);                    // HFOM
   expect(buffer[61] == 0x45);                    // HFOM
   expect(buffer[62] == 0x00);                    // VFOM
   expect(buffer[63] == 0x00);                    // VFOM
   expect(buffer[64] == 0x48);                    // VFOM
   expect(buffer[65] == 0x43);                    // VFOM
   expect(buffer[66] == 0x20);                    // NACv
   expect(buffer[67] == 0x42);                    // Checksum

   return 0;
}

/*
 * Documented in the header file.
 */
int testEncodeGPS(void)
{
    int res1 = testEncodeGPS1();
    int res2 = testEncodeGPS2();
    int res3 = testEncodeGPS3();

    return res1 || res2 || res3;
}

