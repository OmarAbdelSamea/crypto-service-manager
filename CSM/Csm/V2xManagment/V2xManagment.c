#include"V2xManagment.h"
#include"stdio.h"
 void V2xM_GenerateCallbackNotification (
	Crypto_JobType* job,
	Crypto_ResultType result
){

	 printf("management %d",(int)job->jobPrimitiveInputOutput.inputLength);

 }
 void V2xM_VerifyCallbackNotification (
	Crypto_JobType* job,
	Crypto_ResultType result
){}
 void V2xM_HashCallbackNotification (
		Crypto_JobType* job,
		Crypto_ResultType result){}
