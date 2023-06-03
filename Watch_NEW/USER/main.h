 #ifndef __MAIN_H__
#define __MAIN_H__

#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"
#include "dma.h"		
#include "usart.h"	
#include "sys.h"
#include "includes.h"
#include "os_app_hooks.h"
#include "timer.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "app_start.h"
#include "rtc.h"
#include "key.h"
#include "ioi2c.h"
#include "mpu6050.h"
#include <stdio.h>
#include "bmp180.h"
#include "menu.h"
#include "app_meun.h"
#include "app_clock.h"
#include "app_lighting.h"
#include "app_game.h"
#include "app_about.h"
#include "led.h"
#include "pwm.h"
#include "adc.h"
#include "iwdg.h"


//�������ȼ�
#define START_TASK_PRIO		3
//�����ջ��С	
#define START_STK_SIZE 		512
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);



//�������ȼ�
#define MPU6050_TASK_PRIO		4
//�����ջ��С
#define MPU6050_STK_SIZE		512
//������ƿ�
OS_TCB	MPU6050TaskTCB;
//�����ջ
__align(8) CPU_STK	MPU6050_TASK_STK[MPU6050_STK_SIZE];
//������
void MPU6050_task(void *p_arg);

//�������ȼ�
#define BMP_TASK_PRIO		5
//�����ջ��С
#define BMP_STK_SIZE		512
//������ƿ�
OS_TCB	BMPTaskTCB;
//�����ջ
__align(8) CPU_STK	BMP_TASK_STK[BMP_STK_SIZE];
//������
void BMP_task(void *p_arg);


//�������ȼ�
#define BUTTON_TASK_PRIO		7
//�����ջ��С	
#define BUTTON_STK_SIZE 		512
//������ƿ�
OS_TCB BUTTONTaskTCB;
//�����ջ	
CPU_STK BUTTON_TASK_STK[BUTTON_STK_SIZE];
void BUTTON_task(void *p_arg);

//�������ȼ�
#define LVGL_TASK_PRIO		8
//�����ջ��С	
#define LVGL_STK_SIZE 		1024
//������ƿ�
OS_TCB LVGLTaskTCB;
//�����ջ	
CPU_STK LVGL_TASK_STK[LVGL_STK_SIZE];
void LVGL_task(void *p_arg);

//�������ȼ�
#define DATA_TASK_PRIO		6
//�����ջ��С	
#define DATA_STK_SIZE 		512
//������ƿ�
OS_TCB DATATaskTCB;
//�����ջ	
CPU_STK DATA_TASK_STK[DATA_STK_SIZE];
void DATA_task(void *p_arg);





#endif
