#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
#include "usart.h"	
#include "led.h"

/*下面的方式是通过直接操作库函数方式读取IO*/
#define KEY0 		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) //PB0
#define KEY1 		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)	//PB1 
#define KEY2 		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2) //PB2
#define KEY3 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)	//PB1
#define Charge 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)	//PB1

#define KEYPORT  KEY2|((!KEY3)<<1)|0xfc

#define KEY0_PRES 	1
#define KEY1_PRES	2
#define KEY2_PRES	3
#define KEY3_PRES	4



void KEY_Init(void);	//IO初始化
void Power_Key_Init(void);
void Power_Change_Init(void);
u8 KEY_Scan(u8 mode);  		//按键扫描函数	
void KeyRead(void);
u8 KeyProc(void);
#endif
