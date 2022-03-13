/******************************************************************************
 *
 * Module: Crypto Stack
 *
 * File Name: CryIf.h
 *
 * Description: Header file for Crypto interface
 *
 ******************************************************************************/

#ifndef CRYIF_INC_CRYIF_H_
#define CRYIF_INC_CRYIF_H_

/* Id for the company in the AUTOSAR */
#define CRYIF_VENDOR_ID    (1000U)

/* CryIf Module Id */
#define CRYIF_MODULE_ID    (112U)

/* CryIf Instance Id */
#define CRYIF_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define CRYIF_SW_MAJOR_VERSION           (1U)
#define CRYIF_SW_MINOR_VERSION           (0U)
#define CRYIF_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version R21-11
 */
#define CRYIF_AR_RELEASE_MAJOR_VERSION   (4U)
#define CRYIF_AR_RELEASE_MINOR_VERSION   (7U)
#define CRYIF_AR_RELEASE_PATCH_VERSION   (0U)

/*
 * Macros for CRYIF Status
 */
#define CRYIF_INITIALIZED                (1U)
#define CRYIF_NOT_INITIALIZED            (0U)



/* AUTOSAR version checking between CryIf_Cfg.h and CryIf.h */
#include "../../CryIf/inc/CryIf_Cfg.h"
#if       ((CRYIF_CFG_AR_RELEASE_MAJOR_VERSION != CRYIF_AR_RELEASE_MAJOR_VERSION)\
		|| (CRYIF_CFG_AR_RELEASE_MINOR_VERSION != CRYIF_AR_RELEASE_MINOR_VERSION)\
		|| (CRYIF_CFG_AR_RELEASE_PATCH_VERSION != CRYIF_AR_RELEASE_PATCH_VERSION))
#error "The AR version of CryIf_Cfg.h does not match the expected version"

#endif

/* software version checking between CryIf_Cfg.h and CryIf.h */
#if       ((CRYIF_CFG_SW_MAJOR_VERSION != CRYIF_SW_MAJOR_VERSION)\
		|| (CRYIF_CFG_SW_MINOR_VERSION != CRYIF_SW_MINOR_VERSION)\
		|| (CRYIF_CFG_SW_PATCH_VERSION != CRYIF_SW_PATCH_VERSION))
#error "The Software version of CryIf_Cfg.h does not match the expected version"

#endif


/* AUTOSAR version checking between Crypto_GeneralTypes.h and CryIf.h */
#include "../../General/Crypto_GeneralTypes.h"
#if       ((CRYPTO_GENERAL_TYPES_AR_RELEASE_MAJOR_VERSION != CRYIF_AR_RELEASE_MAJOR_VERSION)\
		|| (CRYPTO_GENERAL_TYPES_AR_RELEASE_MINOR_VERSION != CRYIF_AR_RELEASE_MINOR_VERSION)\
		|| (CRYPTO_GENERAL_TYPES_AR_RELEASE_PATCH_VERSION != CRYIF_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Crypto_GeneralTypes.h does not match the expected version"

#endif

/* AUTOSAR version checking between Crypto_GeneralTypes.h and CryIf.h */
#include"../../Rte/Rte_Csm_Type.h"
#if       ((RTE_CSM_TYPE_AR_RELEASE_MAJOR_VERSION != CRYIF_AR_RELEASE_MAJOR_VERSION)\
		|| (RTE_CSM_TYPE_AR_RELEASE_MINOR_VERSION != CRYIF_AR_RELEASE_MINOR_VERSION)\
		|| (RTE_CSM_TYPE_AR_RELEASE_PATCH_VERSION != CRYIF_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Rte_Csm_Type.h does not match the expected version"

#endif

#include"../../Crypto/inc/Crypto.h"
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service id for CryIF init */
#define CRYIF_INIT_SID                   (uint8)0x00
/* Service id for Version info of this module */
#define CRYIF_GET_VERSION_INFO_SID       (uint8)0x01
/* Service id to request Job Processing Interface */
#define CRYIF_PROCESSJOB_SID             (uint8)0x03
/* Service id to dispatch job cancellation */
#define CRYIF_CANCELJOB_SID              (uint8)0x0e
/* Service id to notify  the completion of the request with the result*/
#define CRYIF_CALLBACKNOTIFICATION_SID   (uint8)0x0d

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* [SWS_CryIf_00009] */

 /* Det error when an Api is called before initialization */
 #define CRYIF_E_UNINIT		        (uint8)0x00

 /* Initialization of CRYIF module failed. */
 #define CRYIF_E_INIT_FAILED		(uint8)0x01

 /* API request called with invalid parameter (null pointer) */
 #define CRYIF_E_PARAM_POINTER		(uint8)0x02

 /* API request called with invalid parameter (out of range) */
 #define CRYIF_E_PARAM_HANDLE		(uint8)0x03

 /* API request called with invalid parameter (out of value) */
 #define CRYIF_E_PARAM_VALUE		(uint8)0x04

/* Source key element size does not match the target key elements size. */
#define CRYIF_E_KEY_SIZE_MISMATCH   (uint8)0x05

/*******************************************************************************
 *                              Function Pointer Types                              *
 *******************************************************************************/

 /* Function pointer for configured driver */
 typedef Std_ReturnType (*ProcessJobType) (uint32 objectId, Crypto_JobType* job );



/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/


typedef struct{
	uint32 channelId;
    uint32 objectId;
    uint8 DriverIndex;
}ChannelLookup;

typedef struct {
uint32 CryIfKeyId;
CryptoKey* CryIfKeyRef;

}CryIfKey;

typedef struct {
	uint32 CryIfChannelId;

}CryIfChannel;

 /* Configuration data structure of CryIf module [SWS_CryIf_91118] */
typedef struct{
	 uint8  numDriverObject;    /* Number of driver instances*/
	 uint8 numChannels;
     const ChannelLookup* Mapping;
     const ProcessJobType*    CryIfProcessJob; /* pointer to hold process job info to configured driver object */
}CryIf_ConfigType;




/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
void CryIf_Init (const CryIf_ConfigType* configPtr);
void CryIf_GetVersionInfo (Std_VersionInfoType* versioninfo);
Std_ReturnType CryIf_ProcessJob (uint32 channelId,Crypto_JobType* job);
Std_ReturnType CryIf_CancelJob (uint32 channelId,Crypto_JobType* job);

/*******************************************************************************
 *                      Callback Functions                                  *
 *******************************************************************************/
void CryIf_CallbackNotification (Crypto_JobType* job,Crypto_ResultType result);


/*******************************************************************************
 *                       External Variables                                 *
 *******************************************************************************/
extern const CryIf_ConfigType CryIf_Config;
extern const CryIfChannel cryIfChannel1;
#endif /* CRYIF_INC_CRYIF_H_ */
