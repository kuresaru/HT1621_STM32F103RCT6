/*
3+5�ޱ��������

STC15F2K40S2 LQFP44 11.0592MHz �����²��� PASS
����������һҹ���������ȶ�

2018/7/25

*/

#define WEI 11

#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include<intrins.h>

//D1201����λ��Һ��ģ��ӿڶ��壬�������ѵ���Ҫ���ģ�
sbit D1201_DAT=P3^7;
sbit D1201_CS=P3^4;     //lower enable
sbit D1201_WR=P3^6;     //rising edge
sbit D1201_RD=P3^5;

#include "LCD-1621.c"     //3+5λ��ʽҺ���ޱ��� 0.5Ԫ LCD-V5.3 5v����Ч�����
//#include "DelayMs_15F104E6.h"    //15F104 6M��ʱ

sfr P3M0        =   0xB2;   //0000,0000 �˿�3ģʽ�Ĵ���0
sbit key1=P1^0;
sbit key2=P1^1;
sbit key3=P1^2;






/*------------------------------------------------
 uS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��,������ʱ
 �������� T=tx2+5 uS 
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
unsigned char h,m,s; //ʱ����


D1621_Init();
cls();

h=8;
m=0;
s=0;

while(1)
{
print(1,h/10,0);
print(2,h%10,0);

print(3,22,0);

print(4,m/10,0);
print(5,m%10,0);

print(6,22,0);

print(7,s/10,0);
print(8,s%10,0);

DelayMs(250);
DelayMs(250);
DelayMs(250);


if(!key1) h++;
if(!key2) m++;
if(!key3) m--;

s++;

if(s>60) s=0;
if(m>59) m=59;
if(h>23) h=0;

if(s==60)
 {
  s=0;
  m++;
  if(m==60)
  {
   m=0;
   h++;
   if(h==24) h=0;
  }

 }


}
}

