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


#include "1601_P11C.C"

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
                   蜂呜器子程序
------------------------------------------------*/
void beep()
{
unsigned char y;

for(y=0;y<100;y++)
 {
  spk=0;
  DelayUs2x(250);  DelayUs2x(250);  DelayUs2x(250);  DelayUs2x(250);   DelayUs2x(250);
  spk=1;
  DelayUs2x(250);  DelayUs2x(250);  DelayUs2x(250);  DelayUs2x(250);   DelayUs2x(250);
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
  DelayUs2x(250);   DelayUs2x(250);  DelayUs2x(250);DelayUs2x(250);
  spk=1;
  DelayUs2x(250);   DelayUs2x(250);  DelayUs2x(250);DelayUs2x(250);
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
 if(cc==7373)  // 使用4M晶振，1333，使用12M晶振时4000 22.1184 7272.8
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
print(4,0x30+st/3600/10);
print(5,0x30+(st/3600)%10);
print(6,':');
print(7,0x30+(st%3600)/60/10);
print(8,0x30+(st%3600)/60%10);
print(9,':');
print(10,0x30+st%60/10);
print(11,0x30+st%60%10);

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
LCD_Init();
LCD_Clear();

beep();







st=0;
s2=1;
while(1)
{
 if(run==0) //如果是待机状态，一会儿就进入温度计界面
 {
  DelayMs(30);
  ca3++;
  if(ca3==2500)
   {
     ca3=0;
     wd=getwd(1023-ad(6));  //由于电路上 RT 和分压电阻的位置交换，所以程序里要倒一下，算法才对
     LCD_Clear();
     if(wd>99) print(6,0x30+wd/100);
     print(7,0x30+wd%100/10);
     print(8,'.');
     print(9,0x30+wd%10);
     print(10,'c');
   }
 }

 if(s2!=st)
 {
  disp4led();    //写入显示缓冲区
  s2=st;
  led=~run;
 }

 if(!key1)   //加1分
  {
   DelayMs(30);
   if(!key1)
    {
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
     run=0;
     cc=0;
     st=0;
     printf_str(0,"G162 Timer V1.00");
     beep();
     DelayMs(250);
     while(!key3) DelayMs(30);
     LCD_Clear();
     disp4led(); 
     beep();     beep();    
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
    DelayMs(100);
    led=~led;
    beep1();
    if(!key1) i=100;
    if(!key2) i=100;
    if(!key3) i=100;
    DelayMs(100);
   }
   while(!key1);  //等等松开按键，再重新开始
   while(!key2);
   while(!key3);
   DelayMs(200);
  }


}  //whlie结束

}

