/*


*/

#define WEI 11

#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include<intrins.h>
sfr P4   = 0xC0;
sfr P4SW = 0xBB;
//D1201控制位（液晶模块接口定义，根据自已的需要更改）
sbit D1201_DAT=P4^4;
sbit D1201_CS=P4^6;     //lower enable
sbit D1201_WR=P4^5;     //rising edge


#include "LCD-1621.c"     //3+5位段式液晶无背光 0.5元 LCD-V5.3 5v供电效果最好

sbit key1=P1^0;
sbit key2=P1^1;
sbit key3=P1^2;

#include "v1302.c"



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







/*------------------------------------------------
                     main
------------------------------------------------*/
void main()
{
P4SW = 0x70;
D1621_Init();
cls();

Ds1302_Init();
Ds1302_Read_Time();
Ds1302_Write_Time();

while(1)
{
 print(1,time_buf1[4]/10,0);
 print(2,time_buf1[4]%10,0);

 print(3,22,0);

 print(4,time_buf1[5]/10,0);
 print(5,time_buf1[5]%10,0);

 print(6,22,0);

 print(7,time_buf1[6]/10,0);
 print(8,time_buf1[6]%10,0);

 DelayMs(250);

 if(!key1) time_buf1[4]++;
 if(!key2) time_buf1[5]++;
 if(!key3) time_buf1[5]--;

 if(time_buf1[4]>23) time_buf1[4]=0;
 if(time_buf1[5]>59) time_buf1[5]=0;


}
}

