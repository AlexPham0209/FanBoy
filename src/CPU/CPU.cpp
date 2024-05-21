#include "CPU.h"
#include <iostream>
#include "OpcodeCycles.h"

CPU::CPU(Memory& memory) : memory(memory), F(FlagRegister()), 
AF(Register16(A, F)), BC(Register16(B, C)), DE(Register16(D, E)), HL(Register16(H, L)), interrupts(Interrupts(this->memory, *this)) {
	pc = 0x100;
	sp = 0xFFFE;

	A = 0x01;
	B = 0x00;
	C = 0x13;
	D = 0x00;
	E = 0xD8;
	F = 0xB0;
	H = 0x01;
	L = 0x4D;

	cycles = 0;
}

int CPU::step() {
	interrupts.handleInterrupts();
	std::cout << "PC: " << pc << std::endl;
	unsigned char opcode = fetchOpcode();
	executeOpcode(opcode);

	std::cout << (int)opcode << std::endl;
	std::cout << "A: " << (int)A << std::endl;
	std::cout << "B: " << (int)B << std::endl;
	std::cout << "C: " << (int)C << std::endl;
	std::cout << "D: " << (int)D << std::endl;
	std::cout << "E: " << (int)E << std::endl;
	std::cout << "F: " << (int)F << std::endl;
	std::cout << "H: " << (int)H << std::endl;
	std::cout << "L: " << (int)L << std::endl;
	std::cout << "Cycles: " << cycles << "\n" << std::endl;

	cycles = opcodeCycles[opcode];
	return cycles;
}

void CPU::run(int iterations) {
	for (int i = 0; i < iterations; ++i)
		step();
}

void CPU::run() {
	while(!halt)
		step();
}

unsigned char CPU::fetchOpcode() {
	return memory.readByte(pc++);
}

void CPU::reset() {
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
}


