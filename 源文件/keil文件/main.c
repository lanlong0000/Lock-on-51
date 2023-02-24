#include <reg52.h>
#include <key.h>
#include "Timer.h"
#include <intrins.h>
#include<string.h>
void Key_Proc(void);


//--定时器滴答变量
unsigned long ms_Tick = 0;
//--定时器减速变量
unsigned int SlowDown_Key;
//--按键变量
unsigned char Key_Value;
unsigned char Key_Old, Key_Down;
typedef unsigned char uchar;
typedef unsigned int uint;
uchar j;
uint number=100;
uint n=0;
uint fre=0;   //八位密码
uint set=0;        //设置密码标志（-1表示可以设置）（1表示不可设置）
uint open=0;       //等于1时开始输入密码开锁
sbit  BEEP=P2^5;
sbit  LED=P2^6;
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit lock = P2^7;
uint password_test[8]={0,0,0,0,0,0,0,0};
uint password_admin[8]={1,1,1,1,1,1,1,1};
int i;
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};//共阳数字编码

void main(void)
{
  Timer1Init();
	EA = 1; 
	lock=1;
	BEEP=1;
	LED=0;	  
	while(1)
	{
		if(fre>8){
		fre=1;}
     	Key_Proc();
		 
		P2_3=0;
		P0=0xff;
		P0=table[number];
		delay(5);
		P2_3=1;

		P2_1=0;
		P0=0xff;
		P0=table[fre];
		delay(5);
		P2_1=1;

		P2_0=0;
		P0=0xff;
		P0=0x8e;
		delay(5);
		P2_0=1;

		P2_2=0;
		P0=0xff;
		P0=0xc8;
		delay(5);
		P2_2=1;
	
	 	i++;
		if(i>8)
		 	i=0;
	 	if(fre==i&&set==1){
			password_test[i]=number;
			password_admin[i]=number;}
		
		if(open==1&&(memcmp(password_test,password_admin,sizeof password_admin)==0))
		{
			lock=0;
			open=0;
			fre=0;
			for(n=0;i<8;i++)
				password_admin[i]=99;
    	}		
		if(n==3)
		{
			if(memcmp(password_test,password_admin,sizeof password_admin)!=0)
			{
			open=0;
			fre=0;
			BEEP=0;
			delay(100);	
			for(n=0;i<8;i++)
				password_admin[i]=99;
			}
	 	}

    
	 
		if(n!=3){
		    BEEP=1;}
	}
}




void tm1_isr() interrupt 3
{
	ms_Tick++;
	if(++SlowDown_Key == 3) SlowDown_Key = 0;
}

void	Key_Proc(void)
{
	if(SlowDown_Key) return;
	SlowDown_Key = 1;
	Key_Value = Key_Read();
	Key_Down = Key_Value & (Key_Old ^ Key_Value);
	Key_Old = Key_Value;

	if((Key_Down-1>=0) && (Key_Down-1<=9)){
		number=Key_Down-1;
		fre++;}
	if(Key_Down>=10)
		fre=0;
	if(Key_Down==11)
		set=1;
	if(Key_Down==12)
		set=0;
	if(Key_Down==13){
		open=1;
		n++;
		}
	if(Key_Down==14){
		open=0;
		lock = 1;
		n=0;
	}
	
}

