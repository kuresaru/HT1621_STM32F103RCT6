#include "ht1621.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#define HT1621_DATADELAY Delay_us(1)
#define HT1621_DAT_SET GPIOA->BSRR = GPIO_Pin_0
#define HT1621_DAT_CLR GPIOA->BRR = GPIO_Pin_0
#define HT1621_CS_SET GPIOA->BSRR = GPIO_Pin_1
#define HT1621_CS_CLR GPIOA->BRR = GPIO_Pin_1
#define HT1621_WR_SET GPIOA->BSRR = GPIO_Pin_2
#define HT1621_WR_CLR GPIOA->BRR = GPIO_Pin_2
#define HT1621_RD_SET GPIOA->BSRR = GPIO_Pin_3
#define HT1621_RD_CLR GPIOA->BRR = GPIO_Pin_3

void HT1621_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    HT1621_CS_SET;
    HT1621_WR_SET;
    HT1621_RD_SET;

    HT1621_DATADELAY;

    HT1621_Cmd(0x52);//4个公共口,1/3偏压
    HT1621_Cmd(0x30);//系统时钟片内RC
    HT1621_Cmd(0x00);//关闭系统振荡器和LCD偏压发生器
    HT1621_Cmd(0x0A);//WDT 溢出标志输出失效
    HT1621_Cmd(0x02);//打开系统振荡器
    HT1621_Cmd(0x06);//打开LCD输出
}

void HT1621_Cls() {
    u8 tmp[16], i;
    for (i = 0; i < 16; i++) {
        tmp[i] = 0;
    }
    HT1621_Write(0, tmp, 16);
}

void HT1621_SetBit(u8 dat) {
    if (dat) {
        HT1621_DAT_SET;
    } else {
        HT1621_DAT_CLR;
    }
    HT1621_DATADELAY;
}

void HT1621_SetWrite() {
    HT1621_WR_CLR;
    HT1621_DATADELAY;
    HT1621_WR_SET;
    HT1621_DATADELAY;
}

void HT1621_Cmd(u8 cmd) {
    u8 tmp, i;
    tmp = 0x80;
    HT1621_CS_CLR;
    HT1621_DATADELAY;
    for (i = 0; i < 4; i++) {
        HT1621_SetBit(tmp & 0x80);
        HT1621_SetWrite();
        tmp <<= 1;
    }
    tmp = cmd;
    for (i = 0; i < 8; i++) {
        HT1621_SetBit(tmp & 0x80);
        HT1621_SetWrite();
        tmp <<= 1;
    }
    HT1621_CS_SET;
    HT1621_DATADELAY;
}

void HT1621_WriteOne(u8 addr, u8 dat) {
    u8 i, j, tmp = 0xA0;
    HT1621_CS_CLR;
    HT1621_DATADELAY;
    for (i = 0; i < 3; i++) {
        HT1621_SetBit(tmp & 0x80);
        HT1621_SetWrite();
        tmp <<= 1;
    }
    tmp = addr << 2;
    for (i = 0; i < 6; i++) {
        HT1621_SetBit(tmp & 0x80);
        HT1621_SetWrite();
        tmp <<= 1;
    }
    for (i = 0; i < 8; i++) {
        HT1621_SetBit(dat & 0x80);
        HT1621_SetWrite();
        dat <<= 1;
    }
    HT1621_CS_SET;
    HT1621_DATADELAY;
}

void HT1621_Write(u8 addr, u8* dat, u8 len) {
    u8 i, j, tmp = 0xA0;
    HT1621_CS_CLR;
    HT1621_DATADELAY;
    for (i = 0; i < 3; i++) {
        HT1621_SetBit(tmp & 0x80);
        HT1621_SetWrite();
        tmp <<= 1;
    }
    tmp = addr << 2;
    for (i = 0; i < 6; i++) {
        HT1621_SetBit(tmp & 0x80);
        HT1621_SetWrite();
        tmp <<= 1;
    }
    for (j = 0; j < len; j++) {
        tmp = dat[j];
        for (i = 0; i < 8; i++) {
            HT1621_SetBit(tmp & 0x80);
            HT1621_SetWrite();
            tmp <<= 1;
        }
    }
    HT1621_CS_SET;
    HT1621_DATADELAY;
}

void HT1621_Set(u8 pos, u8 dat) {
    if (pos < 3) {
        HT1621_WriteOne(pos * 2, dat);
    } else if (pos == 3) {
    } else {
        HT1621_WriteOne(pos * 2 + 3, dat);
    }
}