/*
 * ringBuff.c
 *
 *  Created on: May 8, 2020
 *      Author: Administrator
 */


/*========================ringbuff.c========================================*/

#include "ringbuff.h"

RingBuff_t ringBuff;//����һ��ringBuff�Ļ�����


void RingBuff_Init(void)
{

	//��ʼ�������Ϣ

	ringBuff.Head = 0;

	ringBuff.Tail = 0;

	ringBuff.Lenght = 0;

}

/**

*

*

*

* ˵�����������жϺ�������

*/

u8 Write_RingBuff(u8 *data, u8 len)
{

	if ((len + ringBuff.Lenght) >= RINGBUFF_LEN) //�жϻ�����ʣ��ռ��Ƿ����
	{
		return FLASE;
	}
	else
	{

		while (len--)
		{
			ringBuff.Ring_Buff[ringBuff.Tail]=*data++;

			ringBuff.Tail = (ringBuff.Tail+1)%RINGBUFF_LEN;//��ֹԽ��Ƿ�����

			ringBuff.Lenght++;
		}

		return TRUE;
	}

}



/**

* ˵����ԭ���ϲ�����������ɵ��жϣ����������������ɶ�ʱ��������

*/

u8 Read_RingBuff(u8 *rData)
{

	if(ringBuff.Lenght == 0)//�жϷǿ�
	{

		return FLASE;

	}

	*rData = ringBuff.Ring_Buff[ringBuff.Head];//�Ƚ��ȳ�FIFO���ӻ�����ͷ��

	ringBuff.Head = (ringBuff.Head+1)%RINGBUFF_LEN;//��ֹԽ��Ƿ�����


	ringBuff.Lenght--;

	return TRUE;

}
