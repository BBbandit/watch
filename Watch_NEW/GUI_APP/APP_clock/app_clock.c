#include "app_clock.h"

static lv_obj_t *set_clock_cont; //ҳ������
static uint8_t foucs_roller_index = 0;		//��ǰѡ�е�roller

static lv_obj_t *time_date_roller[7]; //ʱ����������roller
static lv_obj_t *time_point_label[2];		//ʱ���: label
static lv_obj_t *date_Hline_label[3];		//���ڵ�20 �� - lable

static lv_obj_t *enter_btn;		//ȷ�ϰ���
static lv_obj_t *enter_btn_lable;		//����label

static const uint8_t roller_max[7] = {24, 60, 60, 30, 12, 31, 7};
static const char roller_string[] = 
{
	"00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n\
24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n\
48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59\n"
};

static const char week_list[] = {"Sun.\nMon.\nTue.\nWen.\nThu.\nFri.\nSat."};				 //���б�

RTC_TimeTypeDef RTC_Up_TimeStruct;
RTC_DateTypeDef RTC_Up_DateStruct;
lv_task_t *task4;
void task4_cb(lv_task_t* task)
{
    
    RTC_GetTime(RTC_Format_BIN,&RTC_Up_TimeStruct);
    RTC_GetDate(RTC_Format_BIN, &RTC_Up_DateStruct);;    
    if(nowIndex!=8 && nowIndex!=14) app_setting_update_roller(&RTC_Up_TimeStruct,&RTC_Up_DateStruct);    

}





//����ʱ�ӽ������
void app_clock_create(void)
{
	uint8_t i;
	char roller_buf[181];    
	lv_obj_t *scr;

	scr = lv_scr_act(); //��ȡ��ǰ��Ծ����Ļ
    /***********************����ʱ�����ÿؼ�****************************/
    set_clock_cont = lv_cont_create(scr, NULL);															  //������ʾ����
    lv_obj_set_pos(set_clock_cont, 135, 37);																  //��������λ��
    lv_obj_set_size(set_clock_cont, 135, 205);															  //���������ߴ�
    lv_obj_set_style_local_bg_opa(set_clock_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	  //���ñ���͸��
    lv_obj_set_style_local_border_opa(set_clock_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP); //���ñ߿�͸��
    lv_cont_set_layout(set_clock_cont, LV_LAYOUT_OFF);												  //���������Ĳ��ַ�ʽ: �����Զ�����
    lv_obj_set_style_local_pad_inner(set_clock_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			  //�����Ӷ���֮��ļ��
    /***********************����ʱ�����ÿؼ�****************************/    
    
	/*********************************************����ʱ����������roller******************************************************/
	for(i = 0; i < 7; i++)
	{
		time_date_roller[i] = lv_roller_create(set_clock_cont, NULL);																//����ʱ������roller
		lv_obj_set_style_local_text_font(time_date_roller[i], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, &lv_font_montserrat_16); //����16������
		lv_obj_set_style_local_text_color(time_date_roller[i], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_COLOR_RED);		   //����������ɫ
		lv_obj_set_style_local_border_color(time_date_roller[i], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_COLOR_RED);			//���ÿؼ��߿��ɫ
		lv_obj_set_style_local_bg_opa(time_date_roller[i], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_OPA_TRANSP);			//���ÿؼ�����͸��
		
		lv_obj_set_style_local_text_color(time_date_roller[i], LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, LV_COLOR_RED);		   //����ѡ����������ɫ
		lv_obj_set_style_local_border_opa(time_date_roller[i], LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, LV_OPA_TRANSP);			//����ѡ����߿�͸��
		lv_obj_set_style_local_bg_opa(time_date_roller[i], LV_ROLLER_PART_SELECTED, LV_STATE_DEFAULT, LV_OPA_TRANSP);			//����ѡ����߿�͸��
		
		lv_roller_set_visible_row_count(time_date_roller[i], 1);															//�������ɼ�1��
		
		if(i != 4 && i != 5)			//�������º���roller
			memcpy(roller_buf, roller_string, roller_max[i] * 3);			//��00��ʼ������������ַ���
		else
			memcpy(roller_buf, roller_string + 3, roller_max[i] * 3);			//��01��ʼ������������ַ���
		
		roller_buf[roller_max[i] * 3] = '\0';
		
		lv_roller_set_options(time_date_roller[i], roller_buf, LV_ROLLER_MODE_INFINITE); //����ѡ��(��������ģʽ)
		lv_obj_align(time_date_roller[i], set_clock_cont, LV_ALIGN_IN_TOP_LEFT,5+i * 45, 10);																					 //���ö���
		lv_roller_set_anim_time(time_date_roller[i], 100);		//����ʱ��500ms
	}    
    	lv_obj_set_style_local_border_color(time_date_roller[0], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_COLOR_GREEN);			//���õ�һ���ؼ��߿���ɫ
    
	for(i = 0; i < 2; i++)		//����ʱ��� ":" lable
	{
		time_point_label[i] = lv_label_create(set_clock_cont, NULL);		//����ʱ��point lable
		lv_obj_set_style_local_text_font(time_point_label[i], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16); //��������20��
		lv_obj_set_style_local_text_color(time_point_label[i], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		   //����������ɫ
		lv_label_set_text(time_point_label[i], ":");
		lv_obj_align(time_point_label[i], time_date_roller[i], LV_ALIGN_OUT_RIGHT_MID, 3, 0);
	}    
	/*********************************************������������rollerλ��******************************************************/
	for(i = 0; i < 3; i++)
	{
		lv_obj_align(time_date_roller[i + 3], set_clock_cont, LV_ALIGN_IN_TOP_LEFT, 5 + i * 45, 70);																					 //���ö���
	}    
	lv_roller_set_options(time_date_roller[6], week_list, LV_ROLLER_MODE_INFINITE); //������ѡ��(��������ģʽ)
	lv_obj_align(time_date_roller[6], set_clock_cont, LV_ALIGN_CENTER, 0, 30);
    
    for(i = 0; i < 2; i++)	//�������ڵ� �� "20" �� "-" lable
	{
		date_Hline_label[i] = lv_label_create(set_clock_cont, NULL);		//�������ڵ� ��20 �� - lable
		lv_obj_set_style_local_text_font(date_Hline_label[i], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16); //��������20��
		lv_obj_set_style_local_text_color(date_Hline_label[i], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		   //����������ɫ
		lv_label_set_text(date_Hline_label[i], "-" );
		lv_obj_align(date_Hline_label[i], time_date_roller[i + 4], LV_ALIGN_OUT_LEFT_MID,  0, 0);
	}
    
	/*********************************************����ȷ�ϰ���btn******************************************************/
	enter_btn = lv_btn_create(set_clock_cont, NULL);
	lv_obj_set_size(enter_btn, 60, 22);		//���ð�ť��С
	lv_obj_align(enter_btn, set_clock_cont, LV_ALIGN_IN_BOTTOM_MID, 0, -10);		//���ð�ť����
	lv_obj_set_style_local_bg_opa(enter_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);		//���ñ���͸��
	lv_obj_set_style_local_border_color(enter_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);		//���ñ߿���ɫ
	
	enter_btn_lable = lv_label_create(enter_btn, NULL);		//������ťlabel
	lv_label_set_text(enter_btn_lable, "Enter");           
	lv_obj_set_style_local_text_color(enter_btn_lable, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);		   //����������ɫ
	lv_obj_align(enter_btn_lable, enter_btn, LV_ALIGN_CENTER, 0, 0);		//���ð�ť�ı�����    

    task4 = lv_task_create(task4_cb,100,LV_TASK_PRIO_MID,NULL);                                          // ��ͼ�ص�����  
    
}

void set_enter (bool enter)
{
    if(enter) 
    {
        lv_obj_set_style_local_border_color(enter_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		//���ñ߿���ɫ        
        lv_obj_set_style_local_text_color(enter_btn_lable, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		   //����������ɫ
    
    
    }
    else 
    {
        lv_obj_set_style_local_border_color(enter_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);		//���ñ߿���ɫ        
        lv_obj_set_style_local_text_color(enter_btn_lable, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);		   //����������ɫ    
    }

}

//���õ�ǰѡ��roller����
void app_setting_change(uint8_t index)
{
	lv_roller_set_selected(time_date_roller[foucs_roller_index], index, LV_ANIM_ON);
}


//���õ�ǰѡ�е�roller
void app_setting_change_roller(uint8_t i)
{
	foucs_roller_index = i;
	
	lv_obj_set_style_local_border_color(time_date_roller[i == 0 ? 6 : i - 1], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_COLOR_RED);			//������һ��ѡ�е�roller�ؼ��߿��ɫ
	if(i != 7)
	{
		lv_obj_set_style_local_border_color(enter_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);		//���ñ߿���ɫ
		lv_obj_set_style_local_border_color(time_date_roller[foucs_roller_index], LV_ROLLER_PART_BG, LV_STATE_DEFAULT, LV_COLOR_GREEN);			//���õ�ǰѡ�е�roller�ؼ��߿���ɫ
	}
	else
		lv_obj_set_style_local_border_color(enter_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		//���ñ߿���ɫ
}

//��ȡ��ǰѡ�е�roller��������
uint8_t app_setting_get_roller_index(void)
{
	return lv_roller_get_selected(time_date_roller[foucs_roller_index]);
}

//��ȡÿ��roller�������ַ
const uint8_t* app_setting_get_roller_max(void)
{
	return roller_max;
}

//���ݵ�ǰʱ���ʼ��roller
void app_setting_update_roller(RTC_TimeTypeDef *rtc_time,RTC_DateTypeDef *rtc_data)
{
    
	lv_roller_set_selected(time_date_roller[0], rtc_time->RTC_Hours, LV_ANIM_OFF);		//ʱ
	lv_roller_set_selected(time_date_roller[1], rtc_time->RTC_Minutes, LV_ANIM_OFF);			//��
	lv_roller_set_selected(time_date_roller[2], rtc_time->RTC_Seconds, LV_ANIM_OFF);			//��
	
	lv_roller_set_selected(time_date_roller[3], rtc_data->RTC_Year - 2000, LV_ANIM_OFF);		//��
	lv_roller_set_selected(time_date_roller[4], rtc_data->RTC_Month - 1, LV_ANIM_OFF);			//��, ��1��ʼ����� - 1
	lv_roller_set_selected(time_date_roller[5], rtc_data->RTC_Date - 1, LV_ANIM_OFF);			//��, ��1��ʼ����� - 1	
	lv_roller_set_selected(time_date_roller[6], rtc_data->RTC_WeekDay, LV_ANIM_OFF);			//��
}


//����roller���ʱ�����ͽṹ��
void app_setting_update_time(void)
{
    RTC_Data_Type rtc_t;
	rtc_t.hour = lv_roller_get_selected(time_date_roller[0]);		//��ȡʱ
	rtc_t.min = lv_roller_get_selected(time_date_roller[1]);		//��ȡ��
	rtc_t.sec = lv_roller_get_selected(time_date_roller[2]);		//��ȡ��
	
	rtc_t.year = lv_roller_get_selected(time_date_roller[3]) + 2000;		//��ȡ��
	rtc_t.month = lv_roller_get_selected(time_date_roller[4]) + 1;		//��ȡ��
	rtc_t.date = lv_roller_get_selected(time_date_roller[5]) + 1;		//��ȡ��
	
	rtc_t.week = lv_roller_get_selected(time_date_roller[6]);		//��ȡ��
    
    RTC_Set_Time(rtc_t.hour,rtc_t.min,rtc_t.sec,RTC_H12_AM);	//����ʱ��
    RTC_Set_Date(rtc_t.year,rtc_t.month,rtc_t.date,rtc_t.week);		//��������    

}


//ʱ������ͼ��ˮƽ�����ƶ�������˳�����
void app_set_clock_anim_Hexit_img( bool dir)
{
	uint16_t start;
	
	start = lv_obj_get_x(set_clock_cont);		//��ȡ��ʼֵ
	
	obj_add_anim(
								set_clock_cont, 		//��������
								(lv_anim_exec_xcb_t)lv_obj_set_x,				//��������
								lv_anim_speed_to_time(100, 0, 42),			//�����ٶ�
								start,																	//��ʼֵ
								start + (dir ? -135 : 135),							//����ֵ
								lv_anim_path_bounce											//������Ч:ģ�ⵯ����������
								);
}






