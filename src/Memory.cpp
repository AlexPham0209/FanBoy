#include "Memory.h"

unsigned char Memory::read(unsigned short address) {
	return this->ram[address];
}

void Memory::write(unsigned short address, unsigned char val) {
	this->ram[address] = val;
}

void Memory::clear() {
	memset(ram, 0x0000, sizeof(ram));
}
