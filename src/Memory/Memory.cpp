#include "Memory.h"
#include "../Joypad.h"

//This class represents the Memory Management Unit inside of the Gameboy.  
//The Memory Management Unit is a component that translates virtual memory address stored inside of a register into the physical location on the various Memory units in the Gameboy
Memory::Memory(Cartridge* cartridge, Joypad& joypad) : cartridge(cartridge), joypad(joypad) {
	wRam.resize(0x1FFF + 1);
	vRam.resize(0x1FFF + 1);
	io.resize(0xFF + 1);
	hRam.resize(0xFF + 1);
	oam.resize(0xFF + 1);
}

Memory::Memory(Joypad& joypad) : cartridge(nullptr), joypad(joypad) {
	wRam.resize(0x1FFF + 1);
	vRam.resize(0x1FFF + 1);
	io.resize(0x7F + 1);
	hRam.resize(0x7F + 1);
	oam.resize(0xFF + 1);
}

//Reads byte value at address
unsigned char Memory::readByte(unsigned short address) {
	//Boot ROM (Only reads from boot rom during the beginning when Boot Rom Register (FF50) is set to 0)
	if (address < 0x100 && !(readByte(0xFF50) & 1))
		return bootRom[address];

	//External Cartridge ROM 
	if (address <= 0x7FFF) 
		return cartridge->readByte(address);
	
	//8 KB of Video RAM
	if (address >= 0x8000 && address <= 0x9FFF)
		return vRam[address - 0x8000];

	//External cartridge RAM
	if (address >= 0xA000 && address <= 0xBFFF)
		return cartridge->readByte(address);

	//8 KB of Work RAM (Combined two WRAM components into one vector data structure)
	if (address >= 0xC000 && address <= 0xDFFF)
		return wRam[address - 0xC000];

	//Echo RAM region (Memory from regions E000-FDFF are mirrored in regions C000-DDFF)
	if (address >= 0xE000 && address <= 0xFDFF)
		return wRam[address - 0xE000];

	//Object Attribute Memory 
	if (address >= 0xFE00 && address <= 0xFE9F)
		return oam[address - 0xFE00];

	//Invalid region 
	if (address >= 0xFEA0 && address <= 0xFEFF)
		return NULL;

	//Joypad input register data
	if (address == 0xFF00)
		return joypad.readByte();
	
	//Mapped IO registers (Memory address space shared between the CPU and IO devices like joypads and PPU)
	if (address >= 0xFF00 && address <= 0xFF7F)
		return io[address - 0xFF00];

	//High RAM (Allows for faster access to memory from the CPU)
	if (address >= 0xFF80 && address <= 0xFFFE)
		return hRam[address - 0xFF80];
	
	//Interrupt register
	if (address == 0xFFFF)
		return interruptEnable;

 	return NULL;
}

//Writes byte value into memory address
void Memory::writeByte(unsigned short address, unsigned char val) {
	//Printing out data written in Serial Port
	if (address == 0xFF02 && val == 0x81)
		std::cout << readByte(0xFF01);

	//Writing into the ROM (Invalid but is handled by individual Cartridge MBC)
	if (address <= 0x7FFF)
		cartridge->writeByte(address, val);

	//8 KB of Video RAM
	if (address >= 0x8000 && address <= 0x9FFF) 
		vRam[address - 0x8000] = val;

	//Writing into Cartridge's external RAM (If it has some)
	if (address >= 0xA000 && address <= 0xBFFF)
		cartridge->writeByte(address, val);

	//8 KB of Work RAM (Combined two WRAM components into one vector data structure)
	if (address >= 0xC000 && address <= 0xDFFF) 
		wRam[address - 0xC000] = val;

	//Echo RAM region (Memory from regions E000-FDFF are mirrored in regions C000-DDFF in WRAM)
	if (address >= 0xE000 && address <= 0xFDFF) 
		wRam[address - 0xE000] = val;

	//Object Attribute Memory (Section of memory inside of )
	if (address >= 0xFE00 && address <= 0xFE9F) 
		oam[address - 0xFE00] = val;

	//Invalid region 
	if (address >= 0xFEA0 && address <= 0xFEFF)
		return;

	//Writing in Joypad IO register (only in bits 5 and 6) 
	if (address == 0xFF00)
		joypad.writeByte(val);

	//OAM DAA transfer (Transfers 160 bytes of data in Work RAM starting at XX00 to OAM)
	if (address == 0xFF46) {
		for (int i = 0; i < 0xA0; ++i) {
			unsigned short temp = readByte((val << 8) + i);
			writeByte(0xFE00 + i, temp);
		}
	}

	//Mapped IO registers (Memory address space shared between the CPU and IO devices like joypads and PPU)
	if (address >= 0xFF00 && address <= 0xFF7F) 
		io[address - 0xFF00] = val;

	//High RAM (Allows for faster access to memory from the CPU)
	if (address >= 0xFF80 && address <= 0xFFFE)
		hRam[address - 0xFF80] = val;

	//Interrupt Enable Register
	if (address == 0xFFFF)
		interruptEnable = val;

}

//Reads byte values inside address i and address i + 1 then merges them into a short (little endian)
unsigned short Memory::readShort(unsigned short address) {
	return readByte(address) | (readByte(address + 1) << 8);
}

//Writes short value into memory address i and i + 1 (little endian)
void Memory::writeShort(unsigned short address, unsigned short val) {
	unsigned short temp = readByte(address) | readByte(address + 1) << 8;
	writeByte(address, val & 0x00FF);
	writeByte(address + 1, (val & 0xFF00) >> 8);
}

void Memory::loadCartridge(Cartridge* cartridge) {
	this->cartridge = cartridge;
}

void Memory::reset() {
	wRam.clear();
	vRam.clear();
	io.clear();
	hRam.clear();
	oam.clear();
}