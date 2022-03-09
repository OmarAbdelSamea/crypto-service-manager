#include "../inc/Crypto.h"
#include "../../DET/inc/Det.h"
#include<stdio.h>
 NvM_KeyPairType KeyPairs[4]={{0,0},{0,0},{0,0},{0,0}};
/* Global variable to hold the state of  Crypto Driver . */
STATIC uint8 Crypto_Status = Crypto_NOT_INITIALIZED; 
/* the state of driver */
STATIC uint8 Crypto_State;
/*state of key (valid or invalid) */
STATIC uint8 Key_State;
/* current job state in process*/
STATIC uint8 current_Job_State;
/* current job id in process*/
STATIC uint8 current_Job_id = -1;

#define QUEUE_MAX_SIZE 128

typedef struct 
{
  uint8 front, rear;
  uint8 size;
  CryptoSavedJobInfoType arr[QUEUE_MAX_SIZE];
}Queue;
STATIC Queue jobQueue;


sint8 getJob(uint32 jobId){

	for(uint8 i=jobQueue.front;i <= jobQueue.rear;i++)
	{

		if(jobId == jobQueue.arr[i].jobPtr->jobId)
		{
			return i;
		}
	}
	return -1;

}
boolean insertJob(Crypto_JobType* job){
   

if(jobQueue.size < QUEUE_MAX_SIZE)
   {
	boolean inserted=0;
	jobQueue.rear +=1;
	CryptoSavedJobInfoType temp;
	uint8 pos;
       for(uint8 i=jobQueue.front;i<=jobQueue.size;i++)
       {
            if (job->jobInfo.jobPriority > jobQueue.arr[i].jobPriority )
            {
            	 temp= jobQueue.arr[i];
			    jobQueue.arr[i].jobPriority =job->jobInfo.jobPriority;
			    jobQueue.arr[i].jobPtr = job;
			    inserted =1;
			    pos = i;
			    break;

            }

        }

       if(inserted==0)
       {

			jobQueue.arr[jobQueue.rear % QUEUE_MAX_SIZE].jobPriority =job->jobInfo.jobPriority;
			jobQueue.arr[jobQueue.rear % QUEUE_MAX_SIZE].jobPtr = job;
       }
       else {
    	   for(int j=jobQueue.rear-1;j>=pos+1;j--)
			{

				jobQueue.arr[j+1].jobPriority =jobQueue.arr[j].jobPriority;
				jobQueue.arr[j+1].jobPtr = jobQueue.arr[j].jobPtr;
			}
		  jobQueue.arr[pos+1] = temp;
       }
       jobQueue.size +=1;

       return TRUE;

   }
   return FALSE;

}

void deleteNextJob()
{
	if(jobQueue.size > 0)
	{
		jobQueue.front += 1;
		jobQueue.size -= 1;
	}
}
/************************************************************************************
* Service Name: Crypto_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to a selected configuration structure
* Parameters (inout): None
* Parameters (out): None
* Return value: void
* Description:  Initializes the Crypto Driver
* Requirements: SWS_Crypto_00215, SWS_Crypto_00198, SWS_Crypto_00045
************************************************************************************/
void Crypto_Init(const Crypto_ConfigType* configPtr){
// configPtr shall always have a null pointer value
// retrieve the key from NvM
NvM_ReadBlock(storedKey.CryptoNvBlockDescriptorRef->NvramBlockIdentifier, KeyPairs);
Crypto_Status= Crypto_INITIALIZED;
Crypto_State = CRYPTO_IDEAL_STATE;
jobQueue.front=0;
jobQueue.rear=-1;
jobQueue.size =0;


}
/************************************************************************************
* Service Name: Crypto_<vi>_<ai>_NvBlock_ReadFrom_<NvBlock>
* Service ID[hex]: 0x17
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): NvmBuffer The address of the buffer where the data can be read from.
* Parameters (inout): None
* Parameters (out): None
* Return value: Std_ReturnType
* Description:  This function is called by NVM to let the crypto driver copy the key data from the
                mirror of the NVM ram block to an internal RAM buffer of the crypto driver.
                The resulting function name shall be set to the container associated with the Nvm
                BlockDescriptor: {CryptoNvBlock/{CryptoNvBlockDescriptorRef} / NvMReadRam
                BlockFromNvCallback.
* Requirements: SRS_CryptoStack_00117, SRS_CryptoStack_00118
************************************************************************************/
Std_ReturnType Crypto_11_STM32F429_NvBlock_ReadFrom_storedKey(const void* NvmBuffer){

// check if NvmBuffer is not empty (SRS_CryptoStack_00117)
if(NvmBuffer!= NULL_PTR)
    {
        Key_State = KEY_VALID;
        return E_OK;
    }
else 
{
    Key_State =CRYPTO_E_KEY_EMPTY ;
    return CRYPTO_E_KEY_EMPTY;
}

}

/************************************************************************************
* Service Name: Crypto_ProcessJob
* Service ID[hex]: 0x03
* Sync/Async: Asynchronous or Async, depends on the job configuration
* Reentrancy: reentrant
* Parameters (in): objectId Holds the identifier of the Crypto Driver Object.
* Parameters (inout): job Pointer to the configuration of the job. 
                      Contains structures with job and primitive relevant information but also pointer to result buffers.
* Parameters (out): None
* Return value: Std_ReturnType
* Description:  Performs the crypto primitive, that is configured in the job parameter
* Requirements: SWS_Crypto_00057, SWS_Crypto_00058, SWS_Crypto_00059, SWS_Crypto_00064, SWS_Crypto_00067, SWS_Crypto_00070
************************************************************************************/
Std_ReturnType Crypto_ProcessJob (uint32 objectId,Crypto_JobType* job)
{

#if (CRYPTO_DEV_ERROR_DETECT == STD_ON)
	if (Crypto_NOT_INITIALIZED == Crypto_Status)
	{
		Det_ReportError(CRYPTO_MODULE_ID, CRYPTO_INSTANCE_ID, CRYPTO_PROCESS_JOB_SID, CRYPTO_E_UNINIT_ID);
		return E_NOT_OK;
	}
	if(objectId != CRYPTO_DRIVER_OBJECT_ID){

			Det_ReportError(CRYPTO_MODULE_ID, CRYPTO_INSTANCE_ID, CRYPTO_PROCESS_JOB_SID, CRYPTO_E_PARAM_HANDLE_ID );
			return E_NOT_OK;
	}

	if(NULL_PTR == job)
	{

		Det_ReportError(CRYPTO_MODULE_ID, CRYPTO_INSTANCE_ID, CRYPTO_PROCESS_JOB_SID, CRYPTO_E_PARAM_POINTER_ID );
	    return E_NOT_OK;
	 }

    if(job->jobPrimitiveInfo->primitiveInfo->service != verifyGenerateCryptoPrimitive.serviceUsed && 
    job->jobPrimitiveInfo->primitiveInfo->service != signatureGenerateCryptoPrimitive.serviceUsed
	&&job->jobPrimitiveInfo->primitiveInfo->service != hashGenerateCryptoPrimitive.serviceUsed  )
    {

        Det_ReportError(CRYPTO_MODULE_ID, CRYPTO_INSTANCE_ID, CRYPTO_PROCESS_JOB_SID, CRYPTO_E_PARAM_HANDLE_ID );
	    return E_NOT_OK;
    }
    if(!(job->jobPrimitiveInfo->primitiveInfo->service == signatureGenerateCryptoPrimitive.serviceUsed &&
       job->jobPrimitiveInfo->primitiveInfo->algorithm.family == signatureGenerateCryptoPrimitive.algorithmUsed &&
	   job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == signatureGenerateCryptoPrimitive.modeUsed &&
	   job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == CRYPTO_KEY_ELEMENT_SIZE))
    {
    	Det_ReportError(CRYPTO_MODULE_ID, CRYPTO_INSTANCE_ID, CRYPTO_PROCESS_JOB_SID, CRYPTO_E_PARAM_HANDLE_ID );
        return E_NOT_OK;

    }

    if(!(job->jobPrimitiveInfo->primitiveInfo->service == verifyGenerateCryptoPrimitive.serviceUsed &&
       job->jobPrimitiveInfo->primitiveInfo->algorithm.family == verifyGenerateCryptoPrimitive.algorithmUsed &&
 	   job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == verifyGenerateCryptoPrimitive.modeUsed &&
 	   job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == CRYPTO_KEY_ELEMENT_SIZE))
     {
     	Det_ReportError(CRYPTO_MODULE_ID, CRYPTO_INSTANCE_ID, CRYPTO_PROCESS_JOB_SID, CRYPTO_E_PARAM_HANDLE_ID );
         return E_NOT_OK;
     }
    if(!(job->jobPrimitiveInfo->primitiveInfo->service == hashGenerateCryptoPrimitive.serviceUsed &&
           job->jobPrimitiveInfo->primitiveInfo->algorithm.family == hashGenerateCryptoPrimitive.algorithmUsed &&
     	   job->jobPrimitiveInfo->primitiveInfo->algorithm.mode == hashGenerateCryptoPrimitive.modeUsed &&
     	   job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == CRYPTO_KEY_ELEMENT_SIZE))
         {
         	Det_ReportError(CRYPTO_MODULE_ID, CRYPTO_INSTANCE_ID, CRYPTO_PROCESS_JOB_SID, CRYPTO_E_PARAM_HANDLE_ID );
             return E_NOT_OK;
         }
    if(job->jobPrimitiveInputOutput.inputPtr == NULL_PTR)
        {
        	Det_ReportError(CRYPTO_MODULE_ID, CRYPTO_INSTANCE_ID, CRYPTO_PROCESS_JOB_SID, CRYPTO_E_PARAM_POINTER_ID );
            return E_NOT_OK;
        }

    if(job->cryptoKeyId != cryptoKey1.CryptoKeyId)
    {
    	Det_ReportError(CRYPTO_MODULE_ID, CRYPTO_INSTANCE_ID, CRYPTO_PROCESS_JOB_SID, CRYPTO_E_PARAM_HANDLE_ID );
    	return E_NOT_OK;


    }
#endif

    // save current job id
    current_Job_id =job->jobId;
    // check if job already in array, and need to start again reset the previous one
    sint8 res = getJob(job->jobId);
    // already in queue
    if(res != -1 && (job->jobPrimitiveInputOutput.mode == CRYPTO_OPERATIONMODE_START || job->jobPrimitiveInputOutput.mode == CRYPTO_OPERATIONMODE_SINGLECALL))
    {
    	// reset the info
    	jobQueue.arr[res].jobPriority = job->jobInfo.jobPriority;
    	jobQueue.arr[res].jobPtr = job;

    }


    // check if job state is idle and mode is not == start then E_NOT_OK
    if(job->jobState == CRYPTO_JOBSTATE_IDLE && (job->jobPrimitiveInputOutput.mode != CRYPTO_OPERATIONMODE_SINGLECALL || job->jobPrimitiveInputOutput.mode != CRYPTO_OPERATIONMODE_START ))
    {
    	return E_NOT_OK;
    }

    // if sync
    if(job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_SYNC)
    {
    	//check if crypto is busy
    	if(Crypto_State != CRYPTO_IDEAL_STATE )
    	{
    		return CRYPTO_E_BUSY;
    	}
    	else
    	{
        	// if not call Crypto_ProcessECDSA();->change states into this fn
    		CryptoSavedJobInfoType jobInfo= {job, job->jobInfo.jobPriority};
    		 return Crypto_ProcessECDSA(jobInfo);

    	}
    }

    else if (job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC)
    {
    	// check if queue is full
    	if (insertJob(job))
    		return E_OK;
    	else
    		return CRYPTO_E_BUSY;
    }
    else
    	return E_NOT_OK;

}

Std_ReturnType Crypto_ProcessECDSA (CryptoSavedJobInfoType jobInfo)
{
	if(jobInfo.jobPtr->jobPrimitiveInfo->primitiveInfo->service == hashGenerateCryptoPrimitive.serviceUsed){

		/*
		 * check if jobInfo.jobPtr->jobPrimitiveInputOutput->outputLengthPtr < hash length of the result returned from lib
		 * take the most significant bits from result
		 * then put result in jobInfo.jobPtr->jobPrimitiveInputOutput->outputPtr
		 *
		 * */
	}
	// at start turn  driver to busy
	Crypto_State = CRYPTO_ACTIVE_STATE;
	// start process
	current_Job_State = CRYPTO_OPERATIONMODE_START;
	/*call  SW_Crypto_SignatureGenerateStart(SW_Crypto_ConfigIdType cfgId,SW_Crypto_SignatureGenerateCtxBufType
	contextBuffer,//(SWS_SW_Crypto_00742)const SW_CRYPTO_AsymPrivateKeyType* keyPtr)
	if returned error or not E_OK
 	turn crypto state to ideal
 	and return E_NOT_OK

	*/
	current_Job_State = CRYPTO_OPERATIONMODE_UPDATE;
	/*call  SW_Crypto_SignatureGenerateUpdate(SW_Crypto_ConfigIdType cfgId,SW_Crypto_SignatureGenerateCtxBufType contextBuffer,const uint8* dataPtr,
	uint32 dataLength)
		if returned error or not E_OK
	 	turn crypto state to ideal
	 	and return E_NOT_OK

		*/
	current_Job_State = CRYPTO_OPERATIONMODE_FINISH;
	/*call  SW_Crypto_SignatureGenerateFinish(
	SW_Crypto_ConfigIdType cfgId,
	SW_Crypto_SignatureGenerateCtxBufType contextBuffer,
	uint8* resultPtr,
	uint32* resultLengthPtr)
			if returned error or not E_OK
		 	turn crypto state to ideal
		 	and return E_NOT_OK

			*/

	// at end turn driver to idle
	Crypto_State = CRYPTO_IDEAL_STATE;
	printf("id:%d pr:%d\n ",(int)jobInfo.jobPtr->jobId, (int)jobInfo.jobPtr->jobPriority);
	return E_OK;
}

/************************************************************************************
* Service Name: Crypto_CancelJob
* Service ID[hex]: 0x0e
* Sync/Async: Synchronous
* Reentrancy: Reentrant but not for same Crypto Driver Object
* Parameters (in): objectId Holds the identifier of the Crypto Driver Object.
* Parameters (inout): job Pointer to the configuration of the job.
                      Contains structures with job and primitive relevant information but also pointer to result buffers.
* Parameters (out): None
* Return value: Std_ReturnType
* Description: This interface removes the provided job from the queue and cancels the processing of the job if possible
* Requirements:
************************************************************************************/
Std_ReturnType Crypto_CancelJob (uint32 objectId,Crypto_JobType* job)
{
#if (CRYPTO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Module is initialized before using this function */
	if (Crypto_NOT_INITIALIZED == Crypto_Status)
	{
		Det_ReportError(CRYPTO_MODULE_ID, CRYPTO_INSTANCE_ID, CRYPTO_CANCEL_JOB_SID, CRYPTO_E_UNINIT_ID);
		return E_NOT_OK;
	}

	if(objectId != CRYPTO_DRIVER_OBJECT_ID)
	{
		Det_ReportError(CRYPTO_MODULE_ID, CRYPTO_INSTANCE_ID, CRYPTO_CANCEL_JOB_SID, CRYPTO_E_PARAM_HANDLE_ID );
		return E_NOT_OK;
	}

	if(NULL_PTR == job)
	{
		Det_ReportError(CRYPTO_MODULE_ID, CRYPTO_INSTANCE_ID, CRYPTO_PROCESS_JOB_SID, CRYPTO_E_PARAM_POINTER_ID );
		return E_NOT_OK;
	}
#endif

		//remove the job from the queue
		sint8 res=getJob(job->jobId);
		if(res!=-1 && job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC)
		{
			/* the main fn checks if priority is not equal -1 before process the job*/
			jobQueue.arr[res].jobPriority = -1;
			return E_OK;
		}
		else if( res==-1 && job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC)
			return E_NOT_OK;

		else if(current_Job_id != job->jobId && job->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_SYNC)
			//driver currently not process this job, the service Crypto_CancelJob() shall return E_OK without any processing
			return E_OK;

return 	E_NOT_OK;

}
/************************************************************************************
* Service Name: Crypto_MainFunction
* Service ID[hex]: 0x0c
* Sync/Async:
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: if asynchronous job processing is configured and there are job queues, the function
* 			   is called cyclically to process queued jobs
* Requirements:
************************************************************************************/

void Crypto_MainFunction (void)
{

//invoke higher priority job to process which is the front process but need to check if it cancelled or no jobs in queue
 if(jobQueue.arr[jobQueue.front].jobPriority != -1 && jobQueue.size != 0)
 {
	 Std_ReturnType res= Crypto_ProcessECDSA(jobQueue.arr[jobQueue.front]);
	 CryIf_CallbackNotification(jobQueue.arr[jobQueue.front].jobPtr,res);
	 deleteNextJob();
 }
 else if(jobQueue.arr[jobQueue.front].jobPriority== -1)
 {
	 deleteNextJob();
 }

}











