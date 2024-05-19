#include "CPU.h"
#include <iostream>
#include "OpcodeCycles.h"

CPU::CPU(Memory& memory) : memory(memory), F(FlagRegister()), 
AF(Register16(A, F)), BC(Register16(B, C)), DE(Register16(D, E)), HL(Register16(H, L)), interrupts(Interrupts(memory, *this)) {
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
	interrupts.handleInterrupts();
	if (halt)
		return -1;

	unsigned char opcode = fetchOpcode();
	executeOpcode(opcode);
	cycles = opcodeCycles[opcode];
	return cycles;
}

void CPU::run(int iterations) {
	for (int i = 0; i < iterations; ++i)
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

