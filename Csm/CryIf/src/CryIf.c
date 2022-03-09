/*
 * CryIf.c
 *
 *  Created on: Feb 28, 2022
 *      Author: UNiversaL
 */

#include "../inc/CryIf.h"
#include<stdio.h>
/* AUTOSAR version checking between Det.c and V2xBtp.c */
#if (CRYIF_DEV_ERROR_DETECT == STD_ON)

#include "../../DET/inc/Det.h"
/* AUTOSAR Version checking between Det and CRYIF Modules */
#if        ((DET_AR_RELEASE_MAJOR_VERSION != CRYIF_AR_RELEASE_MAJOR_VERSION)\
		||  (DET_AR_RELEASE_MINOR_VERSION != CRYIF_AR_RELEASE_MINOR_VERSION)\
		||  (DET_AR_RELEASE_PATCH_VERSION != CRYIF_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"

#endif

#endif


/* Module Status */
uint8 CryIf_status=CRYIF_NOT_INITIALIZED;

/* pointer to Cfg structure */
const CryIf_ConfigType *Cfg=NULL_PTR;

/************************************************************************************
 * Service Name: CryIf_Init
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): ConfigPtr - Pointer to  configuration set
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes CryIf module.
 * Requirements: [SWS_CryIf_91000] [SWS_CryIf_00014] [SWS_CryIf_00015]
 * [SWS_CryIf_91019] The Configuration pointer configPtr shall always have a null
   pointer value
 ************************************************************************************/
void CryIf_Init (const CryIf_ConfigType* configPtr)
{
#if (CRYIF_DEV_ERROR_DETECT == STD_ON)
	if( configPtr!= NULL_PTR)
	{
		Det_ReportError(CRYIF_MODULE_ID, CRYIF_INSTANCE_ID, CRYIF_INIT_SID, CRYIF_E_INIT_FAILED);
	}
	else
#endif
	{
		CryIf_status=CRYIF_INITIALIZED;
		Cfg=&CryIf_Config;
	}
}


/************************************************************************************
 * Service Name: CryIf_GetVersionInfo
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 * Requirements: [SWS_CryIf_00017]
 ************************************************************************************/
#if (CRYIF_VERSION_INFO_API == STD_ON)
void CryIf_GetVersionInfo (Std_VersionInfoType* versioninfo)
{
#if (CRYIF_DEV_ERROR_DETECT == STD_ON)
	if( versioninfo == (void*)0)
	{
		Det_ReportError(CRYIF_MODULE_ID,CRYIF_INSTANCE_ID,CRYIF_GET_VERSION_INFO_SID,CRYIF_E_PARAM_POINTER);
	}
	else
#endif
	{
		versioninfo->vendorID=CRYIF_VENDOR_ID;
		versioninfo->moduleID=CRYIF_MODULE_ID;
		versioninfo->sw_major_version=CRYIF_AR_RELEASE_MAJOR_VERSION;
		versioninfo->sw_minor_version=CRYIF_AR_RELEASE_MINOR_VERSION;
		versioninfo->sw_patch_version=CRYIF_AR_RELEASE_PATCH_VERSION;
	}
}
#endif

/************************************************************************************
 * Service Name: CryIf_ProcessJob
 * Service ID[hex]: 0x02
 * Sync/Async: Depends on Configuration
 * Reentrancy: Reentrant
 * Parameters (in): channelId - Holds the identifier of the crypto channel.
 * Parameters (inout): Job -nter to the configuration of the job. Contains structures with user
 *  and primitive relevant information.
 * Parameters (out): None
 * Description: This interface dispatches the received jobs to the configured crypto driver object
 * Requirements: [SWS_CryIf_00027] [SWS_CryIf_00028]  [SWS_CryIf_00029] [SWS_CryIf_00044] [SWS_CryIf_00136]
 ************************************************************************************/
Std_ReturnType CryIf_ProcessJob (uint32 channelId,Crypto_JobType* job)
{		Std_ReturnType ret;

#if (CRYIF_DEV_ERROR_DETECT == STD_ON)
	if(CRYIF_NOT_INITIALIZED == CryIf_status)
	{
		Det_ReportError(CRYIF_MODULE_ID,CRYIF_INSTANCE_ID,CRYIF_PROCESSJOB_SID ,CRYIF_E_UNINIT);
		return E_NOT_OK;
	}
	else if (channelId > cryIfChannel1.CryIfChannelId )
	{
		Det_ReportError(CRYIF_MODULE_ID,CRYIF_INSTANCE_ID,CRYIF_PROCESSJOB_SID,CRYIF_E_PARAM_HANDLE);
		return E_NOT_OK;
	}
	else if (job == NULL_PTR)
	{
		Det_ReportError(CRYIF_MODULE_ID,CRYIF_INSTANCE_ID,CRYIF_PROCESSJOB_SID,CRYIF_E_PARAM_POINTER);
		return E_NOT_OK;
	}
	else
#endif
	{
		for(int i=0;i<=Cfg->numChannels;i++)
		{
			if(Cfg->Mapping[i].channelId==channelId)
			{
				uint32 ObjId =Cfg->Mapping[i].objectId;
				uint32 index =Cfg->Mapping[i].DriverIndex;
				ret= Cfg->CryIfProcessJob[index](ObjId,job);

				break;
			}
			else ret=E_NOT_OK;
		}
	}
	return ret;
}




/************************************************************************************
 * Service Name: CryIf_CallbackNotification
 * Service ID[hex]: 0x0d
 * Sync/Async: Synchronous
 * Reentrancy: Non Reentrant
 * Parameters (in): job - Points to the completed job's information structure. It contains a callback
   ID to identify which job is finished.
   result -Contains the result of the cryptographic operation
 * Parameters (inout): None
 * Parameters (out): None
 * Description: Notifies the CRYIF about the completion of the request with the result of the
   cryptographic operation.
 * Requirements: [SWS_CryIf_00107] [SWS_CryIf_00108]  [SWS_CryIf_00109]
 ************************************************************************************/

void CryIf_CallbackNotification (Crypto_JobType* job,Crypto_ResultType result)
{
#if (CRYIF_DEV_ERROR_DETECT == STD_ON)
	if(CRYIF_NOT_INITIALIZED == CryIf_status)
	{
		Det_ReportError(CRYIF_MODULE_ID,CRYIF_INSTANCE_ID,CRYIF_CALLBACKNOTIFICATION_SID ,CRYIF_E_UNINIT);
	}
	else if (job == NULL_PTR)
	{
		Det_ReportError(CRYIF_MODULE_ID,CRYIF_INSTANCE_ID,CRYIF_CALLBACKNOTIFICATION_SID ,CRYIF_E_PARAM_POINTER);
	}
	else
#endif
	{				printf("cryif: %d\n",(int) job->jobId);


		//Csm_CallbackNotification(result);
	}
}


