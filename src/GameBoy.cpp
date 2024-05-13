#include "GameBoy.h"
#include <iostream>

GameBoy::GameBoy() : memory(Memory()), mCPU(CPU(memory)) {}

void GameBoy::emulate() {
	//Set value at address 0x101B to 0x26.
	memory.writeByte(0x101B, 0x26);

	//Set B to 0xF
	memory.writeByte(0x100, 0x06);
	memory.writeByte(0x101, 0x0F);

	//Set H to 0x10
	memory.writeByte(0x102, 0x26);
	memory.writeByte(0x103, 0x10);

	//Set L to 0x1B
	memory.writeByte(0x104, 0x2E);
	memory.writeByte(0x105, 0x1B);

	//Set B to val in address 0x101B
	memory.writeByte(0x106, 0x46);
	memory.writeByte(0x107, 0x48);


	//Set B to 0xF
	memory.writeByte(0x108, 0x06);
	memory.writeByte(0x109, 0x09);

	//Writing val of B into address 
	memory.writeByte(0x10A, 0x70);


	std::cout << (int)memory.readByte(0x101B) << std::endl;
	mCPU.run(7);
}

void GameBoy::emulate(int iterations) {
	mCPU.run(iterations);
}

void GameBoy::write(unsigned short address, unsigned char val) {
	memory.writeByte(address, val);
}

void GameBoy::clear() {
	memory.clear();
}

unsigned char GameBoy::read(unsigned short address) {
	return memory.readByte(address);
}
