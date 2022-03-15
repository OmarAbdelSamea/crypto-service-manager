 /******************************************************************************
 *
 * Module: Det
 *
 * File Name: Det.c
 *
 * Description:  Det stores the development errors reported by other modules.
 *               This source file is a STUB for the Det Module
 *
 * Author: Salma Sherif
 ******************************************************************************/

#include "../inc/Det.h"

/* Variables to store last DET error */
uint16 Det_ModuleId = 0;       /*DET module ID*/
uint8 Det_InstanceId = 0;      /*DET instance ID*/
uint8 Det_ApiId = 0;           /* DET API ID*/
uint8 Det_ErrorId = 0;         /* DET Error ID*/

Std_ReturnType Det_ReportError( uint16 ModuleId,
                      uint8 InstanceId,
                      uint8 ApiId,
                      uint8 ErrorId )
{
    Det_ModuleId = ModuleId;
    Det_InstanceId = InstanceId;
    Det_ApiId = ApiId;
    Det_ErrorId = ErrorId;
    return E_OK;
}
