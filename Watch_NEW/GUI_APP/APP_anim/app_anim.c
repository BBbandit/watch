#include "app_anim.h"


void obj_add_anim(lv_obj_t *obj, lv_anim_exec_xcb_t exec_cb, uint16_t time, lv_coord_t start, lv_coord_t end, lv_anim_path_cb_t path_cb)
{
	lv_anim_t a;

	lv_anim_init(&a);
	lv_anim_set_var(&a, obj); //��������

	lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)exec_cb); //��������
	lv_anim_set_time(&a, time);

	a.start = start;		  //��ʼֵ
	a.end = end; //����ֵ
	a.path.cb = path_cb;	  //�������㷽��
	a.playback_time = 0;				  //�ط�ʱ����Ϊ0��ִ�ж����ط�

	lv_anim_start(&a); //��������
}

//ͼƬ���䶯������

;void img_anim_exec_xcb(void *obj, lv_anim_value_t value)
{
	lv_obj_set_style_local_image_opa(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, value); //ͼƬ͸��������
}

