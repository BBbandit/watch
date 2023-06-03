#include "key.h"
#include "delay.h" 

//按键初始化函数
void KEY_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOA,GPIOE时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE2,3,4
  Power_Key_Init();
  Power_Change_Init();
}

void Power_Key_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA,GPIOE时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA2
}


void Power_Change_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA,GPIOE时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA2
    
}





u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;    
	}else if(KEY0==1&&KEY1==1)key_up=1; 	    
 	return 0;// 无按键按下
}

unsigned char Trg=0;
unsigned char Cont=0;
unsigned char PressTime=0;
unsigned char key_mun=0;


void KeyRead(void)
{
    unsigned char ReadData = (KEYPORT)^0xff;
    Trg = ReadData&(ReadData ^ Cont);
    Cont = ReadData;

}

u8 KeyProc(void)
{
    KeyRead();
    
/***********************长按部分******************************/    
    switch (Cont)
    {
        case 0x01:
                    PressTime++, key_mun=1;
                    if(PressTime>40) return 4;
        break;
        case 0x02:  PressTime++, key_mun=2;
                    if(PressTime>40) 
        break; 
        default: 
        break;
    }
/********************************************************/    
/************************短按部分********************************/    
    
    if(Trg==0x00 && Cont==0x00)
    {
        if(PressTime > 0 && PressTime < 20)
        {
            switch (key_mun)
            {
                case 1: return 3;
                break;
                case 2: Power_On=0;
                break;
                default :
                break;
            }
        
        }
        PressTime=0;
    }
/*****************************************************/    
    return 0;
}














