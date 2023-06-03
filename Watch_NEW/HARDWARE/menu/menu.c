#include "menu.h"

const uint8_t *roller_max;
uint8_t index;
u8 Clock_Index;
u8 nowIndex=0;
u8 LastIndex=0;
u16 bglight=360;

Key_index_struct const Key_table[15]=
{
	//��ǰ, ��, ��, ȷ��, ����
    {0, 1, 0, 0, 0,(*mainWindow)},//һ������ ����
	{1, 2, 0, 8, 1, (*menu1)},//���������һ��  ʱ��
	{2, 3, 7, 9, 2,(*menu2)},//��������ڶ���  �ƹ�
	{3, 4, 6, 10, 3,(*menu3)},//�������������  ����
	{4, 4, 5, 11, 4,(*menu4)},//�������������  ��Ϸ
	{5, 4, 6, 12, 5,(*menu5)},//�������������  ����
	{6, 3, 7, 13, 6,(*menu6)},//�������������   �ƹ�
	{7, 2, 0, 14, 7,(*menu7)},//�������������   ʱ��
	{8, 8, 8, 8, 1,(*menu2_1)},//�������������       ʱ������
	{9, 9, 9, 9, 2,(*menu2_2)},//�������������       �ƹ�����
	{10, 10, 10, 10, 3,(*menu2_3)},//�������������  ������Ϣ
	{11, 11, 11, 11, 4,(*menu2_4)},//�������������  ��Ϸ����
	{12, 12, 12, 12, 5,(*menu2_5)},//�������������  ��������1
	{13, 13, 13, 13, 6,(*menu2_6)},//�������������  �ƹ�����1
	{14, 14, 14, 14, 7,(*menu2_7)},//�������������  ʱ����Ϣ1  
    
};
 
/***************************oled����ѡ����*****************************************/

void OLED_display(u8 press)
    {
      if(press!=0)
      {
        LastIndex = nowIndex;
        if(press==KEY0_PRES)       //PB0 ��
        {           
            nowIndex=Key_table[nowIndex].down_index;
            Key_table[nowIndex].operate(press);  
            LED0=1;
            IWDG_Feed();
        }
        else if(press==KEY1_PRES)  //PB1 ��
        {
            nowIndex=Key_table[nowIndex].up_index;
            Key_table[nowIndex].operate(press);
            LED0=1;
            IWDG_Feed();
        }        
        else if(press==KEY2_PRES)  //PB2 ȷ��
        {
            nowIndex=Key_table[nowIndex].enter_index;
            Key_table[nowIndex].operate(press);
            LED0=1;
            IWDG_Feed();
        }        
        else if(press==KEY3_PRES)  //PB3 �˳�
        {
            nowIndex=Key_table[nowIndex].esc_index;
            Key_table[nowIndex].operate(press);
            LED0=1;
            IWDG_Feed();
        }  
    }
      else LED0=0;
}
 
/**********************************���˵�*****************************************/
 
void mainWindow(u8 press)
{   
    if(LastIndex!=0)
    {
        app_digital_clock_meun_re(false); //���ָ̻�
        app_menu_anim_Vexit_clock_img(false); //ʱ���˳�
        app_tip_anim_Vexit(false); //��ʾ�˳�
    }
}


void menu1(u8 press)//�˵�1�б�
{    
    if(LastIndex!=1&&LastIndex!=8)
    {
        app_digital_clock_meun_re(true);    //����ɢ��
        app_menu_anim_Vexit_clock_img(true); //ʱ�ӽ���
        app_tip_anim_Vexit(true);           //��ʾ����
    }
    if(LastIndex!=1&&LastIndex==8) 
    {
        app_menu_anim_Hexit_clock_img(false);
        app_set_clock_anim_Hexit_img(false);
        set_enter(0);
    }
}
void menu2(u8 press)//�˵�2�б�
{
    if(LastIndex!=2&&LastIndex!=9)
    {
        app_menu_anim_Vexit_clock_img(false);  //ʱ���˳�
        app_menu_anim_Vexit_lighting_img(true); //�ƹ����
    }
    if(LastIndex!=2&&LastIndex==9) 
    {
        app_menu_anim_Hexit_lighting_img(false);
        app_set_lighting_anim_Hexit_img(false);
    }    
    
}
void menu3(u8 press)//�˵�3�б�
{
    if(LastIndex!=3&&LastIndex!=10)
    {
        app_menu_anim_Vexit_lighting_img(false); //�ƹ��˳�
        app_menu_anim_Vexit_about_img(true);     //���ڽ���
    }
    if(LastIndex!=3&&LastIndex==10) 
    {
        app_menu_anim_Hexit_about_img(false);
        app_set_about_anim_Hexit_img(false);
    }    
}
void menu4(u8 press)//�˵�4�б�
{
    if(LastIndex!=4&&LastIndex!=11)
    {
        app_menu_anim_Vexit_about_img(false); //�����˳�
        app_menu_anim_Vexit_game_img(true);  //��Ϸ����
    }
    if(LastIndex!=4&&LastIndex==11) 
    {
        app_menu_anim_Hexit_game_img(false);
        app_set_game_anim_Hexit_img(false);
    }    
}

void menu5(u8 press)//�˵�5�б�
{
    if(LastIndex!=5&&LastIndex!=12)
    {
        app_menu_anim_Vexit_game_img(false); //��Ϸ�˳�
        app_menu_anim_Vexit_about_img(true); // ���ڽ���
    }
    if(LastIndex!=5&&LastIndex==12) 
    {
        app_menu_anim_Hexit_about_img(false);
        app_set_about_anim_Hexit_img(false);
    }     
    
}

void menu6(u8 press)//�˵�6�б�
{
    if(LastIndex!=6&&LastIndex!=13)
    {
        app_menu_anim_Vexit_about_img(false); //�����˳�
        app_menu_anim_Vexit_lighting_img(true); //�ƹ����
    }
    if(LastIndex!=6&&LastIndex==13) 
    {
        app_menu_anim_Hexit_lighting_img(false);
        app_set_lighting_anim_Hexit_img(false);
    }          
}

void menu7(u8 press)//�˵�6�б�
{
    if(LastIndex!=7&&LastIndex!=14)
    {
        app_menu_anim_Vexit_lighting_img(false); //�ƹ��˳�
        app_menu_anim_Vexit_clock_img(true); //ʱ�ӽ���
    }  
    if(LastIndex!=7&&LastIndex==14) 
    {
        app_menu_anim_Hexit_clock_img(false);
        app_set_clock_anim_Hexit_img(false);
        set_enter(0);
    }     
}

void menu2_1(u8 press)//ʱ���б�
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
                         app_setting_change(index);		                                //���õ�ǰѡ��roller����(�ݼ�)
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

void menu2_2(u8 press)//�ƹ��б�
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

void menu2_3(u8 press)//�����б�
{
    if(LastIndex!=10)
    {
        app_menu_anim_Hexit_about_img(true);
        app_set_about_anim_Hexit_img(true);
    }  
}

void menu2_4(u8 press)//��Ϸ�б�
{
    if(LastIndex!=11)
    {
        app_menu_anim_Hexit_game_img(true);
        app_set_game_anim_Hexit_img(true);
    }  
}

void menu2_5(u8 press)//�����б�
{
    if(LastIndex!=12)
    {
        app_menu_anim_Hexit_about_img(true);
        app_set_about_anim_Hexit_img(true);
    }  
}

void menu2_6(u8 press)//�ƹ��б�
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

void menu2_7(u8 press)//ʱ���б�
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
                         app_setting_change(index);		                                //���õ�ǰѡ��roller����(�ݼ�)
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

