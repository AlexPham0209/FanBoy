#include "MBC.h"

MBC::MBC(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header) : rom(rom), ram(ram), header(header) {}

MBC0::MBC0(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header) : MBC(rom, ram, header) {}

//For ROM only Cartridges, the MMU directly maps the address between 0000 - 7FFF given to the ROM on the cartridge
unsigned char MBC0::readByte(unsigned short address) {
	return rom[address];
}

//Since There is no writable external RAM, we return null
unsigned char MBC0::writeByte(unsigned short address, unsigned char val) {
	return NULL;
}

//For ROM only Cartridges, the MMU directly maps the address between 0000 - 7FFF given to the ROM on the cartridge
unsigned short MBC0::readShort(unsigned short address) {
	return rom[address] | (rom[address + 1] << 8);
};

//Since There is no writable external RAM, we return null
unsigned short MBC0::writeShort(unsigned short address, unsigned short val) {
	return NULL;
};