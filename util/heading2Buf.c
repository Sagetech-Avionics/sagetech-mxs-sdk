/**
 * @file heading2Buf.c
 * @author Riley Barnes (riley.barnes@sagetech.com)
 * @brief
 * @version 0.1
 * @date 2022-08-24
 *
 * @copyright Copyright (c) 2022 Sagetech, Inc. All rights reserved.
 *
 */

#include "sgUtil.h"
#define SV_RES_HEAD     1.40625


/**
 * Documented in the header file.
 */
void heading2Buf(uint8_t* bufferPos, uint16_t value)
{


	bufferPos[0] = (uint8_t) value/SV_RES_HEAD;

}
