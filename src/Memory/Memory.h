#pragma once
#include <corecrt_memory.h>

class Memory {
public:
	unsigned char readByte(unsigned short address);
	unsigned char readShort(unsigned short address);
	void writeByte(unsigned short address, unsigned char val);
	void writeShort(unsigned short address, unsigned short val);
	void clear();

private:
	unsigned char ram[8192];
};