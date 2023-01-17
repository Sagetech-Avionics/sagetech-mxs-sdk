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


/**
 * Documented in the header file
 */
void gs2Buf(uint8_t* bufferPos, int16_t value, int mov)
{


	float grdspeed = value;


	int step = 0;

	if(mov == 0){
		bufferPos[0] =(uint8_t) 0;
	}
	else if(grdspeed == 0.0f)
	{
		bufferPos[0] = (uint8_t) 1;
	}
	else if(grdspeed <= 0.125f)
	{
		bufferPos[0] = (uint8_t)2;
	}
	else if(grdspeed <= 1.0f)
	{

		step =((int) (grdspeed/0.146f))-1;

		bufferPos[0] = (uint8_t)(3 +  step);
	}
	else if(grdspeed <= 2.0f)
	{
		if(grdspeed != 2.0f)
		{
			step = ((int) ((grdspeed-1.0f)/0.25f));
			bufferPos[0] = (uint8_t)(9 +  step);
		}
		else
		{
			bufferPos[0]= (uint8_t) 12;
		}

	}
	else if(grdspeed <= 15.0f)
	{
		if(grdspeed != 15.0f)
		{
			step = ((int) ((grdspeed-2.0f)/0.50f));
			bufferPos[0] = (uint8_t)(13 + step);
		}
		else
		{
			bufferPos[0] = (uint8_t) 38;
		}

	}
	else if(grdspeed <=70.0f)
	{
		if(grdspeed != 70.0f)
		{
			step = ((int) ((grdspeed-15.0f)/1.0f));
			bufferPos[0] = (uint8_t)(39 + step);
		}
		else
		{
			bufferPos[0] = (uint8_t)93;
		}

	}
	else  if(grdspeed <= 100.0f)
	{
		if(grdspeed != 100.0f)
		{
			step = ((int) ((grdspeed-70.0f)/2.0f));
			bufferPos[0] = (uint8_t)(94 + step);
		}
		else
		{
			bufferPos[0] = (uint8_t)108;
		}

	}
	else if(grdspeed <= 175.0f)
	{
		if(grdspeed != 175.0f)
		{
			step = ((int) ((grdspeed-100.0f)/5.0f));
			bufferPos[0] = (uint8_t)(109 + step);
		}
		else
		{
			bufferPos[0] = (uint8_t)123;
		}

	}
	else if(grdspeed > 175.0f)
	{
		bufferPos[0] = (uint8_t)124;
	}
	if(mov == 2) // decelerating
	{
		bufferPos[0] = (uint8_t)125;
	}
	if(mov == 3) // accelerating
	{
		bufferPos[0] = (uint8_t)127;
	}
	if(mov == 4) // backing up
	{
		bufferPos[0] =(uint8_t) 128;
	}


}
