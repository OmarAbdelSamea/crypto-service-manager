/*
 * V2xManagment.h
 *
 *  Created on: Mar 9, 2022
 *      Author: MBR
 */

#ifndef V2XMANAGMENT_V2XMANAGMENT_H_
#define V2XMANAGMENT_V2XMANAGMENT_H_
#include "../General/Crypto_GeneralTypes.h"

 void V2xM_GenerateCallbackNotification (
	Crypto_JobType* job,
	Crypto_ResultType result
);
 void V2xM_VerifyCallbackNotification (
	Crypto_JobType* job,
	Crypto_ResultType result
);
 void V2xM_HashCallbackNotification (
		Crypto_JobType* job,
		Crypto_ResultType result);
#endif /* V2XMANAGMENT_V2XMANAGMENT_H_ */
