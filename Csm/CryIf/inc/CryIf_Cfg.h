/*
 * CryIf_Cfg.h
 *
 *  Created on: Feb 28, 2022
 *      Author: UNiversaL
 */

#ifndef CRYIF_INC_CRYIF_CFG_H_
#define CRYIF_INC_CRYIF_CFG_H_


/*
 * Module Version 1.0.0
 */
#define CRYIF_CFG_SW_MAJOR_VERSION           (1U)
#define CRYIF_CFG_SW_MINOR_VERSION           (0U)
#define CRYIF_CFG_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.7.0
 */
#define CRYIF_CFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define CRYIF_CFG_AR_RELEASE_MINOR_VERSION   (7U)
#define CRYIF_CFG_AR_RELEASE_PATCH_VERSION   (0U)

/* Pre-compile option for Development Error Detect
 * SWS Item: ECUC_CryIf_00009
 * */
#define CRYIF_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API
 * SWS Item: ECUC_CryIf_00011
 * */
#define CRYIF_VERSION_INFO_API                (STD_ON)

/*Identifier of the crypto channel.
Specifies to which crypto channel the CSM queue is connected to */
#define CRYIF_CHANNEL_ID1                     (0U)

/* This parameter refers to a Crypto Driver Object.
Specifies to which Crypto Driver Object the crypto channel is connected to */

//#define CRYIF_DRIVER_OBJECT_REF           ProcessJob_REF






#endif /* CRYIF_INC_CRYIF_CFG_H_ */
