#include "MBC.h"

MBC::MBC(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header) : rom(rom), ram(ram), header(header) {}

MBC0::MBC0(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header) : MBC(rom, ram, header) {}

MBC1::MBC1(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header) : MBC(rom, ram, header) {

}

//For ROM only Cartridges, the MMU directly maps the address between 0000 - 7FFF given to the ROM on the cartridge
unsigned char MBC0::readByte(unsigned short address) {
	return rom[address];
}

//Since There is no writable external RAM, we return null
void MBC0::writeByte(unsigned short address, unsigned char val) {
	return;
}

//For ROM only Cartridges, the MMU directly maps the address between 0000 - 7FFF given to the ROM on the cartridge
unsigned short MBC0::readShort(unsigned short address) {
	return rom[address] | (rom[address + 1] << 8);
};

//Since There is no writable external RAM, we return null
void MBC0::writeShort(unsigned short address, unsigned short val) {
	return;
};

unsigned char MBC1::readByte(unsigned short address) {
	//ROM Bank 0 
	if (address <= 0x3FFF) 
		return rom[address];
	
	//ROM Banks 1 - 7F
	if (address >= 0x4000 && address <= 0x7FFF) {
		int target = (romBank * 0x4000) + (address - 0x4000);
		return rom[target];
	}

	//RAM Banks 0 - 3
	if (address >= 0xA000 && address <= 0xBFFF && ramEnable) {
		if (!ramEnable)
			return 0xFF;

		int target = (ramBank * 0x2000) + (address - 0xA000);
		return ram[target];
	}
}

void MBC1::writeByte(unsigned short address, unsigned char val) {
	//Set RAM Enable
	if (address <= 0x1FFF) 
		ramEnable = true;

	//Set ROM Bank Number
	if (address >= 0x2000 && address <= 0x3FFF) 
		romBank = std::max(1, (val & 0x1F));
	
	//Set RAM Bank Number or Upper Bits of ROM Bank
	if (address >= 0x4000 && address <= 0x5FFF) {
		int bank = (val & 0xC0) >> 6;
		ramBank = bank;
	}
	//Select Banking Mode
	//0 - Locked to bank 0 
	//1 - Allows bank switching
	if (address >= 0x6000 && address <= 0x7FFF)
		bankingMode = val & 1;

	//Write into RAM Bank
	if (address >= 0xA000 && address <= 0xBFFF && ramEnable) {
		if (!ramEnable)
			return;

		int target = (ramBank * 0x2000) + (address - 0xA000);
		ram[target] = val;
	}
}

void MBC1::writeShort(unsigned short address, unsigned short val) {
	writeByte(address, val & 0x00FF);
	writeByte(address + 1, (val & 0xFF00) >> 8);
}

unsigned short MBC1::readShort(unsigned short address) {
	return readByte(address) | (readByte(address + 1) << 8);
}