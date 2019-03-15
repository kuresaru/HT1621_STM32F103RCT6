/*
�����2Ԫ��1601Һ��ģ����������
         V 1.00

��1602�������ǣ�ǰ8���ַ�Ϊ1602�ĵ�һ��ǰ8����
��8���ַ�Ϊ1602�ĵڶ��к�8����Ϊ��������print����
ʹ��print(x,dat)����ֱ����xλ����ʾ���ַ�dat 

2013-7-4

�޸ĺ��1601
��Ϊʹ����STC12C��Ƭ����22.1184MHz�������ٶ�̫�죬�������ϣ���ʾ��ȫ�����Ը�����æ����

2017-4-8


P11C
ʹ��STC89C58RD+ PQFP44 11.0592MHz
�޸���IO����ʱ

*/
// P7A�Ķ˿ڶ���
sbit RS = P1^5;   //����˿� 
sbit RW = P1^4;
sbit EN = P1^3;
#define DataPort P2
///////////////


#define RS_CLR RS=0 
#define RS_SET RS=1

#define RW_CLR RW=0 
#define RW_SET RW=1 

#define EN_CLR EN=0
#define EN_SET EN=1



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
/*------------------------------------------------
 mS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //������ʱ1mS
     DelayUs2x(225);    //11.0592 225
	 DelayUs2x(225);
     DelayUs2x(225);    //11.0592 225
	 DelayUs2x(225);
     DelayUs2x(225);    //11.0592 225
	 DelayUs2x(225);
     DelayUs2x(225);    //11.0592 225
	 DelayUs2x(225);
     DelayUs2x(225);    //11.0592 225
	 DelayUs2x(225);
     DelayUs2x(225);    //11.0592 225
	 DelayUs2x(225);
     DelayUs2x(225);    //11.0592 225
	 DelayUs2x(225);
     DelayUs2x(225);    //11.0592 225
	 DelayUs2x(225);
     DelayUs2x(225);    //11.0592 225
	 DelayUs2x(225);
     DelayUs2x(225);    //11.0592 225
	 DelayUs2x(225);
     DelayUs2x(225);    //11.0592 225
	 DelayUs2x(225);
     DelayUs2x(225);    //11.0592 225
	 DelayUs2x(225);
 }
}

/*------------------------------------------------
              д�������
------------------------------------------------*/
 void LCD_Write_Com(unsigned char com) 
 {  
 DelayMs(1);
 RS_CLR; 
 RW_CLR; 
 EN_SET; 
 DataPort= com; 
 _nop_();  _nop_();
 EN_CLR;
 }
/*------------------------------------------------
              д�����ݺ���
------------------------------------------------*/
 void LCD_Write_Data(unsigned char Data) 
 { 
 DelayMs(1);
 RS_SET; 
 RW_CLR; 
 EN_SET; 
 DataPort= Data; 
 _nop_(); _nop_();
 EN_CLR;
 }

/*------------------------------------------------
                ��������
------------------------------------------------*/
 void LCD_Clear(void) 
 { 
 LCD_Write_Com(0x01); 
 DelayMs(5);
 }


/*------------------------------------------------
              д���ַ�����
------------------------------------------------*/
 void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data) 
 {     
 if (y == 0) 
 	{     
 	LCD_Write_Com(0x80 + x);     
 	}    
 else 
 	{     
 	LCD_Write_Com(0xC0 + x);     
 	}        
 LCD_Write_Data( Data);  
 }
/*------------------------------------------------
              ��ʼ������
------------------------------------------------*/
 void LCD_Init(void) 
 {
   LCD_Write_Com(0x38);    /*��ʾģʽ����*/ 
   DelayMs(3); 
   LCD_Write_Com(0x38); 
   DelayMs(3); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38);  
   LCD_Write_Com(0x08);    /*��ʾ�ر�*/ 
   LCD_Write_Com(0x01);    /*��ʾ����*/ 
   LCD_Write_Com(0x06);    /*��ʾ����ƶ�����*/ 
   DelayMs(3); 
   LCD_Write_Com(0x0C);    /*��ʾ�����������*/
   }





/*-------------------------------
        ��xλ����ʾdat
         1601���и�ʽ
--------------------------------*/
void print(unsigned char x, unsigned char dat)
{
if(x<8) 
  LCD_Write_Char(x,0,dat);
 else
  LCD_Write_Char(x-8,1,dat);
}



/*-------------------------------
          ��ӡ�ַ���
--------------------------------*/
void printf_str(unsigned char x,unsigned char *s)
{
while(*s)
 {
  print(x,*s);
  x++;
  s++;
  x%=16;  //��������ʱ�������׼�����ӡ
 }
 }



/*-------------------------------
          ��ӡ�ַ���2 ����ָ������ӡ���ַ���
a ��ʼ�Ĵ�ӡλ��
n ��ӡ�ַ�������
--------------------------------
void print_str(unsigned char x,unsigned char *s,unsigned char a,unsigned char n)
{
while( (*s) && (a--) )
{
s++;
}

while((*s) && (n--))
 {
  print(x,*s);
  x++;
  s++;
  x%=16;  //��������ʱ�������׼�����ӡ
 }
 }


*/
