#pragma once
#include <corecrt_memory.h>

class Memory {
public:
	unsigned char readByte(unsigned short address);
	unsigned short readShort(unsigned short address);
	unsigned char writeByte(unsigned short address, unsigned char val);
	unsigned short writeShort(unsigned short address, unsigned short val);
	void clear();

private:
	unsigned char ram[0xFFFF];
};