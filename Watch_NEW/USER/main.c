#include "main.h"

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	delay_init(168);  	//时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组配置
    My_RTC_Init();
    LED_Init();
    TIM1_PWM_Init(360-1,84-1); 
    Adc_Init();    
    LCD_Init();	   //液晶屏初始化
	uart_init(115200);  //串口初始化
    KEY_Init();
    
    BMP_Init();
	BMP_ReadCalibrationData(); 
    IIC_Init();                     //=====IIC初始化    读取MPU6050数据
	MPU6050_initialize();           //=====MPU6050初始化
    DMP_Init();                     //=====初始化DMP     
    IWDG_Init(6,4095);               //32秒的看门狗 没有喂狗就关机 进行低功耗
    
    TIM3_Int_Init(999,71);
    lv_init(); 
    lv_port_disp_init();  

    
    
	OSInit(&err);		//初始化UCOSIII
	OS_CRITICAL_ENTER();//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	//退出临界区	 
	OSStart(&err);  //开启UCOSIII
	while(1);
}

//开始任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,10,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	//进入临界区
	//创建LVGL任务
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

				 
	//创建BMP测试任务
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

	//创建MPU6050测试任务
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

	//创建BUTTON测试任务
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
				 
	//创建DATA测试任务
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
                 
                 
                 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务			 
	OS_CRITICAL_EXIT();	//进入临界区
}



//led0任务函数
void LVGL_task(void *p_arg)
{

	OS_ERR err;
	p_arg = p_arg;
 
    app_show_start();
    start_img_anim();
 	lv_task_handler(); //LVGL更新显示 
	OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err); //延时1S
    app_del_start();
       
   
	app_digital_clock_create(); //创建数字表盘  
    app_menu_tip_create();     
    app_menu_create();
    app_clock_create();     
    app_lighting_create();
    app_about_create();    
    app_game_create();
    
    
	while(1)
	{
        lv_task_handler();
        OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //延时10ms
	}
}



//测试任务
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

//测试任务
void MPU6050_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{    
        Read_DMP();                   //===读取Yaw(-180 - 179)
        dmp_get_pedometer_step_count(&step_count); //得到计步步数     
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err);         
	}
}

//测试任务
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

//测试任务
void DATA_task(void *p_arg)
{
	OS_ERR err;
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;    
    
	p_arg = p_arg;
	while(1)
	{   
       
        adcx=Get_Adc_Average(ADC_Channel_6,5)/23;//获取通道5的转换值，20次取平均
        
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

