

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
	{i++;}											//找到第一个逗号
	i++;												//跳过第一个逗号				
	
	while(RxBuffer3[i] != ',')	//只要值不等于逗号，那就把数据整理起来，如果等于逗号，也就是这个数结束了
	{
		Num[j]=RxBuffer3[i];
		NumCount++;
		i++;
		j++;
	}
	//得到一个数组


	for( p=0; p<NumCount; p++)
	{
				data_last+=Num[p]*pow(10,(NumCount-p-1));
	}
	//data_last位置所对应的数据改变了
	return data_last;
}
	
