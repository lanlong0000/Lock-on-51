#include "Timer.h"





void Timer1Init(void)    //11.0592MHZ   ��ʱʱ��1ms
{
	TMOD|=0X10;
 
	TH1=0XFC;	      //��ʱ����ֵ
	TL1=0X18;	      //��ʱ����ֵ
	ET1=1;
	EA=1;
	TR1=1;//��ʱ������	
}