#include "Timer.h"





void Timer1Init(void)    //11.0592MHZ   定时时间1ms
{
	TMOD|=0X10;
 
	TH1=0XFC;	      //定时器初值
	TL1=0X18;	      //定时器初值
	ET1=1;
	EA=1;
	TR1=1;//定时器启动	
}