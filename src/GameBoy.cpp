#include "GameBoy.h"
#include <iostream>

GameBoy::GameBoy() : memory(Memory()), mCPU(CPU(memory)) {

}

void GameBoy::emulate() {
	//Set value at address 0x101B to 0x26.
	memory.write(0x101B, 0x26);

	//Set B to 0xF
	memory.write(0x100, 0x06);
	memory.write(0x101, 0x0F);

	//Set H to 0x10
	memory.write(0x102, 0x26);
	memory.write(0x103, 0x10);

	//Set L to 0x1B
	memory.write(0x104, 0x2E);
	memory.write(0x105, 0x1B);

	//Set B to val in address 0x101B
	memory.write(0x106, 0x46);
	memory.write(0x107, 0x48);

	
	//Set B to 0xF
	memory.write(0x108, 0x06);
	memory.write(0x109, 0x09);

	//Writing val of B into address 
	memory.write(0x10A, 0x70);


	mCPU.step();
	mCPU.step();
	mCPU.step();
	mCPU.step();
	mCPU.step();
	mCPU.step();
	mCPU.step();

	std::cout << (int)memory.read(0x101B) << std::endl;
}
