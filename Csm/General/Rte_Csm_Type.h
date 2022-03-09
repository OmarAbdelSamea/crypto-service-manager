/*
 * Rte_Csm_Type.h
 *
 *  Created on: Feb 28, 2022
 *      Author: dell
 */

#ifndef RTE_CSM_TYPE_H_
#define RTE_CSM_TYPE_H_

/*
 * Module Version 1.0.0
 */
#define RTE_CSM_TYPE_SW_MAJOR_VERSION           (1U)
#define RTE_CSM_TYPE_SW_MINOR_VERSION           (0U)
#define RTE_CSM_TYPE_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version R21-11
 */
#define RTE_CSM_TYPE_AR_RELEASE_MAJOR_VERSION   (4U)
#define RTE_CSM_TYPE_AR_RELEASE_MINOR_VERSION   (7U)
#define RTE_CSM_TYPE_AR_RELEASE_PATCH_VERSION   (0U)

#include "Crypto_GeneralTypes.h"

/* Return for Std_ReturnType for Cryptostack */
typedef Std_ReturnType Crypto_ResultType;

#endif /* RTE_CSM_TYPE_H_ */
