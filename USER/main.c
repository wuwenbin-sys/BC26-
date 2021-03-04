#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	 
#include "math.h"			
#include "stdio.h"
#include "stm32f10x_flash.h"
#include "stdlib.h"
#include "string.h"
#include "wdg.h"
#include "timer.h"
#include "stm32f10x_tim.h"
#include "bc26.h"	 
#include "dht11.h"
#include "water.h"
extern char  RxBuffer[100],RxCounter;

void OPEN_BC26(void)
{
   char *strx;
 
    printf("AT\r\n"); 
    delay_ms(300);
    strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
    printf("AT\r\n"); 
    delay_ms(300);
    strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
	IWDG_Feed();//喂狗
   if(strx==NULL)
	{
        PWRKEY=1;//拉低
        delay_ms(300);
        delay_ms(300);
        delay_ms(300);
        delay_ms(300);	
        PWRKEY=0;//拉高正常开机
        IWDG_Feed();//喂狗
	}
    printf("AT\r\n"); 
    delay_ms(300);
    IWDG_Feed();//喂狗
    strx=strstr((const char*)RxBuffer,(const char*)"OK");//返回OK
    printf("ATE0&W\r\n"); //关闭回显
    delay_ms(300); 
    LED=0;
    IWDG_Feed();//喂狗
    printf("AT+QMTDISC=0\r\n");//关闭连接
    delay_ms(300);
    printf("AT+QMTCLOSE=0\r\n");
    delay_ms(300); 
}
/***
此功能实现往阿里云发数据，用户需要更改三元素与推送主题一致。保持和自己的设备一样
***/

//适用于NB版本
 int main(void)
 {	
    u8 temp,humi;
		char TEST[]="DATA IS OK";
	  volatile u8 water;
    delay_init();	    	 //延时函数初始化	  
    NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    LED_Init();		  		//初始化与LED连接的硬件接口
    uart_init(115200);//串口1初始化，可连接PC进行打印模块返回数据
    uart2_init(115200);//对接BC26串口初始化
		uart3_init(115200); //串口3初始化，接收水表数据
    IWDG_Init(7,625);    //8S一次
    OPEN_BC26();//对BC26开机  
    BC26_Init();//对设备初始化
    MQTT_Init();
	  //water=50;
	
   while(1)
    {  
      //  DHT11_Read_Data(&temp,&humi);//读取温湿度数据
      // temp=32;
      //  humi=230;
			  
				
				water=data_process();
				Uart1_SendStr((char*)TEST);
			//water++;
				aliyunMQTT_PUBdata(water);
				
        delay_ms(500);
				LED=!LED;
        IWDG_Feed();//喂狗
    }	 
 }






