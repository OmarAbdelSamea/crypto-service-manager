/*
 ============================================================================
 Name        : Csm.c
 Author      : Omar AbdelSamea
 Version     :
 Description :
 ============================================================================
 */
#include "../inc/Csm.h"
#include "../../DET/inc/Det.h"

#if (CSM_DEV_ERROR_DETECT == STD_ON)

/* AUTOSAR Version checking between Det and Csm Modules */
#if ((DET_AR_RELEASE_MAJOR_VERSION != CSM_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != CSM_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_PATCH_VERSION != CSM_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

#define CRYPTO_JOBS_NUM 3

STATIC Csm_StateType Csm_State = CSM_STATE_UNINIT;
uint32 QueueLoopCounter = 0;

Crypto_QueueType queue;

/*signature structs */
const Crypto_AlgorithmInfoType signature_algo_info =
{       CRYPTO_ALGOFAM_ECCSEC,
		CRYPTO_ALGOFAM_NOT_SET,
		KEY_LENGTH_USED,
		CRYPTO_ALGOMODE_NOT_SET};
const Crypto_PrimitiveInfoType signature_primitiveInfo ={32,7,signature_algo_info};

const Crypto_JobPrimitiveInfoType signature_info={0,&signature_primitiveInfo,CRYIF_KEY_ID1,CRYPTO_PROCESSING_ASYNC,FALSE};
Crypto_JobType Crypto_JobType_SignatureGenerate =
{.jobId=CSM_JOB_ID1,
		.jobState=CRYPTO_JOBSTATE_IDLE,
		.jobInfo={CSM_JOB_ID1,JOB_PRIORITY_SIGNATURE_GENERATE},
		.jobPriority= JOB_PRIORITY_SIGNATURE_GENERATE,
		.jobPrimitiveInfo=&signature_info};

/*verify structs */

const Crypto_AlgorithmInfoType verify_algo_info =
{       CRYPTO_ALGOFAM_ECCSEC,
		CRYPTO_ALGOFAM_NOT_SET,
		KEY_LENGTH_USED,
		CRYPTO_ALGOMODE_NOT_SET};
const Crypto_PrimitiveInfoType verify_primitiveInfo ={32,CRYPTO_SIGNATUREVERIFY,verify_algo_info};

const Crypto_JobPrimitiveInfoType verify_info=
{1,&verify_primitiveInfo,CRYIF_KEY_ID1,CRYPTO_PROCESSING_ASYNC,FALSE};
Crypto_JobType Crypto_JobType_SignatureVerify =
{.jobId=CSM_JOB_ID2,
		.jobState=CRYPTO_JOBSTATE_IDLE,
		.jobInfo={CSM_JOB_ID2,JOB_PRIORITY_SIGNATURE_VERIFY},
		.jobPriority= JOB_PRIORITY_SIGNATURE_VERIFY,
		.jobPrimitiveInfo=&verify_info};
/* Hash Structs */


const Crypto_AlgorithmInfoType hash_algo_info =
{       CRYPTO_ALGOFAM_SHA2_256,
		CRYPTO_ALGOFAM_NOT_SET,
		KEY_LENGTH_USED,
		CRYPTO_ALGOMODE_NOT_SET};
const Crypto_PrimitiveInfoType hash_primitiveInfo ={32,CRYPTO_HASH,hash_algo_info};

const Crypto_JobPrimitiveInfoType hash_info=
{2,&hash_primitiveInfo,CRYIF_KEY_ID1,CRYPTO_PROCESSING_ASYNC,FALSE};

Crypto_JobType Crypto_JobType_Hash =
{.jobId=CSM_JOB_ID3,
		.jobState=CRYPTO_JOBSTATE_IDLE,
		.jobInfo={CSM_JOB_ID3,JOB_PRIORITY_HASH},
		.jobPriority= JOB_PRIORITY_HASH,
		.jobPrimitiveInfo=&hash_info};



Crypto_JobType *Crypto_Jobs[CRYPTO_JOBS_NUM] = {
		&Crypto_JobType_SignatureGenerate, &Crypto_JobType_SignatureVerify,
		&Crypto_JobType_Hash };



STATIC sint8 getJob(uint32 jobId){

	if( queue.size ==0)
		return -1;
	for(uint8 i=queue.front;i <= queue.rear;i++)
	{

		if(jobId == queue.jobInfo[i].jobId)
		{
			return i;
		}
	}
	return -1;

}
STATIC boolean insertJob( Crypto_JobInfoType jobInfo){


if(queue.size < MAX_QUEUE_SIZE)
   {
	boolean inserted=0;
	queue.rear +=1;
	Crypto_JobInfoType temp;
	uint8 pos;
       for(uint8 i=queue.front;i<=queue.size;i++)
       {
            if (jobInfo.jobPriority > queue.jobInfo[i].jobPriority )
            {
            	temp= queue.jobInfo[i];
			    queue.jobInfo[i].jobPriority =jobInfo.jobPriority;
			    inserted =1;
			    pos = i;
			    break;

            }

        }

       if(inserted==0)
       {

			queue.jobInfo[queue.rear % MAX_QUEUE_SIZE].jobPriority =jobInfo.jobPriority;
       }
       else {
    	   for(int j=queue.rear-1;j>=pos+1;j--)
			{

				queue.jobInfo[j+1].jobPriority =queue.jobInfo[j].jobPriority;
			}
		  queue.jobInfo[pos+1] = temp;
       }
       queue.size +=1;

       return TRUE;

   }
   return FALSE;

}

STATIC void deleteNextJob()
{
	if(queue.size > 0)
	{
		queue.front += 1;
		queue.size -= 1;
	}
}
/************************************************************************************
 * Service Name: Csm_Init
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): ConfigPtr - Pointer to a selected configuration structure
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the CSM module
 * Requirements: SWS_Csm_00186, SWS_Csm_00659
 ************************************************************************************/

void Csm_Init(const Csm_ConfigType *configPtr) {
	// TODO
	/* Init status global var set to Init
	 all jobs in Idle state.
	 clean all queues csm_jobs, csm_queues
	 clean queues
	 in csm_cfg.c -> csm_jobs , csm_queues
	 */

#if (CSM_DEV_ERROR_DETECT == STD_ON)
	if (configPtr != NULL_PTR) {
		Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID, CSM_INIT_SID,
		CSM_E_PARAM_POINTER);

		Csm_State = CSM_STATE_UNINIT;
	} else
#endif
	{
		queue.capacity = MAX_QUEUE_SIZE;
		queue.size=0;
		queue.rear=-1;
		queue.front=0;

		Csm_State = CSM_STATE_INIT;
	}
	/*
	 - Initialization of CSM module failed CSM_E_INIT_FAILED
	 */
}

/************************************************************************************
 * Service Name: Csm_SignatureGenerate
 * Service ID[hex]: 0x76
 * Sync/Async: Depends on configuration
 * Reentrancy: Reentrant
 * Parameters (in): 	uint32 jobId,
 Crypto_OperationModeType mode,
 const uint8* dataPtr,
 uint32 dataLength,
 uint8* signaturePtr,
 uint32* signatureLengthPtr
 * Parameters (inout): None
 * Parameters (out): Std_ReturnType
 * Return value: None
 * Description: Initializes the CSM module
 * Requirements:
 ************************************************************************************/

Std_ReturnType Csm_SignatureGenerate(uint32 jobId,Crypto_OperationModeType mode, const uint8 *dataPtr, uint32 dataLength,uint8 *signaturePtr, uint32 *signatureLengthPtr) {

	/*
	 Validation
	 1. API request called with invalid parameter (Nullpointer) 						CSM_E_PARAM_POINTER
	 2. Csm Configuration ID out of range 					   						CSM_E_PARAM_HANDLE
	 3. API request called before initialization of CSM module  						CSM_E_UNINIT
	 4. API request called with invalid processing mode 		   						CSM_E_PROCESSING_MODE
	 5. Mismatch between the called API request and the service type of the job		CSM_E_SERVICE_TYPE
	 6. Queue overrun																CSM_E_QUEUE_FULL
	 */

	/*
	 1. [SWS_Csm_91008]  While the CSM is not initialized and any function of the CSM
	 API is called, except of CSM_Init() and Csm_GetVersionInfo(), the operation
	 shall not be performed and CSM_E_UNINIT shall be reported to the DET when
	 CsmDevErrorDetect is true
	 */

	if (Csm_State == CSM_STATE_UNINIT) {
#if (CSM_DEV_ERROR_DETECT == STD_ON)
		Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
		CSM_SIGNATURE_VERIFY_SID,
		CSM_E_UNINIT);
#endif
		return E_NOT_OK;
	}

	/*
	 2. [SWS_Csm_91009] If a pointer to null is passed to an API function and the
	 corresponding input or output data are not re-directed to a key element, the operation
	 shall not be performed and CSM_E_PARAM_POINTER shall be reported to the DET
	 when CsmDevErrorDetect is true.
	 */

	if (dataPtr == NULL_PTR || signatureLengthPtr == NULL_PTR) {
#if (CSM_DEV_ERROR_DETECT == STD_ON)
		Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
		CSM_SIGNATURE_VERIFY_SID,
		CSM_E_PARAM_POINTER);
#endif
		return E_NOT_OK;
	}

	/*
	 3. [SWS_Csm_91011] If a CSM API with a ID handle in its interface is called and the
	 ID handle is out of range, the operation shall not be performed and CSM_E_PARAM_HANDLE
	 shall be reported to the DET when CsmDevErrorDetect is true.
	 */

	if (jobId >= CRYPTO_JOBS_NUM) {
#if (CSM_DEV_ERROR_DETECT == STD_ON)
		Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
		CSM_SIGNATURE_VERIFY_SID,
		CSM_E_PARAM_HANDLE);
#endif
		return E_NOT_OK;
	}

	/*
	 4. [SWS_Csm_01091] If a CSM API with a job handle (called jobId) in its interface is
	 called and the Crypto_ServiceInfoType of the job does not match the requested
	 service, the operation shall not be performed and CSM_E_SERVICE_TYPE shall be
	 reported to the DET when CsmDevErrorDetect is true.
	 */

	if (Crypto_Jobs[jobId]->jobPrimitiveInfo->primitiveInfo->service != CRYPTO_SIGNATUREGENERATE)
	{
#if (CSM_RUNTIME_ERROR_DETECT == STD_ON)
		Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
		CSM_SIGNATURE_VERIFY_SID,
		CSM_E_SERVICE_TYPE);
#endif
		return E_NOT_OK;
	}

	/*
	 5. [SWS_Csm_01088] If a CSM job needs to be queued and the queue is full, the
	 runtime error CSM_E_QUEUE_FULL shall be reported to the DET.
	 */

	if (queue.size == queue.capacity) {
#if (CSM_RUNTIME_ERROR_DETECT == STD_ON)
		Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
		CSM_SIGNATURE_VERIFY_SID,
		CSM_E_QUEUE_FULL);
#endif
		return CRYPTO_E_BUSY;
	}

	/*
	 TODO

	 1. [SWS_Csm_00017] If a service of the CSM module is requested and the
	 corresponding job is in "ACTIVE" state, the job request shall call
	 CryIf_ProcessJob() and pass on the return value. Sync?

	 2. [SWS_Csm_00018] If a service of the CSM module is requested, and the
	 CSM job needs to be queued and the queue is full, the job request shall be rejected
	 with the return value CRYPTO_E_BUSY. DONE
	 */

	/*
	 3. [SWS_Csm_00019] If an asynchronous interface is configured, the CSM module
	 shall provide a main function Csm_MainFunction() which is called cyclically to control
	 processing of the jobs via a state machine.

	 4. [SWS_Csm_01033] The CSM crypto services shall support to process multiple
	 operation mode inputs with a single call.

	 5. [SWS_Csm_01045] If the CRYPTO_OPERATIONMODE_START and
	 CRYPTO_OPERATIONMODE_FINISH bits are set and the
	 CRYPTO_OPERATIONMODE_UPDATE is not set, the Csm_<Service>() function
	 shall return with E_NOT_OK

	 6. [SWS_Csm_00036] If the asynchronous interface is used, the interface functions
	 shall only hand over the necessary information to the underlying Crypto Stack
	 modules.

	 */
	// check if jobId already in queue
	    sint8 res = getJob(jobId);
	 // already in queue
	    if(res != -1)
	    {
	    	return E_NOT_OK;

	    }
	Crypto_JobPrimitiveInputOutputType NewJobPrimitiveInputOutputType = {
			.inputPtr = dataPtr, .inputLength = dataLength, .outputPtr =
					signaturePtr, .outputLengthPtr = signatureLengthPtr,
						.mode=mode};

	Crypto_Jobs[jobId]->jobId = jobId;
	Crypto_Jobs[jobId]->jobState = CRYPTO_JOBSTATE_IDLE;
	Crypto_Jobs[jobId]->jobPrimitiveInputOutput = NewJobPrimitiveInputOutputType;

	Std_ReturnType CryIf_ProcessJob_Return;

	if (queue.size == 0)
	{
		CryIf_ProcessJob_Return = CryIf_ProcessJob(cryIfChannel1.CryIfChannelId,Crypto_Jobs[jobId]);

		if (CryIf_ProcessJob_Return == CRYPTO_E_BUSY)
		{
			if (queue.size == queue.capacity)
			{
				return CRYPTO_E_BUSY;
			}
			else {
				boolean insertJobReturn = insertJob(Crypto_Jobs[jobId]->jobInfo);
				if (insertJobReturn == FALSE)
				{
					#if (CSM_RUNTIME_ERROR_DETECT == STD_ON)
										Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
										CSM_SIGNATURE_VERIFY_SID,
										CSM_E_QUEUE_FULL);
					#endif
					return CRYPTO_E_BUSY;
				}
			}
		}
	}
	else {
		if (queue.size == queue.capacity)
		{
			return CRYPTO_E_BUSY;
		}
		else {
			boolean insertJobReturn = insertJob(Crypto_Jobs[jobId]->jobInfo);
			if (insertJobReturn == FALSE)
			{
				#if (CSM_RUNTIME_ERROR_DETECT == STD_ON)
								Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
								CSM_SIGNATURE_VERIFY_SID,
								CSM_E_QUEUE_FULL);
				#endif
								return CRYPTO_E_BUSY;
			}
		}
	}

	/*

	 7. [SWS_Csm_00039] The users of the CSM shall be notified when a requested
	 cryptographic service has been processed by calling the callback function from the
	 job primitive configuration.

	 8. [SWS_Csm_00734] CSM crypto services shall provide a Csm_<Service>() API. DONE

	 9. [SWS_Csm_00924] The application shall be able to call Csm_<Service>() with
	 the operation mode CRYPTO_OPERATIONMODE_START to initialize cryptographic
	 computations.

	 10. [SWS_Csm_00925] The application shall be able to call Csm_<Service>() with the
	 operation mode CRYPTO_OPERATIONMODE_UPDATE arbitrary often, but at least
	 one time, to feed the job's crypto primitive with input data.

	 11.	[SWS_Csm_01046] The application shall be able to call Csm_<Service>() with
	 the operation mode CRYPTO_OPERATIONMODE_FINISH to finalize cryptographic
	 computations.

	 12. [SWS_Csm_01055]  Only the service operations HASH, MACGENERATE,
	 MACVERIFY, ENCRYPT, DECRYPT, AEAD_ENCRYPT, AEAD_DECRYPT,
	 SIGNATUREGENERATE, SIGNATUREVERIFY shall support the operation mode
	 START, UPDATE and FINISH as specified from the API. For all other service
	 operations, the CSM shall set the operation mode to
	 CRYPTO_OPERATIONMODE_SINGLECALL, even if the API does not provide an
	 operation mode.

	 13. [SWS_Csm_01093] If the CSM issues either the service CRYPTO_MACGENERATE,
	 CRYPTO_MACVERIFY, CRYPTO_ENCRYPT, CRYPTO_DECRYPT,
	 CRYPTO_AEADENCRYPT, CRYPTO_AEADDECRYPT, CRYPTO_RANDOMGENERATE,
	 CRYPTO_SIGNATUREGENERATE or CRYPTO_SIGNATUREVERIFY to the Crypto
	 Interface, it needs to make sure that the element jobPrimitiveInfo-
	 >cryIfKeyId in the job structure of Crypto_JobType references to the assigned
	 key of this job.

	 14. [SWS_Csm_00944] The CsmQueues shall sort the jobs according to the configured
	 jobs priority.

	 15. [SWS_Csm_91072]  A service operation shall only be added to the queue if the
	 data consistency of the job structure can be guaranteed. This shall be particularly
	 considered when services with the same jobID are added to the queue (e.g. with
	 subsequent calls to Csm_SignatureVerify() and Csm_SaveContextJob()). If
	 this cannot be guaranteed, the service operation shall return with E_BUSY.

	 16. [SWS_Csm_91073]  If services with the same JobID can be added to the queue,
	 then the order of execution of these services shall correspond to the order if incoming
	 services operation requests .
	 */

	return E_OK;
}

/************************************************************************************
 * Service Name: Csm_SignatureVerify
 * Service ID[hex]: 0x64
 * Sync/Async: Depends on configuration
 * Reentrancy: Reentrant
 * Parameters (in): 	uint32 jobId,
 Crypto_OperationModeType mode,
 const uint8* dataPtr,
 uint32 dataLength,
 uint8* signaturePtr,
 uint32* signatureLengthPtr,
 Crypto_VerifyResultType* verifyPtr
 * Parameters (inout): None
 * Parameters (out): Std_ReturnType
 * Return value: None
 * Description: Initializes the CSM module
 * Requirements:
 ************************************************************************************/

Std_ReturnType Csm_SignatureVerify(uint32 jobId, Crypto_OperationModeType mode,
		const uint8 *dataPtr, uint32 dataLength, uint8 *signaturePtr,
		uint32 *signatureLengthPtr, Crypto_VerifyResultType *verifyPtr) {
	// TODO
	/*
	 1. Validate inputs (Check requirements and DET errors)
	 */
	return E_OK;
}

/************************************************************************************
 * Service Name: Csm_MainFunction
 * Service ID[hex]: 0x01
 * Sync/Async:
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: if asynchronous job processing is configured and there are job queues, the function
 * 			   is called cyclically to process queued jobs
 * Requirements:
 ************************************************************************************/

void Csm_MainFunction(void)
{
	//invoke higher priority job to process which is the front process but need to check if it cancelled or no jobs in queue
	 if(queue.size != 0)
	 {

		 Crypto_ResultType result=CryIf_ProcessJob(cryIfChannel1.CryIfChannelId,Crypto_Jobs[queue.jobInfo[queue.front].jobId]);

     if(result == E_OK)
    	deleteNextJob();

	 }
}
/************************************************************************************
 * Service Name: Csm_CallbackNotification
 * Service ID[hex]: 0x70
 * Sync/Async:Synchronous
 * Parameters (in): job Holds a pointer to the job, which has finished.
					result Contains the result of the cryptographic operation
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Notifies the CSM that a job has finished. This function is used by the underlying layer (CRYIF)
 ************************************************************************************/

void Csm_CallbackNotification (Crypto_JobType* job,Crypto_ResultType result){
if(job != NULL_PTR)
	/* SWS_Csm_01044 */
	CsmJobPrimitiveCallbackRef[job->jobPrimitiveInfo->callbackId](job,result);

}
