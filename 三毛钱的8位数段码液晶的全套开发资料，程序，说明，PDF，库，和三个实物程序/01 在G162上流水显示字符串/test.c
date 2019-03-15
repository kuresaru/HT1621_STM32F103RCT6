/*
P11C

STC89C58RD+ PQFP44
11.0592MHz

2017-5-16 PASS

*/

sfr P4          =   0xc0;
#include<reg52.h> 
#include<intrins.h>
#include "1601_P11C.c"
sbit led=P4^0;




/*------------------------------------------------
                    主函数
------------------------------------------------*/ 
void main(void) 
{ 
unsigned char a;

LCD_Init(); 
LCD_Clear();
lcd_print(0,"LCD:");
a=0;
while(1)
{
print_str(5,"G162 LCD DEMO. CPU=STC12C5A60S2 LQFP44 22.1184MHz, PCB=ML20180707(G162), LCD=1601. 2018-7-31, OK!                   ",a,10);
a++;
a%=98;
led=~led;
DelayMs(250);DelayMs(250);
led=~led;
DelayMs(250);DelayMs(250);

}//end while

}
// 主程序结束




