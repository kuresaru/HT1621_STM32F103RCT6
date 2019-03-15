/*
G162 �����ޱ����HT1621 3+5������

STC12C5A40S2 3.57MHz

��ʱ���������¶ȼ�


2018-7-31
*/

sfr P4          =   0xc0;
sfr P4SW = 0xBB;


#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include<intrins.h>

//D1201����λ��Һ��ģ��ӿڶ��壬�������ѵ���Ҫ���ģ�
sbit D1201_DAT=P0^3;
sbit D1201_CS=P0^0;     //lower enable
sbit D1201_WR=P0^2;     //rising edge
//sbit D1201_RD=P0^1;

#include "LCD-1621.c"     //3+5λ��ʽҺ���ޱ��� 0.5Ԫ LCD-V5.3 5v����Ч�����
//#include "DelayMs_15F104E6.h"    //15F104 6M��ʱ

sfr P3M0        =   0xB2;   //0000,0000 �˿�3ģʽ�Ĵ���0

#include "ad.h"

sbit spk=P3^4;
sbit led=P4^0;

unsigned int cc;  //200ns ����
unsigned int st;  //�������
bit run;          //�Ƿ�ʱ

sbit key1=P1^0;    //��ť1
sbit key2=P1^1;    //��ť2
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
DelayUs2x(235);
DelayUs2x(235);
}
}



/*------------------------------------------------
                   �������ӳ���
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
                   �������ӳ���
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
     AD ת���¶ȣ������¶ȵ�10��
----------------------------------*/
unsigned int getwd(unsigned int wd)
{
unsigned int x1,x2; //AD�����м���
unsigned char x3,x4; //AD�����м���
           {x1=150; x2=602; x3=63; x4=65; } //8.3-15��
if(wd<602) {x1=198; x2=542; x3=48; x4=60; } //15-19.8��
if(wd<542) {x1=225; x2=515; x3=1; x4=1; } //19.8-22.5��
if(wd<515) {x1=250; x2=484; x3=25; x4=31; } //22.5-25��
if(wd<484) {x1=275; x2=459; x3=1; x4=1; } //25-27.5��
if(wd<459) {x1=300; x2=439; x3=25; x4=20; } //27.5-30��
if(wd<439) {x1=350; x2=396; x3=50; x4=43; } //30-35��
if(wd<396) {x1=502; x2=291; x3=52; x4=36; } //50-35��

return ( x1 - ( wd - x2) * x3 / x4 );
}









/*------------------------------------------------
                    ��ʱ����ʼ���ӳ��� ��ʱ��0
------------------------------------------------*/
void Init_Timer0(void)
{
 TMOD |= 0x02;	  //ʹ��ģʽ2����λ�Զ���װ��ʱ��		     
 TH0=0x05;	      //������ֵ��250nsһ���ж�
 TL0=0x05;
 EA=1;            //���жϴ�
 ET0=1;           //��ʱ���жϴ�
 TR0=1;           //��ʱ�����ش�
}



/*------------------------------------------------
                 ��ʱ���ж��ӳ��� 0
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 using 1
{
 cc++;
 if(cc==1223)  // ʹ��4M����1333��ʹ��12M����ʱ4000
  {
    cc=0;
    if(run)  //���ڵ���ʱ
    if(st)  st--;
  }
}












/*------------------------------------------------
                       ��ʾ
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
unsigned int wd; //�¶�
unsigned int s2; //��һ��
unsigned char i; //for�ı���
unsigned char ca2; //�����ñ���
unsigned int ca3; //����״̬��ʱ ,������ʾ�¶�

P4SW=0x70;    //��P4.4 P4.5 P4.6��ΪIO��

run=0;  //����ʱ

InitADC();
Init_Timer0();
D1621_Init();
cls();

beep();







st=0;
s2=1;
while(1)
{
 if(run==0) //����Ǵ���״̬��һ����ͽ����¶ȼƽ���
 {
  DelayMs(30);
  ca3++;
  if(ca3==25000)
   {
     led=1;
     ca3=0;
     wd=getwd(1023-ad(6));  //���ڵ�·�� RT �ͷ�ѹ�����λ�ý��������Գ�����Ҫ��һ�£��㷨�Ŷ�
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
  disp4led();    //д����ʾ������
  s2=st;
 }

 if(!key1)   //��1��
  {
   DelayMs(30);
   if(!key1)
    {
     ca3=0;
     run=0;
     st+=60;
     disp4led();     
     beep();
     ca2=0; //������ʱ����
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


 if(!key2)   //��1��
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

 
 if(!key3)   //����
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
    if(!key1) i=100;  //����а������£����˳�
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
   while(!key1);  //�ȵ��ɿ������������¿�ʼ
   while(!key2);
   while(!key3);
   DelayMs(200);
   led=1;
  }


}  //whlie����

}

