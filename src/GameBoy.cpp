#include "GameBoy.h"
#include <iostream>

GameBoy::GameBoy() : memory(Memory()), mCPU(CPU(memory)) {

}

void GameBoy::emulate() {
	memory.write(0x100, 0x06);
	memory.write(0x101, 0x0F);
	mCPU.step();
}
