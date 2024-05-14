#include "GameBoy.h"
#include <iostream>

GameBoy::GameBoy() : memory(Memory()), mCPU(CPU(memory)) {}

void GameBoy::emulate() {
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
