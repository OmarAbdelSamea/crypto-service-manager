 /******************************************************************************
 *
 * Module: Common - Compiler Abstraction
 *
 * File Name: Compiler.h
 *
 * Description:  This file contains the definitions and macros specified by
 *               AUTOSAR for the abstraction of compiler specific keywords.
 *
 *******************************************************************************/

#ifndef COMPILER_H
#define COMPILER_H


#define COMPILER_VENDOR_ID                                  (1000U)

/*
 * Module Version 1.0.0
 */
#define COMPILER_SW_MAJOR_VERSION                           (1U)
#define COMPILER_SW_MINOR_VERSION                           (0U)
#define COMPILER_SW_PATCH_VERSION                           (0U)

/*
 * AUTOSAR Version 4.7.0
 */
#define COMPILER_AR_RELEASE_MAJOR_VERSION                   (4U)
#define COMPILER_AR_RELEASE_MINOR_VERSION                   (7U)
#define COMPILER_AR_RELEASE_PATCH_VERSION                   (0U)

/* The memory class is used for the declaration of local pointers */
#define AUTOMATIC

/* The memory class is used within type definitions, where no memory
   qualifier can be specified */
#define TYPEDEF

/* This is used to define the void pointer to zero definition */
#define NULL_PTR          ((void *)0)

/* This is used to define the abstraction of compiler keyword inline */
#define INLINE            inline

/* This is used to define the local inline function */
#define LOCAL_INLINE      static inline

/* This is used to define the abstraction of compiler keyword static */
#define STATIC            static

#endif
