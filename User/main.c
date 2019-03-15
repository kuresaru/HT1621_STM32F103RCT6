#include "ht1621.h"

int main (void) {
	HT1621_Init();
	HT1621_Cls();
	// HT1621_Set(0, 0xFF);
	// HT1621_Set(1, 0xFF);
	// HT1621_Set(2, 0xFF);
	// HT1621_Set(4, 0xFF);
	// HT1621_Set(5, 0xFF);
	// HT1621_Set(6, 0xFF);
	// HT1621_Set(7, 0xFF);
	u8 data[16], i;
	for (i = 0; i < 16; i++) {
		data[i] = 0xFF;
	}
	HT1621_Write(0, data, 16);
	while(1);
}
