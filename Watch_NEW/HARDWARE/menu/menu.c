#include "menu.h"

const uint8_t *roller_max;
uint8_t index;
u8 Clock_Index;
u8 nowIndex=0;
u8 LastIndex=0;
u16 bglight=360;

Key_index_struct const Key_table[15]=
{
	//当前, 下, 上, 确定, 返回
    {0, 1, 0, 0, 0,(*mainWindow)},//一级界面 表盘
	{1, 2, 0, 8, 1, (*menu1)},//二级界面第一行  时钟
	{2, 3, 7, 9, 2,(*menu2)},//二级界面第二行  灯光
	{3, 4, 6, 10, 3,(*menu3)},//二级界面第三行  关于
	{4, 4, 5, 11, 4,(*menu4)},//二级界面第四行  游戏
	{5, 4, 6, 12, 5,(*menu5)},//二级界面第五行  关于
	{6, 3, 7, 13, 6,(*menu6)},//二级界面第六行   灯光
	{7, 2, 0, 14, 7,(*menu7)},//二级界面第七行   时钟
	{8, 8, 8, 8, 1,(*menu2_1)},//二级界面第四行       时钟设置
	{9, 9, 9, 9, 2,(*menu2_2)},//二级界面第五行       灯光设置
	{10, 10, 10, 10, 3,(*menu2_3)},//二级界面第六行  关于信息
	{11, 11, 11, 11, 4,(*menu2_4)},//二级界面第七行  游戏界面
	{12, 12, 12, 12, 5,(*menu2_5)},//二级界面第四行  关于设置1
	{13, 13, 13, 13, 6,(*menu2_6)},//二级界面第五行  灯光设置1
	{14, 14, 14, 14, 7,(*menu2_7)},//二级界面第六行  时钟信息1  
    
};
 
/***************************oled按键选择画面*****************************************/

void OLED_display(u8 press)
    {
      if(press!=0)
      {
        LastIndex = nowIndex;
        if(press==KEY0_PRES)       //PB0 下
        {           
            nowIndex=Key_table[nowIndex].down_index;
            Key_table[nowIndex].operate(press);  
            LED0=1;
            IWDG_Feed();
        }
        else if(press==KEY1_PRES)  //PB1 上
        {
            nowIndex=Key_table[nowIndex].up_index;
            Key_table[nowIndex].operate(press);
            LED0=1;
            IWDG_Feed();
        }        
        else if(press==KEY2_PRES)  //PB2 确定
        {
            nowIndex=Key_table[nowIndex].enter_index;
            Key_table[nowIndex].operate(press);
            LED0=1;
            IWDG_Feed();
        }        
        else if(press==KEY3_PRES)  //PB3 退出
        {
            nowIndex=Key_table[nowIndex].esc_index;
            Key_table[nowIndex].operate(press);
            LED0=1;
            IWDG_Feed();
        }  
    }
      else LED0=0;
}
 
/**********************************主菜单*****************************************/
 
void mainWindow(u8 press)
{   
    if(LastIndex!=0)
    {
        app_digital_clock_meun_re(false); //表盘恢复
        app_menu_anim_Vexit_clock_img(false); //时钟退出
        app_tip_anim_Vexit(false); //提示退出
    }
}


void menu1(u8 press)//菜单1列表
{    
    if(LastIndex!=1&&LastIndex!=8)
    {
        app_digital_clock_meun_re(true);    //表盘散开
        app_menu_anim_Vexit_clock_img(true); //时钟进入
        app_tip_anim_Vexit(true);           //提示进入
    }
    if(LastIndex!=1&&LastIndex==8) 
    {
        app_menu_anim_Hexit_clock_img(false);
        app_set_clock_anim_Hexit_img(false);
        set_enter(0);
    }
}
void menu2(u8 press)//菜单2列表
{
    if(LastIndex!=2&&LastIndex!=9)
    {
        app_menu_anim_Vexit_clock_img(false);  //时钟退出
        app_menu_anim_Vexit_lighting_img(true); //灯光进入
    }
    if(LastIndex!=2&&LastIndex==9) 
    {
        app_menu_anim_Hexit_lighting_img(false);
        app_set_lighting_anim_Hexit_img(false);
    }    
    
}
void menu3(u8 press)//菜单3列表
{
    if(LastIndex!=3&&LastIndex!=10)
    {
        app_menu_anim_Vexit_lighting_img(false); //灯光退出
        app_menu_anim_Vexit_about_img(true);     //关于进入
    }
    if(LastIndex!=3&&LastIndex==10) 
    {
        app_menu_anim_Hexit_about_img(false);
        app_set_about_anim_Hexit_img(false);
    }    
}
void menu4(u8 press)//菜单4列表
{
    if(LastIndex!=4&&LastIndex!=11)
    {
        app_menu_anim_Vexit_about_img(false); //关于退出
        app_menu_anim_Vexit_game_img(true);  //游戏进入
    }
    if(LastIndex!=4&&LastIndex==11) 
    {
        app_menu_anim_Hexit_game_img(false);
        app_set_game_anim_Hexit_img(false);
    }    
}

void menu5(u8 press)//菜单5列表
{
    if(LastIndex!=5&&LastIndex!=12)
    {
        app_menu_anim_Vexit_game_img(false); //游戏退出
        app_menu_anim_Vexit_about_img(true); // 关于进入
    }
    if(LastIndex!=5&&LastIndex==12) 
    {
        app_menu_anim_Hexit_about_img(false);
        app_set_about_anim_Hexit_img(false);
    }     
    
}

void menu6(u8 press)//菜单6列表
{
    if(LastIndex!=6&&LastIndex!=13)
    {
        app_menu_anim_Vexit_about_img(false); //关于退出
        app_menu_anim_Vexit_lighting_img(true); //灯光进入
    }
    if(LastIndex!=6&&LastIndex==13) 
    {
        app_menu_anim_Hexit_lighting_img(false);
        app_set_lighting_anim_Hexit_img(false);
    }          
}

void menu7(u8 press)//菜单6列表
{
    if(LastIndex!=7&&LastIndex!=14)
    {
        app_menu_anim_Vexit_lighting_img(false); //灯光退出
        app_menu_anim_Vexit_clock_img(true); //时钟进入
    }  
    if(LastIndex!=7&&LastIndex==14) 
    {
        app_menu_anim_Hexit_clock_img(false);
        app_set_clock_anim_Hexit_img(false);
        set_enter(0);
    }     
}

void menu2_1(u8 press)//时钟列表
{
    if(LastIndex!=8)
    {
        app_menu_anim_Hexit_clock_img(true);
        app_set_clock_anim_Hexit_img(true);  
        roller_max = app_setting_get_roller_max();        
    } 
        if(press==KEY1_PRES) 
        {
            Clock_Index++;
            Clock_Index%=8;
            app_setting_change_roller(Clock_Index);
        }
        if(press==KEY0_PRES)
        {
            
            switch(Clock_Index)
            {
                case 0 : index ++;	index%=24;		
                         app_setting_change(index);		                                //设置当前选中roller的项(递减)
                    break;
                case 1 : index ++;	index%=60;		
                         app_setting_change(index);
                    break;
                case 2 : index ++;	index%=60;		
                         app_setting_change(index);
                    break;
                case 3 : index ++;	index%=30;		
                         app_setting_change(index);
                    break;
                case 4 : index ++;	index%=12;		
                         app_setting_change(index);
                    break;
                case 5 :index ++;	index%=31;		
                         app_setting_change(index);
                    break;
                case 6 :index ++;	index%=7;		
                         app_setting_change(index);
                    break;
                case 7 :    app_setting_update_time();set_enter(1);
                    break;
            }
        }    
}

void menu2_2(u8 press)//灯光列表
{
    if(LastIndex!=9)
    {
        app_menu_anim_Hexit_lighting_img(true);
        app_set_lighting_anim_Hexit_img(true);
    } 
        if(press==KEY1_PRES) 
        {
            bglight+=10;
            if(bglight==370) bglight=360;
        }
        if(press==KEY0_PRES) 
        {
            bglight-=10;
            if(bglight==65526)  bglight=0;
        } 
            set_bglighting(bglight);           
}

void menu2_3(u8 press)//关于列表
{
    if(LastIndex!=10)
    {
        app_menu_anim_Hexit_about_img(true);
        app_set_about_anim_Hexit_img(true);
    }  
}

void menu2_4(u8 press)//游戏列表
{
    if(LastIndex!=11)
    {
        app_menu_anim_Hexit_game_img(true);
        app_set_game_anim_Hexit_img(true);
    }  
}

void menu2_5(u8 press)//关于列表
{
    if(LastIndex!=12)
    {
        app_menu_anim_Hexit_about_img(true);
        app_set_about_anim_Hexit_img(true);
    }  
}

void menu2_6(u8 press)//灯光列表
{
    if(LastIndex!=13)
    {
        app_menu_anim_Hexit_lighting_img(true);
        app_set_lighting_anim_Hexit_img(true);  
    } 
        if(press==KEY1_PRES) 
        {
            bglight+=10;
            if(bglight==370) bglight=360;
        }
        if(press==KEY0_PRES) 
        {
            bglight-=10;
            if(bglight==65526)  bglight=0;
        }
            set_bglighting(bglight);         
}

void menu2_7(u8 press)//时钟列表
{
    if(LastIndex!=14)
    {
        app_menu_anim_Hexit_clock_img(true);
        app_set_clock_anim_Hexit_img(true);
        roller_max = app_setting_get_roller_max();
    }
        if(press==KEY1_PRES) 
        {
            Clock_Index++;
            Clock_Index%=8;
            app_setting_change_roller(Clock_Index);
        }
        if(press==KEY0_PRES)
        {
            
            switch(Clock_Index)
            {
                case 0 : index ++;	index%=24;		
                         app_setting_change(index);		                                //设置当前选中roller的项(递减)
                    break;
                case 1 : index ++;	index%=60;		
                         app_setting_change(index);
                    break;
                case 2 : index ++;	index%=60;		
                         app_setting_change(index);
                    break;
                case 3 : index ++;	index%=30;		
                         app_setting_change(index);
                    break;
                case 4 : index ++;	index%=12;		
                         app_setting_change(index);
                    break;
                case 5 :index ++;	index%=31;		
                         app_setting_change(index);
                    break;
                case 6 :index ++;	index%=7;		
                         app_setting_change(index);
                    break;
                case 7 :    app_setting_update_time(); set_enter(1);
                    break;
            }
            
        }
    
}

