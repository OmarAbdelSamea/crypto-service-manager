/*
 ============================================================================
 Name        : Csm_Cfg.c
 Author      : Omar AbdelSamea
 Version     :
 Description : Pre-Compile Configuration Source file.
 ============================================================================
 */

#include "../inc/Csm.h"
/*
 1- array (LUTs) CsmJobInfo, CsmPermitiveJob
 */

/*
 1. [SWS_Csm_91005] Each crypto primitive configuration shall be realized as a
 constant structure of type Crypto_PrimitiveInfoType.

 2. [SWS_Csm_91006] Each job primitive configuration shall be realized as a constant
 structure of type Crypto_JobPrimitiveInfoType.

 3. [SWS_Csm_00028] It shall be possible to create several configurations for each
 cryptographic primitive. One configuration per job per primitive is possible.

 4. [SWS_Csm_00029] When creating a primitive configuration, it shall be possible to
 configure all available and allowed schemes from the underlying Crypto Driver
 Object.

 5. [SWS_Csm_00032] If the asynchronous interface is chosen, each job primitive
 configuration shall contain a callback function.

 6. [SWS_Csm_00940] It shall be possible to queue CSM jobs in configured
 CsmQueues in the CSM.

 */
const CsmCallback CsmJobPrimitiveCallbackRef[3]=
		{&V2xM_GenerateCallbackNotification
		,&V2xM_VerifyCallbackNotification,
		&V2xM_HashCallbackNotification };

const CsmSignatureGenerateConfig CsmJobPrimitiveRef1=
{ CRYPTO_ALGOFAM_ECCSEC, CRYPTO_ALGOMODE_NOT_SET, CRYPTO_ALGOFAM_NOT_SET, KEY_LENGTH_USED };
const CsmSignatureVerifyConfig CsmJobPrimitiveRef2={ CRYPTO_ALGOFAM_ECCSEC, CRYPTO_ALGOMODE_NOT_SET, CRYPTO_ALGOFAM_NOT_SET, KEY_LENGTH_USED };
const CsmHashConfig CsmJobPrimitiveRef3= {CRYPTO_ALGOFAM_SHA2_256 , 0, 0, KEY_LENGTH_USED } ;
const CsmPrimitives primitive1=
{CsmJobPrimitiveRef1,CsmJobPrimitiveRef2,CsmJobPrimitiveRef3};

const CsmQueue csmQueue = { MAX_QUEUE_SIZE, &cryIfChannel1, { 0.1 } };

const CsmKey csmKey = {CSM_KEY_ID, FALSE, &cryIfkey };
/*
const CsmJob generateSignatureCsmJob = {
CSM_JOB_ID1,
USE_FNC,
JOB_PRIORITY_SIGNATURE_GENERATE,
USE_FNC, CRYPTO_PROCESSING_ASYNC, &csmKey, &CsmJobPrimitiveCallbackRef1,
		&primitive1,
		&csmQueue };

const CsmJob verifySignatureCsmJob = {
CSM_JOB_ID2,
USE_FNC,
JOB_PRIORITY_SIGNATURE_VERIFY,
USE_FNC, CRYPTO_PROCESSING_ASYNC, &csmKey, &CsmJobPrimitiveCallbackRef2,
		&primitive1, &csmQueue };

const CsmJob hashCsmJob = {
CSM_JOB_ID3,
USE_FNC,
JOB_PRIORITY_HASH,
USE_FNC, CRYPTO_PROCESSING_ASYNC, &csmKey, &CsmJobPrimitiveCallbackRef3,
		&primitive1, &csmQueue };
const CsmJob *CsmJobs[] = { &generateSignatureCsmJob, &verifySignatureCsmJob,
		&hashCsmJob };
*/
