/*
 * ringBuff.h
 *
 *  Created on: May 8, 2020
 *      Author: Administrator
 */

#ifndef RINGBUFF_H_
#define RINGBUFF_H_

/*========================ringbuff.H========================================*/

#include "typedef.h"

#define USER_RINGBUFF 1 //ʹ�û��λ�������ʽ��������

#if USER_RINGBUFF

/**���ʹ�û��λ�����ʽ���մ�������***/

#define RINGBUFF_LEN 1024 /*�����2^N,��ʱ�Ϳ��Խ�����ȡģ���� */

#define FLASE 1

#define TRUE 0


typedef struct
{

	u16 Head; //������ģ�ͣ��Ӷ�ͷɾ��

	u16 Tail; //������ģ�ͣ��Ӷ�β���

	u16 Lenght; //�������ݵĳ���ΪringBuff.Lenght=Ring_Buff.Tail-Ring_Buff.Head

	u8 Ring_Buff[RINGBUFF_LEN];

}RingBuff_t;



void RingBuff_Init(void);

u8 Write_RingBuff(u8 *data, u8 len);

u8 Read_RingBuff(u8 *rData);

#endif //end of USER_RINGBUFF


#endif /* RINGBUFF_H_ */

