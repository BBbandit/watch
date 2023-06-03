#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"

 
//IO方向设置
#define sDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9输入模式
#define sDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9输出模式
//IO操作函数	 
#define IIC_sCL    PBout(8) //SCL
#define IIC_sDA    PBout(9) //SDA	 
#define READ_sDA   PBin(9)  //输入SDA 

//IIC所有操作函数
void iiC_Init(void);                //初始化IIC的IO口				 
void iiC_Start(void);				//发送IIC开始信号
void iiC_Stop(void);	  			//发送IIC停止信号
void iiC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 iiC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 iiC_Wait_Ack(void); 				//IIC等待ACK信号
void iiC_Ack(void);					//IIC发送ACK信号
void iiC_NAck(void);				//IIC不发送ACK信号

void iiC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 iiC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















