#ifndef RTE_CSM_TYPE_H_
#define RTE_CSM_TYPE_H_

#include "Std_Types.h"


#define RTE_CSM_TYPE_VENDOR_ID                                  (1105U)

/*
 * Module Version 1.0.0
 */
#define RTE_CSM_TYPE_SW_MAJOR_VERSION                           (1U)
#define RTE_CSM_TYPE_SW_MINOR_VERSION                           (0U)
#define RTE_CSM_TYPE_SW_PATCH_VERSION                           (0U)

/*
 * AUTOSAR Version 4.7.0
 */
#define RTE_CSM_TYPE_AR_RELEASE_MAJOR_VERSION                   (4U)
#define RTE_CSM_TYPE_AR_RELEASE_MINOR_VERSION                   (7U)
#define RTE_CSM_TYPE_AR_RELEASE_PATCH_VERSION                   (0U)

typedef enum
{
  CRYPTO_OPERATIONMODE_START = 1, CRYPTO_OPERATIONMODE_UPDATE,
  CRYPTO_OPERATIONMODE_STREAMSTART, CRYPTO_OPERATIONMODE_FINISH,
  CRYPTO_OPERATIONMODE_SINGLECALL
} Crypto_OperationModeType;

typedef enum {
    CRYPTO_E_VER_OK,
    CRYPTO_E_VER_NOT_OK
} Crypto_VerifyResultType;



#endif /* RTE_CSM_TYPE_H_ */
