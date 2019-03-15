/*
测试7寸独立触摸屏


经测试，如果4P转接板FPC朝上，2.54排针朝自己，那么，从左向右
左1 2.2  x0 x+
左2 1.1  y1 y-
左3 1.0  x1 x-
右  2.3  y0 y+

这个触摸屏的x座标很准，Y座标范围小，而且不对称，左半屏分辨率特别小

2018-8-28

*/

#define WEI 11

#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include<intrins.h>

//D1201控制位（液晶模块接口定义，根据自已的需要更改）
sbit D1201_DAT=P3^7;
sbit D1201_CS=P3^4;     //lower enable
sbit D1201_WR=P3^6;     //rising edge
sbit D1201_RD=P3^5;

#include "LCD-1621.c"     //3+5位段式液晶无背光 0.5元 LCD-V5.3 5v供电效果最好
//#include "DelayMs_15F104E6.h"    //15F104 6M延时

sbit key1=P1^0;
sbit key2=P1^1;
sbit key3=P1^2;

//#include "ADC.h"

#include "getxy.h"



/*------------------------------------------------
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}

void DelayMs(unsigned int t)
{
while(--t)
{
DelayUs2x(225);
DelayUs2x(225);
}
}

void DelayS(unsigned char s)
{
while(s--)
 {
  DelayMs(250);  DelayMs(250);
  DelayMs(250);  DelayMs(250);
 }

}






/*------------------------------------------------
                     main
------------------------------------------------*/
void main()
{
unsigned char x,y;

D1621_Init();

cls();

print(1,21,0);
print(5,21,0);

while(1)
{
getxy(&x,&y);

print(2,x/100,0);
print(3,x%100/10,0);
print(4,x%10,0);

print(6,y/100,0);
print(7,y%100/10,0);
print(8,y%10,0);

DelayS(3);
}

}

