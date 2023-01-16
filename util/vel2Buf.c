/**
 * @file vel2Buf.c
 * @author Riley Barnes (riley.barnes@sagetech.com)
 * @brief
 * @version 0.1
 * @date 2022-08-25
 *
 * @copyright Copyright (c) 2022 Sagetech, Inc. All rights reserved.
 *
 */

#include "sgUtil.h"

#define SV_RES_VEL      0.125

/*
 * Documented in the header file.
 */
void vel2Buf(uint8_t *bufferPos, uint16_t value)
{
	double newvalue = value;

	uint16_t uvalue = newvalue/SV_RES_VEL;
	bufferPos[0] = uvalue >> 8;
	bufferPos[1] = uvalue & 0xFF;

}
