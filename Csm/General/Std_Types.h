 /******************************************************************************
 *
 * Module: Common - Platform
 *
 * File Name: Std_Types.h
 *
 * Description: General type definitions
 *
 *******************************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

#include "Platform_Types.h"
#include "Compiler.h"


#define STD_TYPES_VENDOR_ID                                  (1000U)

/*
 * Module Version 1.0.0
 */
#define STD_TYPES_SW_MAJOR_VERSION                           (1U)
#define STD_TYPES_SW_MINOR_VERSION                           (0U)
#define STD_TYPES_SW_PATCH_VERSION                           (0U)

/*
 * AUTOSAR Version 4.7.0
 */
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION                   (4U)
#define STD_TYPES_AR_RELEASE_MINOR_VERSION                   (7U)
#define STD_TYPES_AR_RELEASE_PATCH_VERSION                   (0U)

/*
 *  Describes the standard Return Type Definitions used in the project
 */
typedef uint8  Std_ReturnType;

/*
 * Structure for the Version of the module.
 * This is requested by calling <Module name>_GetVersionInfo()
 */


typedef struct
{
  uint16  vendorID;
  uint16  moduleID;
  uint8 sw_major_version;
  uint8 sw_minor_version;
  uint8 sw_patch_version;
} Std_VersionInfoType;

#define STD_HIGH        0x01U       /* Standard HIGH */
#define STD_LOW         0x00U       /* Standard LOW */

#define STD_ACTIVE      0x01U       /* Logical state active */
#define STD_IDLE        0x00U       /* Logical state idle */

#define STD_ON          0x01U       /* Standard ON */
#define STD_OFF         0x00U       /* Standard OFF */

#define E_OK            ((Std_ReturnType)0x00U)      /* Function Return OK */
#define E_NOT_OK        ((Std_ReturnType)0x01U)      /* Function Return NOT OK */
#define CRYPTO_E_BUSY   ((Std_ReturnType)0x02U)
#define TO_E_ENTROPY_EXHAUSTED  ((Std_ReturnType)0x04U)
#define CRYPTO_E_KEY_READ_FAIL  ((Std_ReturnType)0x06U)
#define CRYPTO_E_KEY_WRITE_FAIL ((Std_ReturnType)0x07U)
#define CRYPTO_E_KEY_NOT_AVAILABLE  ((Std_ReturnType)0x08U)
#define CRYPTO_E_KEY_NOT_VALID    ((Std_ReturnType)0x09U)
#define CRYPTO_E_KEY_SIZE_MISMATCH  ((Std_ReturnType)0x0AU)
#define TO_E_JOB_CANCELED       ((Std_ReturnType)0x0CU)
#define CRYPTO_E_KEY_EMPTY    ((Std_ReturnType)0x0DU)
#endif /* STD_TYPES_H */
