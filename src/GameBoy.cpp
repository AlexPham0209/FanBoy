#include "GameBoy.h"

GameBoy::GameBoy() : memory(Memory()), mCpu(CPU(memory)) {
}

void GameBoy::loadGame(const char* rom) {

}

void GameBoy::emulate() {
	memory.write(0x100, 0x06);
	memory.write(0x101, 0x0F);
	mCpu.step();
}
