#include"../inc/NvM.h"


Std_ReturnType NvM_ReadBlock (
	NvM_BlockIdType BlockId,
	void* NvM_DstPtr
)
{

	switch(BlockId)
	{
	case NVRAM_BLOCK_KEY_ID:
		NvM_DstPtr = StoredKeyPairs;
		break;
	case NVRAM_BLOCK_PESUDONUM_CERTFIFCATE_ID:
		NvM_DstPtr = &NvmBlock_Pesudonym_Cerficates;
		break;
	case NVRAM_BLOCK_LONGTERM_CERTFIFCATE_ID:
		NvM_DstPtr = &NvmBlock_LongTerm_Cerficates;

	}

	return  E_OK;

}
