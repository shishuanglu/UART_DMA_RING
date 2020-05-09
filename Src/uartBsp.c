/*
 * uartBsp.c
 *
 *  Created on: 2019年3月5日
 *      Author: shi
 */

/*****************************************  Include  ******************************************************/
#include "uartBsp.h"
#include "main.h"
#include "string.h"
#include "ringBuff.h"

/******************************************  Private macro definition  ******************************************/
#define UART1_RECVBUFF_MAXLEN_M		1024


#define FIRST_FRAME_HEAD_VAL			0x5A
#define SECOND_FRAME_HEAD_VAL			0xA5



/******************************************  P8rivate type definition  *******************************************/
typedef enum
{
	FIRST_FRAME_HEAD_ID = 0,
	SECOND_FRAME_HEAD_ID,
	FRAME_LEN_ID,
}recvDataId;
/******************************************  Private function declaration  **************************************/

/******************************************  Private variable definition  ***************************************/
U8 testBuff [16];
/******************************************  Global variable definition  ****************************************/

U8 uart1RecvBuffG[UART1_RECVBUFF_MAXLEN_M];

findFrame_T findFrame =
		{
			.pRecvData = testBuff,
			.frameHead = {FIRST_FRAME_HEAD_VAL, SECOND_FRAME_HEAD_VAL},
//			.frameHeadCount = 0,
			.frameHeadFlg.byte = 0,
			.recvdLen = 0,
			.findFrameFlg = INVALID,
			.frameLen = 0
		};

/******************************************  Function definition  ***********************************************/


/**************************************************************************
  * @function:
  * @param[in]:
  * @param[out]:
  * @return:
  * @others:
***************************************************************************/
U8 ucFindOneFrame (findFrame_T* pFindFrame, const U8* pData, U8 dataLen)
{
	U8 srcLen = 0;

	if (pFindFrame->findFrameFlg == VALID)
	{
		return srcLen;
	}

	while (dataLen--)
	{

		if (0 == pFindFrame->frameHeadFlg.bit.headId1Flg)
		{
			/*找第一个帧头*/
			if (pFindFrame->frameHead[FIRST_FRAME_HEAD_ID] == pData[srcLen++])
			{
				pFindFrame->pRecvData[pFindFrame->recvdLen++] = pFindFrame->frameHead[FIRST_FRAME_HEAD_ID];
				pFindFrame->frameHeadFlg.bit.headId1Flg = 1;
			}
			else
			{
				pFindFrame->recvdLen = 0;
				pFindFrame->frameHeadFlg.bit.headId1Flg = 0;
			}

		}
		else if (0 == pFindFrame->frameHeadFlg.bit.headId2Flg)
		{
			/*找第二个帧头*/
			if (pFindFrame->frameHead[SECOND_FRAME_HEAD_ID] == pData[srcLen++])
			{
				pFindFrame->pRecvData[pFindFrame->recvdLen++] = pFindFrame->frameHead[SECOND_FRAME_HEAD_ID];
				pFindFrame->frameHeadFlg.bit.headId2Flg = 1;
			}
			else
			{
				pFindFrame->recvdLen = 0;
				pFindFrame->frameHeadFlg.bit.headId1Flg = 0;
				pFindFrame->frameHeadFlg.bit.headId2Flg = 0;
			}
		}
		else
		{
			/*帧头已找到*/
			if (FRAME_LEN_ID == pFindFrame->recvdLen)
			{
				pFindFrame->frameLen = pData[srcLen++] + 2 + 1;//帧首+长度+数据+校验
				pFindFrame->pRecvData[pFindFrame->recvdLen++] = pFindFrame->frameLen;
			}
			else
			{
				pFindFrame->pRecvData[pFindFrame->recvdLen++] = pData[srcLen++];

				if (pFindFrame->recvdLen > pFindFrame->frameLen)
				{
					pFindFrame->recvdLen = 0;
					pFindFrame->frameHeadFlg.byte = 0;
					pFindFrame->findFrameFlg = VALID;

					return srcLen;
				}
			}
		}

		pFindFrame->findFrameFlg = INVALID;
	}

	return srcLen;
}




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	HAL_UART_Receive_DMA(huart,uart1RecvBuffG,UART1_RECVBUFF_MAXLEN_M);

}

U8 uart1RecvLen;

void vUartRecvIDLE_CallBack(UART_HandleTypeDef *huart)
{

    U32 temp=0;

    if((__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) != RESET))
    {

		__HAL_UART_CLEAR_IDLEFLAG(huart);



        if(huart->Instance == USART1)
        {
			temp = huart->Instance->SR;
			temp = huart->Instance->DR;
			HAL_UART_DMAStop(huart);

//            if(rightJoyStickRecvHandle.recvFlag == INVALID)
            {
				uart1RecvLen =  UART1_RECVBUFF_MAXLEN_M - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);

/*				if (rightJoyStickRecvHandle.recvDataLen <= UART1_RECVBUFF_MAXLEN_M)
				{
	                memcpy(rightJoyStickRecvHandle.recvDataP,uart1RecvBuffG,RIGHT_JOYSTICK_RECV_DATA_LEN);
	                rightJoyStickRecvHandle.recvFlag = VALID;
				}*/

//				ucFindOneFrame (&findFrame, uart1RecvBuffG, uart1RecvLen);
				Write_RingBuff(uart1RecvBuffG, uart1RecvLen);


            }


//            memset(uart1RecvBuffG,0x00,UART1_RECVBUFF_MAXLEN_M);

			HAL_UART_Receive_DMA(huart,uart1RecvBuffG,UART1_RECVBUFF_MAXLEN_M);
        }


    }
}

void vUartBspInit (void)
{
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart1,uart1RecvBuffG,UART1_RECVBUFF_MAXLEN_M);
}



