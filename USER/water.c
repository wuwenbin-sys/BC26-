

#include "usart.h"	
#include "math.h"
#include "water.h"



extern unsigned char  RxBuffer3[100],RxCounter3;

u8 data_process(void)
{
	u8 i=0,j=0,p;
	u8 NumCount=0;
	u8 Num[10]={0};
	u16 data_last=0;
	while(RxBuffer3[i] != ',') 
	{i++;}											//�ҵ���һ������
	i++;												//������һ������				
	
	while(RxBuffer3[i] != ',')	//ֻҪֵ�����ڶ��ţ��ǾͰ���������������������ڶ��ţ�Ҳ���������������
	{
		Num[j]=RxBuffer3[i];
		NumCount++;
		i++;
		j++;
	}
	//�õ�һ������


	for( p=0; p<NumCount; p++)
	{
				data_last+=Num[p]*pow(10,(NumCount-p-1));
	}
	//data_lastλ������Ӧ�����ݸı���
	return data_last;
}
	
