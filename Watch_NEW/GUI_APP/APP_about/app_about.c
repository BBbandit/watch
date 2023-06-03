#include "app_about.h"


static lv_obj_t *set_about_cont; //页面容器


//创建时钟界面界面
void app_about_create(void)
{
	lv_obj_t *scr;

	scr = lv_scr_act(); //获取当前活跃的屏幕
    /***********************创建时钟设置控件****************************/
    set_about_cont = lv_cont_create(scr, NULL);															  //创建提示容器
    lv_obj_set_pos(set_about_cont, 135, 37);																  //设置容器位置
    lv_obj_set_size(set_about_cont, 135, 205);															  //设置容器尺寸
    lv_obj_set_style_local_bg_opa(set_about_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	  //设置背景透明
    lv_obj_set_style_local_border_opa(set_about_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP); //设置边框透明
    lv_cont_set_layout(set_about_cont, LV_LAYOUT_OFF);												  //设置容器的布局方式: 开启自动布局
    lv_obj_set_style_local_pad_inner(set_about_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			  //设置子对象之间的间距
    /***********************创建时钟设置控件****************************/
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




//时钟设置图标水平方向移动进入或退出中心
void app_set_about_anim_Hexit_img( bool dir)
{
	uint16_t start;
	
	start = lv_obj_get_x(set_about_cont);		//获取起始值
	
	obj_add_anim(
								set_about_cont, 		//动画对象
								(lv_anim_exec_xcb_t)lv_obj_set_x,				//动画函数
								lv_anim_speed_to_time(100, 0, 42),			//动画速度
								start,																	//起始值
								start + (dir ? -135 : 135),							//结束值
								lv_anim_path_bounce											//动画特效:模拟弹性物体下落
								);
}






