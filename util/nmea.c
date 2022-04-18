/**
 * @copyright (c) 2020 Sagetech, Inc. All rights reserved.
 *
 * @file nmea.c
 *
 * @date Mar 25, 2022
 */

#include <assert.h>
#include <stddef.h>
#include "nmea.h"

static bool convDeg(const char *str, uint8_t *degrees, uint8_t *minutes, float *minFrac)
{
   const uint8_t *start = (const uint8_t *) str;
   const uint8_t *end;
   const uint8_t *p;

   // Skip leading whitespace
   while (*start == ' ' || *start == '\t')
   {
       ++start;
   }
   // Find integer part
   for (end = start; *end >= '0' && *end <= '9'; ++end)
       ;
   // At least one degree digit?
   if (end - start < 3)
   {
       return false;
   }

   const uint8_t *const min = end - 2;

   // Integer minutes
   *minutes = ((min[0] - '0') * 10U) + (min[1] - '0');

   // Integer degrees
   while (start < min)
   {
       *degrees = (*degrees * 10U) + (*start++ - '0');
   }

   // Fractional minutes (if any)
   if (*end == '.')
   {
       start = end + 1;

       // Find fractional part
       for (end = start; *end >= '0' && *end <= '9'; ++end)
           ;
       // Fractional minutes
       for (p = end - 1; p >= start; --p)
       {
           *minFrac = (*minFrac + (*p - '0')) * 0.1;
       }
   }

   return true;
}

/*
 * Defined in the header file.
 */
bool nmea2Lat(const char *str, float *deg)
{
   assert(str != NULL);
   assert(deg != NULL);

   uint8_t degrees, minutes;
   float   minFrac;

   if (!convDeg(str, &degrees, &minutes, &minFrac))
   {
      return false;
   }

   if (degrees > 90 || minutes > 59)
   {
      return false;
   }

   float lat = degrees + (((float) minutes + minFrac) / 60.0);
   if (lat > 90.0)
   {
      return false;
   }

   *deg = lat;
   return true;
}

/*
 * Defined in the header file.
 */
bool nmea2Lon(const char *str, float *deg)
{
   assert(str != NULL);
   assert(deg != NULL);

   uint8_t degrees, minutes;
   float   minFrac;

   if (!convDeg(str, &degrees, &minutes, &minFrac))
   {
      return false;
   }

   if (degrees > 180 || minutes > 59)
   {
      return false;
   }

   float lat = degrees + (((float) minutes + minFrac) / 60.0);
   if (lat > 180.0)
   {
      return false;
   }

   *deg = lat;
   return true;
}

/*
 * Defined in the header files.
 */
bool nmea2Float(const char *str, float *value)
{
   assert(str != NULL);
   assert(value != NULL);

   const uint8_t *start = (const uint8_t *)str;
   const uint8_t *end;
   const uint8_t *p;

   // Components of parsed value.
   bool       negFlag = false;
   uint32_t   whole   = 0U;
   float      frac    = 0.0;

   // Skip leading whitespace
   while (*start == ' ' || *start == '\t')
   {
       ++start;
   }
   // Sign?
   if (*start == '-')
   {
       negFlag = true;
       ++start;
   }
   // Convert integer part
   while (*start >= '0' && *start <= '9')
   {
       whole = (whole * 10U) + (*start++ - '0');
   }

   end = start; // Save for function return value.

   // Fractional part (if any)
   if (*end == '.')
   {
       ++start;
       // Find end
       for (end = start; *end >= '0' && *end <= '9'; ++end)
           ;
       // Parse fraction
       for (p = end - 1; p >= start; --p)
       {
           frac = (frac + (*p - '0')) * 0.1;
       }
   }

   // Build result
   frac += whole;
   if (negFlag)
   {
      frac = -frac;
   }

   *value = frac;

   // Any unexpected characters?
   return *end == 0;
}

/*
 * Defined in the header files.
 */
bool nmea2Int(const char *str, int *value)
{
   assert(str != NULL);
   assert(value != NULL);

   const uint8_t *start = (const uint8_t *)str;
   const uint8_t *end;

   // Components of parsed value.
   bool       negFlag = false;
   uint32_t   whole   = 0U;

   // Skip leading whitespace
   while (*start == ' ' || *start == '\t')
   {
       ++start;
   }
   // Sign?
   if (*start == '-')
   {
       negFlag = true;
       ++start;
   }
   // Convert integer part
   while (*start >= '0' && *start <= '9')
   {
       whole = (whole * 10U) + (*start++ - '0');
   }

   end = start; // Save for function return value.

   if (negFlag)
   {
      whole = -whole;
   }

   *value = whole;

   // Any unexpected characters?
   return *end == 0;
}
