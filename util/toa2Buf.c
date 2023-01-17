/**
 * @file toa2Buf.c
 * @author Riley Barnes (riley.barnes@sagetech.com)
 * @brief
 * @version 0.1
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022 Sagetech, Inc. All rights reserved.
 *
 */
#include "sgUtil.h"
/**
 * Documented in the header file.
 */
void toa2Buf(uint8_t *bufferPos, float value)
{
    //convert to uint16_t

	uint16_t toa = (uint16_t)(value * 128.0);

	bufferPos[0] = (toa & 0xFF00) >>8;
	bufferPos[1] = toa & 0x00FF;
}
