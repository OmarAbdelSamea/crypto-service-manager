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

#include <Platform_Types.h>

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



/* CsmCallback */
#define CSM_CALLBACK_FUNC (void)(*Csm_MainFunction)(void)

#endif /* CSM_CFG_H */
