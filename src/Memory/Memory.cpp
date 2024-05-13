#include "Memory.h"
#include <iostream>

unsigned char Memory::readByte(unsigned short address) {
	if (address >= sizeof(ram) / sizeof(unsigned char))
		return 0;

	return this->ram[address];
}

unsigned char Memory::readShort(unsigned short address) {
	if (address + 1 >= sizeof(ram) / sizeof(unsigned char))
		return 0;

	return (this->ram[address] << 8) | this->ram[address + 1];
}

void Memory::writeByte(unsigned short address, unsigned char val) {
	if (address >= sizeof(ram) / sizeof(unsigned char))
		return;

	this->ram[address] = val;
}

void Memory::writeShort(unsigned short address, unsigned short val) {
	if (address + 1 >= sizeof(ram) / sizeof(unsigned char))
		return;

	this->ram[address] = (val & 0xFF00) >> 8;
	this->ram[address + 1] = val & 0x00FF;
}

void Memory::clear() {
	memset(ram, 0x0000, sizeof(ram));
}