#ifndef _APP_START_H_
#define _APP_START_H_

#include "lvgl.h"
#include "app_anim.h"
#include "string.h"
#include "sys.h"
#include "usart.h"	
#include "stdio.h"
#include "rtc.h"
#include "key.h"
#include "bmp180.h"
#include "mpu6050.h"
#include "app_clock.h"
#include "menu.h"
#include "adc.h"


extern unsigned long step_count;
extern u8 adcx;
extern char timer[5];
extern char Seconds[2];
extern char date[5];
extern char TEMP[8];
extern char walk[8];
extern char bat[5];
extern char week;
extern char hours;
extern char minutes;
extern char seconds;



void app_show_start(void);
void start_img_anim(void);
void app_del_start(void);
void app_digital_clock_create(void);
void get_num(int i);
void app_digital_clock_meun_re( bool dir);

    


#endif


