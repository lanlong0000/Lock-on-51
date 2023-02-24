#include "key.h"
void delay(unsigned int i)	 //延时函数
{
  unsigned int j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}  

//--16位按键扫描
unsigned char Key_Read(void)
{
	
	unsigned char Key_Value;
	unsigned char confirm_first_founcation=0,confirm_second_founcation=0,confirm_founcation=0;
	unsigned int num=99;
	    P1=0xf0;
	if(P1!=0Xf0)
		{
			delay(20);
			confirm_first_founcation=P1;
			P1=0x0f;
	   if(P1!=0x0f)   
			{
				confirm_second_founcation=P1;
			}
		}
			confirm_founcation=confirm_first_founcation+confirm_second_founcation;   
	
	switch(confirm_founcation)
	{
		case 0xee: Key_Value = 1; break;
		case 0xed: Key_Value = 2; break;	
		case 0xeb: Key_Value = 3; break;	
		case 0xe7: Key_Value = 4; break;	
	
		case 0xde: Key_Value = 5; break;
		case 0xdd: Key_Value = 6; break;	
		case 0xdb: Key_Value = 7; break;	
		case 0xd7: Key_Value = 8; break;	

		case 0xbe: Key_Value = 9; break;
		case 0xbd: Key_Value = 10; break;	
		case 0xbb: Key_Value = 11; break;	
		case 0xb7: Key_Value = 12; break;			
	
		case 0x7e: Key_Value = 13; break;
		case 0x7d: Key_Value = 14; break;	
		case 0x7b: Key_Value = 15; break;	
		case 0x77: Key_Value = 16; break;			
		default :  Key_Value = 0;
	}
	
	return Key_Value;
	
}
