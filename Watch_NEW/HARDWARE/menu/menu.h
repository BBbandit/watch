#ifndef __MENU_H
#define __MENU_H	 
#include "sys.h"
#include "stdlib.h"
#include "delay.h"
#include "key.h"
#include "usart.h"
#include "app_start.h"
#include "app_meun.h"
#include "app_clock.h"
#include "app_lighting.h"
#include "app_about.h"
#include "app_game.h"
#include "iwdg.h"
#include "led.h"

extern u8 nowIndex;


typedef struct{
	u8 current_index;	//��ŵ�ǰ����������ţ�
	u8 down_index;		//��Ű��¡�down�����£�����ʱ��Ҫ��ת���������ţ�
	u8 up_index;		//��Ű��¡�up�����ϣ�����ʱ��Ҫ��ת���������ţ�
	u8 enter_index;		//��Ű��¡�enter�����룩����ʱ��Ҫ��ת�������ţ�
	u8 esc_index;		//��Ű��¡�esc���˳�������ʱ��Ҫ��ת�������ţ�
	void (*operate)(u8);	//����ָ���������ŵ�ǰ����������Ҫִ�еĺ�������ڵ�ַ��
}Key_index_struct;
 



void OLED_display(u8 press);
void mainWindow(u8 press);//������
void menu1(u8 press);//�˵��б�
void menu2(u8 press);//�˵��б�
void menu3(u8 pressd);//�˵��б�
void menu4(u8 press);//�˵��б�
void menu5(u8 press);//�˵��б�
void menu6(u8 press);//�˵��б� 
void menu7(u8 press);//�˵��б� 
void menu2_1(u8 press);//�˵��б�
void menu2_2(u8 press);//�˵��б�
void menu2_3(u8 press);//�˵��б� 
void menu2_4(u8 press);//�˵��б� 
void menu2_5(u8 press);//�˵��б�
void menu2_6(u8 press);//�˵��б� 
void menu2_7(u8 press);//�˵��б� 


#endif

