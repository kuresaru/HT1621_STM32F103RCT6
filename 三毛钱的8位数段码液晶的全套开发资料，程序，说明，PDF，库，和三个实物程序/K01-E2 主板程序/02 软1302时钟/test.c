/*


*/

#define WEI 11

#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include<intrins.h>
sfr P4   = 0xC0;
sfr P4SW = 0xBB;
//D1201����λ��Һ��ģ��ӿڶ��壬�������ѵ���Ҫ���ģ�
sbit D1201_DAT=P4^4;
sbit D1201_CS=P4^6;     //lower enable
sbit D1201_WR=P4^5;     //rising edge


#include "LCD-1621.c"     //3+5λ��ʽҺ���ޱ��� 0.5Ԫ LCD-V5.3 5v����Ч�����

sbit key1=P1^0;
sbit key2=P1^1;
sbit key3=P1^2;

#include "v1302.c"



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

