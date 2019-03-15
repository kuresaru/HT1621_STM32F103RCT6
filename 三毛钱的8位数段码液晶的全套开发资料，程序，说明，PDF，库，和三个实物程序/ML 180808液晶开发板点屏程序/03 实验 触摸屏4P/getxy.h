/*---------------------------

 四线式电阻触摸屏
 单片机读取座标模块 v1.00
 诗织崎缘@淘宝店
 2013-7-11

 调用方法：
 在程序中写 getxy(&x, &y)
 就可以从x, y中得到座标，
 就象判断独立按键一样操作

----------------------------*/

//-----------------------
//新一代 1T 8051系列 单片机I/O 口特殊功能寄存器
//                                      7     6     5     4     3     2     1     0         Reset Value
sfr P0M0 = 0x94; //                                                                         0000,0000
sfr P0M1 = 0x93; //                                                                         0000,0000
sfr P1M0 = 0x92; //                                                                         0000,0000
sfr P1M1 = 0x91; //                                                                         0000,0000
sfr P2M0 = 0x96; //                                                                         0000,0000
sfr P2M1 = 0x95; //                                                                         0000,0000
sfr P3M0 = 0xB2; //                                                                         0000,0000
sfr P3M1 = 0xB1; //                                                                         0000,0000
sfr P4   = 0xC0; //8 bitPort4          P4.7  P4.6  P4.5  P4.4  P4.3  P4.2  P4.1  P4.0       1111,1111
sfr P4M0 = 0xB4; //                                                                         0000,0000
sfr P4M1 = 0xB3; //                                                                         0000,0000
//                                      7      6         5         4      3     2     1     0     Reset Value
sfr P4SW = 0xBB; //Port-4 switch	    -   LVD_P4.6  ALE_P4.5  NA_P4.4   -     -     -     -	    x000,xxxx

sfr P5   = 0xC8; //8 bitPort5           -     -       -      -    P5.3  P5.2  P5.1  P5.0    xxxx,1111
sfr P5M0 = 0xCA; //                                                                         0000,0000
sfr P5M1 = 0xC9; //                                                                         0000,0000
//--------------------------------------------------------------------------------



//--------------
//四线电阻屏 IO
//--------------
sbit x0=P2^2;       //x+
sbit x1=P1^0;       //x-
sbit y0=P2^3;       //y+
sbit y1=P1^1;       //y-



/*Declare SFR associated with the ADC */
sfr ADC_CONTR   =   0xBC;           //ADC control register
sfr ADC_RES     =   0xBD;           //ADC high 8-bit result register
sfr ADC_LOW2    =   0xBE;           //ADC low 2-bit result register
sfr P1ASF       =   0x9D;           //P1 secondary function control register

/*Define ADC operation const for ADC_CONTR*/
#define ADC_POWER   0x80            //ADC power control bit
#define ADC_FLAG    0x10            //ADC complete flag
#define ADC_START   0x08            //ADC start control bit
#define ADC_SPEEDLL 0x00            //420 clocks
#define ADC_SPEEDL  0x20            //280 clocks
#define ADC_SPEEDH  0x40            //140 clocks
#define ADC_SPEEDHH 0x60            //70 clocks

unsigned char ad(unsigned char ch);
void Delay(unsigned int n);



/*----------------------------
Get ADC result
----------------------------*/
unsigned char ad(unsigned char ch)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //Must wait before inquiry
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//Wait complete flag
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

//    return ADC_RES;                 //Return ADC result
    return ( ADC_RES);                 //Return ADC result

}



/*----------------------------
Initial ADC sfr
----------------------------*/
void InitADC0()
{
//    P1ASF = 0xff;                   //Open 8 channels ADC function
    P1ASF = 0x01;                   //P1.0 

    ADC_RES = 0;                    //Clear previous result
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay(2);                       //ADC power-on and delay
}









/*----------------------------
Initial ADC sfr
----------------------------*/
void InitADC1()
{
//    P1ASF = 0xff;                   //Open 8 channels ADC function
    P1ASF = 0x02;                   //P1.1

    ADC_RES = 0;                    //Clear previous result
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay(2);                       //ADC power-on and delay
}





/*----------------------------
Initial ADC sfr
----------------------------*/
void CloseADC()
{
//    P1ASF = 0xff;                   //Open 8 channels ADC function
    P1ASF = 0x00;                   //P1.0 

    ADC_RES = 0;                    //Clear previous result
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay(2);                       //ADC power-on and delay
}





/*----------------------------
Software delay function
----------------------------*/
void Delay(unsigned int n)
{
    unsigned int x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}





/*-----------------------------------------
             获取触摸屏座标
-----------------------------------------*/
void getxy(unsigned char *x, unsigned char *y)
{
P2M0|=0x0c;          //开漏   这段可实际应用中，应该和1.0 1.1置1放初始化中
P2M1|=0x0c;           

P1M0=0x03;        //p0.0 p0.1 推挽    此片是 x-, y- 的两个引脚，工作在PP模式下


 InitADC0();
 x0=1;
 y0=0;

// y1=1;         //如果程序中没有改变x1, y1的值，这两句可以忽略
 *y=ad(0);
 CloseADC();


 InitADC1();
 y0=1;
 x0=0;

// x1=1;
 *x=ad(1);
 CloseADC();
 
// if(*y<20) { *x=0; *y=0; } //抗干扰
// if(*x<25) { *x=0; *y=0; } //抗干扰
}