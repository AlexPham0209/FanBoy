#include "CPUTest.h";
#include "../src/GameBoy.h"
#include <gtest/gtest.h>

unsigned short AddTest(unsigned char& ms, unsigned char& ls, unsigned char instruction, unsigned short val, unsigned short val2, CPU* CPU, Memory* memory) {
	ms = (val2 & 0xFF00) >> 8;
	ls = (val2 & 0xFF);

	CPU->H = (val & 0xFF00) >> 8;
	CPU->L = (val & 0xFF);

	std::vector<unsigned char> instructions = { instruction };
	memory->loadProgram(instructions);
	CPU->run(1);
	unsigned short res = (CPU->H << 8) | CPU->L;
	memory->clear();
	CPU->reset();
	return res;
}
