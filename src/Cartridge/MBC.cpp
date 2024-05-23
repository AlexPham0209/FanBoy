#include "MBC.h"

MBC::MBC(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header) : rom(rom), ram(ram), header(header) {}

MBC0::MBC0(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header) : MBC(rom, ram, header) {}


unsigned char MBC0::readByte(unsigned short address) {
	return rom[address];
}

unsigned char MBC0::writeByte(unsigned short address, unsigned char val) {
	return NULL;
}

unsigned short MBC0::readShort(unsigned short address) {
	return this->rom[address] | (this->rom[address + 1] << 8);
};

unsigned short MBC0::writeShort(unsigned short address, unsigned short val) {
	return NULL;
};