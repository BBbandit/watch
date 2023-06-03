#include "app_game.h"

static lv_obj_t *set_game_cont; //页面容器


//创建时钟界面界面
void app_game_create(void)
{
	lv_obj_t *scr;

	scr = lv_scr_act(); //获取当前活跃的屏幕
    /***********************创建时钟设置控件****************************/
    set_game_cont = lv_cont_create(scr, NULL);															  //创建提示容器
    lv_obj_set_pos(set_game_cont, 135, 37);																  //设置容器位置
    lv_obj_set_size(set_game_cont, 135, 205);															  //设置容器尺寸
    lv_obj_set_style_local_bg_opa(set_game_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);	  //设置背景透明
    lv_obj_set_style_local_border_opa(set_game_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER); //设置边框透明
    lv_cont_set_layout(set_game_cont, LV_LAYOUT_OFF);												  //设置容器的布局方式: 开启自动布局
    lv_obj_set_style_local_pad_inner(set_game_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);			  //设置子对象之间的间距
    /***********************创建时钟设置控件****************************/
}

//时钟设置图标水平方向移动进入或退出中心
void app_set_game_anim_Hexit_img( bool dir)
{
	uint16_t start;
	
	start = lv_obj_get_x(set_game_cont);		//获取起始值
	
	obj_add_anim(
								set_game_cont, 		//动画对象
								(lv_anim_exec_xcb_t)lv_obj_set_x,				//动画函数
								lv_anim_speed_to_time(100, 0, 42),			//动画速度
								start,																	//起始值
								start + (dir ? -135 : 135),							//结束值
								lv_anim_path_bounce											//动画特效:模拟弹性物体下落
								);
}

