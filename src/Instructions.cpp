#include "CPU.h"
void LDNN(unsigned char& reg, const unsigned char& val, int& cycles) {
	reg = val;
	cycles += 8;
}