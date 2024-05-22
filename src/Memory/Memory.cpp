#include "Memory.h"

Memory::Memory(Cartridge& cartridge) : cartridge(cartridge) {}
//Reads byte value at address
unsigned char Memory::readByte(unsigned short address) {
	if (address >= sizeof(ram) / sizeof(unsigned char) || address < 0)
		return 0;

	return this->ram[address];
}

//Reads byte values inside address i and address i + 1 then merges them into a short (little endian)
unsigned short Memory::readShort(unsigned short address) {
	//Making sure address is not outside of RAM
	if (address + 1 >= sizeof(ram) / sizeof(unsigned char) || address + 1 < 0)
		return 0;


	return this->ram[address] | (this->ram[address + 1] << 8);
}

//Writes byte value into memory address
unsigned char Memory::writeByte(unsigned short address, unsigned char val) {
	if (address >= sizeof(ram) / sizeof(unsigned char) || address < 0)
		return -1;

	////Can't write into read only memory
	//if (address < 0x8000)
	//	return -1;

	////Restricted access
	//if (address >= 0xFEA0 && address < 0xFEFF)
	//	return -1;


	unsigned char temp = this->ram[address];
	this->ram[address] = val;
	return temp;
}

//Writes short value into memory address i and i + 1 (little endian)
unsigned short Memory::writeShort(unsigned short address, unsigned short val) {
	if (address + 1 >= sizeof(ram) / sizeof(unsigned char) || address + 1 < 0)
		return 0;

	unsigned short temp = (this->ram[address] << 8) | this->ram[address + 1];
	this->ram[address] = val & 0x00FF;
	this->ram[address + 1] = (val & 0xFF00) >> 8;
	return temp;
}

//Clears all memory
void Memory::clear() {
	memset(ram, 0x0000, sizeof(ram));
}