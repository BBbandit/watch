#ifndef _APP_CLOCK_H_
#define _APP_CLOCK_H_
#include "lvgl.h"
#include "app_anim.h"
#include "rtc.h"
#include "menu.h"


typedef struct 
{
  uint16_t year;  //��
  uint8_t month;  //��
  uint8_t date;   //��
  uint8_t hour;   //ʱ
  uint8_t min;    //��
  uint8_t sec;    //��
  uint8_t week;   //����
}RTC_Data_Type; //RTCʱ�����ݽṹ����



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

