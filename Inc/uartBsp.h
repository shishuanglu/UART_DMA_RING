/*
 * uartBsp.h
 *
 *  Created on: 2019年3月5日
 *      Author: shi
 */

#ifndef UARTBSP_H_
#define UARTBSP_H_

/*****************************************  Include  ******************************************************/
#include "typedef.h"
#include "stm32f4xx_hal.h"

/******************************************  Global macro definition  ******************************************/
#define FRAME_HEAD_NUM 				2

/******************************************  Global type definition  *******************************************/
typedef union
{
	U8 byte;
	struct
	{
		U8 headId1Flg : 1;
		U8 headId2Flg : 1;
		U8 headId3Flg : 1;
		U8 headId4Flg : 1;
		U8 headId5Flg : 1;
		U8 headId6Flg : 1;
		U8 headId7Flg : 1;
		U8 headId8Flg : 1;
	}bit;
}frameHeadFlg_T;

typedef struct
{
	U8* pRecvData;						//指向接收缓存
	U8	frameHead[FRAME_HEAD_NUM];		//帧头标志
//	U8	frameHeadCount;					//帧头个数
	frameHeadFlg_T	frameHeadFlg;	//找到帧头标志置有效
	U8 recvdLen;               			//已经接收的字节数
	ValidStatus findFrameFlg;       	//找到完整帧后,置有效
	U8 frameLen;                  		//本帧数据总长度，这个区域是可选的
}findFrame_T;
/******************************************  Global variable declaration  **************************************/
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart6;

extern DMA_HandleTypeDef hdma_usart1_rx;
/******************************************  Global function declaration  **************************************/

void vUartRecvIDLE_CallBack(UART_HandleTypeDef *huart);
void vUartBspInit (void);
U8 ucFindOneFrame (findFrame_T* pFindFrame, const U8* pData, U8 dataLen);


#endif /* UARTBSP_H_ */
