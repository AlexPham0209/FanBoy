#include "CPU.h"
#include "Instructions.cpp"
#include <iostream>


CPU::CPU() {
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

	this->memory = memory;
}


CPU::CPU(Memory& memory) {
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

	this->memory = memory;
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
		//LD nn, n
		case 0x06:
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


unsigned char CPU::fetchOpcode() {
	return memory.read(pc++);
}



