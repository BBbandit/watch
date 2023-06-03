#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

 
//IO��������
#define sDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9����ģʽ
#define sDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9���ģʽ
//IO��������	 
#define IIC_sCL    PBout(8) //SCL
#define IIC_sDA    PBout(9) //SDA	 
#define READ_sDA   PBin(9)  //����SDA 

//IIC���в�������
void iiC_Init(void);                //��ʼ��IIC��IO��				 
void iiC_Start(void);				//����IIC��ʼ�ź�
void iiC_Stop(void);	  			//����IICֹͣ�ź�
void iiC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 iiC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 iiC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void iiC_Ack(void);					//IIC����ACK�ź�
void iiC_NAck(void);				//IIC������ACK�ź�

void iiC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 iiC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















