#pragma once
#include <fstream>
#include <vector>
#include "MBC.h"

struct Header {
	std::string title;
	std::string license;
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

	Cartridge(const char* path);
	Cartridge(Header header, MBC memory);

};