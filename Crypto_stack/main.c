#include"Csm/inc/Csm.h"
int main(){


	Csm_Init(NULL_PTR);
	CryIf_Init (NULL_PTR);
	Crypto_Init(NULL_PTR);

	uint32 jobI1=0, jobI2=1;
	const uint8 dataPtr1=56;
	const uint8 dataPtr2=46;

	uint32 dataLength1=32;
	uint32 dataLength2=2;
	Crypto_VerifyResultType verifyPtr;
	uint8 signaturePtr;
	uint32 signatureLengthPtr;
    Csm_SignatureGenerate( jobI1, CRYPTO_OPERATIONMODE_SINGLECALL, &dataPtr1, dataLength1,&signaturePtr, &signatureLengthPtr);
    Csm_SignatureVerify(jobI2, CRYPTO_OPERATIONMODE_SINGLECALL,&dataPtr2, dataLength2,&signaturePtr,&signatureLengthPtr,&verifyPtr);

  /*  Csm_Hash(
    		 jobId3,
    		Crypto_OperationModeType mode,
    		const uint8* dataPtr,
    		uint32 dataLength,
    		uint8* resultPtr,
    		uint32* resultLengthPtr);*/
    Crypto_MainFunction();
    // for first job
	//Csm_MainFunction();
	// for sec job
    Crypto_MainFunction();

	return 0;
}
