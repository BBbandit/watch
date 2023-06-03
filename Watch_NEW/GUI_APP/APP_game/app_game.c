#include "app_game.h"

static lv_obj_t *set_game_cont; //ҳ������


//����ʱ�ӽ������
void app_game_create(void)
{
	lv_obj_t *scr;

	scr = lv_scr_act(); //��ȡ��ǰ��Ծ����Ļ
    /***********************����ʱ�����ÿؼ�****************************/
    set_game_cont = lv_cont_create(scr, NULL);															  //������ʾ����
    lv_obj_set_pos(set_game_cont, 135, 37);																  //��������λ��
    lv_obj_set_size(set_game_cont, 135, 205);															  //���������ߴ�
    lv_obj_set_style_local_bg_opa(set_game_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	  //���ñ���͸��
    lv_obj_set_style_local_border_opa(set_game_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER); //���ñ߿�͸��
    lv_cont_set_layout(set_game_cont, LV_LAYOUT_OFF);												  //���������Ĳ��ַ�ʽ: �����Զ�����
    lv_obj_set_style_local_pad_inner(set_game_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			  //�����Ӷ���֮��ļ��
    /***********************����ʱ�����ÿؼ�****************************/
}

//ʱ������ͼ��ˮƽ�����ƶ�������˳�����
void app_set_game_anim_Hexit_img( bool dir)
{
	uint16_t start;
	
	start = lv_obj_get_x(set_game_cont);		//��ȡ��ʼֵ
	
	obj_add_anim(
								set_game_cont, 		//��������
								(lv_anim_exec_xcb_t)lv_obj_set_x,				//��������
								lv_anim_speed_to_time(100, 0, 42),			//�����ٶ�
								start,																	//��ʼֵ
								start + (dir ? -135 : 135),							//����ֵ
								lv_anim_path_bounce											//������Ч:ģ�ⵯ����������
								);
}

