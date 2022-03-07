/*
 ============================================================================
 Name        : Csm.h
 Author      : Omar AbdelSamea
 Version     :
 Description : 
 ============================================================================
 */

#ifndef CSM_H
#define CSM_H

/* Id for the company in the AUTOSAR */
#define CSM_VENDOR_ID    (1101U)

/* CSM Module Id */
#define CSM_MODULE_ID    (110U)

/* Csm Instance Id */
#define CSM_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 * Requirement: SWS_Csm_00006
 */
#define CSM_SW_MAJOR_VERSION           (1U)
#define CSM_SW_MINOR_VERSION           (0U)
#define CSM_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.7.0
 */
#define CSM_AR_RELEASE_MAJOR_VERSION   (4U)
#define CSM_AR_RELEASE_MINOR_VERSION   (7U)
#define CSM_AR_RELEASE_PATCH_VERSION   (0U)

/*
 * Macros for Csm Status
 */
#define CSM_INITIALIZED                (1U)
#define CSM_NOT_INITIALIZED            (0U)


/* Csm Pre-Compile Configuration Header file */
#include "Csm_Cfg.h"


/* AUTOSAR Version checking between Csm_Cfg.h and Csm.h files
 * Requirement: SWS_EthIf_00007
 *
 *  */
#if ((CSM_CFG_AR_RELEASE_MAJOR_VERSION != CSM_AR_RELEASE_MAJOR_VERSION)\
 ||  (CSM_CFG_AR_RELEASE_MINOR_VERSION != CSM_AR_RELEASE_MINOR_VERSION)\
 ||  (CSM_CFG_AR_RELEASE_PATCH_VERSION != CSM_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Csm_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Csm_Cfg.h and Csm.h files
 * Requirement: SWS_Csm_00007
 *  */
#if ((CSM_CFG_SW_MAJOR_VERSION != CSM_SW_MAJOR_VERSION)\
 ||  (CSM_CFG_SW_MINOR_VERSION != CSM_SW_MINOR_VERSION)\
 ||  (CSM_CFG_SW_PATCH_VERSION != CSM_SW_PATCH_VERSION))
  #error "The SW version of Csm_Cfg.h does not match the expected version"
#endif

#include "../../General/Crypto_GeneralTypes.h"

/* AUTOSAR Version checking between Crypto_GeneralTypes.h and Csm.h files
 * Requirement: SWS_Csm_00007
 *  */
#if ((CRYPTO_GENERAL_TYPES_AR_RELEASE_MAJOR_VERSION != CSM_AR_RELEASE_MAJOR_VERSION)\
 ||  (CRYPTO_GENERAL_TYPES_AR_RELEASE_MINOR_VERSION != CSM_AR_RELEASE_MINOR_VERSION)\
 ||  (CRYPTO_GENERAL_TYPES_AR_RELEASE_PATCH_VERSION != CSM_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of WEth.h does not match the expected version"
#endif

#include "../../General/Platform_Types.h"

#include "../../Rte/Rte_Csm_Type.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
#define CSM_INIT_SID                0x00
#define CSM_SIGNATURE_GENERATE_SID  0x76
#define CSM_SIGNATURE_VERIFY_SID    0x64
#define CSM_MAIN_FUNCTION_SID    0x01

/*******************************************************************************
 *                      DET Error Codes                                        *
 ******************************************************************************/
#define CSM_E_PARAM_POINTER     0x01
#define CSM_E_PARAM_HANDLE      0x05
#define CSM_E_UNINIT            0x05
#define CSM_E_INIT_FAILED       0x07
#define CSM_E_PROCESSING_MOD    0x08
#define CSM_E_SERVICE_TYPE      0x09

#define CSM_E_QUEUE_FULL        0x01
/*******************************************************************************
 *                              Function Pointer Types                          *
 *******************************************************************************/


/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
typedef struct {
	/* Implmentation specfic */
} Csm_ConfigType;

typedef uint16 Csm_ConfigIdType;

typedef struct {
    float32 CsmMainFunctionPeriod
    // EcucPartition*  CsmMainFunctionPartitionRef
} CsmMainFunction;

/* CsmKey */
typedef struct {
    uint32 CsmKeyId;
    boolean CsmKeyUsePort;
    // CryIfKey* CsmKeyRef;
} CsmKey;
/******************************/

/* CsmQueue */
typedef struct {
    const uint32 CsmQueueSize;
    // CryIfChannel* CsmChannelRef;
    // CsmQueueMainFunctionRef 
} CsmQueue;
/******************************/

/* CsmInOutRedirection */
typedef struct {
    uint32 CsmInputKeyElementId;
    uint32 CsmOutputKeyElementId;
    uint32 CsmSecondaryInputKeyElementId;
    uint32 CsmSecondaryOutputKeyElementId;
    uint32 CsmTertiaryInputKeyElementId;
    CsmKey* CsmInputKeyRef;
    CsmKey* CsmOutputKeyRef;
    CsmKey* CsmSecondaryInputKeyRef;
    CsmKey* CsmSecondaryOutputKeyRef;
    CsmKey* CsmTertiaryInputKeyRef;
} CsmInOutRedirection;
/******************************/

/* CsmPrimitives */
typedef struct {
    
} CsmPrimitives;
/******************************/

/* CsmSignatureGenerate */
typedef enum {
    CRYPTO_ALGOFAM_BRAINPOOL,
    CRYPTO_ALGOFAM_CUSTOM,
    CRYPTO_ALGOFAM_ECCNIST,
    CRYPTO_ALGOFAM_ECDSA,
    CRYPTO_ALGOFAM_ED25519,
    CRYPTO_ALGOFAM_RSA,
    CRYPTO_ALGOFAM_SM2
} CsmSignatureGenerateAlgorithmFamilyType;

typedef enum {
    CRYPTO_ALGOFAM_BLAKE_1_256,
    CRYPTO_ALGOFAM_BLAKE_1_512,
    CRYPTO_ALGOFAM_BLAKE_2s_256,
    CRYPTO_ALGOFAM_BLAKE_2s_512,
    CRYPTO_ALGOFAM_CUSTOM,
    CRYPTO_ALGOFAM_NOT_SET,
    CRYPTO_ALGOFAM_RIPEMD160,
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
    CRYPTO_ALGOFAM_SHAKE256
} CsmSignatureGenerateAlgorithmSecondaryFamilyType;

typedef enum {
    CRYPTO_ALGOMODE_CUSTOM,
    CRYPTO_ALGOMODE_NOT_SET,
    CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5,
    CRYPTO_ALGOMODE_RSASSA_PSS
} CsmSignatureGenerateAlgorithmModeType;

typedef struct {
    CsmSignatureGenerateAlgorithmFamilyType CsmSignatureGenerateAlgorithmFamily;
    CsmSignatureGenerateAlgorithmModeType CsmSignatureGenerateAlgorithmMode;
    CsmSignatureGenerateAlgorithmSecondaryFamilyType CsmSignatureGenerateAlgorithmSecondaryFamily;
    uint32 CsmSignatureGenerateDataMaxLength;
    uint32 CsmSignatureGenerateKeyLength;
    // CryptoPrimitiveAlgorithmFamilyCustom* CsmSignatureGenerateAlgorithmFamilyCustomRef;
    // CryptoPrimitiveAlgorithmModeCustom* CsmSignatureGenerateAlgorithmModeCustomRef;
    // CryptoPrimitiveAlgorithmFamilyCustom* CsmSignatureGenerateAlgorithmSecondaryFamilyCustomRef;

} CsmSignatureGenerateConfig;
/******************************/

/* CsmSignatureVerify */
typedef enum {
    CRYPTO_ALGOFAM_BRAINPOOL,
    CRYPTO_ALGOFAM_CUSTOM,
    CRYPTO_ALGOFAM_ECCNIST,
    CRYPTO_ALGOFAM_ECDSA,
    CRYPTO_ALGOFAM_ED25519,
    CRYPTO_ALGOFAM_RSA,
    CRYPTO_ALGOFAM_SM2
} CsmSignatureVerifyAlgorithmFamilyType;

typedef enum {
    CRYPTO_ALGOMODE_CUSTOM,
    CRYPTO_ALGOMODE_NOT_SET,
    CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5,
    CRYPTO_ALGOMODE_RSASSA_PSS
} CsmSignatureVerifyAlgorithmModeType;

typedef enum {
    CRYPTO_ALGOFAM_BLAKE_1_256,
    CRYPTO_ALGOFAM_BLAKE_1_512,
    CRYPTO_ALGOFAM_BLAKE_2s_256,
    CRYPTO_ALGOFAM_BLAKE_2s_512,
    CRYPTO_ALGOFAM_CUSTOM,
    CRYPTO_ALGOFAM_NOT_SET,
    CRYPTO_ALGOFAM_RIPEMD160,
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
    CRYPTO_ALGOFAM_SHAKE256
} CsmSignatureVerifyAlgorithmSecondaryFamilyType;

typedef struct {
    CsmSignatureVerifyAlgorithmFamilyType CsmSignatureVerifyAlgorithmFamily;
    CsmSignatureVerifyAlgorithmModeType CsmSignatureVerifyAlgorithmMode;
    CsmSignatureVerifyAlgorithmSecondaryFamilyType CsmSignatureVerifyAlgorithmSecondaryFamily;
    uint32 CsmSignatureVerifyCompareLength;
    uint32 CsmSignatureVerifyDataMaxLength;
    uint32 CsmSignatureVerifyKeyLength;
    // CryptoPrimitiveAlgorithmFamilyCustom* CsmSignatureVerifyAlgorithmFamilyCustomRef;
    // CryptoPrimitiveAlgorithmModeCustom* CsmSignatureVerifyAlgorithmModeCustomRef;
    // CryptoPrimitiveAlgorithmFamilyCustom* CsmSignatureVerifyAlgorithmSecondaryFamilyCustomRef;
} CsmSignatureVerifyConfig;
/******************************/

/* CsmJob */
typedef enum {
    CRYPTO_USE_FNC,
    CRYPTO_USE_PORT,
    CRYPTO_USE_PORT_OPTIMIZED
} CsmJobInterfaceUsePortType;

typedef enum {
    CRYPTO_USE_FNC,
    CRYPTO_USE_PORT,
} CsmJobServiceInterfaceContextUsePortType;

typedef enum {
    CRYPTO_PROCESSING_ASYNC,
    CRYPTO_PROCESSING_SYNC,
} CsmProcessingModeType;

typedef struct {
    uint32 CsmJobId;
    CsmJobInterfaceUsePortType CsmJobInterfaceUsePort;
    uint32 CsmJobPriority;
    CsmJobServiceInterfaceContextUsePortType CsmJobServiceInterfaceContextUsePort;
    CsmProcessingModeType CsmProcessingMode;
    CsmInOutRedirection* CsmInOutRedirectionRef;
    CsmKey* CsmKeyRef;
    //CsmCallback* CsmJobPrimitiveCallbackRef;
    CsmPrimitives* CsmJobPrimitiveRef;
    CsmQueue* CsmJobQueueRef;
} CsmJob;

typedef enum{CSM_STATE_UNINIT, CSM_STATE_INIT}Csm_StateType;

/******************************/

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

void Csm_Init(const Csm_ConfigType * configPtr);

Std_ReturnType Csm_SignatureGenerate (
	uint32 jobId, 
	Crypto_OperationModeType mode,
	const uint8* dataPtr,
	uint32 dataLength,
	uint8* signaturePtr,
	uint32* signatureLengthPtr);

Std_ReturnType Csm_SignatureVerify (
	uint32 jobId, 
	Crypto_OperationModeType mode,
	const uint8* dataPtr,
	uint32 dataLength,
	uint8* signaturePtr,
	uint32* signatureLengthPtr,
	Crypto_VerifyResultType* verifyPtr);

boolean insertJob(Crypto_JobType *job)
#endif /* CSM_H */
