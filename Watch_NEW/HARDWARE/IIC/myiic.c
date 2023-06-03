#include "myiic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//��ʼ��IIC
void iiC_Init(void)
{					     
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��

  //GPIOB8,B9��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;//50MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
}
//����IIC��ʼ�ź�
void iiC_Start(void)
{
	sDA_OUT();     //sda�����
	IIC_sDA=1;	  	  
	IIC_sCL=1;
	delay_us(4);
 	IIC_sDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_sCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void iiC_Stop(void)
{
	sDA_OUT();//sda�����
	IIC_sCL=0;
	IIC_sDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_sCL=1; 
	IIC_sDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 iiC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	sDA_IN();      //SDA����Ϊ����  
	IIC_sDA=1;delay_us(1);	   
	IIC_sCL=1;delay_us(1);	 
	while(READ_sDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			iiC_Stop();
			return 1;
		}
	}
	IIC_sCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void iiC_Ack(void)
{
	IIC_sCL=0;
	sDA_OUT();
	IIC_sDA=0;
	delay_us(2);
	IIC_sCL=1;
	delay_us(2);
	IIC_sCL=0;
}
//������ACKӦ��		    
void iiC_NAck(void)
{
	IIC_sCL=0;
	sDA_OUT();
	IIC_sDA=1;
	delay_us(2);
	IIC_sCL=1;
	delay_us(2);
	IIC_sCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void iiC_Send_Byte(u8 txd)
{                        
    u8 t;   
	sDA_OUT(); 	    
    IIC_sCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_sDA=1;
		else
			IIC_sDA=0;
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_sCL=1;
		delay_us(2); 
		IIC_sCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 iiC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	sDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_sCL=0; 
        delay_us(2);
		IIC_sCL=1;
        receive<<=1;
        if(READ_sDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        iiC_NAck();//����nACK
    else
        iiC_Ack(); //����ACK   
    return receive;
}



























