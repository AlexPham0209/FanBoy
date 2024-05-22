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

public:
	MBC memory;
	Header header;

	Cartridge(Header header, MBC memory);
	std::string getInfo();

};