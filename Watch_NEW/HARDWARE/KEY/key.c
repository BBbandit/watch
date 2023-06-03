#include "key.h"
#include "delay.h" 

//������ʼ������
void KEY_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOA,GPIOEʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
  Power_Key_Init();
  Power_Change_Init();
}

void Power_Key_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOA,GPIOEʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA2
}


void Power_Change_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOA,GPIOEʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA2
    
}





u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;    
	}else if(KEY0==1&&KEY1==1)key_up=1; 	    
 	return 0;// �ް�������
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
    
/***********************��������******************************/    
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
/************************�̰�����********************************/    
    
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














