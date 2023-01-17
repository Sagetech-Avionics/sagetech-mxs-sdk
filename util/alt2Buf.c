/**
 * @file alt2Buf.c
 * @author Riley Barnes (riley.barnes@sagetech.com)
 * @brief
 * @version 0.1
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022 Sagetech, Inc. All rights reserved.
 *
 */
#include "sgUtil.h"
#define SV_RES_ALT      0.015625


/**
 * Documented in the header file.
 */
void alt2Buf(uint8_t *bufferPos, uint32_t value)
{

	double alt = (double)value / SV_RES_ALT;

	int32_t altint  = (int32_t) alt;

	bufferPos[0] =  altint & 0xFF000000 >> 24;
	bufferPos[1] =  altint & 0x00FF0000 >> 16;
	bufferPos[2] =  altint & 0x0000FF00 >> 8;

}
