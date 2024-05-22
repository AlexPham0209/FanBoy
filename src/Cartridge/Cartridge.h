#pragma once
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include "MBC.h"

struct Header {
	std::string title;
	std::string newLicense;
	char oldLicense;
	unsigned char version;
	unsigned char SGBFlag;
	int romSize;
	int ramSize;
};

class Cartridge {
private:
	std::vector<unsigned char> ROM;
	MBC& memory;
	Header& header;

public:
	Cartridge(Header& header, MBC& memory);
	Cartridge();
	~Cartridge() {
		delete &memory;
		delete &header;
	}

	unsigned char readByte(unsigned short address);
	unsigned char writeByte(unsigned short address, unsigned char val);

	unsigned short readShort(unsigned short address);
	unsigned short writeShort(unsigned short address, unsigned short val);

	std::string getInfo();

};