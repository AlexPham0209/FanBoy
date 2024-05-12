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
	return cycles;
}

void CPU::executeOpcode(unsigned char opcode) {

	//Executes certain instruction based on 8 bit opcode
	switch (opcode) {
		//LD N, NN
		case 0x06:
			LDNN(B, memory.read(pc++));
			break;
		case 0x0E:
			LDNN(C, memory.read(pc++));
			break;
		case 0x16:
			LDNN(D, memory.read(pc++));
			break;
		case 0x1E:
			LDNN(E, memory.read(pc++));
			break;
		case 0x26:
			LDNN(H, memory.read(pc++));
			break;
		case 0x2E:
			LDNN(L, memory.read(pc++));
			break;

		//LD A, r2
		case 0x7F:
			LDR(A, A);
			break;
		case 0x78:
			LDR(A, B);
			break;
		case 0x79:
			LDR(A, C);
			break;
		case 0x7A:
			LDR(A, D);
			break;
		case 0x7B:
			LDR(A, E);
			break;
		case 0x7C:
			LDR(A, H);
			break;
		case 0x7D:
			LDR(A, L);
			break;
		case 0x7E:
			LDR(A, memory.read((H << 8) | L));
			break;

		//LD B, r2
		case 0x40:
			LDR(B, B);
			break;
		case 0x41:
			LDR(B, C);
			break;
		case 0x42:
			LDR(B, D);
			break;
		case 0x43:
			LDR(B, E);
			break;
		case 0x44:
			LDR(B, H);
			break;
		case 0x45:
			LDR(B, L);
			break;
		case 0x46:
			LDR(B, memory.read((H << 8) | L));
			break;
	}
}

//Put 8 bit value into register
void CPU::LDNN(unsigned char& reg, const unsigned char& val) {
	reg = val;
	cycles += 8;
}

//Load value inside register 2/memory address into register 1
void CPU::LDR(unsigned char& reg, const unsigned char& val) {
	reg = val;
	cycles += 4;
}


unsigned char CPU::fetchOpcode() {
	return memory.read(pc++);
}

