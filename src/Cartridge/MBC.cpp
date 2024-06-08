#include "MBC.h"

MBC::MBC(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header) : rom(rom), ram(ram), header(header) {}

MBC0::MBC0(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header) : MBC(rom, ram, header) {}

MBC1::MBC1(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header) : MBC(rom, ram, header) {}

MBC2::MBC2(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header) : MBC(rom, ram, header) {}

MBC3::MBC3(std::vector<unsigned char> rom, std::vector<unsigned char> ram, Header& header) : MBC(rom, ram, header) {}

//For ROM only Cartridges, the MMU directly maps the address between 0000 - 7FFF given to the ROM on the cartridge
unsigned char MBC0::readByte(unsigned short address) {
	return rom[address];
}

//Since There is no writable external RAM, we return null
void MBC0::writeByte(unsigned short address, unsigned char val) {
	return;
}

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
		ramBank = val & 0x03;
		return;
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


unsigned char MBC2::readByte(unsigned short address) {
	//ROM Bank 0 
	if (address <= 0x3FFF)
		return rom[address];

	//ROM Banks 1 - 7F
	if (address >= 0x4000 && address <= 0x7FFF) {
		int target = (romBank * 0x4000) + (address - 0x4000);
		return rom[target];
	}

	//RAM Banks
	if (address >= 0xA000 && address <= 0xA1FF) {
		if (!ramEnable)
			return 0xFF;

		return ram[address];
	}
}

void MBC2::writeByte(unsigned short address, unsigned char val) {
	//Set RAM Enable
	if (address <= 0x3FFF) {
		bool enable = (address >> 8) & 1;

		if (!enable) {
			ramEnable = (val == 0x0A);
			return;
		}
		
		romBank = std::max(1, (val & 0xF));
	}
	
	//Write into RAM Bank
	if (address >= 0xA000 && address <= 0xA1FF) {
		if (!ramEnable)
			return;
		ram[address] = val;
	}
}


unsigned char MBC3::readByte(unsigned short address) {
	//ROM Bank 0 
	if (address <= 0x3FFF)
		return rom[address];

	//ROM Banks 1 - 7F
	if (address >= 0x4000 && address <= 0x7FFF) {
		int target = (romBank * 0x4000) + (address - 0x4000);
		return rom[target];
	}

	//RAM Banks 0 - 3
	if (address >= 0xA000 && address <= 0xBFFF) {
		if (!ramEnable)
			return 0xFF;

		int target = (ramBank * 0x2000) + (address - 0xA000);
		return ram[target];
	}
}

void MBC3::writeByte(unsigned short address, unsigned char val) {
	//Set RAM and Timer Enable
	if (address <= 0x1FFF) {
		if (val == 0xA)
			ramEnable = true;
		else if (val == 0x0)
			ramEnable = false;
	}

	//Set ROM Bank Number
	if (address >= 0x2000 && address <= 0x3FFF)
		romBank = std::max(1, (val & 0x7F));

	//Select RAM Bank Number or RTC Register select
	if (address >= 0x4000 && address <= 0x5FFF) {
		if (val <= 0x3) {
			bankingMode = true;
			ramBank = val;
			return;
		}

		else if (val >= 0x8 && val <= 0xC) 
			bankingMode = false;
	}

	//Write into RAM Bank
	if (address >= 0xA000 && address <= 0xBFFF) {
		if (!ramEnable || !bankingMode)
			return;
		
		int target = (ramBank * 0x2000) + (address - 0xA000);
		ram[target] = val;
	}
}