/*
����7�����������


�����ԣ����4Pת�Ӱ�FPC���ϣ�2.54���볯�Լ�����ô����������
��1 2.2  x0 x+
��2 1.1  y1 y-
��3 1.0  x1 x-
��  2.3  y0 y+

�����������x�����׼��Y���귶ΧС�����Ҳ��Գƣ�������ֱ����ر�С

2018-8-28

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

sbit key1=P1^0;
sbit key2=P1^1;
sbit key3=P1^2;

//#include "ADC.h"

#include "getxy.h"



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

