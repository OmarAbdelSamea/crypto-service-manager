#ifndef CRYPTO_GENERAL_TYPES_H
#define CRYPTO_GENERAL_TYPES_H

/*
 * Module Version 1.0.0
 */
#define CRYPTO_GENERAL_TYPES_SW_MAJOR_VERSION (1U)
#define CRYPTO_GENERAL_TYPES_SW_MINOR_VERSION (0U)
#define CRYPTO_GENERAL_TYPES_SW_PATCH_VERSION (0U)

/*
 * AUTOSAR Version 4.7.0
 */
#define CRYPTO_GENERAL_TYPES_AR_RELEASE_MAJOR_VERSION (4U)
#define CRYPTO_GENERAL_TYPES_AR_RELEASE_MINOR_VERSION (7U)
#define CRYPTO_GENERAL_TYPES_AR_RELEASE_PATCH_VERSION (0U)
#include "Std_Types.h"

/* In Autosar specfied to be in Rte_Csm_Type.h */
typedef enum
{
  CRYPTO_OPERATIONMODE_START=1, CRYPTO_OPERATIONMODE_UPDATE,
  CRYPTO_OPERATIONMODE_STREAMSTART, CRYPTO_OPERATIONMODE_FINISH,
  CRYPTO_OPERATIONMODE_SINGLECALL
} Crypto_OperationModeType;

typedef enum {
    CRYPTO_E_VER_OK,
    CRYPTO_E_VER_NOT_OK
} Crypto_VerifyResultType;


/* Return for Std_ReturnType for Cryptostack */
typedef Std_ReturnType Crypto_ResultType;
 /**************************************/

typedef enum {
	CRYPTO_JOBSTATE_IDLE, CRYPTO_JOBSTATE_ACTIVE
} Crypto_JobStateType;

typedef struct {
	const uint8 *inputPtr;
	uint32 inputLength;
	const uint8 *secondaryInputPtr;
	uint32 secondaryInputLength;
	const uint8 *tertiaryInputPtr;
	uint32 tertiaryInputLength;
	uint8 *outputPtr;
	uint32 *outputLengthPtr;
	uint8 *secondaryOutputPtr;
	uint32 *secondaryOutputLengthPtr;
	uint64 input64;
	Crypto_VerifyResultType *verifyPtr;
	uint64 *output64Ptr;
	Crypto_OperationModeType mode;
} Crypto_JobPrimitiveInputOutputType;
typedef struct {

	uint32 jobId;
	uint32 jobPriority;

} Crypto_JobInfoType;
typedef enum {
	CRYPTO_HASH,
	CRYPTO_MACGENERATE,
	CRYPTO_MACVERIFY,
	CRYPTO_ENCRYPT,
	CRYPTO_DECRYPT,
	CRYPTO_AEADENCRYPT,
	CRYPTO_AEADDECRYPT,
	CRYPTO_SIGNATUREGENERATE,
	CRYPTO_SIGNATUREVERIFY,
	CRYPTO_RANDOMGENERATE,
	CRYPTO_RANDOMSEED,
	CRYPTO_KEYGENERATE,
	CRYPTO_KEYDERIVE,
	CRYPTO_KEYEXCHANGECALCPUBVAL
} Crypto_ServiceInfoType;

typedef enum {
	CRYPTO_ALGOFAM_NOT_SET,
	CRYPTO_ALGOFAM_SHA1,
	CRYPTO_ALGOFAM_SHA2_224,
	CRYPTO_ALGOFAM_SHA2_256,
	CRYPTO_ALGOFAM_SHA2_384,
	CRYPTO_ALGOFAM_SHA2_512,
	CRYPTO_ALGOFAM_SHA2_512_224,
	CRYPTO_ALGOFAM_SHA2_512_256,
	CRYPTO_ALGOFAM_SHA3_224,
	CRYPTO_ALGOFAM_SHA3_256,
	CRYPTO_ALGOFAM_SHA3_384,
	CRYPTO_ALGOFAM_SHA3_512,
	CRYPTO_ALGOFAM_SHAKE128,
	CRYPTO_ALGOFAM_SHAKE256,
	CRYPTO_ALGOFAM_RIPEMD160,
	CRYPTO_ALGOFAM_BLAKE_1_256,
	CRYPTO_ALGOFAM_BLAKE_1_512,
	CRYPTO_ALGOFAM_BLAKE_2s_256,
	CRYPTO_ALGOFAM_BLAKE_2s_512,
	CRYPTO_ALGOFAM_3DES,
	CRYPTO_ALGOFAM_AES,
	CRYPTO_ALGOFAM_CHACHA,
	CRYPTO_ALGOFAM_RSA,
	CRYPTO_ALGOFAM_ED25519,
	CRYPTO_ALGOFAM_BRAINPOOL,
	CRYPTO_ALGOFAM_ECCNIST,
	NOT_USED,
	CRYPTO_ALGOFAM_RNG,
	CRYPTO_ALGOFAM_SIPHASH,
	CRYPTO_ALGOFAM_ECCANSI,
	CRYPTO_ALGOFAM_ECCSEC,
	CRYPTO_ALGOFAM_DRBG,
	CRYPTO_ALGOFAM_FIPS186,
	CRYPTO_ALGOFAM_PADDING_PKCS7,
	CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS,
	CRYPTO_ALGOFAM_PBKDF2,
	CRYPTO_ALGOFAM_KDFX963,
	CRYPTO_ALGOFAM_DH,
	CRYPTO_ALGOFAM_SM2,
	CRYPTO_ALGOFAM_EEA3,
	CRYPTO_ALGOFAM_SM3,
	CRYPTO_ALGOFAM_EIA3,
	CRYPTO_ALGOFAM_HKDF,
	CRYPTO_ALGOFAM_ECDSA,
	CRYPTO_ALGOFAM_X25519,
	CRYPTO_ALGOFAM_ECDH,
} Crypto_AlgorithmFamilyType;

typedef enum {
	CRYPTO_ALGOMODE_NOT_SET,
	CRYPTO_ALGOMODE_ECB,
	CRYPTO_ALGOMODE_CBC,
	CRYPTO_ALGOMODE_CFB,
	CRYPTO_ALGOMODE_OFB,
	CRYPTO_ALGOMODE_CTR,
	CRYPTO_ALGOMODE_GCM,
	CRYPTO_ALGOMODE_XTS,
	CRYPTO_ALGOMODE_RSAES_OAEP,
	CRYPTO_ALGOMODE_PXXXR,
	CRYPTO_ALGOMODE_RSASSA_PSS,
	CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5,
	CRYPTO_ALGOMODE_8ROUNDS,
	CRYPTO_ALGOMODE_12ROUNDS,
	CRYPTO_ALGOMODE_20ROUNDS,
	CRYPTO_ALGOMODE_HMAC,
	CRYPTO_ALGOMODE_CMAC,
	CRYPTO_ALGOMODE_GMAC,
	CRYPTO_ALGOMODE_CTRDRBG,
	CRYPTO_ALGOMODE_SIPHASH_2_4,
	CRYPTO_ALGOMODE_SIPHASH_4_8
} Crypto_AlgorithmModeType;

typedef struct {
	const Crypto_AlgorithmFamilyType family;
const Crypto_AlgorithmFamilyType secondaryFamily;
	const uint32 keyLength;
	const Crypto_AlgorithmModeType mode;

} Crypto_AlgorithmInfoType;
typedef struct {
	const uint32 resultLength;
	const Crypto_ServiceInfoType service;
	const Crypto_AlgorithmInfoType algorithm;

} Crypto_PrimitiveInfoType;
typedef enum {
	CRYPTO_PROCESSING_ASYNC, CRYPTO_PROCESSING_SYNC
} Crypto_ProcessingType;

typedef struct {
	uint32 callbackId;
	const Crypto_PrimitiveInfoType *primitiveInfo;
	uint32 cryIfKeyId;
	Crypto_ProcessingType processingType;
	const boolean callbackUpdateNotification;

} Crypto_JobPrimitiveInfoType;
typedef struct {
	uint8 redirectionConfig;
	uint32 inputKeyId;
	uint32 inputKeyElementId;
	uint32 secondaryInputKeyId;
	uint32 secondaryInputKeyElementId;
	uint32 tertiaryInputKeyId;
	uint32 tertiaryInputKeyElementId;
	uint32 outputKeyId;
	uint32 outputKeyElementId;
	uint32 secondaryOutputKeyId;
	uint32 secondaryOutputKeyElementId;

} Crypto_JobRedirectionInfoType;

typedef struct {
	uint32 jobId;
	Crypto_JobStateType jobState;
	Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput;
	const Crypto_JobPrimitiveInfoType *jobPrimitiveInfo;
	const Crypto_JobInfoType jobInfo;
	uint32 cryptoKeyId;
	uint32 targetCryptoKeyId;
	const uint32 jobPriority;
} Crypto_JobType;



#endif /*CRYPTO_GENERAL_TYPES_H */
