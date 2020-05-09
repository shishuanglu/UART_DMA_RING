/*
 * ringBuff.c
 *
 *  Created on: May 8, 2020
 *      Author: Administrator
 */


/*========================ringbuff.c========================================*/

#include "ringbuff.h"

RingBuff_t ringBuff;//创建一个ringBuff的缓冲区


void RingBuff_Init(void)
{

	//初始化相关信息

	ringBuff.Head = 0;

	ringBuff.Tail = 0;

	ringBuff.Lenght = 0;

}

/**

*

*

*

* 说明：被接收中断函数调用

*/

u8 Write_RingBuff(u8 *data, u8 len)
{

	if ((len + ringBuff.Lenght) >= RINGBUFF_LEN) //判断缓冲区剩余空间是否充足
	{
		return FLASE;
	}
	else
	{

		while (len--)
		{
			ringBuff.Ring_Buff[ringBuff.Tail]=*data++;

			ringBuff.Tail = (ringBuff.Tail+1)%RINGBUFF_LEN;//防止越界非法访问

			ringBuff.Lenght++;
		}

		return TRUE;
	}

}



/**

* 说明：原则上不用做接收完成的判断，当缓冲区读都不可读时会有提醒

*/

u8 Read_RingBuff(u8 *rData)
{

	if(ringBuff.Lenght == 0)//判断非空
	{

		return FLASE;

	}

	*rData = ringBuff.Ring_Buff[ringBuff.Head];//先进先出FIFO，从缓冲区头出

	ringBuff.Head = (ringBuff.Head+1)%RINGBUFF_LEN;//防止越界非法访问


	ringBuff.Lenght--;

	return TRUE;

}
