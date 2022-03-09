/*
 * CryIf_Cfg.c
 *
 *  Created on: Feb 28, 2022
 *      Author: dell
 */



#include "../../CryIf/inc/CryIf.h"
#if       ((CRYIF_CFG_AR_RELEASE_MAJOR_VERSION != CRYIF_AR_RELEASE_MAJOR_VERSION)\
		|| (CRYIF_CFG_AR_RELEASE_MINOR_VERSION != CRYIF_AR_RELEASE_MINOR_VERSION)\
		|| (CRYIF_CFG_AR_RELEASE_PATCH_VERSION != CRYIF_AR_RELEASE_PATCH_VERSION))
#error "The AR version of CryIf.h does not match the expected version"

#endif

/* software version checking between CryIf_Cfg.h and CryIf.h */
#if       ((CRYIF_CFG_SW_MAJOR_VERSION != CRYIF_SW_MAJOR_VERSION)\
		|| (CRYIF_CFG_SW_MINOR_VERSION != CRYIF_SW_MINOR_VERSION)\
		|| (CRYIF_CFG_SW_PATCH_VERSION != CRYIF_SW_PATCH_VERSION))
#error "The Software version of CryIf.h does not match the expected version"

#endif

//include .h file of driver
#include "../inc/CryIf.h"



 #define CRYIF_DRIVER_OBJECT_NUM              (1U) /* Number of configured drivers */


/* Mapping Channel id to configured driver */
const ChannelLookup Channel_Cfg[1]={{0,0,0}};

const ProcessJobType ProcessJob_REF[1]  = {&Crypto_ProcessJob};

const CryIf_ConfigType CryIf_Config = {CRYIF_DRIVER_OBJECT_NUM,
		CRYIF_CHANNEL_ID1,
		Channel_Cfg,
		ProcessJob_REF};

const CryIfChannel cryIfChannel1={CRYIF_CHANNEL_ID1};
