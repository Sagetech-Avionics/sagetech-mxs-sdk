/**
 * @copyright (c) 2020 Sagetech, Inc. All rights reserved.
 *
 * @file nmea.h
 *
 * @date Mar 25, 2022
 */

#ifndef NMEA_H_
#define NMEA_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * Convert a NMEA latitude string of DDMM.MMM format to a double value in degrees.
 *
 * Note: contains the full NMEA conversion support and error detection.
 *
 * @param[in]  str The NMEA format latitude string value.
 * @param[out] deg On success the converted latitude in degrees.
 *
 * @return true if the conversion was successful, false if it failed.
 */
bool nmea2Lat(const char *str, float *deg);

/**
 * Convert a NMEA longitude string of DDDMM.MMM format to a double value in degrees.
 *
 * Note: contains the full NMEA conversion support and error detection.
 *
 * @param[in]  str The NMEA format longitude string value.
 * @param[out] deg On success the converted longitude in degrees.
 *
 * @return true if the conversion was successful, false if it failed.
 */
bool nmea2Lon(const char *str, float *deg);

/**
 * Convert a NMEA floating point string value to a double.
 *
 * Note: contains the full NMEA conversion support and error detection.
 *
 * @param[in]  str   The NMEA floating point formatted string to convert.
 * @param[out] value The converted double number.
 *
 * @return true if the conversion was successful, false if it failed.
 */
bool nmea2Float(const char *str, float *value);

/**
 * Convert a NMEA integer number to an int.
 *
 * @param str   The NMEA integer formatted string to convert.
 * @param value The converted int number.
 *
 * @return true if the conversion was successful, false if it failed.
 */
bool nmea2Int(const char *str, int *value);

#endif /* NMEA_H_ */
