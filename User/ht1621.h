#include "stm32f10x.h"
#include "common.h"

void HT1621_Init();
void HT1621_Cls();
void HT1621_WriteOne(u8 addr, u8 dat);
void HT1621_Write(u8 addr, u8* dat, u8 len);
void HT1621_Set(u8 pos, u8 dat);
