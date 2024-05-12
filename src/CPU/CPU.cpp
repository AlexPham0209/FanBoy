#include "CPU.h"
#include <iostream>

CPU::CPU(Memory& memory) : memory(memory) {
	pc = 0x100;
	sp = 0xFFFE;

	A = 0x0000;
	B = 0x0000;
	C = 0x0000;
	D = 0x0000;
	E = 0x0000;
	F = 0x0000;
	H = 0x0000;
	L = 0x0000;

	cycles = 0;
}

int CPU::step() {
	cycles = 0;
	unsigned char opcode = fetchOpcode();
	executeOpcode(opcode);
	std::cout << "reg b: " << (int)(this->B) << std::endl;
	return cycles;
}

void CPU::executeOpcode(unsigned char opcode) {
	switch (opcode) {
	case 0x06:
		std::cout << "load b" << std::endl;
		LDNN(B, memory.read(pc++), cycles);
		break;
	case 0x0E:
		LDNN(C, memory.read(pc++), cycles);
		break;
	case 0x16:
		LDNN(D, memory.read(pc++), cycles);
		break;
	case 0x1E:
		LDNN(E, memory.read(pc++), cycles);
		break;
	case 0x26:
		LDNN(H, memory.read(pc++), cycles);
		break;
	case 0x2E:
		LDNN(L, memory.read(pc++), cycles);
		break;

	}
}

void CPU::LDNN(unsigned char& reg, const unsigned char& val, int& cycles) {
	reg = val;
	cycles += 8;
}


unsigned char CPU::fetchOpcode() {
	return memory.read(pc++);
}

