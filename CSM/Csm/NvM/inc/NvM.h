#ifndef NVM_H
#define NVM_H
#include "NvM_Cfg.h"
#include "../../General/Std_Types.h"
typedef uint16 NvM_BlockIdType;
#define HashAlgorithm_sha256 0



typedef enum {
	NVM_BLOCK_NATIVE,
	NVM_BLOCK_REDUNDANT,
	NVM_BLOCK_DATASET
} NvM_BlockManagementTypeType;

typedef Std_ReturnType (*NvMReadRamBlockFromNvCallback) (const void* NvmBuffer);

/* Type definition for Nvm block descriptor  */
typedef struct {
	// Identification of a NVRAM block via a unique block identifier
	NvM_BlockIdType		NvramBlockIdentifier;
	/* Pointer to the stucture  */
	void*		NvmBlockPtr;

}NvM_BlockDescriptorType;
/* Type definition for key array  */
/*
 * Public key is 64 byte (X coordinates | y Coordinates)
 * private key is 32 byte
 *
 * */
typedef struct{
	uint8* PublicKey;
	uint8* PrivateKey;
}NvM_KeyPairType;


/* Type definition for certificate validity period in minutes */
typedef struct{
	uint16 duration;
	uint32 start;
}NvM_CertificateValidityPeriodType;
/* Type definiton for certificate type.  Certificate type: Explicit */
typedef struct{
	uint8  CertificateId;
	uint8* issuerHashId;
	NvM_CertificateValidityPeriodType ValidityPeriod;
	uint8* PublicKey;
	uint8* CertHash;
}NvM_CertificateType;

Std_ReturnType NvM_ReadBlock (
NvM_BlockIdType BlockId,
void* NvM_DstPtr
);
extern const NvM_KeyPairType StoredKeyPairs[];
extern const NvM_BlockDescriptorType NvmBlock_StoredKeyPairs;
extern const NvM_BlockDescriptorType NvmBlock_Pesudonym_Cerficates ;
extern const NvM_BlockDescriptorType NvmBlock_LongTerm_Cerficates;

#endif
