#pragma once
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include "MBC.h"
#include "Header.h"

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

class Cartridge {
private:
	std::vector<unsigned char> ROM;
	MBC& memory;
	Header& header;

public:
	Cartridge(Header& header, MBC& memory);
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