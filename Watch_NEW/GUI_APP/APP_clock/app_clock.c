#include "app_clock.h"

static lv_obj_t *set_clock_cont; //页面容器
static uint8_t foucs_roller_index = 0;		//当前选中的roller

static lv_obj_t *time_date_roller[7]; //时间日期设置roller
static lv_obj_t *time_point_label[2];		//时间的: label
static lv_obj_t *date_Hline_label[3];		//日期的20 和 - lable

static lv_obj_t *enter_btn;		//确认按键
static lv_obj_t *enter_btn_lable;		//按键label

static const uint8_t roller_max[7] = {24, 60, 60, 30, 12, 31, 7};
static const char roller_string[] = 
{
	"00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n\
24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n\
48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59\n"
};

static const char week_list[] = {"Sun.\nMon.\nTue.\nWen.\nThu.\nFri.\nSat."};				 //周列表

RTC_TimeTypeDef RTC_Up_TimeStruct;
RTC_DateTypeDef RTC_Up_DateStruct;
lv_task_t *task4;
void task4_cb(lv_task_t* task)
{
    
    RTC_GetTime(RTC_Format_BIN,&RTC_Up_TimeStruct);
    RTC_GetDate(RTC_Format_BIN, &RTC_Up_DateStruct);;    
    if(nowIndex!=8 && nowIndex!=14) app_setting_update_roller(&RTC_Up_TimeStruct,&RTC_Up_DateStruct);    

}





//创建时钟界面界面
void app_clock_create(void)
{
	uint8_t i;
	char roller_buf[181];    
	lv_obj_t *scr;

	scr = lv_scr_act(); //获取当前活跃的屏幕
    /***********************创建时钟设置控件****************************/
    set_clock_cont = lv_cont_create(scr, NULL);															  //创建提示容器
    lv_obj_set_pos(set_clock_cont, 135, 37);																  //设置容器位置
    lv_obj_set_size(set_clock_cont, 135, 205);															  //设置容器尺寸
    lv_obj_set_style_local_bg_opa(set_clock_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	  //设置背景透明
    lv_obj_set_style_local_border_opa(set_clock_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP); //设置边框透明
    lv_cont_set_layout(set_clock_cont, LV_LAYOUT_OFF);												  //设置容器的布局方式: 开启自动布局
    lv_obj_set_style_local_pad_inner(set_clock_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			  //设置子对象之间的间距
    /***********************创建时钟设置控件****************************/    
    
	/*********************************************创建时间日期设置roller******************************************************/
	for(i = 0; i < 7; i++)
	{
		time_date_roller[i] = lv_roller_create(set_clock_cont, NULL);																//创建时间设置roller
		lv_obj_set_style_local_text_font(time_date_roller[i], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, &lv_font_montserrat_16); //设置16号字体
		lv_obj_set_style_local_text_color(time_date_roller[i], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_COLOR_RED);		   //设置字体颜色
		lv_obj_set_style_local_border_color(time_date_roller[i], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_COLOR_RED);			//设置控件边框红色
		lv_obj_set_style_local_bg_opa(time_date_roller[i], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_OPA_TRANSP);			//设置控件背景透明
		
		lv_obj_set_style_local_text_color(time_date_roller[i], LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, LV_COLOR_RED);		   //设置选中项字体颜色
		lv_obj_set_style_local_border_opa(time_date_roller[i], LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, LV_OPA_TRANSP);			//设置选中项边框透明
		lv_obj_set_style_local_bg_opa(time_date_roller[i], LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, LV_OPA_TRANSP);			//设置选中项边框透明
		
		lv_roller_set_visible_row_count(time_date_roller[i], 1);															//设置最多可见1行
		
		if(i != 4 && i != 5)			//若不是月和日roller
			memcpy(roller_buf, roller_string, roller_max[i] * 3);			//从00开始拷贝所有项的字符串
		else
			memcpy(roller_buf, roller_string + 3, roller_max[i] * 3);			//从01开始拷贝所有项的字符串
		
		roller_buf[roller_max[i] * 3] = '\0';
		
		lv_roller_set_options(time_date_roller[i], roller_buf, LV_ROLLER_MODE_INFINITE); //设置选项(正常滚动模式)
		lv_obj_align(time_date_roller[i], set_clock_cont, LV_ALIGN_IN_TOP_LEFT,5+i * 45, 10);																					 //设置对齐
		lv_roller_set_anim_time(time_date_roller[i], 100);		//动画时间500ms
	}    
    	lv_obj_set_style_local_border_color(time_date_roller[0], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_COLOR_GREEN);			//设置第一个控件边框绿色
    
	for(i = 0; i < 2; i++)		//创建时间的 ":" lable
	{
		time_point_label[i] = lv_label_create(set_clock_cont, NULL);		//创建时间point lable
		lv_obj_set_style_local_text_font(time_point_label[i], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16); //设置字体20号
		lv_obj_set_style_local_text_color(time_point_label[i], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		   //设置字体颜色
		lv_label_set_text(time_point_label[i], ":");
		lv_obj_align(time_point_label[i], time_date_roller[i], LV_ALIGN_OUT_RIGHT_MID, 3, 0);
	}    
	/*********************************************调整日期设置roller位置******************************************************/
	for(i = 0; i < 3; i++)
	{
		lv_obj_align(time_date_roller[i + 3], set_clock_cont, LV_ALIGN_IN_TOP_LEFT, 5 + i * 45, 70);																					 //设置对齐
	}    
	lv_roller_set_options(time_date_roller[6], week_list, LV_ROLLER_MODE_INFINITE); //设置周选项(正常滚动模式)
	lv_obj_align(time_date_roller[6], set_clock_cont, LV_ALIGN_CENTER, 0, 30);
    
    for(i = 0; i < 2; i++)	//创建日期的 年 "20" 和 "-" lable
	{
		date_Hline_label[i] = lv_label_create(set_clock_cont, NULL);		//创建日期的 年20 和 - lable
		lv_obj_set_style_local_text_font(date_Hline_label[i], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16); //设置字体20号
		lv_obj_set_style_local_text_color(date_Hline_label[i], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		   //设置字体颜色
		lv_label_set_text(date_Hline_label[i], "-" );
		lv_obj_align(date_Hline_label[i], time_date_roller[i + 4], LV_ALIGN_OUT_LEFT_MID,  0, 0);
	}
    
	/*********************************************创建确认按键btn******************************************************/
	enter_btn = lv_btn_create(set_clock_cont, NULL);
	lv_obj_set_size(enter_btn, 60, 22);		//设置按钮大小
	lv_obj_align(enter_btn, set_clock_cont, LV_ALIGN_IN_BOTTOM_MID, 0, -10);		//设置按钮对齐
	lv_obj_set_style_local_bg_opa(enter_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);		//设置背景透明
	lv_obj_set_style_local_border_color(enter_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);		//设置边框颜色
	
	enter_btn_lable = lv_label_create(enter_btn, NULL);		//创建按钮label
	lv_label_set_text(enter_btn_lable, "Enter");           
	lv_obj_set_style_local_text_color(enter_btn_lable, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);		   //设置字体颜色
	lv_obj_align(enter_btn_lable, enter_btn, LV_ALIGN_CENTER, 0, 0);		//设置按钮文本对齐    

    task4 = lv_task_create(task4_cb,100,LV_TASK_PRIO_MID,NULL);                                          // 动图回调函数  
    
}

void set_enter (bool enter)
{
    if(enter) 
    {
        lv_obj_set_style_local_border_color(enter_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		//设置边框颜色        
        lv_obj_set_style_local_text_color(enter_btn_lable, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		   //设置字体颜色
    
    
    }
    else 
    {
        lv_obj_set_style_local_border_color(enter_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);		//设置边框颜色        
        lv_obj_set_style_local_text_color(enter_btn_lable, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);		   //设置字体颜色    
    }

}

//设置当前选中roller的项
void app_setting_change(uint8_t index)
{
	lv_roller_set_selected(time_date_roller[foucs_roller_index], index, LV_ANIM_ON);
}


//设置当前选中的roller
void app_setting_change_roller(uint8_t i)
{
	foucs_roller_index = i;
	
	lv_obj_set_style_local_border_color(time_date_roller[i == 0 ? 6 : i - 1], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_COLOR_RED);			//设置上一个选中的roller控件边框红色
	if(i != 7)
	{
		lv_obj_set_style_local_border_color(enter_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);		//设置边框颜色
		lv_obj_set_style_local_border_color(time_date_roller[foucs_roller_index], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_COLOR_GREEN);			//设置当前选中的roller控件边框绿色
	}
	else
		lv_obj_set_style_local_border_color(enter_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		//设置边框颜色
}

//获取当前选中的roller的项索引
uint8_t app_setting_get_roller_index(void)
{
	return lv_roller_get_selected(time_date_roller[foucs_roller_index]);
}

//获取每个roller最大项保存地址
const uint8_t* app_setting_get_roller_max(void)
{
	return roller_max;
}

//根据当前时间初始化roller
void app_setting_update_roller(RTC_TimeTypeDef *rtc_time,RTC_DateTypeDef *rtc_data)
{
    
	lv_roller_set_selected(time_date_roller[0], rtc_time->RTC_Hours, LV_ANIM_OFF);		//时
	lv_roller_set_selected(time_date_roller[1], rtc_time->RTC_Minutes, LV_ANIM_OFF);			//分
	lv_roller_set_selected(time_date_roller[2], rtc_time->RTC_Seconds, LV_ANIM_OFF);			//秒
	
	lv_roller_set_selected(time_date_roller[3], rtc_data->RTC_Year - 2000, LV_ANIM_OFF);		//年
	lv_roller_set_selected(time_date_roller[4], rtc_data->RTC_Month - 1, LV_ANIM_OFF);			//月, 从1开始，因此 - 1
	lv_roller_set_selected(time_date_roller[5], rtc_data->RTC_Date - 1, LV_ANIM_OFF);			//日, 从1开始，因此 - 1	
	lv_roller_set_selected(time_date_roller[6], rtc_data->RTC_WeekDay, LV_ANIM_OFF);			//周
}


//根据roller填充时间类型结构体
void app_setting_update_time(void)
{
    RTC_Data_Type rtc_t;
	rtc_t.hour = lv_roller_get_selected(time_date_roller[0]);		//获取时
	rtc_t.min = lv_roller_get_selected(time_date_roller[1]);		//获取分
	rtc_t.sec = lv_roller_get_selected(time_date_roller[2]);		//获取秒
	
	rtc_t.year = lv_roller_get_selected(time_date_roller[3]) + 2000;		//获取年
	rtc_t.month = lv_roller_get_selected(time_date_roller[4]) + 1;		//获取月
	rtc_t.date = lv_roller_get_selected(time_date_roller[5]) + 1;		//获取日
	
	rtc_t.week = lv_roller_get_selected(time_date_roller[6]);		//获取周
    
    RTC_Set_Time(rtc_t.hour,rtc_t.min,rtc_t.sec,RTC_H12_AM);	//设置时间
    RTC_Set_Date(rtc_t.year,rtc_t.month,rtc_t.date,rtc_t.week);		//设置日期    

}


//时钟设置图标水平方向移动进入或退出中心
void app_set_clock_anim_Hexit_img( bool dir)
{
	uint16_t start;
	
	start = lv_obj_get_x(set_clock_cont);		//获取起始值
	
	obj_add_anim(
								set_clock_cont, 		//动画对象
								(lv_anim_exec_xcb_t)lv_obj_set_x,				//动画函数
								lv_anim_speed_to_time(100, 0, 42),			//动画速度
								start,																	//起始值
								start + (dir ? -135 : 135),							//结束值
								lv_anim_path_bounce											//动画特效:模拟弹性物体下落
								);
}






