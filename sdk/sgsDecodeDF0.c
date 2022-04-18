/**
 * @copyright Copyright (c) 2020 Sagetech, Inc. All rights reserved.
 *
 * @file sgsDecodeDF0.c
 * @author jimbillmeyer
 *
 * @date Mar 30, 2021
 */

#include <stdint.h>
#include <stdbool.h>
#include "sgs.h"
#include "sgUtil.h"

#define DF0_PARAM_SLANT_RANGE   0
#define DF0_PARAM_BEARING       2
#define DF0_PARAM_BAROALT       3
#define DF0_PARAM_ADDR          6
#define DF0_PARAM_QUANT         9
#define DF0_PARAM_RI           10
#define DF0_PARAM_SURV         11
#define DF0_PARAM_TOA          12

/// the payload offset.
#define PBASE 4

/*
 * Documented in the header file.
 */
bool sgsDecodeDF0(uint8_t *data, sgs_df0_t *df0)
{
   df0->slantRange = toDist(&data[PBASE + DF0_PARAM_SLANT_RANGE]);
   df0->bearing    = toHeading(&data[PBASE + DF0_PARAM_BEARING]);
   df0->baroAlt    = toAlt(&data[PBASE + DF0_PARAM_BAROALT]);
   df0->addr       = toIcao(&data[PBASE + DF0_PARAM_ADDR]);
   df0->quant      = data[PBASE + DF0_PARAM_QUANT];
   df0->ri         = data[PBASE + DF0_PARAM_RI];
   df0->surv       = data[PBASE + DF0_PARAM_SURV];
   df0->toa        = toTOA(&data[PBASE + DF0_PARAM_TOA]);

   return true;
}
