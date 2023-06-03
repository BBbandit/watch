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
	u8 current_index;	//存放当前界面的索引号；
	u8 down_index;		//存放按下“down（向下）”键时需要跳转到的索引号；
	u8 up_index;		//存放按下“up（向上）”键时需要跳转到的索引号；
	u8 enter_index;		//存放按下“enter（进入）”键时需要跳转的索引号；
	u8 esc_index;		//存放按下“esc（退出）”键时需要跳转的索引号；
	void (*operate)(u8);	//函数指针变量，存放当前索引号下需要执行的函数的入口地址。
}Key_index_struct;
 



void OLED_display(u8 press);
void mainWindow(u8 press);//主界面
void menu1(u8 press);//菜单列表
void menu2(u8 press);//菜单列表
void menu3(u8 pressd);//菜单列表
void menu4(u8 press);//菜单列表
void menu5(u8 press);//菜单列表
void menu6(u8 press);//菜单列表 
void menu7(u8 press);//菜单列表 
void menu2_1(u8 press);//菜单列表
void menu2_2(u8 press);//菜单列表
void menu2_3(u8 press);//菜单列表 
void menu2_4(u8 press);//菜单列表 
void menu2_5(u8 press);//菜单列表
void menu2_6(u8 press);//菜单列表 
void menu2_7(u8 press);//菜单列表 


#endif

