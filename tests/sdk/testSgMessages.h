/**
 * @copyright Copyright (c) 2021 Sagetech, Inc. All rights reserved.
 *
 * @file testSgMessages.h
 * @author Jacob.Garrison
 *
 * @date Mar 2, 2021
 *      
 */

#ifndef SG_TESTMESSAGES_H_
#define SG_TESTMESSAGES_H_

/**
 * Unit test the Installation message builder.
 *
 * @return 0 of successful, -1 on failure.
 */
int testEncodeInstall(void);

/**
 * Unit test the Flight Identification message builder.
 *
 * @return 0 of successful, -1 on failure.
 */
int testEncodeFlightId(void);

/**
 * Unit test the Operating message builder.
 *
 * @return 0 of successful, -1 on failure.
 */
int testEncodeOperating(void);

/**
 * Unit test the GPS message builder.
 *
 * @return 0 of successful, -1 on failure.
 */
int testEncodeGPS(void);

/**
 * Unit test the Data Request message builder.
 *
 * @return 0 of successful, -1 on failure.
 */
int testEncodeDataReq(void);

/**
 * Unit test the Target Request message builder.
 *
 * @return 0 of successful, -1 on failure.
 */
int testEncodeTargetReq(void);

/**
 * Unit test the Mode message builder.
 *
 * @return 0 of successful, -1 on failure.
 */
int testEncodeMode(void);

/**
 * Unit test the ACK raw buffer message parser.
 *
 * @return 0 of successful, -1 on failure.
 */
int testDecodeAck(void);

/**
 * Unit test the Installation raw buffer message parser.
 *
 * @return 0 of successful, -1 on failure.
 */
int testDecodeInstall(void);

/**
 * Unit test the Flight Id raw buffer message parser.
 *
 * @return 0 of successful, -1 on failure.
 */
int testDecodeFlightId(void);

/**
 * Unit test the Status raw buffer message parser.
 *
 * @return 0 of successful, -1 on failure.
 */
int testDecodeStatus(void);

/**
 * Unit test the Health Monitor raw buffer message parser.
 *
 * @return 0 of successful, -1 on failure.
 */
int testDecodeHealthMonitor(void);

/**
 * Unit test the Version raw buffer message parser.
 *
 * @return 0 of successful, -1 on failure.
 */
int testDecodeVersion(void);

/**
 * Unit test the Serial Number raw buffer message parser.
 *
 * @return 0 of successful, -1 on failure.
 */
int testDecodeSerialNumber(void);

/**
 * Unit test the airborne SVR raw buffer message parser.
 *
 * @return 0 of successful, -1 on failure.
 */
int testDecodeSvrAirborne(void);

/**
 * Unit test the surface SVR raw buffer message parser.
 *
 * @return 0 of successful, -1 on failure.
 */
int testDecodeSvrSurface(void);

/**
 * Unit test the MSR raw buffer message parser.
 *
 * @return 0 of successful, -1 on failure.
 */
int testDecodeMsr(void);

#endif /* SG_TESTMESSAGES_H_ */
