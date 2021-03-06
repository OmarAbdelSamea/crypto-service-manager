 /******************************************************************************
 *
 * Module: NvM_Cfg.c
 *
 * File Name: V2xM.h
 *
 * Description: Pre-compile configuration source file for NvM module - Non AUTOSAR module
 *
 * Author: Mohamed AbdelAzeem
 ******************************************************************************/


#include "../inc/Nvm.h"


/* NvM  Key Contianer  */
/* keys form NIST test vectors */
const uint8 PubKey0XY_ptr[] = {0x1c,0xcb,0xe9,0x1c,0x07,0x5f,0xc7,0xf4,0xf0,0x33,0xbf,0xa2,0x48,0xdb,0x8f,0xcc,0xd3,0x56,0x5d,0xe9,0x4b,0xbf,0xb1,0x2f,0x3c,0x59,0xff,0x46,0xc2,0x71,0xbf,0x83, 0xce,0x40,0x14,0xc6,0x88,0x11,0xf9,0xa2,0x1a,0x1f,0xdb,0x2c,0x0e,0x61,0x13,0xe0,0x6d,0xb7,0xca,0x93,0xb7,0x40,0x4e,0x78,0xdc,0x7c,0xcd,0x5c,0xa8,0x9a,0x4c,0xa9};
const uint8 PrivKey0_ptr [] = {0x51,0x9b,0x42,0x3d,0x71,0x5f,0x8b,0x58,0x1f,0x4f,0xa8,0xee,0x59,0xf4,0x77,0x1a,0x5b,0x44,0xc8,0x13,0x0b,0x4e,0x3e,0xac,0xca,0x54,0xa5,0x6d,0xda,0x72,0xb4,0x64};


const uint8 PubKey1XY_ptr[]  = {0xe2,0x66,0xdd,0xfd,0xc1,0x26,0x68,0xdb,0x30,0xd4,0xca,0x3e,0x8f,0x77,0x49,0x43,0x2c,0x41,0x60,0x44,0xf2,0xd2,0xb8,0xc1,0x0b,0xf3,0xd4,0x01,0x2a,0xef,0xfa,0x8a,0xbf,0xa8,0x64,0x04,0xa2,0xe9,0xff,0xe6,0x7d,0x47,0xc5,0x87,0xef,0x7a,0x97,0xa7,0xf4,0x56,0xb8,0x63,0xb4,0xd0,0x2c,0xfc,0x69,0x28,0x97,0x3a,0xb5,0xb1,0xcb,0x39};
const uint8 PrivKey1_ptr []  = {0x0f,0x56,0xdb,0x78,0xca,0x46,0x0b,0x05,0x5c,0x50,0x00,0x64,0x82,0x4b,0xed,0x99,0x9a,0x25,0xaa,0xf4,0x8e,0xbb,0x51,0x9a,0xc2,0x01,0x53,0x7b,0x85,0x47,0x98,0x13};


const uint8 PubKey2XY_ptr[]  = {0x74,0xcc,0xd8,0xa6,0x2f,0xba,0x0e,0x66,0x7c,0x50,0x92,0x9a,0x53,0xf7,0x8c,0x21,0xb8,0xff,0x0c,0x3c,0x73,0x7b,0x0b,0x40,0xb1,0x75,0x0b,0x23,0x02,0xb0,0xbd,0xe8, 0x29,0x07,0x4e,0x21,0xf3,0xa0,0xef,0x88,0xb9,0xef,0xdf,0x10,0xd0,0x6a,0xa4,0xc2,0x95,0xcc,0x16,0x71,0xf7,0x58,0xca,0x0e,0x4c,0xd1,0x08,0x80,0x3d,0x0f,0x26,0x14};
const uint8 PrivKey2_ptr []  = {0xe2,0x83,0x87,0x12,0x39,0x83,0x7e,0x13,0xb9,0x5f,0x78,0x9e,0x6e,0x1a,0xf6,0x3b,0xf6,0x1c,0x91,0x8c,0x99,0x2e,0x62,0xbc,0xa0,0x40,0xd6,0x4c,0xad,0x1f,0xc2,0xef};


const uint8 PubKey3XY_ptr[]  = {0x32,0x2f,0x80,0x37,0x1b,0xf6,0xe0,0x44,0xbc,0x49,0x39,0x1d,0x97,0xc1,0x71,0x4a,0xb8,0x7f,0x99,0x0b,0x94,0x9b,0xc1,0x78,0xcb,0x7c,0x43,0xb7,0xc2,0x2d,0x89,0xe1, 0x3c,0x15,0xd5,0x4a,0x5c,0xc6,0xb9,0xf0,0x9d,0xe8,0x45,0x7e,0x87,0x3e,0xb3,0xde,0xb1,0xfc,0xeb,0x54,0xb0,0xb2,0x95,0xda,0x60,0x50,0x29,0x4f,0xae,0x7f,0xd9,0x99};
const uint8 PrivKey3_ptr []  = {0xa3,0xd2,0xd3,0xb7,0x59,0x6f,0x65,0x92,0xce,0x98,0xb4,0xbf,0xe1,0x0d,0x41,0x83,0x7f,0x10,0x02,0x7a,0x90,0xd7,0xbb,0x75,0x34,0x94,0x90,0x01,0x8c,0xf7,0x2d,0x07};

/* key pairs array  */
const NvM_KeyPairType StoredKeyPairs[]={
		{PubKey0XY_ptr, PrivKey0_ptr},
		{PubKey1XY_ptr, PrivKey1_ptr},
		{PubKey2XY_ptr, PrivKey2_ptr},
		{PubKey3XY_ptr, PrivKey3_ptr}
};

/* NvM_BlockDescriptor for keys stored */
const NvM_BlockDescriptorType NvmBlock_StoredKeyPairs =  {NVRAM_BLOCK_KEY_ID, StoredKeyPairs} ;


/* Certificate Container  */

/*  Certificate validity for 5 mins starts from dummy time */
const NvM_CertificateValidityPeriodType Valid_5min =  {
		5,
		2172814212
};

 uint8 Certficate0_hash[]= {0x2c,0xf2,0x4d,0xba,0x5f,0xb0,0xa3,0x0e,0x26,0xe8,0x3b,0x2a,0xc5,0xb9,0xe2,0x9e,0x1b,0x16,0x1e,0x5c,0x1f,0xa7,0x42,0x5e,0x73,0x04,0x33,0x62,0x93,0x8b,0x98,0x24};

const NvM_CertificateType certficate_0 =
{
		0,
		NULL_PTR,
		Valid_5min,
		PubKey0XY_ptr,
		Certficate0_hash

};

 uint8 Certificate1_hash []= {0x91,0xe9,0x24,0x0f,0x41,0x52,0x23,0x98,0x2e,0xdc,0x34,0x55,0x32,0x63,0x07,0x10,0xe9,0x4a,0x7f,0x52,0xcd,0x5f,0x48,0xf5,0xee,0x1a,0xfc,0x55,0x50,0x78,0xf0,0xab};

const NvM_CertificateType certficate_1 =
{
		1,
		NULL_PTR,
		Valid_5min,
		PubKey1XY_ptr,
		Certificate1_hash

};

 uint8 Certificate2_hash[] = {0x87,0x29,0x8c,0xc2,0xf3,0x1f,0xba,0x73,0x18,0x1e,0xa2,0xa9,0xe6,0xef,0x10,0xdc,0xe2,0x1e,0xd9,0x5e,0x98,0xbd,0xac,0x9c,0x4e,0x15,0x04,0xea,0x16,0xf4,0x86,0xe4};

const NvM_CertificateType certficate_2 =
{
		2,
		NULL_PTR,
		Valid_5min,
		PubKey2XY_ptr,
		Certificate2_hash

};

 uint8 Certificate3_hash[]= {0x60,0xc6,0x7a,0x0b,0x22,0x71,0x27,0x02,0x17,0x72,0xfe,0xda,0x63,0x8a,0xe9,0x98,0x6b,0x84,0x6c,0xf4,0xcf,0xbd,0xba,0x07,0xc3,0xf3,0x70,0xb9,0x99,0x21,0x4c,0x40};

const NvM_CertificateType certficate_3 =
{
		3,
		NULL_PTR,
		Valid_5min,
		PubKey3XY_ptr,
		Certificate3_hash
};


/* PSEUDONYM_CERTIFICATES */
const NvM_CertificateType Pesudonym_Cerficates[] ={
		certficate_0,
		certficate_1,
		certficate_2,
		certficate_3
};


const NvM_BlockDescriptorType NvmBlock_Pesudonym_Cerficates = {NVRAM_BLOCK_PESUDONUM_CERTFIFCATE_ID, Pesudonym_Cerficates} ;


/*  Certificate validity for 1 year  starts from dummy time */
const NvM_CertificateValidityPeriodType Valid_1year =  {
		525960,
		2172814212
};

/* Long term certficiate  */
 NvM_CertificateType LongTermCertfificate =
{
		1001,
		NULL_PTR,
		Valid_1year,
		PubKey3XY_ptr,

};

const NvM_BlockDescriptorType NvmBlock_LongTerm_Cerficates = {NVRAM_BLOCK_LONGTERM_CERTFIFCATE_ID,&LongTermCertfificate} ;
