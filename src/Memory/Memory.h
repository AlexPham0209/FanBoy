#pragma once
#include <corecrt_memory.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include "../Cartridge/Cartridge.h"
#include <map>


class Memory {
public:
	Memory(Cartridge& cartridge);

	void loadProgram(std::vector<unsigned char> rom);
	unsigned char readByte(unsigned short address);
	unsigned short readShort(unsigned short address);
	unsigned char writeByte(unsigned short address, unsigned char val);
	unsigned short writeShort(unsigned short address, unsigned short val);
	void clear();

private:
	Cartridge& cartridge;
	std::vector<unsigned char> ram;
};