 /*
 ============================================================================
 Name        : Csm_Cfg.c
 Author      : Omar AbdelSamea
 Version     :
 Description : Pre-Compile Configuration Source file.
 ============================================================================
 */

#include <Csm.h>
/*
1- array (LUTs) CsmJobInfo, CsmPermitiveJob
*/ 

/*
1. [SWS_Csm_91005] Each crypto primitive configuration shall be realized as a
    constant structure of type Crypto_PrimitiveInfoType.

2. [SWS_Csm_91006] Each job primitive configuration shall be realized as a constant
    structure of type Crypto_JobPrimitiveInfoType.

3. [SWS_Csm_00028] It shall be possible to create several configurations for each
    cryptographic primitive. One configuration per job per primitive is possible.

4. [SWS_Csm_00029] When creating a primitive configuration, it shall be possible to
    configure all available and allowed schemes from the underlying Crypto Driver
    Object.

5. [SWS_Csm_00032] ⌈If the asynchronous interface is chosen, each job primitive
    configuration shall contain a callback function.

6. [SWS_Csm_00940] ⌈It shall be possible to queue CSM jobs in configured
    CsmQueues in the CSM.

*/







