#ifndef __BC26_H
#define __BC26_H	
#include "usart.h"
#include <stm32f10x.h>
#include "delay.h"
void Clear_Buffer(void);//清空缓存	
void BC26_Init(void);
void BC26_PDPACT(void);
void BC26_ConTCP(void);
void BC26_CreateTCPSokcet(void);
void BC26_RECData(void);
void BC26_Senddata(uint8_t *len,uint8_t *data);
void BC26_Senddatahex(uint8_t *len,uint8_t *data);
void BC26_CreateSokcet(void);
void Clear_Buffer(void);
void BC26_ChecekConStatus(void);
void  MQTT_Init(void);
void aliyunMQTT_PUBdata(u8 water);
u8 Mqttaliyun_Savedata(u8 *t_payload,u8 water);
typedef struct
{
    uint8_t CSQ;    
    uint8_t Socketnum;   //编号
    uint8_t reclen;   //获取到数据的长度
    uint8_t res;      
    uint8_t recdatalen[10];
    uint8_t recdata[100];
    uint8_t netstatus;//网络指示灯
} BC26;

#endif

