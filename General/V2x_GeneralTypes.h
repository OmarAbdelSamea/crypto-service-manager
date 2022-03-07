/******************************************************************************
 *
 * Module: V2xBtp
 *
 * File Name: V2x_GeneralTypes.h
 *
 * Description: Header file for General Types in V2x stack
 *
 * Author:
 ******************************************************************************/

#ifndef V2X_GENERALTYPES_H_
#define V2X_GENERALTYPES_H_


/* Id for the company in the AUTOSAR */
#define V2X_GENERALTYPES_VENDOR_ID                                  (1000U)


/*
 * Module Version 1.0.0
 */
#define V2X_GENERALTYPES_SW_MAJOR_VERSION                           (1U)
#define V2X_GENERALTYPES_SW_MINOR_VERSION                           (0U)
#define V2X_GENERALTYPES_SW_PATCH_VERSION                           (0U)

/*
 * AUTOSAR Version 4.7.0
 */
#define V2X_GENERALTYPES_AR_RELEASE_MAJOR_VERSION                   (4U)
#define V2X_GENERALTYPES_AR_RELEASE_MINOR_VERSION                   (7U)
#define V2X_GENERALTYPES_AR_RELEASE_PATCH_VERSION                   (0U)

/* standard AUTOSAR types */
#include "Std_Types.h"

#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != V2X_GENERALTYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != V2X_GENERALTYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != V2X_GENERALTYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif


#include "../V2xM/inc/Rte_V2xM_Type.h"

/* AUTOSAR Version checking between Rte_V2xM_Type.h and V2xGeneralTypes.h files */
#if ((RTE_V2XM_TYPE_AR_RELEASE_MAJOR_VERSION != V2X_GENERALTYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (RTE_V2XM_TYPE_AR_RELEASE_MINOR_VERSION != V2X_GENERALTYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (RTE_V2XM_TYPE_AR_RELEASE_PATCH_VERSION != V2X_GENERALTYPES_AR_RELEASE_PATCH_VERSION))
    #error "The AR version of Rte_V2xM_Type.h does not match the expected version"

#endif
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Destination address for GeoUnicast */
typedef uint64 V2x_GnAddressType;

/* Specifies the shape type for GeoNetworking Areas.  */
typedef enum{V2X_GN_SHAPE_CIRCLE,V2X_GN_SHAPE_RECT,V2X_GN_SHAPE_ELLIPSE}V2x_GnAreaShapeType;

/*  Definition of the GeoNetworking destination area */
typedef struct{
 sint32 latitude;
 sint32 longitude;
 uint16 distanceA;
 uint16 distanceB;
 uint16 angle;
 V2x_GnAreaShapeType shape;
}V2x_GnDestinationAreaType;


/* Select which destination type (destinationAddress or destinationArea(for GeoBroadcast/GeoAnycast)
 is used for this packet) */
typedef enum{V2X_GN_DESTINATION_ADDRESS,V2X_GN_DESTINATION_AREA} V2x_GnDestinationType;


/* Specifies the packet transport type for GeoNetworking packages  */
typedef enum{V2X_GN_GEOUNICAST,V2X_GN_GEOANYCAST,V2X_GN_GEOBROADCAST,V2X_GN_TSB,
	V2X_GN_SHB}V2x_GnPacketTransportType;


/* describe the security service invoked by V2xM
 - Cam Security Profile - Den Security Profile -Security Profile for other
message types that have to be signed - Security Profile for other
message types that have to be signed externally - Security Profile for other message types
that have to be signed and encrypted
  */
typedef enum{V2X_SECPROF_CAM,V2X_SECPROF_DENM,V2X_SECPROF_OTHER_SIGNED,V2X_SECPROF_OTHER_SIGNED_EXTERNAL,
	V2X_SECPROF_OTHER_SIGNED_ENCRYPTED } V2x_SecProfileType;


/* Traffic class id for the message valid values 0 to 63 */
typedef uint8 V2x_TrafficClassIdType;

/* Specifies whether the BTP is interactive (BTP-A) or non-interactive
(BTP-B) */
typedef enum {V2X_ANY,V2X_BTPA,V2X_BTPB,V2X_IPV6}V2x_GnUpperProtocolType;

/*The result code used to specify if a V2xGn_Transmit has been processed successfully. */
 /* accepted - rejected due to maximum length exceedance - rejected due to maximum
 lifetime exceedance - rejected due to unsupported Traffic Class ID -
 rejected due to GeoArea exceeds max size -rejected due
to unspecified reasons
*/
typedef enum{V2X_GNTX_ACCEPTED,V2X_GNTX_E_MAXSDUSIZEOVFL,V2X_GNTX_E_MAXPACKETLIFETIME,
	V2X_GNTX_E_TCID ,V2X_GNTX_E_MAXGEOAREASIZE,V2X_GNTX_E_UNSPECIFIED}V2x_GnTxResultType;


/* Geographical position for the source of the received GeoNetworking packet.*/
typedef struct{
	V2x_GnAddressType gnAddress;   /* GeoNetworking Address */
    uint32 timestamp;
    sint32 latitude;
    sint32 longitude;
    boolean pai;             /* Positional accuracy indicator */
    sint16 speed;
    uint16 heading;

}V2x_GnLongPositionVectorType;

/* Pseudonym, derived from Pseudonym Certificates. The pseudonym is distributed to
   different modules to support privacy within the V2X System to the outside world.
   Requirement:[SWS_V2xM_00057]  */
typedef uint64 V2x_PseudonymType;



#endif /* V2X_GENERALTYPES_H_ */
