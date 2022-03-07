#include"../inc/EthIf.h"
#include "../inc/EthIf_PBcfg.h"
#define TEST_SUCCEEDS (1U)
#define TEST_NOT_SUCCEEDS (0U);

/************************************************************************************
* Test ID :TestCase1
* Description: Test for Transmission through Wireless Ethernet functionality.
* Pre-requisits: EthIf must be initialized before this test.
* Test Procedure : 1. Call EthIf_ProvideTxBuffer must return buffer is provided or not to confirm that the corresponding function in wireless Ethernet is called
*                  2. Call EthIf_Transmit must return E_OK or E_NOT_OK to confirm that the corresponding function in wireless Ethernet is called.
*                  3. Call EthIf_MainFunctionTx for Checking transmission confirmation.
*************************************************************************************/
boolean TestCase1(uint8 testCase1Input[]){
	/* buffer length */
	uint16 len=26;
	Eth_BufIdxType bufidx;
	/* pointer for the buffer */
	uint8 *bufptr;
	/* target physical address */
	const uint8 physicalAddr=11;

	/* provide buffer */
	BufReq_ReturnType out1= EthIf_ProvideTxBuffer(ETHIF_CTRL_IDX,ETHIF_FRAME_TYPE,1,&bufidx,&bufptr,&len);

	if(out1!=BUFREQ_OK && out1!=BUFREQ_E_NOT_OK){
		return TEST_NOT_SUCCEEDS;
	}
	/* start Transmission */
	uint8* ptr=bufptr;
	*ptr=testCase1Input[0];
	Std_ReturnType out2=EthIf_Transmit(ETHIF_CTRL_IDX,bufidx,ETHIF_FRAME_TYPE,1,len,&physicalAddr);
	if(out2!=E_OK && out2!=E_NOT_OK)
	{
			return TEST_NOT_SUCCEEDS;
	}

	// delay for ETHIF_MAIN_FUNCTION_PERIOD seconds
	/* check if transmission Confirmation was received */
    EthIf_MainFunctionTx();

	return TEST_SUCCEEDS;

}
/************************************************************************************
* Test ID :TestCase2
* Description: Test for checking the reception of frames from Wireless Ethernet then sending them to GeoNetworking Layer.
* Pre-requisits: EthIf must be initialized before this test.
* Test Procedure : 1. Call EthIf_MainFunctionRx.
* 				   2. Call getTestingResult from GeoNetwork layer if both is the same that means the value we put in WEth driver equal value in geoNetwork layer.
*************************************************************************************/
boolean TestCase2(uint8 testCase2Input){

	// delay for ETHIF_MAIN_FUNCTION_PERIOD seconds
	/* check if Wireless Eth had received new frames */
	EthIf_MainFunctionRx();
	uint8 res=getTestingResult();
	if(res== testCase2Input)
		return TEST_SUCCEEDS;
	else
		return TEST_NOT_SUCCEEDS;




}
int main(){

    /* Initialize Ethernet Interface */
	EthIf_Init(&ethif_congif);
	/* the value that will be sent*/
	uint8 testCase1Input[]="j";
	boolean testCase1Output=TestCase1(testCase1Input);

	/* the value that will be received from WEth */
	uint8 testCase2Input=12;
	boolean testCase2Output=TestCase2(testCase2Input);


return 0;

}

