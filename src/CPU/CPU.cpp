#include "CPU.h"
#include <iostream>


CPU::CPU(Memory& memory) : memory(memory), flag(Flag()) {
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
	return cycles;
}

void CPU::run(int iterations) {
	for (int i = 0; i < iterations; ++i)
		step();
}


void CPU::executeOpcode(unsigned char opcode) {
	//Executes certain instruction based on 8 bit opcode
	switch (opcode) {
		//LD N, NN
		case 0x06:
			loadByteIntoReg(B, memory.readByte(pc++));
			cycles = 8;
			break;

		case 0x0E:
			loadByteIntoReg(C, memory.readByte(pc++));
			cycles = 8;
			break;

		case 0x16:
			loadByteIntoReg(D, memory.readByte(pc++));
			cycles = 8;
			break;

		case 0x1E:
			loadByteIntoReg(E, memory.readByte(pc++));
			cycles = 8;
			break;

		case 0x26:
			loadByteIntoReg(H, memory.readByte(pc++));
			cycles = 8;
			break;

		case 0x2E:
			loadByteIntoReg(L, memory.readByte(pc++));
			cycles = 8;
			break;


		//LD A, r2
		case 0x7F:
			loadByteIntoReg(A, A);
			cycles = 4;
			break;

		case 0x78:
			loadByteIntoReg(A, B);
			cycles = 4;
			break;

		case 0x79:
			loadByteIntoReg(A, C);
			cycles = 4;
			break;

		case 0x7A:
			loadByteIntoReg(A, D);
			cycles = 4;
			break;

		case 0x7B:
			loadByteIntoReg(A, E);
			cycles = 4;
			break;

		case 0x7C:
			loadByteIntoReg(A, H);
			cycles = 4;
			break;

		case 0x7D:
			loadByteIntoReg(A, L);
			cycles = 4;
			break;

		case 0x7E:
			loadByteIntoReg(A, memory.readByte((H << 8) | L));
			cycles = 8;
			break;


		//LD B, r2
		case 0x40:
			loadByteIntoReg(B, B);
			cycles = 4;
			break;

		case 0x41:
			loadByteIntoReg(B, C);
			cycles = 4;
			break;

		case 0x42:
			loadByteIntoReg(B, D);
			cycles = 4;
			break;

		case 0x43:
			loadByteIntoReg(B, E);
			cycles = 4;
			break;

		case 0x44:
			loadByteIntoReg(B, H);
			cycles = 4;
			break;

		case 0x45:
			loadByteIntoReg(B, L);
			cycles = 4;
			break;

		case 0x46:
			loadByteIntoReg(B, memory.readByte((H << 8) | L));
			cycles = 8;
			break;

		//LD C, r2
		case 0x48:
			loadByteIntoReg(C, B);
			cycles = 4;
			break;

		case 0x49:
			loadByteIntoReg(C, C);
			cycles = 4;
			break;

		case 0x4A:
			loadByteIntoReg(C, D);
			cycles = 4;
			break;

		case 0x4B:
			loadByteIntoReg(C, E);
			cycles = 4;
			break;

		case 0x4C:
			loadByteIntoReg(C, H);
			cycles = 4;
			break;

		case 0x4D:
			loadByteIntoReg(C, L);
			cycles = 4;
			break;

		case 0x4E:
			loadByteIntoReg(C, memory.readByte((H << 8) | L));
			cycles = 8;
			break;

		//LD D, r2
		case 0x50:
			loadByteIntoReg(D, B);
			cycles = 4;
			break;

		case 0x51:
			loadByteIntoReg(D, C);
			cycles = 4;
			break;

		case 0x52:
			loadByteIntoReg(D, D);
			cycles = 4;
			break;

		case 0x53:
			loadByteIntoReg(D, E);
			cycles = 4;
			break;

		case 0x54:
			loadByteIntoReg(D, H);
			cycles = 4;
			break;

		case 0x55:
			loadByteIntoReg(D, L);
			cycles = 4;
			break;

		case 0x56:
			loadByteIntoReg(D, memory.readByte((H << 8) | L));
			cycles = 8;
			break;

		//LD E, r2
		case 0x58:
			loadByteIntoReg(E, B);
			cycles = 4;
			break;

		case 0x59:
			loadByteIntoReg(E, C);
			cycles = 4;
			break;

		case 0x5A:
			loadByteIntoReg(E, D);
			cycles = 4;
			break;

		case 0x5B:
			loadByteIntoReg(E, E);
			cycles = 4;
			break;

		case 0x5C:
			loadByteIntoReg(E, H);
			cycles = 4;
			break;

		case 0x5D:
			loadByteIntoReg(E, L);
			cycles = 4;
			break;

		case 0x5E:
			loadByteIntoReg(E, memory.readByte((H << 8) | L));
			cycles = 8;
			break;

		//LD H, r2
		case 0x60:
			loadByteIntoReg(H, B);
			cycles = 4;
			break;

		case 0x61:
			loadByteIntoReg(H, C);
			cycles = 4;
			break;

		case 0x62:
			loadByteIntoReg(H, D);
			cycles = 4;
			break;

		case 0x63:
			loadByteIntoReg(H, E);
			cycles = 4;
			break;

		case 0x64:
			loadByteIntoReg(H, H);
			cycles = 4;
			break;

		case 0x65:
			loadByteIntoReg(H, L);
			cycles = 4;
			break;

		case 0x66:
			loadByteIntoReg(H, memory.readByte((H << 8) | L));
			cycles = 8;
			break;

		//LD L, r2
		case 0x68:
			loadByteIntoReg(L, B);
			cycles = 4;
			break;

		case 0x69:
			loadByteIntoReg(L, C);
			cycles = 4;
			break;

		case 0x6A:
			loadByteIntoReg(L, D);
			cycles = 4;
			break;

		case 0x6B:
			loadByteIntoReg(L, E);
			cycles = 4;
			break;

		case 0x6C:
			loadByteIntoReg(L, H);
			cycles = 4;
			break;

		case 0x6D:
			loadByteIntoReg(L, L);
			cycles = 4;
			break;

		case 0x6E:
			loadByteIntoReg(L, memory.readByte((H << 8) | L));
			cycles = 8;
			break;
		
		//LD (HL), r2
		case 0x70:
			loadByteIntoMemory(((H << 8) | L), B);
			cycles = 8;
			break;

		case 0x71:
			loadByteIntoMemory(((H << 8) | L), C);
			cycles = 8;
			break;
		case 0x72:
			loadByteIntoMemory(((H << 8) | L), D);
			cycles = 8;
			break;
		case 0x73:
			loadByteIntoMemory(((H << 8) | L), E);
			cycles = 8;
			break;

		case 0x74:
			loadByteIntoMemory(((H << 8) | L), H);
			cycles = 8;
			break;

		case 0x75:
			loadByteIntoMemory(((H << 8) | L), L);
			cycles = 8;
			break;

		case 0x36:
			loadByteIntoMemory(((H << 8) | L), memory.readByte(pc++));
			cycles = 12;
			break;

		//LD A, n
		case 0x0A:
			loadByteIntoReg(A, memory.readByte((B << 8) | C));
			cycles = 8;
			break;

		case 0x1A:
			loadByteIntoReg(A, memory.readByte((D << 8) | E));
			cycles = 8;
			break;

		case 0xFA:
			loadByteIntoReg(A, memory.readByte((memory.readByte(pc++) | memory.readByte(pc++) << 8)));
			cycles = 16;
			break;

		case 0x3E:
			loadByteIntoReg(A, memory.readByte(pc++));
			cycles = 8;
			break;

		//LD n, A
		case 0x47:
			loadByteIntoReg(B, A);
			cycles = 4;
			break;

		case 0x4F:
			loadByteIntoReg(C, A);
			cycles = 4;
			break;

		case 0x57:
			loadByteIntoReg(D, A);
			cycles = 4;
			break;

		case 0x5F:
			loadByteIntoReg(E, A);
			cycles = 4;
			break;

		case 0x67:
			loadByteIntoReg(H, A);
			cycles = 4;
			break;

		case 0x6F:
			loadByteIntoReg(F, A);
			cycles = 4;
			break;

		case 0x02:
			loadByteIntoMemory(((B << 8) | C), A);
			cycles = 8;
			break;

		case 0x12:
			loadByteIntoMemory(((D << 8) | E), A);
			cycles = 8;
			break;

		case 0x77:
			loadByteIntoMemory(((H << 8) | L), A);
			cycles = 8;
			break;

		case 0xEA:
			loadByteIntoMemory((memory.readByte(pc++) | (memory.readByte(pc++) << 8)), A);
			cycles = 16;
			break;

		//LD A, (C)
		case 0xF2:
			loadByteIntoReg(A, memory.readByte(0xFF00 + C));
			cycles = 8;
			break;

		//LD (C), A
		case 0xE2:
			loadByteIntoMemory(0xFF00 + C, A);
			cycles = 8;
			break;

		//LDD A, (HL)
		case 0x3A:
			loadByteIntoRegDecrement(A, H, L);
			cycles = 8;
			break;
		
		//LDD (HL), A
		case 0x32:
			loadByteIntoMemoryDecrement(A, H, L);
			cycles = 8;
			break;

		//LDI A, (HL)
		case 0x2A:
			loadByteIntoRegIncrement(A, H, L);
			cycles = 8;
			break;

		//LDI (HL), A
		case 0x22:
			loadByteIntoMemoryIncrement(A, H, L);
			cycles = 8;
			break;

		//LDH (n), A
		case 0xE0:
			loadByteIntoMemory(0xFF00 + memory.readByte(pc++), A);
			cycles = 12;
			break;

		//LDH A, (n)
		case 0xF0:
			loadByteIntoReg(A, memory.readByte(0xFF00 + memory.readByte(pc++)));
			cycles = 12;
			break;
		
		//LD n, nn
		case 0x01:
			loadShortIntoReg(B, C, memory.readShort(pc));
			cycles = 12;
			break;

		case 0x11:
			loadShortIntoReg(D, E, memory.readShort(pc));
			cycles = 12;
			break;

		case 0x21:
			loadShortIntoReg(H, L, memory.readShort(pc));
			cycles = 12;
			break;

		case 0x31:
			sp = memory.readShort(pc);
			cycles = 12;
			break;
		
		//LD SP, HL
		case 0xF9:
			sp = (H << 8) | L;
			cycles = 8;
			break;

		//LD HL, SP+n
		case 0xF8:
			loadShortIntoReg(H, L, sp + memory.readByte(pc++));
			cycles = 12;
			break;

		//LD (nn), SP
		case 0x08:
			loadShortIntoMemory(memory.readByte(pc), sp);
			cycles = 20;
			break;

		//PUSH nn
		case 0xF5:
			push(A, F);
			cycles = 16;
			break;

		case 0xC5:
			push(B, C);
			cycles = 16;
			break;

		case 0xD5:
			push(D, E);
			cycles = 16;
			break;

		case 0xE5:
			push(H, L);
			cycles = 16;
			break;

		//POP nn
		case 0xF1:
			pop(A, F);
			cycles = 12;
			break;

		case 0xC1:
			pop(B, C);
			cycles = 12;
			break;

		case 0xD1:
			pop(D, E);
			cycles = 12;
			break;

		case 0xE1:
			pop(H, L);
			cycles = 12;
			break;
		
		//ADD A, n
		case 0x87:
			add(A, A);
			cycles = 4;
			break;

		case 0x80:
			add(A, B);
			cycles = 4;
			break;

		case 0x81:
			add(A, C);
			cycles = 4;
			break;

		case 0x82:
			add(A, D);
			cycles = 4;
			break;

		case 0x83:
			add(A, E);
			cycles = 4;
			break;

		case 0x84:
			add(A, H);
			cycles = 4;
			break;

		case 0x85:
			add(A, L);
			cycles = 4;
			break;

		case 0x86:
			add(A, memory.readByte((H << 8) | L));
			cycles = 8;
			break;

		case 0xC6:
			add(A, memory.readByte(pc++));
			cycles = 8;
			break;

		//ADC A, n
		case 0x8F:
			addCarry(A, A);
			cycles = 4;
			break;

		case 0x88:
			addCarry(A, B);
			cycles = 4;
			break;

		case 0x89:
			addCarry(A, C);
			cycles = 4;
			break;

		case 0x8A:
			addCarry(A, D);
			cycles = 4;
			break;

		case 0x8B:
			addCarry(A, E);
			cycles = 4;
			break;

		case 0x8C:
			addCarry(A, H);
			cycles = 4;
			break;

		case 0x8D:
			addCarry(A, L);
			cycles = 4;
			break;

		case 0x8E:
			addCarry(A, memory.readByte((H << 8) | L));
			cycles = 8;
			break;

		case 0xCE:
			addCarry(A, memory.readByte(pc++));
			cycles = 8;
			break;
			
	}
}

//Put byte into register
void CPU::loadByteIntoReg(unsigned char& reg, const unsigned char& val) {
	reg = val;
}

//Put byte inside address (AB) into register, then decrement the 16 bit register
void CPU::loadByteIntoRegDecrement(unsigned char& reg, unsigned char& a, unsigned char& b) {
	unsigned short ab = (a << 8) | b;
	loadByteIntoReg(reg, memory.readByte(ab--));
	a = (ab & 0xFF00) >> 8;
	b = (ab & 0x00FF);
}

//Put byte inside address (AB) into register, then increment the 16 bit register
void CPU::loadByteIntoRegIncrement(unsigned char& reg, unsigned char& a, unsigned char& b) {
	unsigned short ab = (a << 8) | b;
	loadByteIntoReg(reg, memory.readByte(ab++));
	a = (ab & 0xFF00) >> 8;
	b = (ab & 0x00FF);
}


//Load value inside register into memory location
void CPU::loadByteIntoMemory(const unsigned short& address, const unsigned char& reg) {
	memory.writeByte(address, reg);
}

//Load byte inside register into memory address (AB), then decrement the 16 bit register a
void CPU::loadByteIntoMemoryDecrement(unsigned char& reg, unsigned char& a, unsigned char& b) {
	unsigned short ab = (a << 8) | b;
	loadByteIntoMemory(ab--, reg);
	a = (ab & 0xFF00) >> 8;
	b = (ab & 0x00FF);
}

//Load byte inside register into memory address (AB), then decrement the 16 bit register 
void CPU::loadByteIntoMemoryIncrement(unsigned char& reg, unsigned char& a, unsigned char& b) {
	unsigned short ab = (a << 8) | b;
	loadByteIntoMemory(ab++, reg);
	a = (ab & 0xFF00) >> 8;
	b = (ab & 0x00FF);
}

//Load short into the 16 bit register which is just 2 8 bit registers
void CPU::loadShortIntoReg(unsigned char& reg1, unsigned char& reg2, const unsigned short& val) {
	reg1 = (val & 0xFF00) >> 8;
	reg2 = (val & 0x00FF);
}

//Load short into memory location
void CPU::loadShortIntoMemory(const unsigned short& address, const unsigned short& val) {
	memory.writeShort(address, val);
}

//Load 16 bit register pair into the stack pointer
void CPU::loadRegIntoSP(unsigned char& a, unsigned char& b) {
	sp = (H << 8) | L;
}

//Pushes values inside register pair onto the stack (decrements SP twice)
void CPU::push(unsigned char a, unsigned char b) {
	memory.writeByte(--sp, a);
	memory.writeByte(--sp, b);
}

//Pops the top two bytes off the stack and stores them inside register pair (increments SP twice)
void CPU::pop(unsigned char& a, unsigned char& b) {
	unsigned char n1 = memory.writeByte(sp++, 0);
	unsigned char n2 = memory.writeByte(sp++, 0);
	a = n2;
	b = n1;
}

//Adds a register and another value togethers and stores the result into the register
void CPU::add(unsigned char& reg, const unsigned char val) {
	int res = reg + val;

	//Set flags 
	flag.setFlag(SUB, false);
	flag.setFlag(ZERO, ((unsigned char)res == 0));
	flag.setFlag(HALF, ((reg & 0xF) + (val & 0xF) + flag.getFlag(CARRY) > 0xF));
	flag.setFlag(CARRY, (res > 0xFF));
	
	reg = (unsigned char)res;
}

//Adds a register and another value togethers and stores the result into the register
void CPU::addCarry(unsigned char& reg, const unsigned char val) {
	int res = reg + val + flag.getFlag(CARRY);

	//Set flags 
	flag.setFlag(SUB, false);
	flag.setFlag(ZERO, ((unsigned char)res == 0));
	flag.setFlag(HALF, ((reg & 0xF) + (val & 0xF) + flag.getFlag(CARRY) > 0xF));
	flag.setFlag(CARRY, (res > 0xFF));

	reg = (unsigned char)res;
}


unsigned char CPU::fetchOpcode() {
	return memory.readByte(pc++);
}

