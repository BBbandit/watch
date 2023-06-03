#include "app_start.h"



LV_IMG_DECLARE(people1);
LV_IMG_DECLARE(people2);
LV_IMG_DECLARE(people3);
LV_IMG_DECLARE(people4);
LV_IMG_DECLARE(people5);
LV_IMG_DECLARE(people6);
LV_IMG_DECLARE(people7);
LV_IMG_DECLARE(people8);
LV_IMG_DECLARE(people9);
LV_IMG_DECLARE(people10);
LV_IMG_DECLARE(people11);
LV_IMG_DECLARE(people12);
LV_IMG_DECLARE(people13);
LV_IMG_DECLARE(people14);
LV_IMG_DECLARE(people15);
LV_IMG_DECLARE(people16);
LV_IMG_DECLARE(people17);
LV_IMG_DECLARE(people18);
LV_IMG_DECLARE(people19);
LV_IMG_DECLARE(people20);
LV_IMG_DECLARE(people21);
LV_IMG_DECLARE(people22);
LV_IMG_DECLARE(people23);
LV_IMG_DECLARE(people24);
LV_IMG_DECLARE(people25);
LV_IMG_DECLARE(people26);
LV_IMG_DECLARE(people27);
LV_IMG_DECLARE(people28);
LV_IMG_DECLARE(people29);
LV_IMG_DECLARE(people30);

//����ͼƬ
LV_IMG_DECLARE(start);
LV_IMG_DECLARE(main_back);


LV_FONT_DECLARE(my_font_icon_num60);//�������� ��������
LV_FONT_DECLARE(my_font_icon_num20);//�������� ��������
LV_FONT_DECLARE(my_font_icon_30);//�������� ��������
LV_FONT_DECLARE(my_font_icon_31);//�������� ��������
#define MY_ICON_RUNING "\xEE\x98\xA6" //����ͼ������
#define MY_ICON_TEMP "\xEE\x9B\x9E" //����ͼ������   


static lv_obj_t *start_img; //���忪ʼ����ͼƬimg
static lv_obj_t *main_img;	//����������ͼƬimg
static lv_obj_t *people_img;	//����������ͼƬimg
static lv_obj_t *bar_img;	//����������ͼƬimg
static lv_obj_t *charge_img;
lv_obj_t *scr;
lv_obj_t *anim_cont; //̫���˶�ͼ����
lv_obj_t *upscr_cont; //ʱ������
lv_obj_t *time_cont; //ʱ������
lv_obj_t *sec_cont; //������
lv_obj_t *data_cont; //��������
lv_obj_t *week_cont; //��������


lv_obj_t* label_time;
lv_obj_t* label_sec;
lv_obj_t* label_data;
lv_obj_t* label_week;
lv_obj_t* label_Run;
lv_obj_t* label_text_Run;
lv_obj_t* label_temp;
lv_obj_t* label_text_temp;

lv_obj_t* up_line;
lv_obj_t* down_line;



const lv_point_t line_points[] = { {0, 0}, {135, 00} };
#define LINE_POINTS_NUM (sizeof(line_points)/sizeof(line_points[0]))

u8 i=1;
lv_task_t *task3;
void task3_cb(lv_task_t* task)
{
    i++;
    if(i==30) i=0;
    get_num(i);
}


lv_task_t *task1;
char TEMP[8];
char walk[8];
   
unsigned long step_count=0;  
void task1_cb(lv_task_t* task)
{

    lv_label_set_static_text(label_text_temp, TEMP);  
    lv_label_set_static_text(label_text_Run,walk);  
    
}


char week;
char hours;
char minutes;
char seconds;

char timer[5];
char Seconds[2];
char date[5];

lv_task_t *task2;

u8 adcx;
char bat[5];

lv_obj_t * label_BAT;

void task2_cb(lv_task_t* task)
{
    lv_label_set_static_text(label_BAT, bat);
    if(adcx>80)   lv_img_set_src(bar_img,LV_SYMBOL_DUMMY LV_SYMBOL_BATTERY_FULL);
    else if(adcx>60&&adcx<=80) lv_img_set_src(bar_img,LV_SYMBOL_DUMMY LV_SYMBOL_BATTERY_3);    
    else if(adcx>40&&adcx<=60) lv_img_set_src(bar_img,LV_SYMBOL_DUMMY LV_SYMBOL_BATTERY_2);    
    else if(adcx>20&&adcx<=40) lv_img_set_src(bar_img,LV_SYMBOL_DUMMY LV_SYMBOL_BATTERY_1);     
    else  lv_img_set_src(bar_img,LV_SYMBOL_DUMMY LV_SYMBOL_BATTERY_EMPTY); 
    if(Charge==1) lv_img_set_src(charge_img,LV_SYMBOL_DUMMY LV_SYMBOL_CHARGE); 
    else          lv_img_set_src(charge_img,LV_SYMBOL_DUMMY LV_SYMBOL_GPS);
    
    lv_label_set_static_text(label_time, timer);
    lv_label_set_static_text(label_sec, Seconds);
    lv_label_set_static_text(label_data,date);  
    switch (week)
    {    
        case 1: lv_label_set_static_text(label_week,"Mon");break;
        case 2: lv_label_set_static_text(label_week,"Tues");break;
        case 3: lv_label_set_static_text(label_week,"Wed");break;
        case 4: lv_label_set_static_text(label_week,"Thur");break;
        case 5: lv_label_set_static_text(label_week,"Fri");break;
        case 6: lv_label_set_static_text(label_week,"Sat");break;
        case 7: lv_label_set_static_text(label_week,"Sun");break;
    }
    if(hours==23&&minutes==59&&seconds==59) 
    {
        dmp_set_pedometer_step_count(0);
        dmp_set_pedometer_walk_time(0);
    }   
}


//������ʼͼƬ
void app_show_start(void)
{

	scr = lv_scr_act();																		  //��ȡ��ǰ��Ծ����Ļ
	lv_obj_set_style_local_bg_color(scr, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE); //���ñ�����ɫΪ��ɫ

	start_img = lv_img_create(scr, NULL);

	lv_obj_set_size(start_img, 135, 240); //���ô�С

	lv_obj_align(start_img, scr, LV_ALIGN_CENTER, 0, 0); //����ͼƬ�������

	lv_img_set_src(start_img, &start); //Ȼ����ʾ��ͼƬ

	lv_obj_set_style_local_image_opa(start_img, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP); //ͼƬ͸��
}


//��ʼͼƬ�Ľ��䶯��
void start_img_anim(void)
{
	lv_anim_t anim;

	lv_anim_init(&anim);

	lv_anim_set_var(&anim, start_img); //��������

	lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)img_anim_exec_xcb); //���亯��
	lv_anim_set_time(&anim, lv_anim_speed_to_time(100, 0, 80));

	anim.start = LV_OPA_TRANSP;			//��ʼֵ
	anim.end = LV_OPA_COVER;			//����ֵ
	anim.path.cb = lv_anim_path_linear; //����
	anim.playback_time = 0;				//�ط�ʱ����Ϊ0��ִ�ж����ط�

	lv_anim_start(&anim);
}


//ɾ����ʼͼƬ
void app_del_start(void)
{
	lv_obj_del(start_img); //ɾ������ͼƬ����
}

//�������ֱ���
void app_digital_clock_create(void)
{

        scr = lv_scr_act();  //��ȡ��Ļ����

        main_img = lv_img_create(scr, NULL);

        lv_obj_set_pos(main_img, -10, 5);		 //����λ��
        lv_img_set_src(main_img, &main_back); //Ȼ����ʾ��ͼƬ
        /***********************�����ϰ���Ļ�ؼ�****************************/
        upscr_cont = lv_cont_create(scr, NULL);															  //����ʱ������
        lv_obj_set_pos(upscr_cont, 0, 0);																  //��������λ��
        lv_obj_set_size(upscr_cont, 135, 120);															  //���������ߴ�
        lv_obj_set_style_local_bg_opa(upscr_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	  //���ñ���͸��
        lv_obj_set_style_local_border_opa(upscr_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP); //���ñ߿�͸��
        lv_cont_set_layout(upscr_cont, LV_LAYOUT_OFF);												  //���������Ĳ��ַ�ʽ: �����Զ�����
        lv_obj_set_style_local_pad_inner(upscr_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			  //�����Ӷ���֮��ļ��
        /***********************�����ϰ���Ļ�ؼ�****************************/

        /***********************����ʱ��ؼ�****************************/

        time_cont = lv_cont_create(upscr_cont, NULL);													  //����ʱ������
        lv_obj_set_pos(time_cont, 0, 30);																  //��������λ��
        lv_obj_set_size(time_cont, 135, 30);															  //���������ߴ�
        lv_obj_set_style_local_bg_opa(time_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	  //���ñ���͸��
        lv_obj_set_style_local_border_opa(time_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP); //���ñ߿�͸��
        lv_cont_set_layout(time_cont, LV_LAYOUT_ROW_MID);												  //���������Ĳ��ַ�ʽ: �����Զ�����
        lv_obj_set_style_local_pad_inner(time_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			  //�����Ӷ���֮��ļ��

        label_time = lv_label_create(time_cont, NULL); 
        lv_obj_align(label_time, time_cont, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
        lv_obj_set_style_local_text_font(label_time, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &my_font_icon_num60); //��������
        lv_obj_set_style_local_text_color(label_time, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		  //������ɫ

	/***********************����ʱ��ؼ�****************************/
	/***********************������ؼ�****************************/
        sec_cont = lv_cont_create(upscr_cont, NULL);															  //����������
        lv_obj_set_pos(sec_cont, 100, 70);																  //��������λ��
        lv_obj_set_size(sec_cont, 50, 30);															  //���������ߴ�
        lv_obj_set_style_local_bg_opa(sec_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	  //���ñ���͸��
        lv_obj_set_style_local_border_opa(sec_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP); //���ñ߿�͸��
        lv_cont_set_layout(sec_cont, LV_LAYOUT_ROW_MID);												  //���������Ĳ��ַ�ʽ: �����Զ�����
        lv_obj_set_style_local_pad_inner(sec_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			  //�����Ӷ���֮��ļ��

        label_sec = lv_label_create(sec_cont, NULL); //������label
        lv_obj_align(label_sec, NULL, LV_ALIGN_CENTER, 100, 0);
        lv_obj_set_style_local_text_font(label_sec, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &my_font_icon_num20); //��������
        lv_obj_set_style_local_text_color(label_sec, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		  //������ɫ

	/***********************������ؼ�****************************/
	/***********************�������ڿؼ�****************************/
        data_cont = lv_cont_create(upscr_cont, NULL);															  //������������
        lv_obj_set_pos(data_cont, 0, 70);																  //��������λ��
        lv_obj_set_size(data_cont, 90, 30);															  //���������ߴ�
        lv_obj_set_style_local_bg_opa(data_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	  //���ñ���͸��
        lv_obj_set_style_local_border_opa(data_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP); //���ñ߿�͸��
        lv_cont_set_layout(data_cont, LV_LAYOUT_ROW_MID);												  //���������Ĳ��ַ�ʽ: �����Զ�����
        lv_obj_set_style_local_pad_inner(data_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			  //�����Ӷ���֮��ļ��

        label_data = lv_label_create(data_cont, NULL); //������label
        lv_obj_align(label_data, NULL, LV_ALIGN_CENTER, 100, 0);
        lv_obj_set_style_local_text_font(label_data, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &my_font_icon_num20); //��������
        lv_obj_set_style_local_text_color(label_data, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		  //������ɫ

	/***********************�������ڿؼ�****************************/
	/***********************�������ڿؼ�****************************/    
        week_cont = lv_cont_create(upscr_cont, NULL);															  //������������
        lv_obj_set_pos(week_cont, 0, 0);																  //��������λ��
        lv_obj_set_size(week_cont, 135, 30);															  //���������ߴ�
        lv_obj_set_style_local_bg_opa(week_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	  //���ñ���͸��
        lv_obj_set_style_local_border_opa(week_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP); //���ñ߿�͸��
        lv_cont_set_layout(week_cont, LV_LAYOUT_OFF);												  //���������Ĳ��ַ�ʽ: �����Զ�����
        lv_obj_set_style_local_pad_inner(week_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			  //�����Ӷ���֮��ļ��

        label_week = lv_label_create(week_cont, NULL); //������label
        lv_obj_align(label_week, week_cont, LV_ALIGN_IN_TOP_LEFT, 0, 0);
        lv_obj_set_style_local_text_font(label_week, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16); //��������
        lv_obj_set_style_local_text_color(label_week, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);		  //������ɫ

 	/***********************�������ڿؼ�****************************/
    /************************��ص�������***************************/     
        bar_img = lv_img_create(week_cont,NULL);
        lv_obj_align(bar_img,week_cont,LV_ALIGN_IN_TOP_RIGHT,20,0);

        label_BAT = lv_label_create(week_cont, NULL); //������label
        lv_obj_align(label_BAT, bar_img, LV_ALIGN_OUT_LEFT_MID, 0, 0);
        lv_obj_set_style_local_text_font(label_BAT, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16); //��������
        lv_obj_set_style_local_text_color(label_BAT, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);		  //������ɫ  
        
        charge_img = lv_img_create(week_cont,NULL);         
        lv_obj_align(charge_img,label_BAT,LV_ALIGN_OUT_LEFT_MID,0,0); 

    /************************��ص�������***************************/       
 	/***********************�����ϰ�����****************************/ 
        up_line = lv_line_create(week_cont, NULL);//������������
        lv_obj_set_pos(up_line,0,19);
        lv_line_set_points(up_line, line_points, LINE_POINTS_NUM);
        lv_obj_set_style_local_line_color(up_line, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);		  //������ɫ
        lv_obj_set_style_local_line_width(up_line, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 6);		  //�����߿�
        lv_obj_set_style_local_line_rounded(up_line, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 1);		  //����Բ�� 
 	/***********************�����ϰ�����****************************/ 
        task2 = lv_task_create(task2_cb,100,LV_TASK_PRIO_MID,NULL);     
        lv_task_ready(task2);
        /***********************����̫���˿ؼ�****************************/
        anim_cont = lv_cont_create(scr, NULL);															  //����̫��������
        lv_obj_set_pos(anim_cont, 0, 125);																  //��������λ��
        lv_obj_set_size(anim_cont, 135, 120);															  //���������ߴ�
        lv_obj_set_style_local_bg_opa(anim_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);	  //���ñ���͸��
        lv_obj_set_style_local_border_opa(anim_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);   //���ñ߿�͸��
        lv_cont_set_layout(anim_cont, LV_LAYOUT_OFF);												  //���������Ĳ��ַ�ʽ: �����Զ�����
        lv_obj_set_style_local_pad_inner(anim_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			      //�����Ӷ���֮��ļ��
  
        people_img =lv_img_create(anim_cont,NULL);                                                          // //����ͼƬ
        lv_obj_align(people_img, anim_cont, LV_ALIGN_IN_TOP_LEFT, 15, -10);

        /***********************����̫���˿ؼ�****************************/

        /************************�˶�������***************************/     
        label_Run = lv_label_create(anim_cont,NULL);
        lv_obj_set_style_local_text_font(label_Run, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &my_font_icon_30); //��������
        lv_obj_set_style_local_text_color(label_Run, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);		  //������ɫ        
        lv_obj_set_style_local_text_sel_color(label_Run, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);		  //������ɫ
        lv_label_set_static_text(label_Run, MY_ICON_RUNING);
        lv_obj_align(label_Run,anim_cont,LV_ALIGN_IN_BOTTOM_LEFT,0,-30);
        
        label_text_Run = lv_label_create(anim_cont, NULL); 
        lv_obj_align(label_text_Run, anim_cont, LV_ALIGN_IN_BOTTOM_LEFT, 0, -5);
        lv_obj_set_style_local_text_font(label_text_Run, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16); //��������
        lv_obj_set_style_local_text_color(label_text_Run, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);		  //������ɫ
       
        /************************�˶�������***************************/
        /************************�¶ȶ���***************************/ 
        label_temp = lv_label_create(anim_cont,NULL);
        lv_obj_set_style_local_text_font(label_temp, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &my_font_icon_31); //��������
        lv_obj_set_style_local_text_color(label_temp, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		  //������ɫ        
        lv_obj_set_style_local_text_sel_color(label_temp, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);		  //������ɫ
        lv_label_set_static_text(label_temp, MY_ICON_TEMP);
        lv_obj_align(label_temp,anim_cont,LV_ALIGN_IN_BOTTOM_RIGHT,0,-30);
        
        label_text_temp = lv_label_create(anim_cont, NULL); 
        lv_obj_align(label_text_temp, anim_cont, LV_ALIGN_IN_BOTTOM_RIGHT, -15, -5);
        lv_obj_set_style_local_text_font(label_text_temp, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16); //��������
        lv_obj_set_style_local_text_color(label_text_temp, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);		  //������ɫ
         /************************�¶ȶ���***************************/ 
    /***********************�����°�����****************************/ 
        down_line = lv_line_create(anim_cont, NULL);//������������
        lv_obj_set_pos(down_line,0,95);
        lv_line_set_points(down_line, line_points, LINE_POINTS_NUM);
        lv_obj_set_style_local_line_color(down_line, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);		  //������ɫ
        lv_obj_set_style_local_line_width(down_line, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 6);		  //�����߿�
        lv_obj_set_style_local_line_rounded(down_line, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 1);		  //����Բ��    
    /***********************�����°�����****************************/
        task3 = lv_task_create(task3_cb,20,LV_TASK_PRIO_HIGH,NULL);                                          // ��ͼ�ص����� 
        lv_task_ready(task3);
        task1 = lv_task_create(task1_cb,100,LV_TASK_PRIO_MID,NULL);                                          // ��ͼ�ص����� 
        lv_task_ready(task1);        
}
void get_num(int i)
{
        switch(i)
        {
            case 1: lv_img_set_src(people_img,&people1);break;
            case 2: lv_img_set_src(people_img,&people2);break;
            case 3: lv_img_set_src(people_img,&people3);break;
            case 4: lv_img_set_src(people_img,&people4);break;
            case 5: lv_img_set_src(people_img,&people5);break;
            case 6: lv_img_set_src(people_img,&people6);break;
            case 7: lv_img_set_src(people_img,&people7);break;
            case 8: lv_img_set_src(people_img,&people8);break;
            case 9: lv_img_set_src(people_img,&people9);break;
            case 10: lv_img_set_src(people_img,&people10);break;
            case 11: lv_img_set_src(people_img,&people11);break;
            case 12: lv_img_set_src(people_img,&people12);break;
            case 13: lv_img_set_src(people_img,&people13);break;
            case 14: lv_img_set_src(people_img,&people14);break;
            case 15: lv_img_set_src(people_img,&people15);break;
            case 16: lv_img_set_src(people_img,&people16);break;
            case 17: lv_img_set_src(people_img,&people17);break;
            case 18: lv_img_set_src(people_img,&people18);break;
            case 19: lv_img_set_src(people_img,&people19);break;
            case 20: lv_img_set_src(people_img,&people20);break;
            case 21: lv_img_set_src(people_img,&people21);break;
            case 22: lv_img_set_src(people_img,&people22);break;
            case 23: lv_img_set_src(people_img,&people23);break;
            case 24: lv_img_set_src(people_img,&people24);break;
            case 25: lv_img_set_src(people_img,&people25);break;
            case 26: lv_img_set_src(people_img,&people26);break;
            case 27: lv_img_set_src(people_img,&people27);break;
            case 28: lv_img_set_src(people_img,&people28);break;
            case 29: lv_img_set_src(people_img,&people29);break;
            case 30: lv_img_set_src(people_img,&people30);break;

        }
}



//��������ʼ���������˳�����(true�����룬false���˳�)
void app_digital_clock_meun_re(bool dir)
{
    
    uint16_t start;
    start = lv_obj_get_x(upscr_cont);		//��ȡ��ʼֵ
/***************************�ϰ���Ļ**********************************/    
        obj_add_anim(
                    upscr_cont, 		                        //��������
                    (lv_anim_exec_xcb_t)lv_obj_set_x,		//��������
                    lv_anim_speed_to_time(100, 0, 42),		//�����ٶ�
                    start,									//��ʼֵ
                    start + (dir ? 135 : -135),							//����ֵ
                    lv_anim_path_bounce						//������Ч:ģ�ⵯ����������
                    );    

/***************************�°���Ļ**********************************/ 
        start = lv_obj_get_x(anim_cont);		//��ȡ��ʼֵ
        obj_add_anim(
                    anim_cont, 		                        //��������
                    (lv_anim_exec_xcb_t)lv_obj_set_x,		//��������
                    lv_anim_speed_to_time(100, 0, 42),		//�����ٶ�
                    start,									//��ʼֵ
                    start + (dir ? -135 : 135),							//����ֵ
                    lv_anim_path_bounce						//������Ч:ģ�ⵯ����������
                    );  
}











