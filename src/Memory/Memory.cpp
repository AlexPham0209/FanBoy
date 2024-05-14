#include "Memory.h"
#include <iostream>

unsigned char Memory::readByte(unsigned short address) {
	if (address >= sizeof(ram) / sizeof(unsigned char) || address < 0)
		return 0;

	return this->ram[address];
}

unsigned short Memory::readShort(unsigned short address) {
	if (address + 1 >= sizeof(ram) / sizeof(unsigned char) || address + 1 < 0)
		return 0;

	return (this->ram[address] << 8) | this->ram[address + 1];
}

unsigned char Memory::writeByte(unsigned short address, unsigned char val) {
	if (address >= sizeof(ram) / sizeof(unsigned char) || address < 0)
		return 0;

	unsigned char temp = this->ram[address];
	this->ram[address] = val;
	return temp;
}

unsigned short Memory::writeShort(unsigned short address, unsigned short val) {
	if (address + 1 >= sizeof(ram) / sizeof(unsigned char) || address + 1 < 0)
		return 0;

	unsigned short temp = (this->ram[address] << 8) | this->ram[address + 1];
	this->ram[address] = (val & 0xFF00) >> 8;
	this->ram[address + 1] = val & 0x00FF;
	return temp;
}

void Memory::clear() {
	memset(ram, 0x0000, sizeof(ram));
}