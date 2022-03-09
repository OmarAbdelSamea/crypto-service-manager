#include"../inc/Crypto.h"

/* struct for cryptoPrimitives used through signature process*/
const CryptoPrimitive signatureGenerateCryptoPrimitive = 
{CRYPTO_ALGOFAM_ECCSEC,CRYPTO_ALGOMODE_ECB,CRYPTO_ALGOFAM_NOT_SET,CRYPTO_SIGNATUREGENERATE,TRUE};

/* struct for cryptoPrimitives used through verification process*/
const CryptoPrimitive verifyGenerateCryptoPrimitive = 
{CRYPTO_ALGOFAM_ECCSEC,CRYPTO_ALGOMODE_ECB,CRYPTO_ALGOFAM_NOT_SET,CRYPTO_SIGNATUREVERIFY,TRUE};

/* struct for cryptoPrimitives used through HASH process*/
const CryptoPrimitive hashGenerateCryptoPrimitive =
{SHA_2_256,CRYPTO_ALGOMODE_ECB,CRYPTO_ALGOFAM_NOT_SET,CRYPTO_HASH,TRUE};

const CryptoKey cryptoKey1={CRYPTO_KEY_ID1};

const CryptoNvBlock storedKey ={ &NvmBlock_StoredKeyPairs,CRYPTO_NV_BLOCK_IMMEDIATE};
