/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file main.c
 * @author jimb
 *
 * @date Feb 11, 2021
 */

#include <stdio.h>
#include <mocha.h>
#include "testSgMessages.h"

int main(void)
{
   return describe(
         "Sagetech SDK",
         testEncodeInstall,
         testEncodeFlightId,
         testEncodeOperating,
         testEncodeGPS,
         testEncodeDataReq,
         testEncodeTargetReq,
         testEncodeMode,
         testDecodeAck,
         testDecodeInstall,
         testDecodeFlightId,
         testDecodeStatus,
         testDecodeHealthMonitor,
         testDecodeVersion,
         testDecodeSerialNumber,
         testDecodeSvrAirborne,
         testDecodeSvrSurface,
         testDecodeMsr);
   return 0;
}
