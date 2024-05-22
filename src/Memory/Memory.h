#pragma once
#include <corecrt_memory.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "../Cartridge/Cartridge.h"
#include <map>

const std::map<unsigned char, const char*> newLicenseCode = {
	{0x00, "NONE"},
	{0x01, "Nintendo Research and Development"},
	{0x08, "Capcom"},
	{0x13, "EA"},
	{0x18, "Hudston Soft"},
	{0x19, "B-AI"},
};

const std::map<unsigned char, std::string> oldLicenseCode = {

};

class Memory {
public:
	Memory(const char* path);
	Memory();

	Memory(Cartridge& cartridge);
	unsigned char readByte(unsigned short address);
	unsigned short readShort(unsigned short address);
	unsigned char writeByte(unsigned short address, unsigned char val);
	unsigned short writeShort(unsigned short address, unsigned short val);
	void clear();

private:
	unsigned char ram[0xFFFF];
	Cartridge& cartridge;
};