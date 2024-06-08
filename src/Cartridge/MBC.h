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
};

//ROM Only Cartridge type
//Directly maps address 0000-7FFF in the Gameboy's memory to the ROM in the Cartridge 
class MBC0 : public MBC {
public:
	MBC0(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header);
	unsigned char readByte(unsigned short address) override;
	void writeByte(unsigned short address, unsigned char val) override;
};

//Memory Bank Controller 1 Cartridge type
class MBC1 : public MBC {
public:
	MBC1(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header);
	unsigned char readByte(unsigned short address) override;
	void writeByte(unsigned short address, unsigned char val) override;

private:
	unsigned short romBank = 1;
	unsigned short ramBank = 1;
	bool ramEnable = false;
	bool bankingMode = true;
};

class MBC2 : public MBC {
public:
	MBC2(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header);
	unsigned char readByte(unsigned short address) override;
	void writeByte(unsigned short address, unsigned char val) override;

private:
	unsigned short romBank = 1;
	unsigned short ramBank = 1;
	bool ramEnable = false;
	bool bankingMode = true;
};


class MBC3 : public MBC {
public:
	MBC3(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header);
	unsigned char readByte(unsigned short address) override;
	void writeByte(unsigned short address, unsigned char val) override;

private:
	unsigned short romBank = 1;
	unsigned short ramBank = 1;
	unsigned short rtc = 0;
	bool ramEnable = false;
	bool bankingMode = true;
};