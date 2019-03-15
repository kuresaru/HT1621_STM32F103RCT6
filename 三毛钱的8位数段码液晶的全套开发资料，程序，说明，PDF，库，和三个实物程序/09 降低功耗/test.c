/*
G162 驱动无背光的HT1621 3+5断码屏

STC12C5A40S2 3.57MHz

倒时器，内置温度计


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
//sbit D1201_RD=P0^1;

#include "LCD-1621.c"     //3+5位段式液晶无背光 0.5元 LCD-V5.3 5v供电效果最好
//#include "DelayMs_15F104E6.h"    //15F104 6M延时

sfr P3M0        =   0xB2;   //0000,0000 端口3模式寄存器0

#include "ad.h"

sbit spk=P3^4;
sbit led=P4^0;

unsigned int cc;  //200ns 变量
unsigned int st;  //计秒变量
bit run;          //是否倒时

sbit key1=P1^0;    //按钮1
sbit key2=P1^1;    //按钮2
sbit key3=P1^2;





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







/*------------------------------------------------
                   蜂呜器子程序
------------------------------------------------*/
void beep1()
{
unsigned char y;

for(y=0;y<100;y++)
 {
  spk=0;
  DelayUs2x(250); 
  spk=1;
  DelayUs2x(250); 
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
                    定时器初始化子程序 定时器0
------------------------------------------------*/
void Init_Timer0(void)
{
 TMOD |= 0x02;	  //使用模式2，八位自动重装定时器		     
 TH0=0x05;	      //给定初值，250ns一个中断
 TL0=0x05;
 EA=1;            //总中断打开
 ET0=1;           //定时器中断打开
 TR0=1;           //定时器开关打开
}



/*------------------------------------------------
                 定时器中断子程序 0
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 using 1
{
 cc++;
 if(cc==1223)  // 使用4M晶振，1333，使用12M晶振时4000
  {
    cc=0;
    if(run)  //正在倒计时
    if(st)  st--;
  }
}












/*------------------------------------------------
                       显示
------------------------------------------------*/
void disp4led()
{
print(1,st/3600/10,0);
print(2,(st/3600)%10,0);
print(3,22,0);
print(4,(st%3600)/60/10,0);
print(5,(st%3600)/60%10,0);
print(6,22,0);
print(7,st%60/10,0);
print(8,st%60%10,0);
}







/*------------------------------------------------
                     main
------------------------------------------------*/
void main()
{
unsigned int wd; //温度
unsigned int s2; //上一秒
unsigned char i; //for的变量
unsigned char ca2; //长按用变量
unsigned int ca3; //待机状态计时 ,用于显示温度

P4SW=0x70;    //将P4.4 P4.5 P4.6设为IO口

run=0;  //不倒时

InitADC();
Init_Timer0();
D1621_Init();
cls();

beep();







st=0;
s2=1;
while(1)
{
 if(run==0) //如果是待机状态，一会儿就进入温度计界面
 {
  DelayMs(30);
  ca3++;
  if(ca3==25000)
   {
     led=1;
     ca3=0;
     wd=getwd(1023-ad(6));  //由于电路上 RT 和分压电阻的位置交换，所以程序里要倒一下，算法才对
     print(1,21,0);
     print(2,21,0);
     print(3,21,0);
     print(4,21,0);
     if(wd>99) print(4,wd/100,0);
     print(5,wd%100/10,0);
     print(6,21,0);
     print(7,21,0);
     print(8,21,0);
   }
 }

 if(s2!=st)
 {
  disp4led();    //写入显示缓冲区
  s2=st;
 }

 if(!key1)   //加1分
  {
   DelayMs(30);
   if(!key1)
    {
     ca3=0;
     run=0;
     st+=60;
     disp4led();     
     beep();
     ca2=0; //长按计时清零
     while(!key1) 
      {
       DelayMs(25);
       if(ca2<50) ca2++;
       if(ca2>40)
       {
        st+=120;
        disp4led();     
        beep();
        DelayMs(200);
        DelayMs(100);
       }

      }
      cc=0;
      run=1;
    }
   }


 if(!key2)   //减1分
  {
   DelayMs(30);
   if(!key2)
    {
     ca3=0;
     if(st>59)
     {
      st-=60;
      cc=0;
      run=1;
     }
     disp4led();     
     beep();
     while(!key2) DelayMs(30);
    }
   }

 
 if(!key3)   //清零
  {
   DelayMs(30);
   if(!key3)
    {
     ca3=0;
     run=0;
     cc=0;
     st=0;
     print(1,22,0);
     print(2,22,0);
     print(3,22,0);
     print(4,15,0);
     print(5,22,0);
     print(6,22,0);
     print(7,22,0);
     print(8,22,0);
     beep();
     DelayMs(250);
     beep();     beep();
     while(!key3) DelayMs(30);
     disp4led();     
    }
   }



 if(run)
  if(st==0)
  {
   disp4led();
   run=0;
   for(i=0;i<20;i++)
   {
    led=~led;
    beep();
    if(!key1) i=100;  //如果有按键按下，就退出
    if(!key2) i=100;
    if(!key3) i=100;
    DelayMs(200);
    led=~led;
    beep1();
    if(!key1) i=100;
    if(!key2) i=100;
    if(!key3) i=100;
    DelayMs(200);
   }
   while(!key1);  //等等松开按键，再重新开始
   while(!key2);
   while(!key3);
   DelayMs(200);
   led=1;
  }


}  //whlie结束

}

