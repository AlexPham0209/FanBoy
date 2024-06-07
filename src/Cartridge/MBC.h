#pragma once
#include <vector>
#include <iostream>
#include "Header.h"

//Base class used for all memory bank controller types
class MBC {
protected:
	std::vector<unsigned char> rom;
	std::vector<unsigned char> ram;
	Header& header;

public:
	MBC(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header);
	virtual unsigned char readByte(unsigned short address) = 0;
	virtual void writeByte(unsigned short address, unsigned char val) = 0;
		
	virtual unsigned short readShort(unsigned short address) = 0;
	virtual void writeShort(unsigned short address, unsigned short val) = 0;
};

//ROM Only Cartridge type
//Directly maps address 0000-7FFF in the Gameboy's memory to the ROM in the Cartridge 
class MBC0 : public MBC {
public:
	MBC0(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header);
	unsigned char readByte(unsigned short address) override;
	void writeByte(unsigned short address, unsigned char val) override;

	unsigned short readShort(unsigned short address) override;
	void writeShort(unsigned short address, unsigned short val) override;
};

//Memory Bank Controller 1 Cartridge type

class MBC1 : public MBC {
	MBC1(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header);
	unsigned char readByte(unsigned short address) override;
	void writeByte(unsigned short address, unsigned char val) override;

	unsigned short readShort(unsigned short address) override;
	void writeShort(unsigned short address, unsigned short val) override;
};