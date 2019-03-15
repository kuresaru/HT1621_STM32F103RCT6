/*
网络版2元的1601液晶模块驱动程序
         V 1.00

与1602的区别是，前8个字符为1602的第一行前8个，
后8个字符为1602的第二行后8个，为此制作了print函数
使用print(x,dat)可以直接在x位置显示出字符dat 

2013-7-4

修改后的1601
因为使用了STC12C单片机，22.1184MHz，可能速度太快，屏跟不上，显示不全，所以改了判忙程序

2017-4-8


P11C
使用STC89C58RD+ PQFP44 11.0592MHz
修改了IO和延时

*/
// P7A的端口定义
sbit RS = P1^5;   //定义端口 
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
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //大致延时1mS
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
              写入命令函数
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
              写入数据函数
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
                清屏函数
------------------------------------------------*/
 void LCD_Clear(void) 
 { 
 LCD_Write_Com(0x01); 
 DelayMs(5);
 }


/*------------------------------------------------
              写入字符函数
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
              初始化函数
------------------------------------------------*/
 void LCD_Init(void) 
 {
   LCD_Write_Com(0x38);    /*显示模式设置*/ 
   DelayMs(3); 
   LCD_Write_Com(0x38); 
   DelayMs(3); 
   LCD_Write_Com(0x38); 
   DelayMs(5); 
   LCD_Write_Com(0x38);  
   LCD_Write_Com(0x08);    /*显示关闭*/ 
   LCD_Write_Com(0x01);    /*显示清屏*/ 
   LCD_Write_Com(0x06);    /*显示光标移动设置*/ 
   DelayMs(3); 
   LCD_Write_Com(0x0C);    /*显示开及光标设置*/
   }





/*-------------------------------
        在x位置显示dat
         1601特有格式
--------------------------------*/
void print(unsigned char x, unsigned char dat)
{
if(x<8) 
  LCD_Write_Char(x,0,dat);
 else
  LCD_Write_Char(x-8,1,dat);
}



/*-------------------------------
          打印字符串
--------------------------------*/
void printf_str(unsigned char x,unsigned char *s)
{
while(*s)
 {
  print(x,*s);
  x++;
  s++;
  x%=16;  //超过长度时，回行首继续打印
 }
 }



/*-------------------------------
          打印字符串2 可以指定最多打印的字符数
a 起始的打印位置
n 打印字符串长度
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
  x%=16;  //超过长度时，回行首继续打印
 }
 }


*/
