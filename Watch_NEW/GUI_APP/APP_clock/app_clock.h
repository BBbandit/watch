#ifndef _APP_CLOCK_H_
#define _APP_CLOCK_H_
#include "lvgl.h"
#include "app_anim.h"
#include "rtc.h"
#include "menu.h"


typedef struct 
{
  uint16_t year;  //年
  uint8_t month;  //月
  uint8_t date;   //日
  uint8_t hour;   //时
  uint8_t min;    //分
  uint8_t sec;    //秒
  uint8_t week;   //星期
}RTC_Data_Type; //RTC时间数据结构类型



void app_clock_create(void);
void app_set_clock_anim_Hexit_img( bool dir);
void app_setting_update_roller(RTC_TimeTypeDef *rtc_time,RTC_DateTypeDef *rtc_data);
void app_setting_change_roller(uint8_t i);
void app_setting_change(uint8_t index);
uint8_t app_setting_get_roller_index(void);
const uint8_t* app_setting_get_roller_max(void);
void app_setting_update_time(void);
void set_enter (bool enter);


#endif

