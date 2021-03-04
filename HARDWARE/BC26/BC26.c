#include "bc26.h"
#include "string.h"
#include "usart.h"
#include "wdg.h"
#include "led.h"
char *strx,*extstrx;
extern unsigned char  RxBuffer[255],RxCounter;
BC26 BC26_Status;
////�����Ƶ���Ԫ��,���豸���涼���Բ�ѯ��//////////////////////
#define ProductKey     "a1SSUTip94N"             //��ƷKEY
#define DeviceName          "mzhtest001"      //
#define DeviceSecret    "b6be916a7792e75e9371c604101db034"  //
#define PubTopic         "/sys/a1SSUTip94N/mzhtest001/thing/event/property/post"//��������
#define SubTopic        "/sys/a1SSUTip94N/mzhtest001/thing/service/property/set"//��������
void Clear_Buffer(void)//��ջ���
{
		u8 i;
		Uart1_SendStr((char*)RxBuffer);
		for(i=0;i<100;i++)
		RxBuffer[i]=0;//����
		RxCounter=0;
		IWDG_Feed();//ι��
	
}
void BC26_Init(void)
{
    printf("AT\r\n"); 
    delay_ms(300);
    strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
    Clear_Buffer();	
    while(strx==NULL)
    {
        Clear_Buffer();	
        printf("AT\r\n"); 
        delay_ms(300);
        strx=strstr((const char*)RxBuffer,(const char*)"OK");//����OK
    }
    printf("AT+CFUN=1\r\n");//��ȡ���ţ������Ƿ���ڿ�����˼���Ƚ���Ҫ��
    delay_ms(300);
    printf("AT+CIMI\r\n");//��ȡ���ţ������Ƿ���ڿ�����˼���Ƚ���Ҫ��
    delay_ms(300);
    strx=strstr((const char*)RxBuffer,(const char*)"460");//��460������ʶ�𵽿���
    Clear_Buffer();	
    while(strx==NULL)
    {
        Clear_Buffer();	
        printf("AT+CIMI\r\n");//��ȡ���ţ������Ƿ���ڿ�����˼���Ƚ���Ҫ��
        delay_ms(300);
        strx=strstr((const char*)RxBuffer,(const char*)"460");//����OK,˵�����Ǵ��ڵ�
    }
        printf("AT+CGATT=1\r\n");//�������磬PDP
        delay_ms(300);
        strx=strstr((const char*)RxBuffer,(const char*)"OK");//��OK
        Clear_Buffer();	
        printf("AT+CGATT?\r\n");//��ѯ����״̬
        delay_ms(300);
        strx=strstr((const char*)RxBuffer,(const char*)"+CGATT: 1");//��1
        Clear_Buffer();	
		while(strx==NULL)
		{
            Clear_Buffer();	
            printf("AT+CGATT?\r\n");//��ȡ����״̬
            delay_ms(300);
            strx=strstr((const char*)RxBuffer,(const char*)"+CGATT: 1");//����1,����ע���ɹ�
		}
		printf("AT+CESQ\r\n");//�鿴��ȡCSQֵ
        delay_ms(300);
        strx=strstr((const char*)RxBuffer,(const char*)"+CESQ");//����CSQ
		if(strx)
			{
				BC26_Status.CSQ=(strx[7]-0x30)*10+(strx[8]-0x30);//��ȡCSQ
				if((BC26_Status.CSQ==99)||((strx[7]-0x30)==0))//˵��ɨ��ʧ��
				{
					while(1)
					{
            BC26_Status.netstatus=0;
						Uart1_SendStr("�ź�����ʧ�ܣ���鿴ԭ��!\r\n");
						delay_ms(300);//û���źž͸�λ
                        
					}
				}
             else
             {
                 BC26_Status.netstatus=1;
              }
                
            }
              Clear_Buffer();	
}




void BC26_ConTCP(void)
{
	printf("AT+QICLOSE=0\r\n");//�ر�socekt����
	delay_ms(300);
    Clear_Buffer();
    IWDG_Feed();//ι��
}
void BC26_CreateTCPSokcet(void)//����sokcet
{

    printf("AT+QIOPEN=1,0,\"TCP\",\"47.99.80.89\",14269,1234,1\r\n");//��������TCP,����IP�Լ��������˿ں��� ,����ֱ���³��ķ�ʽ
    delay_ms(300);
    strx=strstr((const char*)RxBuffer,(const char*)"+QIOPEN: 0,0");//����Ƿ��½�ɹ�
 	while(strx==NULL)
		{
            strx=strstr((const char*)RxBuffer,(const char*)"+QIOPEN: 0,0");//����Ƿ��½�ɹ�
            delay_ms(100);
		}  
     Clear_Buffer();	
    
}
void BC26_Senddata(uint8_t *len,uint8_t *data)//�ַ�����ʽ
{
    printf("AT+QSOSEND=0,%s,%s\r\n",len,data);
}

void BC26_Senddatahex(uint8_t *len,uint8_t *data)//����ʮ����������
{
    printf("AT+QISENDEX=0,%s,%s\r\n",len,data);
        delay_ms(300);
 	while(strx==NULL)
		{
            strx=strstr((const char*)RxBuffer,(const char*)"SEND OK");//����Ƿ��ͳɹ�
            delay_ms(100);
		}  
     Clear_Buffer();	
}

void BC26_RECData(void)
{

  
}



void  MQTT_Init(void)
{
  
    printf("AT+QMTCFG=\"aliauth\",0,\"%s\",\"%s\",\"%s\"\r\n",ProductKey,DeviceName,DeviceSecret);
    delay_ms(300);
    printf("AT+QMTOPEN=0,\"139.196.135.135\",1883\r\n");//ͨ��TCP��ʽȥ����MQTT�����Ʒ����� 
    delay_ms(300);
    strx=strstr((const char*)RxBuffer,(const char*)"+QMTOPEN: 0,0");//���·���״̬
  while(strx==NULL)
    {
      strx=strstr((const char*)RxBuffer,(const char*)"+QMTOPEN: 0,0");//ȷ�Ϸ���ֵ��ȷ
    }
    Clear_Buffer(); 
   printf("AT+QMTCONN=0,\"clientExample_1987\"\r\n");//ȥ��¼MQTT������
    delay_ms(300);
    strx=strstr((const char*)RxBuffer,(const char*)"+QMTCONN: 0,0,0");//���·���״̬
  while(strx==NULL)
    {
        strx=strstr((const char*)RxBuffer,(const char*)"+QMTCONN: 0,0,0");//���·���״̬
    }
    Clear_Buffer(); 
    /*
    printf("AT+QMTSUB=0,1,\"mzh_m26\",0\r\n");//���ĸ�����
        delay_ms(500);
    strx=strstr((const char*)RxBuffer,(const char*)"+QMTSUB: 0,1,0,0");//���ĳɹ�
  while(strx==NULL)
    {
        strx=strstr((const char*)RxBuffer,(const char*)"+QMTSUB: 0,1,0,0");//���ĳɹ�
    }
    Clear_Buffer(); 
    */
}

void aliyunMQTT_PUBdata(u8 water)
{
     u8 t_payload[200],len;
     printf("AT+QMTPUB=0,0,0,0,%s\r\n",PubTopic);//��������
     delay_ms(300);
     len=Mqttaliyun_Savedata(t_payload,water);
     t_payload[len]=0;
     printf("%s",t_payload);
  while((USART2->SR&0X40)==0){}//ѭ������,ֱ���������   
     USART2->DR = (u8) 0x1A;    
     delay_ms(100);
     strx=strstr((const char*)RxBuffer,(const char*)"+QMTPUB: 0,0,0");//���·���״̬
  while(strx==NULL)
    {
        strx=strstr((const char*)RxBuffer,(const char*)"+QMTPUB: 0,0,0");//���·���״̬
    }
    Clear_Buffer(); 
}

//���ʰ�������Ҫ�ύJSON����
u8 Mqttaliyun_Savedata(u8 *t_payload,u8 water)
{

    char json[]="{\"id\":\"26\",\"version\":\"1.0\",\"params\":{\"WaterConsumption\":{\"value\":%d}},\"method\":\"thing.event.property.post\"}";	 //     char json[]="{\"datastreams\":[{\"id\":\"location\",\"datapoints\":[{\"value\":{\"lon\":%2.6f,\"lat\":%2.6f}}]}]}";
    char t_json[200];
    unsigned short json_len;
    sprintf(t_json, json, water);
    json_len = strlen(t_json)/sizeof(char);
  	memcpy(t_payload, t_json, json_len);
    return json_len;
}

