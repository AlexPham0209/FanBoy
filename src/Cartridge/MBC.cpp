#include "MBC.h"

MBC::MBC(unsigned char romBankSize, unsigned char ramBankSize, std::vector<unsigned char> rom, std::vector<unsigned char> ram) : 
	romBankSize(romBankSize), ramBankSize(ramBankSize), rom(rom), ram(ram) {}

MBC0::MBC0(unsigned char romBankSize, unsigned char ramBankSize, std::vector<unsigned char> rom, std::vector<unsigned char> ram) :
	MBC(romBankSize, ramBankSize, rom, ram) {
}

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