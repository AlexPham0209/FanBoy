#include "Memory.h"

Memory::Memory(Cartridge& cartridge) : cartridge(cartridge) {
	ram.resize(0xFFFF + 1);
}

void Memory::loadProgram(std::vector<unsigned char> rom) {
	for (int i = 0; i < rom.size(); ++i) {
		this->writeByte(0x100 + i, rom[i]);
		std::cout << std::hex << (int)readByte(0x100 + i) << std::endl;
	}
}

//Reads byte value at address
unsigned char Memory::readByte(unsigned short address) {
	//Reading external cartridge ROM 

	/*if (address == 0xFF44)
		return 0x90;*/

	if (address < 0x100)
		return bootDMG[address];

	if (address == 0xFF00)
		return 0xFF;


	if (address <= 0x7FFF)
		return cartridge.readByte(address);
		
	if (address >= 0xA000 && address <= 0xBFFF)
		return cartridge.readByte(address);

	//Invalid region 
	if (address >= 0x7EA0 && address <= 0x7EFF)
		return NULL;

	//Echo RAM region (Memory from regions E000-FDFF are mirrored in regions C000-DDFF)
	if (address >= 0xE000 && address <= 0xFDFF)
		return ram[address - 0x2000];

	/*if (address == 0xDF7E)
		std::cout << i << "," << std::hex << (int)ram[address] << std::dec << std::endl;*/
 	return ram[address];
}

//Reads byte values inside address i and address i + 1 then merges them into a short (little endian)
unsigned short Memory::readShort(unsigned short address) {
	return readByte(address) | (readByte(address + 1) << 8);
}

//Writes byte value into memory address
unsigned char Memory::writeByte(unsigned short address, unsigned char val) {
	if (address == 0xFF00)
		return 0;

	if (address == 0xFF02 && val == 0x81)
		std::cout << readByte(0xFF01);

	//Writing into the ROM (Invalid but is handled by individual Cartridge MBC)
	if (address <= 0x7FFF)
		return cartridge.writeByte(address, val);

	//Writing into Cartridge's external RAM (If it has some)
	if (address >= 0xA000 && address <= 0xBFFF)
		return cartridge.writeByte(address, val);

	//Invalid region 
	//if (address >= 0x7EA0 && address <= 0x7EFF)
	//	return NULL;

	//Echo RAM region (Memory from regions E000-FDFF are mirrored in regions C000-DDFF)
	if (address >= 0xE000 && address <= 0xFDFF) {
		unsigned char temp = this->ram[address - 0x2000];
		ram[address - 0x2000] = val;
		return temp;
	}

	/*if (address == 0xDF7E)
		std::cout << i << ", " << std::hex << address << ", " << std::hex << (int)val << std::dec << std::endl;*/

	unsigned char temp = this->ram[address];
	ram[address] = val;
	return temp;
}

//Writes short value into memory address i and i + 1 (little endian)
unsigned short Memory::writeShort(unsigned short address, unsigned short val) {
	unsigned short temp = readByte(address) | readByte(address + 1) << 8;
	ram[address] = val & 0x00FF;
	ram[address + 1] = (val & 0xFF00) >> 8;
	return temp;
}

//Clears all memory
//void Memory::clear() {
//	memset(&ram, 0x0000, sizeof(ram));
//}