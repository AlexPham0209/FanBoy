#pragma once
#include <corecrt_memory.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "../Cartridge/Cartridge.h"


class Memory {
public:
	Memory(const char* path);
	Memory();

	void loadProgram(std::vector<unsigned char> ROM);
	std::vector<unsigned char> loadROM(const char* path);
	unsigned char readByte(unsigned short address);
	unsigned short readShort(unsigned short address);
	unsigned char writeByte(unsigned short address, unsigned char val);
	unsigned short writeShort(unsigned short address, unsigned short val);
	void clear();

private:
	unsigned char ram[0xFFFF];
};