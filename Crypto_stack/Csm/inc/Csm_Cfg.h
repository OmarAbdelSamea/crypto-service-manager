 /*
 ============================================================================
 Name        : Csm_Cfg.h
 Author      : Omar AbdelSamea
 Version     :
 Description : Pre-Compile Configuration Header file.
 ============================================================================
 */

#ifndef CSM_CFG_H
#define CSM_CFG_H

#include "Csm.h"

/*
 * Module Version 1.0.0
 */
#define CSM_CFG_SW_MAJOR_VERSION           (1U)
#define CSM_CFG_SW_MINOR_VERSION           (0U)
#define CSM_CFG_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.7.0
 */
#define CSM_CFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define CSM_CFG_AR_RELEASE_MINOR_VERSION   (7U)
#define CSM_CFG_AR_RELEASE_PATCH_VERSION   (0U)

/* Pre-compile option for Development Error Detect
 * SWS Item: 
 * */
#define CSM_DEV_ERROR_DETECT                (STD_ON)
#define CSM_RUNTIME_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API
 * SWS Item: 
 * */
#define CSM_VERSION_INFO_API                (STD_ON)

#define CSM_JOB_ID1		(0U)
#define CSM_JOB_ID2		(1U)
#define CSM_JOB_ID3		(2U)
#define USE_FNC 		(0U)
#define JOB_PRIORITY_SIGNATURE_GENERATE (2U)
#define JOB_PRIORITY_SIGNATURE_VERIFY   (1U)
#define JOB_PRIORITY_HASH               (3U)

#define MAX_QUEUE_SIZE 3

#define KEY_LENGTH_USED 64
#define CSM_KEY_ID (0U)
/* CsmCallback */
#define CSM_CALLBACK_FUNC (void)(*Csm_MainFunction)(void)

#endif /* CSM_CFG_H */
