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

#define USER_RINGBUFF 1 //使用环形缓冲区形式接收数据

#if USER_RINGBUFF

/**如果使用环形缓冲形式接收串口数据***/

#define RINGBUFF_LEN 1024 /*最好是2^N,此时就可以进行用取模运算 */

#define FLASE 1

#define TRUE 0


typedef struct
{

	u16 Head; //消费者模型，从队头删除

	u16 Tail; //生产者模型，从队尾添加

	u16 Lenght; //接收数据的长度为ringBuff.Lenght=Ring_Buff.Tail-Ring_Buff.Head

	u8 Ring_Buff[RINGBUFF_LEN];

}RingBuff_t;



void RingBuff_Init(void);

u8 Write_RingBuff(u8 *data, u8 len);

u8 Read_RingBuff(u8 *rData);

#endif //end of USER_RINGBUFF


#endif /* RINGBUFF_H_ */

