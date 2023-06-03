#include "app_meun.h"


//��ʾͼƬ����
LV_IMG_DECLARE(lighting);
LV_IMG_DECLARE(game);
LV_IMG_DECLARE(about);
LV_IMG_DECLARE(clock);

static lv_obj_t *clock_img;	//����������ͼƬimg
static lv_obj_t *game_img;	//����������ͼƬimg
static lv_obj_t *about_img;	//����������ͼƬimg
static lv_obj_t *lighting_img;	//����������ͼƬimg


lv_obj_t *tip_cont; //��ʾ����
lv_obj_t *label_tip;//��ʾ��ǩ
lv_obj_t* tip_line;  //��ʾ����

const lv_point_t tip_line_points[] = { {20, 0}, {115, 00} };
#define TIP_LINE_POINTS_NUM (sizeof(tip_line_points)/sizeof(tip_line_points[0]))


//�����˵�����
void app_menu_create(void)
{
    lv_obj_t *scr = lv_scr_act(); //��ȡ��ǰ��Ծ����Ļ

    clock_img = lv_img_create(scr, NULL);						  //����img��ʾ�˵�
    lv_img_set_src(clock_img, &clock);			  //������ʾͼƬ
    lv_obj_align(clock_img, scr, LV_ALIGN_OUT_BOTTOM_MID, 0, 0); //����ͼƬ�������
    
    game_img = lv_img_create(scr, NULL);						  //����img��ʾ�˵�
    lv_img_set_src(game_img, &game);			  //������ʾͼƬ
    lv_obj_align(game_img, scr, LV_ALIGN_OUT_BOTTOM_MID, 0, 0); //����ͼƬ�������    
    
    about_img = lv_img_create(scr, NULL);						  //����img��ʾ�˵�
    lv_img_set_src(about_img, &about);			  //������ʾͼƬ
    lv_obj_align(about_img, scr, LV_ALIGN_OUT_BOTTOM_MID, 0, 0); //����ͼƬ�������

    lighting_img = lv_img_create(scr, NULL);						  //����img��ʾ�˵�
    lv_img_set_src(lighting_img, &lighting);			  //������ʾͼƬ
    lv_obj_align(lighting_img, scr, LV_ALIGN_OUT_BOTTOM_MID, 0, 0); //����ͼƬ�������    
}






//ʱ��ͼ�괹ֱ�����ƶ�������˳�����
void app_menu_anim_Vexit_clock_img( bool dir)
{
	uint16_t start;
	start = lv_obj_get_y(clock_img);		//��ȡ��ʼֵ
	obj_add_anim(
								clock_img, 		//��������
								(lv_anim_exec_xcb_t)lv_obj_set_y,				//��������
								lv_anim_speed_to_time(100, 0, 42),			//�����ٶ�
								start,																	//��ʼֵ
								start + (dir ? -160 : 160),							//����ֵ
								lv_anim_path_bounce											//������Ч:ģ�ⵯ����������
								);
    if(dir)        lv_label_set_static_text(label_tip,"Clock");
    
}
//�ƹ�ͼ�괹ֱ�����ƶ�������˳�����
void app_menu_anim_Vexit_lighting_img( bool dir)
{
	uint16_t start;
	start = lv_obj_get_y(lighting_img);		//��ȡ��ʼֵ
	obj_add_anim(
								lighting_img, 		//��������
								(lv_anim_exec_xcb_t)lv_obj_set_y,				//��������
								lv_anim_speed_to_time(100, 0, 42),			//�����ٶ�
								start,																	//��ʼֵ
								start + (dir ? -160 : 160),							//����ֵ
								lv_anim_path_bounce											//������Ч:ģ�ⵯ����������
								);
        if(dir)        lv_label_set_static_text(label_tip,"Lighting");
}

//����ͼ�괹ֱ�����ƶ�������˳�����
void app_menu_anim_Vexit_about_img( bool dir)
{
	uint16_t start;
	start = lv_obj_get_y(about_img);		//��ȡ��ʼֵ
	obj_add_anim(
								about_img, 		//��������
								(lv_anim_exec_xcb_t)lv_obj_set_y,				//��������
								lv_anim_speed_to_time(100, 0, 42),			//�����ٶ�
								start,																	//��ʼֵ
								start + (dir ? -160 : 160),							//����ֵ
								lv_anim_path_bounce											//������Ч:ģ�ⵯ����������
								);
        if(dir)        lv_label_set_static_text(label_tip,"About");
}

//��Ϸͼ�괹ֱ�����ƶ�������˳�����
void app_menu_anim_Vexit_game_img( bool dir)
{
	uint16_t start;
	start = lv_obj_get_y(game_img);		//��ȡ��ʼֵ
	obj_add_anim(
								game_img, 		//��������
								(lv_anim_exec_xcb_t)lv_obj_set_y,				//��������
								lv_anim_speed_to_time(100, 0, 42),			//�����ٶ�
								start,																	//��ʼֵ
								start + (dir ? -160 : 160),							//����ֵ
								lv_anim_path_bounce											//������Ч:ģ�ⵯ����������
								);
        if(dir)        lv_label_set_static_text(label_tip,"Game");
}

/****************************************************************************************************************/
//ʱ��ͼ��ˮƽ�����ƶ�������˳�����
void app_menu_anim_Hexit_clock_img( bool dir)
{
	uint16_t start;
	
	start = lv_obj_get_x(clock_img);		//��ȡ��ʼֵ
	
	obj_add_anim(
								clock_img, 		//��������
								(lv_anim_exec_xcb_t)lv_obj_set_x,				//��������
								lv_anim_speed_to_time(100, 0, 42),			//�����ٶ�
								start,																	//��ʼֵ
								start + (dir ? -130 : 130),							//����ֵ
								lv_anim_path_bounce											//������Ч:ģ�ⵯ����������
								);
}

//�ƹ�ͼ��ˮƽ�����ƶ�������˳�����
void app_menu_anim_Hexit_lighting_img( bool dir)
{
	uint16_t start;
	
	start = lv_obj_get_x(lighting_img);		//��ȡ��ʼֵ
	
	obj_add_anim(
								lighting_img, 		//��������
								(lv_anim_exec_xcb_t)lv_obj_set_x,				//��������
								lv_anim_speed_to_time(100, 0, 42),			//�����ٶ�
								start,																	//��ʼֵ
								start + (dir ? -130 : 130),							//����ֵ
								lv_anim_path_bounce											//������Ч:ģ�ⵯ����������
								);
}


//����ͼ��ˮƽ�����ƶ�������˳�����
void app_menu_anim_Hexit_about_img( bool dir)
{
	uint16_t start;
	
	start = lv_obj_get_x(about_img);		//��ȡ��ʼֵ
	
	obj_add_anim(
								about_img, 		//��������
								(lv_anim_exec_xcb_t)lv_obj_set_x,				//��������
								lv_anim_speed_to_time(100, 0, 42),			//�����ٶ�
								start,																	//��ʼֵ
								start + (dir ? -130 : 130),							//����ֵ
								lv_anim_path_bounce											//������Ч:ģ�ⵯ����������
								);
}


//��Ϸͼ��ˮƽ�����ƶ�������˳�����
void app_menu_anim_Hexit_game_img( bool dir)
{
	uint16_t start;
	
	start = lv_obj_get_x(game_img);		//��ȡ��ʼֵ
	
	obj_add_anim(
								game_img, 		//��������
								(lv_anim_exec_xcb_t)lv_obj_set_x,				//��������
								lv_anim_speed_to_time(100, 0, 42),			//�����ٶ�
								start,																	//��ʼֵ
								start + (dir ? -130 : 130),							//����ֵ
								lv_anim_path_bounce											//������Ч:ģ�ⵯ����������
								);
}





/******************************************************************************************************/
//�����˵���ʾ����
void app_menu_tip_create(void)
{
    lv_obj_t *scr = lv_scr_act(); //��ȡ��ǰ��Ծ����Ļ	
    
    /***********************������ʾ�ؼ�****************************/
    tip_cont = lv_cont_create(scr, NULL);															  //������ʾ����
    lv_obj_set_pos(tip_cont, 0, -60);																  //��������λ��
    lv_obj_set_size(tip_cont, 135, 60);															  //���������ߴ�
    lv_obj_set_style_local_bg_opa(tip_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	  //���ñ���͸��
    lv_obj_set_style_local_border_opa(tip_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP); //���ñ߿�͸��
    lv_cont_set_layout(tip_cont, LV_LAYOUT_OFF);												  //���������Ĳ��ַ�ʽ: �����Զ�����
    lv_obj_set_style_local_pad_inner(tip_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			  //�����Ӷ���֮��ļ��
    /***********************������ʾ�ؼ�****************************/

 	/***********************������ʾ����****************************/ 
    tip_line = lv_line_create(tip_cont, NULL);//������������
    lv_obj_set_pos(tip_line,0,35);
    lv_line_set_points(tip_line, tip_line_points, TIP_LINE_POINTS_NUM);
    lv_obj_set_style_local_line_color(tip_line, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		  //������ɫ
    lv_obj_set_style_local_line_width(tip_line, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 4);		  //�����߿�
    lv_obj_set_style_local_line_rounded(tip_line, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 1);		  //����Բ�� 
 	/***********************������ʾ����****************************/     
    
    
    label_tip = lv_label_create(tip_cont, NULL); 
    lv_obj_align(label_tip, tip_line, LV_ALIGN_OUT_TOP_MID, 0, -5);
    lv_obj_set_style_local_text_font(label_tip, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserrat_16); //��������
    lv_obj_set_style_local_text_color(label_tip, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);		  //������ɫ

}


void app_tip_anim_Vexit( bool dir)
{
	uint16_t start;
	start = lv_obj_get_y(tip_cont);		//��ȡ��ʼֵ
	obj_add_anim(
								tip_cont, 		//��������
								(lv_anim_exec_xcb_t)lv_obj_set_y,				//��������
								lv_anim_speed_to_time(100, 0, 42),			//�����ٶ�
								start,																	//��ʼֵ
								start + (dir ? 60 : -60),							//����ֵ
								lv_anim_path_bounce											//������Ч:ģ�ⵯ����������
								);
}



