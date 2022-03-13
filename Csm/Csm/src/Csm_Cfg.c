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
const CsmCallback CsmJobPrimitiveCallbackRef[3] = {
		&V2xM_GenerateCallbackNotification, &V2xM_VerifyCallbackNotification,
		&V2xM_HashCallbackNotification };

const CsmPrimitives CsmJobPrimitiveRef = { { 0x2C, 0, 0, 32 },
		{ 0x2C, 0, 0, 32 }, { 3, 0, 0, 32 } };



const CsmQueue csmQueue = { 128, &cryIfChannel1, { 0.1 } };

const CsmKey csmKey = { 0, FALSE, &cryIfChannel1 };

const CsmJob generateSignatureCsmJob = {
CSM_JOB_ID1,
USE_FNC,
JOB_PRIORITY_SIGNATURE_GENERATE,
USE_FNC, CRYPTO_PROCESSING_ASYNC, &csmKey, &CsmJobPrimitiveCallbackRef[0],
		&CsmJobPrimitiveRef[0], &csmQueue };

const CsmJob verifySignatureCsmJob = {
CSM_JOB_ID2,
USE_FNC,
JOB_PRIORITY_SIGNATURE_VERIFY,
USE_FNC, CRYPTO_PROCESSING_ASYNC, &csmKey, &CsmJobPrimitiveCallbackRef[1],
		&CsmJobPrimitiveRef[1], &csmQueue };

const CsmJob hashCsmJob = {
CSM_JOB_ID3,
USE_FNC,
JOB_PRIORITY_HASH,
USE_FNC, CRYPTO_PROCESSING_ASYNC, &csmKey, &CsmJobPrimitiveCallbackRef[2],
		&CsmJobPrimitiveRef[2], &csmQueue };
