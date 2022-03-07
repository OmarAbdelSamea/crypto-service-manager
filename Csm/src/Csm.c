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
#if ((DET_AR_MAJOR_VERSION != CSM_AR_RELEASE_MAJOR_VERSION) || (DET_AR_MINOR_VERSION != CSM_AR_RELEASE_MINOR_VERSION) || (DET_AR_PATCH_VERSION != CSM_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

#define CRYPTO_JOBS_NUM 2
#define CRYPTO_QUEUES_NUM 2
#define QUEUE_MAX_SIZE 128

STATIC Csm_StateType Csm_State = CSM_STATE_UNINIT;
uint32 QueueLoopCounter = 0;

Crypto_QueueType Crypto_Queue_SignatureGenerate = {
	.size = 50};

Crypto_QueueType Crypto_Queue_SignatureVerify = {
	.size = 50};

Crypto_QueueType *Crypto_Queue[CRYPTO_QUEUES_NUM] = {
	&Crypto_Queue_SignatureGenerate,
	&Crypto_Queue_SignatureVerify};

Crypto_PrimitiveInfoType Crypto_PrimitiveInfo_SignatureGenerate = {
	.service = CSM_SIGNATURE_GENERATE_SID // SignatureGenerate SID
};

Crypto_PrimitiveInfoType Crypto_PrimitiveInfo_SignatureVerify = {
	.service = CSM_SIGNATURE_VERIFY_SID // SignatureVerify SID
};

Crypto_PrimitiveInfoType *Crypto_PrimitiveInfo[] = {
	&Crypto_PrimitiveInfo_SignatureGenerate,
	&Crypto_PrimitiveInfo_SignatureVerify

};

const CsmJob CsmJob_SignatureGenerate = {
	.CsmJobId = 0,
	.CsmInOutRedirectionRef = 5,
	.CsmJobQueueRef = &CsmQueue_SignatureGenerate};
const CsmJob CsmJob_SignatureVerify = {
	.CsmJobId = 1,
	.CsmJobQueueRef = &CsmQueue_SignatureVerify};

CsmJob *CsmJobs[] = {
	&CsmJob_SignatureGenerate,
	&CsmJob_SignatureVerify};

const CsmQueue CsmQueue_SignatureGenerate = {
	.CsmQueueSize = 10,
};

const CsmQueue CsmQueue_SignatureVerify = {
	.CsmQueueSize = 20,
};

const Crypto_JobInfoType Crypto_JobInfo_SignatureGenerate = {
	.jobId = 0,
	.jobPriority = 1};

const Crypto_JobInfoType Crypto_JobInfo_SignatureVerify = {
	.jobId = 1,
	.jobPriority = 2};

const Crypto_JobInfoType *Crypto_JobInfo[] = {
	&Crypto_JobInfo_SignatureGenerate,
	&Crypto_JobInfo_SignatureVerify};

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

void Csm_Init(const Csm_ConfigType *configPtr)
{
	// TODO
	/* Init status global var set to Init
	all jobs in Idle state.
	clean all queues csm_jobs, csm_queues
	clean queues
	in csm_cfg.c -> csm_jobs , csm_queues
	*/

#if (CSM_DEV_ERROR_DETECT == STD_ON)
	if (configPtr != NULL_PTR)
	{
		Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID, CSM_INIT_SID,
						CSM_E_PARAM_POINTER);

		Csm_State = CSM_STATE_UNINIT;
	}
	else
#endif
	{
		for (QueueLoopCounter; QueueLoopCounter < CRYPTO_QUEUES_NUM; QueueLoopCounter++)
		{
			Crypto_Queue[QueueLoopCounter]->size = 0;
		}

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

Std_ReturnType Csm_SignatureGenerate(
	uint32 jobId,
	Crypto_OperationModeType mode,
	const uint8 *dataPtr,
	uint32 dataLength,
	uint8 *signaturePtr,
	uint32 *signatureLengthPtr)
{

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

	if (Csm_State == CSM_STATE_UNINIT)
	{
#if (CSM_DEV_ERROR_DETECT == STD_ON)
		Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID, CSM_SIGNATURE_VERIFY_SID,
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

	if (dataPtr == NULL_PTR || signatureLengthPtr == NULL_PTR)
	{
#if (CSM_DEV_ERROR_DETECT == STD_ON)
		Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID, CSM_SIGNATURE_VERIFY_SID,
						CSM_E_PARAM_POINTER);
#endif
		return E_NOT_OK;
	}

	/*
	3. [SWS_Csm_91011] If a CSM API with a ID handle in its interface is called and the
		ID handle is out of range, the operation shall not be performed and CSM_E_PARAM_HANDLE
		shall be reported to the DET when CsmDevErrorDetect is true.
	*/

	if (jobId >= CRYPTO_JOBS_NUM)
	{
#if (CSM_DEV_ERROR_DETECT == STD_ON)
		Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID, CSM_SIGNATURE_VERIFY_SID,
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

	if (Crypto_PrimitiveInfo[jobId]->service != CSM_SIGNATURE_GENERATE_SID)
	{
#if (CSM_RUNTIME_ERROR_DETECT == STD_ON)
		Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID, CSM_SIGNATURE_VERIFY_SID,
						CSM_E_SERVICE_TYPE);
#endif
		return E_NOT_OK;
	}

	/*
	5. [SWS_Csm_01088] If a CSM job needs to be queued and the queue is full, the
		runtime error CSM_E_QUEUE_FULL shall be reported to the DET.
	*/

	if (Crypto_Queue[jobId]->size == Crypto_Queue[jobId]->capacity)
	{
#if (CSM_RUNTIME_ERROR_DETECT == STD_ON)
		Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID, CSM_SIGNATURE_VERIFY_SID,
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
	Crypto_JobType NewJobInQueue = {
		.jobId = jobId,
		.jobState = CsmJobs[jobId],
		.jobPrimitiveInputOutput = CsmJobs[jobId],
		.jobPrimitiveInfo = Crypto_PrimitiveInfo[jobId],
		.jobInfo = Crypto_JobInfo[jobId],
		.cryptoKeyId = CsmJobs[jobId],
		.jobRedirectionInfoRef = CsmJobs[jobId],
		.targetCryptoKeyId = CsmJobs[jobId],
		.jobPriority = Crypto_JobInfo[jobId]->jobPriority,
	};

	if (insertJob(&NewJobInQueue))
	{
		/* code */
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

	12. [SWS_Csm_01055] ⌈ Only the service operations HASH, MACGENERATE,
		MACVERIFY, ENCRYPT, DECRYPT, AEAD_ENCRYPT, AEAD_DECRYPT,
		SIGNATUREGENERATE, SIGNATUREVERIFY shall support the operation mode
		START, UPDATE and FINISH as specified from the API. For all other service
		operations, the CSM shall set the operation mode to
		CRYPTO_OPERATIONMODE_SINGLECALL, even if the API does not provide an
		operation mode.

	13. [SWS_Csm_01093] ⌈If the CSM issues either the service CRYPTO_MACGENERATE,
		CRYPTO_MACVERIFY, CRYPTO_ENCRYPT, CRYPTO_DECRYPT,
		CRYPTO_AEADENCRYPT, CRYPTO_AEADDECRYPT, CRYPTO_RANDOMGENERATE,
		CRYPTO_SIGNATUREGENERATE or CRYPTO_SIGNATUREVERIFY to the Crypto
		Interface, it needs to make sure that the element jobPrimitiveInfo-
		>cryIfKeyId in the job structure of Crypto_JobType references to the assigned
		key of this job.

	14. [SWS_Csm_00944] ⌈The CsmQueues shall sort the jobs according to the configured
		job’s priority.

	15. [SWS_Csm_91072] ⌈ A service operation shall only be added to the queue if the
		data consistency of the job structure can be guaranteed. This shall be particularly
		considered when services with the same jobID are added to the queue (e.g. with
		subsequent calls to Csm_SignatureVerify() and Csm_SaveContextJob()). If
		this cannot be guaranteed, the service operation shall return with E_BUSY.

	16. [SWS_Csm_91073] ⌈ ⌈ If services with the same JobID can be added to the queue,
		then the order of execution of these services shall correspond to the order if incoming
		services operation requests (“First-In-First-Out”).
	*/
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

Std_ReturnType Csm_SignatureVerify(
	uint32 jobId,
	Crypto_OperationModeType mode,
	const uint8 *dataPtr,
	uint32 dataLength,
	uint8 *signaturePtr,
	uint32 *signatureLengthPtr,
	Crypto_VerifyResultType *verifyPtr)
{
	// TODO
	/*
	1. Validate inputs (Check requirments and DET errors)
	*/
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
 if(jobQueue.arr[jobQueue.front].jobPriority != -1 && jobQueue.size != 0)
 {
	 Std_ReturnType res= Crypto_ProcessECDSA(jobQueue.arr[jobQueue.front]);
	 CryIf_CallbackNotification(jobQueue.arr[jobQueue.front].jobPtr,res);
	 deleteNextJob();
 }
 else if(jobQueue.arr[jobQueue.front].jobPriority == -1)
 {
	 deleteNextJob();
 }

}

boolean insertJob(Crypto_JobType *job)
{

	if (Crypto_Queue[job->jobId]->size < QUEUE_MAX_SIZE)
	{
		boolean inserted = 0;
		Crypto_Queue[job->jobId]->rear += 1;
		for (uint8 i = Crypto_Queue[job->jobId]->front; i <= Crypto_Queue[job->jobId]->size; i++)
		{
			if (job->jobInfo.jobPriority > Crypto_Queue[job->jobId]->Crypto_Jobs[i].jobPriority)
			{
				Crypto_JobType temp = Crypto_Queue[job->jobId]->Crypto_Jobs[i];
				Crypto_Queue[job->jobId]->Crypto_Jobs[i].jobId = job->jobId;
				Crypto_Queue[job->jobId]->Crypto_Jobs[i].cryptoKeyId = job->cryptoKeyId;
				Crypto_Queue[job->jobId]->Crypto_Jobs[i].jobPriority = job->jobInfo.jobPriority;
				Crypto_Queue[job->jobId]->Crypto_Jobs[i].jobPrimitiveInfo = job->jobPrimitiveInfo->primitiveInfo->service;
				Crypto_Queue[job->jobId]->Crypto_Jobs[i].jobPtr = job;
				for (int j = Crypto_Queue[job->jobId]->rear - 1; j >= i + 1; j--)
				{
					Crypto_Queue[job->jobId]->Crypto_Jobs[j + 1].jobId = Crypto_Queue[job->jobId]->Crypto_Jobs[j].jobId;
					Crypto_Queue[job->jobId]->Crypto_Jobs[j + 1].cryptoKeyId = Crypto_Queue[job->jobId]->Crypto_Jobs[j].cryptoKeyId;
					Crypto_Queue[job->jobId]->Crypto_Jobs[j + 1].jobPriority = Crypto_Queue[job->jobId]->Crypto_Jobs[j].jobPriority;
					Crypto_Queue[job->jobId]->Crypto_Jobs[j + 1].service = Crypto_Queue[job->jobId]->Crypto_Jobs[j].service;
					Crypto_Queue[job->jobId]->Crypto_Jobs[j + 1].jobPtr = Crypto_Queue[job->jobId]->Crypto_Jobs[j].jobPtr;
				}
				Crypto_Queue[job->jobId]->Crypto_Jobs[i + 1] = temp;
				inserted = 1;
				break;
			}
		}

		if (inserted == 0)
		{
			Crypto_Queue[job->jobId]->Crypto_Jobs[Crypto_Queue[job->jobId]->rear % QUEUE_MAX_SIZE].jobId = job->jobId;
			Crypto_Queue[job->jobId]->Crypto_Jobs[Crypto_Queue[job->jobId]->rear % QUEUE_MAX_SIZE].cryptoKeyId = job->cryptoKeyId;
			Crypto_Queue[job->jobId]->Crypto_Jobs[Crypto_Queue[job->jobId]->rear % QUEUE_MAX_SIZE].jobPriority = job->jobInfo.jobPriority;
			Crypto_Queue[job->jobId]->Crypto_Jobs[Crypto_Queue[job->jobId]->rear % QUEUE_MAX_SIZE].service = job->jobPrimitiveInfo->primitiveInfo->service;
			Crypto_Queue[job->jobId]->Crypto_Jobs[Crypto_Queue[job->jobId]->rear % QUEUE_MAX_SIZE].jobPtr = job;
		}
		Crypto_Queue[job->jobId]->size += 1;

		return TRUE;
	}
	return FALSE;
}


void deleteNextJob(Crypto_QueueType* queue)
{
	if(queue->size > 0)
	{
		queue->front += 1;
		queue->size -= 1;
	}
}