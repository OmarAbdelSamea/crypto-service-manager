
#ifndef CRYPTO_CFG_H
#define CRYPTO_CFG_H
#include "../../NvM/inc/NvM.h"

/*
 * Module Version 1.0.0
 */
#define CRYPTO_CFG_SW_MAJOR_VERSION           (1U)
#define CRYPTO_CFG_SW_MINOR_VERSION           (0U)
#define CRYPTO_CFG_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.7.0
 */
#define CRYPTO_CFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define CRYPTO_CFG_AR_RELEASE_MINOR_VERSION   (7U)
#define CRYPTO_CFG_AR_RELEASE_PATCH_VERSION   (0U)

/**********  ECUC_Crypto_00002 CryptoGeneral Container   **********/

/* ECUC_Crypto_00006 :  Pre-compile option for Development Error Detect  */
#define CRYPTO_DEV_ERROR_DETECT                (STD_ON)

/* ECUC_Crypto_00007 : Pre-compile option for Version Info API */
#define CRYPTO_VERSION_INFO_API                (STD_ON)

/* TODO :  MAIN FUNCTION period */
/* ECUC_Crypto_00038 : Specifies the period of main function Crypto_MainFunction in seconds */
#define CRYPTO_MAIN_FUNCTION_PERIOD				(0.1) //assumption


/* ECUC_Crypto_00042 : Reference to EcuC Partition  */
/* According to  SWS_Crypto_00212 this configuration is not supported by crypto driver*/
#define CRYPTO_ECUC_PARTITION_REF 				(NULL)


/************  ECUC_Crypto_00003 : CryptoDriverObject Container  ********/
/* TODO */
/* ECUC_Crypto_00009 : Pre-compile configuration for Identifier of the Crypto Driver Object. */
#define CRYPTO_DRIVER_OBJECT_ID  				(0)//Symbolic name from crypto.h

/* TODO */
/* ECUC_Crypto_00019 : Pre-compile configuration for Crypto Queue Size (MAx Number of jobs in the queue) */
#define CRYPTO_QUEUE_SIZE 						 (10)//Implementation specific


/* ECUC_Crypto_00045 : Pre-compile configuration for a reference to the CryptoKey that is used by the Random Generator */
/* Random Generator is not used in our project  */
#define CRYPTO_DEFAULT_RANDOM_KEY_REF   	  	  (NULL)

/* ECUC_Crypto_00044 : Pre-compile configuration for CryptoDefaultRandomPrimitiveRef  */
/* Random Generator is not used in our project  */
#define CRYPTO_DEFAULT_RANDOM_PRIMITIVE_REF   	   (NULL)

/* ECUC_Crypto_00043 : Pre-compile configuration for CryptoDriverObjectEcucPartitionRef */
#define CRYPTO_DRIVER_OBJECT_ECUC_PARTITION_REF    (NULL)

/* TODO */
/* ECUC_Crypto_00018 : Pre-compiler configuration for Refers to primitive in the CRYPTO */
#define CRYPTO_PRIMITIVE_REF 						()

/************  ECUC_Crypto_00011 : CryptoKey Container  ********/

/* TODO */
/* ECUC_Crypto_00012 : Pre-compile configuration for  Identifier of the CRYPTO Key */
#define CRYPTO_KEY_ID1 					(0U)//Symbolic name from crypto.h
#define CRYPTO_KEY_ID2					(1U)//Symbolic name from crypto.h
#define CRYPTO_KEY_ID3 					(2U)//Symbolic name from crypto.h
#define CRYPTO_KEY_ID4 					(3U)//Symbolic name from crypto.h

/* TODO : Look at CryptoNvBlock  */
/* ECUC_Crypto_00059 : Pre-compile configuration for Reference to the NV block where the persistent key elements of this key shall be stored to. */
#define CRYPTO_KEY_NVBLOCK_REF 			

/* TODO  */
/* ECUC_Crypto_00020 : Pro-compile configuration for Refers to a pointer in the CRYPTO to a CryptoKeyType.*/
/* CryptoKeyType provides the information which key elements are contained in a CryptoKey. */
#define	CRYPTO_KEYTYPE_REF 				()


/**********  ECUC_Crypto_00005 : Crypto Key Element container  **********/

/* ECUC_Crypto_00025 : Pre-compile configuration for Enable or disable writing and reading the key element with data smaller than the size of the element. */
#define  CRYPTO_KEY_ELEMENT_ALLOW_PARTIAL_ACCESS (STD_OFF)

/* TODO: Create format enum in crypto.h */
/* ECUC_Crypto_00041 : Pre-compile Defines the format for the key element */
#define  CRYPTO_KEY_ELEMENT_FORMAT 		(CRYPTO_KE_FORMAT_BIN_OCTET)

/* TODO: KEY element ID */
/* ECUC_Crypto_00021 : Pre-compile configuration Identifier of the CRYPTO key element */
#define  CRYPTO_KEY_ELEMENT_ID			()


/* ECUC_Crypto_00023 : Pre-compile configuration for Value which will be used to fill the key element during startup  */
/* We assume that all persistant keys are already in the memory and have a value */
#define  CRYPTO_KEY_ELEMENT_INIT_VALUE 	(0)


/* ECUC_Crypto_00026 : Pre-compile configuration Enable or disable persisting of the key element in non-volatile storage */
/* SEE : Crypto driver clause 7.2.6 */
#define  CRYPTO_KEY_ELEMENT_PERSIST 	(TRUE)

/* TODO: Implement the enum in crypto.h */
/* ECUC_Crypto_00024 : Pre-compile configuration for Define the reading access rights of the key element through external API */
#define	CRYPTO_KEY_ELEMENT_READ_ACCESS	(CRYPTO_RA_ALLOWED)

/* TODO: what is the KEY ELEMENT SIZE ?  */
/* ECUC_Crypto_00022 : Pre-compile configuration for Maximum Size size of a CRYPTO key element in bytes  **/
/* Assumign the max size is max(public key, private key) which is 64 */
#define  CRYPTO_KEY_ELEMENT_SIZE 		(64)

/* TODO: Implement the enum in crypto.h */
/* ECUC_Crypto_00027 : Pre-compile configuration for Define the writing access rights of the key element through external API. */
#define  CRYPTO_KEY_ELEMENT_WRITE_ACCESS  ( CRYPTO_WA_DENIED )

//#define CRYPTO_SIGNATUREGENERATE 7
//#define CRYPTO_SIGNATUREVERIFY 8
//#define CRYPTO_ALGOFAM_NOT_SET 0
//#define CRYPTO_ALGOMODE_ECB 0
//#define CRYPTO_ALGOFAM_ECCSEC 31
//#define SHA_2_256 3

/* Determines the algorithm family used for the crypto service */
typedef Crypto_AlgorithmFamilyType CryptoPrimitiveAlgorithmFamily;

/* Determines the algorithm mode used for the crypto service */
typedef Crypto_AlgorithmModeType CryptoPrimitiveAlgorithmMode;

/* Determines the algorithm secondary family used for the crypto service */
typedef CryptoPrimitiveAlgorithmFamily CryptoPrimitiveAlgorithmSecondaryFamily;

typedef Crypto_ServiceInfoType CryptoPrimitiveService;



#endif /* CRYPTO_CFG_H */
