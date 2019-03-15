/*
G162 驱动无背光的HT1621 3+5断码屏

STC12C5A40S2 3.57MHz

2018-7-31
*/

sfr P4          =   0xc0;
sfr P4SW = 0xBB;


#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include<intrins.h>

//D1201控制位（液晶模块接口定义，根据自已的需要更改）
sbit D1201_DAT=P0^3;
sbit D1201_CS=P0^0;     //lower enable
sbit D1201_WR=P0^2;     //rising edge
sbit D1201_RD=P0^1;

#include "LCD-1621.c"     //3+5位段式液晶无背光 0.5元 LCD-V5.3 5v供电效果最好
//#include "DelayMs_15F104E6.h"    //15F104 6M延时

sfr P3M0        =   0xB2;   //0000,0000 端口3模式寄存器0

#include "ad.h"

sbit spk=P3^4;
sbit led=P4^0;

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
DelayUs2x(235);
DelayUs2x(235);
}

}



/*------------------------------------------------
                   蜂呜器子程序
------------------------------------------------*/
void beep()
{
unsigned char y;

for(y=0;y<100;y++)
 {
  spk=0;
  DelayUs2x(250);  DelayUs2x(50);
  spk=1;
  DelayUs2x(250);  DelayUs2x(50);
 }


}




/*---------------------------------
     AD 转成温度，返回温度的10倍
----------------------------------*/
unsigned int getwd(unsigned int wd)
{
unsigned int x1,x2; //AD计算中间量
unsigned char x3,x4; //AD计算中间量
           {x1=150; x2=602; x3=63; x4=65; } //8.3-15度
if(wd<602) {x1=198; x2=542; x3=48; x4=60; } //15-19.8度
if(wd<542) {x1=225; x2=515; x3=1; x4=1; } //19.8-22.5度
if(wd<515) {x1=250; x2=484; x3=25; x4=31; } //22.5-25度
if(wd<484) {x1=275; x2=459; x3=1; x4=1; } //25-27.5度
if(wd<459) {x1=300; x2=439; x3=25; x4=20; } //27.5-30度
if(wd<439) {x1=350; x2=396; x3=50; x4=43; } //30-35度
if(wd<396) {x1=502; x2=291; x3=52; x4=36; } //50-35度

return ( x1 - ( wd - x2) * x3 / x4 );
}




/*------------------------------------------------
                     main
------------------------------------------------*/
void main()
{
unsigned int wd;


P4SW=0x70;    //将P4.4 P4.5 P4.6设为IO口


InitADC();

D1621_Init();
cls();

beep();
while(1)
{
wd=getwd(1023-ad(6));  //由于电路上 RT 和分压电阻的位置交换，所以程序里要倒一下，算法才对


print(2,wd/100,0);
print(3,wd%100/10,0);
print(4,12,0);
print(8,wd%10,0);

DelayMs(250); 
DelayMs(250);
DelayMs(250);
DelayMs(250);
led=~led;



}
}

