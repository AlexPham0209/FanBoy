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
	std::cout << "PC: " << pc << std::endl;
	unsigned char opcode = fetchOpcode();
	executeOpcode(opcode);
	std::cout << "A: " << (int)A << std::endl;
	std::cout << "B: " << (int)B << std::endl;
	std::cout << "C: " << (int)C << std::endl;
	std::cout << "D: " << (int)D << std::endl;
	std::cout << "E: " << (int)E << std::endl;
	std::cout << "F: " << (int)F << std::endl;
	std::cout << "H: " << (int)H << std::endl;
	std::cout << "L: " << (int)L << std::endl;
	std::cout << "Cycles: " << cycles << "\n" << std::endl;
	return cycles;
}

void CPU::run(int iterations) {
	for (int i = 0; i < iterations; ++i)
		step();
}


void CPU::executeOpcode(unsigned char opcode) {
	//Executes certain instruction based on 8 bit opcode
	unsigned short HL = HL = (H << 8) | L;
	switch (opcode) {
		//LD N, NN
		case 0x06:
			LDNN(B, memory.readByte(pc++));
			break;
		case 0x0E:
			LDNN(C, memory.readByte(pc++));
			break;
		case 0x16:
			LDNN(D, memory.readByte(pc++));
			break;
		case 0x1E:
			LDNN(E, memory.readByte(pc++));
			break;
		case 0x26:
			LDNN(H, memory.readByte(pc++));
			break;
		case 0x2E:
			LDNN(L, memory.readByte(pc++));
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
			LDR(A, memory.readByte((H << 8) | L));
			cycles += 4;
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
			LDR(B, memory.readByte((H << 8) | L));
			cycles += 4;
			break;

		//LD C, r2
		case 0x48:
			LDR(C, B);
			break;
		case 0x49:
			LDR(C, C);
			break;
		case 0x4A:
			LDR(C, D);
			break;
		case 0x4B:
			LDR(C, E);
			break;
		case 0x4C:
			LDR(C, H);
			break;
		case 0x4D:
			LDR(C, L);
			break;
		case 0x4E:
			LDR(C, memory.readByte((H << 8) | L));
			cycles += 4;
			break;

		//LD D, r2
		case 0x50:
			LDR(D, B);
			break;
		case 0x51:
			LDR(D, C);
			break;
		case 0x52:
			LDR(D, D);
			break;
		case 0x53:
			LDR(D, E);
			break;
		case 0x54:
			LDR(D, H);
			break;
		case 0x55:
			LDR(D, L);
			break;
		case 0x56:
			LDR(D, memory.readByte((H << 8) | L));
			cycles += 4;
			break;

		//LD E, r2
		case 0x58:
			LDR(E, B);
			break;
		case 0x59:
			LDR(E, C);
			break;
		case 0x5A:
			LDR(E, D);
			break;
		case 0x5B:
			LDR(E, E);
			break;
		case 0x5C:
			LDR(E, H);
			break;
		case 0x5D:
			LDR(E, L);
			break;
		case 0x5E:
			LDR(E, memory.readByte((H << 8) | L));
			cycles += 4;
			break;

		//LD H, r2
		case 0x60:
			LDR(H, B);
			break;
		case 0x61:
			LDR(H, C);
			break;
		case 0x62:
			LDR(H, D);
			break;
		case 0x63:
			LDR(H, E);
			break;
		case 0x64:
			LDR(H, H);
			break;
		case 0x65:
			LDR(H, L);
			break;
		case 0x66:
			LDR(H, memory.readByte((H << 8) | L));
			cycles += 4;
			break;

		//LD L, r2
		case 0x68:
			LDR(L, B);
			break;
		case 0x69:
			LDR(L, C);
			break;
		case 0x6A:
			LDR(L, D);
			break;
		case 0x6B:
			LDR(L, E);
			break;
		case 0x6C:
			LDR(L, H);
			break;
		case 0x6D:
			LDR(L, L);
			break;
		case 0x6E:
			LDR(L, memory.readByte((H << 8) | L));
			cycles += 4;
			break;
		
		//LD (HL), r2
		case 0x70:
			LDR(((H << 8) | L), B);
			break;
		case 0x71:
			LDR(((H << 8) | L), C);
			break;
		case 0x72:
			LDR(((H << 8) | L), D);
			break;
		case 0x73:
			LDR(((H << 8) | L), E);
			break;
		case 0x74:
			LDR(((H << 8) | L), H);
			break;
		case 0x75:
			LDR(((H << 8) | L), L);
			break;
		case 0x36:
			LDR(((H << 8) | L), memory.readByte(pc++));
			cycles += 4;
			break;

		//LD A, n
		case 0x0A:
			LDR(A, memory.readByte((B << 8) | C));
			cycles += 4;
			break;
		case 0x1A:
			LDR(A, memory.readByte((D << 8) | E));
			cycles += 4;
			break;
		case 0xFA:
			LDR(A, (memory.readByte(pc++) | memory.readByte(pc++) << 8));
			cycles += 12;
			break;
		case 0x3E:
			LDNN(A, memory.readByte(pc++));
			cycles += 4;
			break;

		//LD n, A
		case 0x47:
			LDR(B, A);
			break;
		case 0x4F:
			LDR(C, A);
			break;
		case 0x57:
			LDR(D, A);
			break;
		case 0x5F:
			LDR(E, A);
			break;
		case 0x67:
			LDR(H, A);
			break;
		case 0x6F:
			LDR(F, A);
			break;
		case 0x02:
			LDR(((B << 8) | C), A);
			break;
		case 0x12:
			LDR(((D << 8) | E), A);
			break;
		case 0x77:
			LDR(((H << 8) | L), A);
			break;
		case 0xEA:
			LDR((memory.readByte(pc++) | memory.readByte(pc++) << 8), A);
			break;

		//LD A, (C)
		case 0xF2:
			LDR(A, memory.readByte(0xFF00 + C));
			cycles += 4;
			break;

		//LD (C), A
		case 0xE2:
			LDR(0xFF00 + C, A);
			cycles += 4;
			break;

		//LDD A, (HL)
		case 0x3A:
			LDR(A, memory.readByte(HL));
			HL--;
			H = (HL & 0xFF00) >> 8;
			L = (HL & 0x00FF);
			break;
		
		//LDD (HL), A
		case 0x32:
			LDR(HL, A);
			HL--;
			H = (HL & 0xFF00) >> 8;
			L = (HL & 0x00FF);
			break;

		//LDI A, (HL)
		case 0x2A:
			LDR(A, memory.readByte(HL));
			HL++;
			H = (HL & 0xFF00) >> 8;
			L = (HL & 0x00FF);
			break;

		//LDI (HL), A
		case 0x22:
			LDR(HL, A);
			HL++;
			H = (HL & 0xFF00) >> 8;
			L = (HL & 0x00FF);
			break;

		//LDH (n), A
		case 0xE0:
			LDR(0xFF00 + memory.readByte(pc++), A);
			cycles += 4;
			break;

		//LDH A, (n)
		case 0xF0:
			LDR(A, memory.readByte(0xFF00 + memory.readByte(pc++)));
			cycles += 4;
			break;
		
		//LD n, nn
		case 0x01:
			LDNNN(B, C);
			break;
		case 0x11:
			LDNNN(D, E);
			break;
		case 0x21:
			LDNNN(H, L);
			break;
		case 0x31:
			sp = (memory.readByte(pc++) << 8) | memory.readByte(pc++);
			cycles = 12;
			break;
		
		//LD SP, HL
		case 0xF9:
			sp = (H << 8) | L;
			cycles = 8;
			break;

		//LD HL, SP+n
		case 0xF8:
			LDR(HL, sp + memory.readByte(pc++));
			cycles = 12;
			break;

		case 0x08:
			LDR(memory.readByte(pc++) | (memory.readByte(pc++) << 8), sp);
			cycles = 20;
			break;
	}
}

//Put 8 bit value into register
void CPU::LDNN(unsigned char& reg, const unsigned char& val) {
	reg = val;
	cycles = 8;
}

//Load value inside register 2/memory address into register 1
void CPU::LDR(unsigned char& reg, const unsigned char& val) {
	reg = val;
	cycles = 4;
}

//Load value inside register into memory location
void CPU::LDR(const unsigned short& address, const unsigned char& reg) {
	memory.writeByte(address, reg);
	cycles = 8;
}

void CPU::LDNNN(unsigned char& reg1, unsigned char& reg2) {
	reg1 = memory.readByte(pc++);
	reg2 = memory.readByte(pc++);
	cycles = 12;
}

unsigned char CPU::fetchOpcode() {
	return memory.readByte(pc++);
}

