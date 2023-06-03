#include "main.h"

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	delay_init(168);  	//ʱ�ӳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������
    My_RTC_Init();
    LED_Init();
    TIM1_PWM_Init(360-1,84-1); 
    Adc_Init();    
    LCD_Init();	   //Һ������ʼ��
	uart_init(115200);  //���ڳ�ʼ��
    KEY_Init();
    
    BMP_Init();
	BMP_ReadCalibrationData(); 
    IIC_Init();                     //=====IIC��ʼ��    ��ȡMPU6050����
	MPU6050_initialize();           //=====MPU6050��ʼ��
    DMP_Init();                     //=====��ʼ��DMP     
    IWDG_Init(6,4095);               //32��Ŀ��Ź� û��ι���͹ػ� ���е͹���
    
    TIM3_Int_Init(999,71);
    lv_init(); 
    lv_port_disp_init();  

    
    
	OSInit(&err);		//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	OSStart(&err);  //����UCOSIII
	while(1);
}

//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,10,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	//�����ٽ���
	//����LVGL����
	OSTaskCreate((OS_TCB 	* )&LVGLTaskTCB,		
				 (CPU_CHAR	* )"LVGL task", 		
                 (OS_TASK_PTR )LVGL_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )LVGL_TASK_PRIO,     
                 (CPU_STK   * )&LVGL_TASK_STK[0],	
                 (CPU_STK_SIZE)LVGL_STK_SIZE/10,	
                 (CPU_STK_SIZE)LVGL_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);				

				 
	//����BMP��������
	OSTaskCreate((OS_TCB 	* )&BMPTaskTCB,		
				 (CPU_CHAR	* )"BMP task", 		
                 (OS_TASK_PTR )BMP_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )BMP_TASK_PRIO,     	
                 (CPU_STK   * )&BMP_TASK_STK[0],	
                 (CPU_STK_SIZE)BMP_STK_SIZE/10,	
                 (CPU_STK_SIZE)BMP_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);

	//����MPU6050��������
	OSTaskCreate((OS_TCB 	* )&MPU6050TaskTCB,		
				 (CPU_CHAR	* )"MPU6050 task", 		
                 (OS_TASK_PTR )MPU6050_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )MPU6050_TASK_PRIO,     	
                 (CPU_STK   * )&MPU6050_TASK_STK[0],	
                 (CPU_STK_SIZE)MPU6050_STK_SIZE/10,	
                 (CPU_STK_SIZE)MPU6050_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);

	//����BUTTON��������
	OSTaskCreate((OS_TCB 	* )&BUTTONTaskTCB,		
				 (CPU_CHAR	* )"BUTTON task", 		
                 (OS_TASK_PTR )BUTTON_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )BUTTON_TASK_PRIO,     	
                 (CPU_STK   * )&BUTTON_TASK_STK[0],	
                 (CPU_STK_SIZE)BUTTON_STK_SIZE/10,	
                 (CPU_STK_SIZE)BUTTON_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//����DATA��������
	OSTaskCreate((OS_TCB 	* )&DATATaskTCB,		
				 (CPU_CHAR	* )"DATA task", 		
                 (OS_TASK_PTR )DATA_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )DATA_TASK_PRIO,     	
                 (CPU_STK   * )&DATA_TASK_STK[0],	
                 (CPU_STK_SIZE)DATA_STK_SIZE/10,	
                 (CPU_STK_SIZE)DATA_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);                 
                 
                 
                 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����			 
	OS_CRITICAL_EXIT();	//�����ٽ���
}



//led0������
void LVGL_task(void *p_arg)
{

	OS_ERR err;
	p_arg = p_arg;
 
    app_show_start();
    start_img_anim();
 	lv_task_handler(); //LVGL������ʾ 
	OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err); //��ʱ1S
    app_del_start();
       
   
	app_digital_clock_create(); //�������ֱ���  
    app_menu_tip_create();     
    app_menu_create();
    app_clock_create();     
    app_lighting_create();
    app_about_create();    
    app_game_create();
    
    
	while(1)
	{
        lv_task_handler();
        OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ10ms
	}
}



//��������
void BMP_task(void *p_arg)
{
    lv_task_handler();    
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
        lv_task_handler();
        BMP_UncompemstatedToTrue();          
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err);         
	}
}

//��������
void MPU6050_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{    
        Read_DMP();                   //===��ȡYaw(-180 - 179)
        dmp_get_pedometer_step_count(&step_count); //�õ��Ʋ�����     
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err);         
	}
}

//��������
void BUTTON_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{   
        OLED_display(KEY_Scan(0));
        OLED_display(KeyProc());        
		OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_STRICT,&err);         
	}
}

//��������
void DATA_task(void *p_arg)
{
	OS_ERR err;
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;    
    
	p_arg = p_arg;
	while(1)
	{   
       
        adcx=Get_Adc_Average(ADC_Channel_6,5)/23;//��ȡͨ��5��ת��ֵ��20��ȡƽ��
        
        RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);   
        sprintf((char*)timer,"%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes);
        sprintf((char*)Seconds,"%02d",RTC_TimeStruct.RTC_Seconds); 
        
        RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
        sprintf((char*)date,"%02d-%02d",RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date);
        week=RTC_DateStruct.RTC_WeekDay;
        hours=RTC_TimeStruct.RTC_Hours;
        minutes=RTC_TimeStruct.RTC_Minutes;
        seconds=RTC_TimeStruct.RTC_Seconds;
        
        sprintf((char*)TEMP,"%2d.%dC",bmp180.Temp/10,bmp180.Temp%10); 
        sprintf((char*)walk,"%4d M",(int)step_count);
        
        sprintf((char*)bat,"%02d",adcx);
        
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);         
	}
}

