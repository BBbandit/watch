#include "app_about.h"


static lv_obj_t *set_about_cont; //ҳ������


//����ʱ�ӽ������
void app_about_create(void)
{
	lv_obj_t *scr;

	scr = lv_scr_act(); //��ȡ��ǰ��Ծ����Ļ
    /***********************����ʱ�����ÿؼ�****************************/
    set_about_cont = lv_cont_create(scr, NULL);															  //������ʾ����
    lv_obj_set_pos(set_about_cont, 135, 37);																  //��������λ��
    lv_obj_set_size(set_about_cont, 135, 205);															  //���������ߴ�
    lv_obj_set_style_local_bg_opa(set_about_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	  //���ñ���͸��
    lv_obj_set_style_local_border_opa(set_about_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP); //���ñ߿�͸��
    lv_cont_set_layout(set_about_cont, LV_LAYOUT_OFF);												  //���������Ĳ��ַ�ʽ: �����Զ�����
    lv_obj_set_style_local_pad_inner(set_about_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			  //�����Ӷ���֮��ļ��
    /***********************����ʱ�����ÿؼ�****************************/
    static lv_style_t label_shadow_style;
    lv_style_init(&label_shadow_style);
    lv_style_set_text_opa(&label_shadow_style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_text_color(&label_shadow_style, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_obj_t * shadow_label = lv_label_create(set_about_cont, NULL);
    lv_obj_add_style(shadow_label, LV_LABEL_PART_MAIN, &label_shadow_style);
    lv_obj_t * main_label = lv_label_create(set_about_cont, NULL);
    lv_label_set_text(main_label,                                     "Design By Bandit\n\n"
                                                                      "2021.7.16\n"
                                                                      "Generation One\n"
                                                                      "Bandit Watch.");
                                                                                                                                 
    lv_label_set_text(shadow_label, lv_label_get_text(main_label));
    lv_obj_align(main_label, set_about_cont, LV_ALIGN_IN_LEFT_MID, 0, 10);
    lv_obj_align(shadow_label, main_label, LV_ALIGN_IN_TOP_LEFT, 1, 2);

}




//ʱ������ͼ��ˮƽ�����ƶ�������˳�����
void app_set_about_anim_Hexit_img( bool dir)
{
	uint16_t start;
	
	start = lv_obj_get_x(set_about_cont);		//��ȡ��ʼֵ
	
	obj_add_anim(
								set_about_cont, 		//��������
								(lv_anim_exec_xcb_t)lv_obj_set_x,				//��������
								lv_anim_speed_to_time(100, 0, 42),			//�����ٶ�
								start,																	//��ʼֵ
								start + (dir ? -135 : 135),							//����ֵ
								lv_anim_path_bounce											//������Ч:ģ�ⵯ����������
								);
}






