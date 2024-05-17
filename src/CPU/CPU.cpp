#include "CPU.h"
#include <iostream>
#include <Cpl.h>


CPU::CPU(Memory& memory) : memory(memory), flag(Flag()), running(true) {
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
	//std::cout << "PC: " << pc << std::endl;
	unsigned char opcode = fetchOpcode();
	executeOpcode(opcode);
	//std::cout << (int)opcode << std::endl;
	//std::cout << "A: " << (int)A << std::endl;
	//std::cout << "B: " << (int)B << std::endl;
	//std::cout << "C: " << (int)C << std::endl;
	//std::cout << "D: " << (int)D << std::endl;
	//std::cout << "E: " << (int)E << std::endl;
	//std::cout << "F: " << (int)F << std::endl;
	//std::cout << "H: " << (int)H << std::endl;
	//std::cout << "L: " << (int)L << std::endl;
	//std::cout << "Cycles: " << cycles << "\n" << std::endl;
	return cycles;
}

void CPU::run(int iterations) {
	for (int i = 0; i < iterations; ++i)
		step();
}


//TODO: Create Instructions STOP, DI, EL
void CPU::executeOpcode(unsigned char opcode) {
	//Executes certain instruction based on 8 bit opcode
	switch (opcode) {
		//LD N, NN
		case 0x06:
			loadByteIntoReg(B, memory.readByte(pc++));
			break;

		case 0x0E:
			loadByteIntoReg(C, memory.readByte(pc++));
			break;

		case 0x16:
			loadByteIntoReg(D, memory.readByte(pc++));
			break;

		case 0x1E:
			loadByteIntoReg(E, memory.readByte(pc++));
			break;

		case 0x26:
			loadByteIntoReg(H, memory.readByte(pc++));
			break;

		case 0x2E:
			loadByteIntoReg(L, memory.readByte(pc++));
			break;


		//LD A, r2
		case 0x7F:
			loadByteIntoReg(A, A);			
			break;

		case 0x78:
			loadByteIntoReg(A, B);			
			break;

		case 0x79:
			loadByteIntoReg(A, C);		
			break;

		case 0x7A:
			loadByteIntoReg(A, D);			
			break;

		case 0x7B:
			loadByteIntoReg(A, E);			
			break;

		case 0x7C:
			loadByteIntoReg(A, H);			
			break;

		case 0x7D:
			loadByteIntoReg(A, L);			
			break;

		case 0x7E:
			loadByteIntoReg(A, memory.readByte((H << 8) | L));			
			break;


		//LD B, r2
		case 0x40:
			loadByteIntoReg(B, B);			
			break;

		case 0x41:
			loadByteIntoReg(B, C);		
			break;

		case 0x42:
			loadByteIntoReg(B, D);
			break;

		case 0x43:
			loadByteIntoReg(B, E);
			break;

		case 0x44:
			loadByteIntoReg(B, H);			
			break;

		case 0x45:
			loadByteIntoReg(B, L);
			break;

		case 0x46:
			loadByteIntoReg(B, memory.readByte((H << 8) | L));
			break;

		//LD C, r2
		case 0x48:
			loadByteIntoReg(C, B);
			break;

		case 0x49:
			loadByteIntoReg(C, C);
			break;

		case 0x4A:
			loadByteIntoReg(C, D);
			
			break;

		case 0x4B:
			loadByteIntoReg(C, E);		
			break;

		case 0x4C:
			loadByteIntoReg(C, H);			
			break;

		case 0x4D:
			loadByteIntoReg(C, L);			
			break;

		case 0x4E:
			loadByteIntoReg(C, memory.readByte((H << 8) | L));			
			break;

		//LD D, r2
		case 0x50:
			loadByteIntoReg(D, B);			
			break;

		case 0x51:
			loadByteIntoReg(D, C);			
			break;

		case 0x52:
			loadByteIntoReg(D, D);			
			break;

		case 0x53:
			loadByteIntoReg(D, E);			
			break;

		case 0x54:
			loadByteIntoReg(D, H);			
			break;

		case 0x55:
			loadByteIntoReg(D, L);			
			break;

		case 0x56:
			loadByteIntoReg(D, memory.readByte((H << 8) | L));			
			break;

		//LD E, r2
		case 0x58:
			loadByteIntoReg(E, B);			
			break;

		case 0x59:
			loadByteIntoReg(E, C);		
			break;

		case 0x5A:
			loadByteIntoReg(E, D);			
			break;

		case 0x5B:
			loadByteIntoReg(E, E);			
			break;

		case 0x5C:
			loadByteIntoReg(E, H);			
			break;

		case 0x5D:
			loadByteIntoReg(E, L);			
			break;

		case 0x5E:
			loadByteIntoReg(E, memory.readByte((H << 8) | L));			
			break;

		//LD H, r2
		case 0x60:
			loadByteIntoReg(H, B);			
			break;

		case 0x61:
			loadByteIntoReg(H, C);			
			break;

		case 0x62:
			loadByteIntoReg(H, D);			
			break;

		case 0x63:
			loadByteIntoReg(H, E);			
			break;

		case 0x64:
			loadByteIntoReg(H, H);			
			break;

		case 0x65:
			loadByteIntoReg(H, L);			
			break;

		case 0x66:
			loadByteIntoReg(H, memory.readByte((H << 8) | L));			
			break;

		//LD L, r2
		case 0x68:
			loadByteIntoReg(L, B);			
			break;

		case 0x69:
			loadByteIntoReg(L, C);			
			break;

		case 0x6A:
			loadByteIntoReg(L, D);			
			break;

		case 0x6B:
			loadByteIntoReg(L, E);			
			break;

		case 0x6C:
			loadByteIntoReg(L, H);			
			break;

		case 0x6D:
			loadByteIntoReg(L, L);			
			break;

		case 0x6E:
			loadByteIntoReg(L, memory.readByte((H << 8) | L));			
			break;
		
		//LD (HL), r2
		case 0x70:
			loadByteIntoMemory(((H << 8) | L), B);			
			break;

		case 0x71:
			loadByteIntoMemory(((H << 8) | L), C);			
			break;
		case 0x72:
			loadByteIntoMemory(((H << 8) | L), D);			
			break;
		case 0x73:
			loadByteIntoMemory(((H << 8) | L), E);			
			break;

		case 0x74:
			loadByteIntoMemory(((H << 8) | L), H);			
			break;

		case 0x75:
			loadByteIntoMemory(((H << 8) | L), L);			
			break;

		case 0x36:
			loadByteIntoMemory(((H << 8) | L), memory.readByte(pc++));
			break;

		//LD A, n
		case 0x0A:
			loadByteIntoReg(A, memory.readByte((B << 8) | C));
			
			break;

		case 0x1A:
			loadByteIntoReg(A, memory.readByte((D << 8) | E));
			
			break;

		case 0xFA:
			loadByteIntoReg(A, memory.readByte((memory.readByte(pc++) | memory.readByte(pc++) << 8)));
			break;

		case 0x3E:
			loadByteIntoReg(A, memory.readByte(pc++));		
			break;

		//LD n, A
		case 0x47:
			loadByteIntoReg(B, A);			
			break;

		case 0x4F:
			loadByteIntoReg(C, A);			
			break;

		case 0x57:
			loadByteIntoReg(D, A);			
			break;

		case 0x5F:
			loadByteIntoReg(E, A);			
			break;

		case 0x67:
			loadByteIntoReg(H, A);			
			break;

		case 0x6F:
			loadByteIntoReg(F, A);			
			break;

		case 0x02:
			loadByteIntoMemory(((B << 8) | C), A);			
			break;

		case 0x12:
			loadByteIntoMemory(((D << 8) | E), A);
			break;

		case 0x77:
			loadByteIntoMemory(((H << 8) | L), A);			
			break;

		case 0xEA:
			loadByteIntoMemory((memory.readByte(pc++) | (memory.readByte(pc++) << 8)), A);
			break;

		//LD A, (C)
		case 0xF2:
			loadByteIntoReg(A, memory.readByte(0xFF00 + C));		
			break;

		//LD (C), A
		case 0xE2:
			loadByteIntoMemory(0xFF00 + C, A);	
			break;

		//LDD A, (HL)
		case 0x3A:
			loadByteIntoRegDecrement(A, H, L);			
			break;
		
		//LDD (HL), A
		case 0x32:
			loadByteIntoMemoryDecrement(A, H, L);		
			break;

		//LDI A, (HL)
		case 0x2A:
			loadByteIntoRegIncrement(A, H, L);			
			break;

		//LDI (HL), A
		case 0x22:
			loadByteIntoMemoryIncrement(A, H, L);			
			break;

		//LDH (n), A
		case 0xE0:
			loadByteIntoMemory(0xFF00 + memory.readByte(pc++), A);
			break;

		//LDH A, (n)
		case 0xF0:
			loadByteIntoReg(A, memory.readByte(0xFF00 + memory.readByte(pc++)));
			break;
		
		//LD n, nn
		case 0x01:
			loadShortIntoReg(B, C, memory.readShort(pc));
			pc += 2;
			break;

		case 0x11:
			loadShortIntoReg(D, E, memory.readShort(pc));
			pc += 2;
			break;

		case 0x21:
			loadShortIntoReg(H, L, memory.readShort(pc));
			pc += 2;
			break;

		case 0x31:
			sp = memory.readShort(pc);
			pc += 2;
			break;
		
		//LD SP, HL
		case 0xF9:
			sp = (H << 8) | L;
			break;

		//LD HL, SP+n
		case 0xF8:
			loadShortIntoReg(H, L, sp + memory.readByte(pc++));
			break;

		//LD (nn), SP
		case 0x08:
			loadShortIntoMemory(memory.readByte(pc++), sp);
			break;

		//PUSH nn
		case 0xF5:
			push(A, F);
			break;

		case 0xC5:
			push(B, C);
			break;

		case 0xD5:
			push(D, E);
			break;

		case 0xE5:
			push(H, L);
			break;

		//POP nn
		case 0xF1:
			pop(A, F);
			break;

		case 0xC1:
			pop(B, C);
			break;

		case 0xD1:
			pop(D, E);
			break;

		case 0xE1:
			pop(H, L);
			break;
		
		//ADD A, n
		case 0x87:
			add(A, A);
			break;

		case 0x80:
			add(A, B);			
			break;

		case 0x81:
			add(A, C);			
			break;

		case 0x82:
			add(A, D);			
			break;

		case 0x83:
			add(A, E);			
			break;

		case 0x84:
			add(A, H);			
			break;

		case 0x85:
			add(A, L);			
			break;

		case 0x86:
			add(A, memory.readByte((H << 8) | L));			
			break;

		case 0xC6:
			add(A, memory.readByte(pc++));			
			break;

		//ADC A, n
		case 0x8F:
			addCarry(A, A);			
			break;

		case 0x88:
			addCarry(A, B);			
			break;

		case 0x89:
			addCarry(A, C);			
			break;

		case 0x8A:
			addCarry(A, D);			
			break;

		case 0x8B:
			addCarry(A, E);			
			break;

		case 0x8C:
			addCarry(A, H);			
			break;

		case 0x8D:
			addCarry(A, L);			
			break;

		case 0x8E:
			addCarry(A, memory.readByte((H << 8) | L));			
			break;

		case 0xCE:
			addCarry(A, memory.readByte(pc++));			
			break;

		//SUB n
		case 0x97:
			sub(A, A);			
			break;

		case 0x90:
			sub(A, B);			
			break;

		case 0x91:
			sub(A, C);		
			break;
		
		case 0x92:
			sub(A, D);		
			break;
		
		case 0x93:
			sub(A, E);			
			break;
		
		case 0x94:
			sub(A, H);			
			break;

		case 0x95:
			sub(A, L);			
			break;

		case 0x96:
			sub(A, memory.readByte((H << 8) | L));			
			break;

		case 0xD6:
			sub(A, memory.readByte(pc++));			
			break;

		//SUBC n
		case 0x9F:
			subBorrow(A, A);			
			break;

		case 0x98:
			subBorrow(A, B);			
			break;

		case 0x99:
			subBorrow(A, C);			
			break;

		case 0x9A:
			subBorrow(A, D);			
			break;

		case 0x9B:
			subBorrow(A, E);			
			break;

		case 0x9C:
			subBorrow(A, H);			
			break;

		case 0x9D:
			subBorrow(A, L);			
			break;

		case 0x9E:
			subBorrow(A, memory.readByte((H << 8) | L));		
			break;

		//AND n 
		case 0xA7:
			AND(A, A);			
			break;

		case 0xA0:
			AND(A, B);			
			break;

		case 0xA1:
			AND(A, C);			
			break;

		case 0xA2:
			AND(A, D);			
			break;

		case 0xA3:
			AND(A, E);			
			break;

		case 0xA4:
			AND(A, H);			
			break;

		case 0xA5:
			AND(A, L);			
			break;

		case 0xA6:
			AND(A, memory.readByte((H << 8) | L));			
			break;

		case 0xE6:
			AND(A, memory.readByte(pc++));			
			break;

		//OR operation
		case 0xB7:
			OR(A, A);			
			break;
		
		case 0xB0:
			OR(A, B);			
			break;
		
		case 0xB1:
			OR(A, C);			
			break;
		
		case 0xB2:
			OR(A, D);			
			break;
		
		case 0xB3:
			OR(A, E);			
			break;

		case 0xB4:
			OR(A, H);			
			break;
				
		case 0xB5:
			OR(A, L);			
			break;

		case 0xB6:
			OR(A, memory.readByte((H << 8) | L));		
			break;

		case 0xF6:
			OR(A, memory.readByte(pc++));			
			break;

			
		//XOR operation
		case 0xAF:
			XOR(A, A);			
			break;

		case 0xA8:
			XOR(A, B);			
			break;

		case 0xA9:
			XOR(A, C);			
			break;

		case 0xAA:
			XOR(A, D);			
			break;

		case 0xAB:
			XOR(A, E);			
			break;

		case 0xAC:
			XOR(A, H);			
			break;

		case 0xAD:
			XOR(A, L);
			break;

		case 0xAE:
			XOR(A, memory.readByte((H << 8) | L));			
			break;

		case 0xEE:
			XOR(A, memory.readByte(pc++));			
			break;

			//XOR operation
		case 0xBF:
			CP(A, A);			
			break;

		case 0xB8:
			CP(A, B);			
			break;

		case 0xB9:
			CP(A, C);			
			break;

		case 0xBA:
			CP(A, D);		
			break;

		case 0xBB:
			CP(A, E);			
			break;

		case 0xBC:
			CP(A, H);		
			break;

		case 0xBD:
			CP(A, L);			
			break;

		case 0xBE:
			CP(A, memory.readByte((H << 8) | L));			
			break;

		case 0xFE:
			XOR(A, memory.readByte(pc++));
			break;

		//INC n
		case 0x3C:
			INC(A);
			break;
		
		case 0x04:
			INC(B);	
			break;
		
		case 0x0C:
			INC(C);	
			break;
		
		case 0x14:
			INC(D);	
			break;

		case 0x1C:
			INC(E);	
			break;

		case 0x24:
			INC(H);		
			break;

		case 0x2C:
			INC(H);		
			break;

		case 0x34:
			INC((H << 8)  | L);
			cycles = 12;
			break;

		//DEC n
		case 0x3D:
			DEC(A);
			break;

		case 0x05:
			DEC(B);		
			break;

		case 0x0D:
			DEC(C);			
			break;

		case 0x15:
			DEC(D);			
			break;

		case 0x1D:
			DEC(E);
			break;

		case 0x25:
			DEC(H);			
			break;

		case 0x2D:
			DEC(H);		
			break;

		case 0x35:
			DEC((H << 8) | L);
			break;

		//ADD HL, n
		case 0x09:
			add(H, L, (B << 8) | C);			
			break;

		case 0x19:
			add(H, L, (D << 8) | E);			
			break;

		case 0x29:
			add(H, L, (H << 8) | L);			
			break;

		case 0x39:
			add(H, L, sp);			
			break;

		case 0xE8:
			add(sp, memory.readShort(pc));
			pc += 2;			
			break;

		//INC nn
		case 0x03:
			INC(B, C);
			break;

		case 0x13:
			INC(D, E);
			break;

		case 0x23:
			INC(H, L);
			break;

		case 0x33:
			sp++;
			break;

		//DEC nn
		case 0x0B:
			DEC(B, C);
			break;

		case 0x1B:
			DEC(D, E);
			break;

		case 0x2B:
			DEC(H, L);
			break;

		case 0x3B:
			sp--;
			break;

		//DAA
		case 0x27:
			DAA(A);
			break;

		//CPL
		case 0x2F:
			CPL(A);
			break;
		
		//CCF
		case 0x3F:
			CCF();
			break;

		//SCF
		case 0x37:
			SCF(); 
			break;
		
		//HALT
		case 0x76:
			running = false;
			break;

		
	}


}

//Put byte into register
void CPU::loadByteIntoReg(unsigned char& reg, const unsigned char& val) {
	reg = val;
}

//Put byte inside address (AB) into register, then decrement the 16 bit register
void CPU::loadByteIntoRegDecrement(unsigned char& reg, unsigned char& ms, unsigned char& ls) {
	unsigned short res = (ms << 8) | ls;
	loadByteIntoReg(reg, memory.readByte(res--));
	ms = (res & 0xFF00) >> 8;
	ls = (res & 0x00FF);
}

//Put byte inside address (AB) into register, then increment the 16 bit register
void CPU::loadByteIntoRegIncrement(unsigned char& reg, unsigned char& ms, unsigned char& ls) {
	unsigned short res = (ms << 8) | ls;
	loadByteIntoReg(reg, memory.readByte(res++));
	ms = (res & 0xFF00) >> 8;
	ls = (res & 0x00FF);
}


//Load value inside register into memory location
void CPU::loadByteIntoMemory(const unsigned short& address, const unsigned char& reg) {
	memory.writeByte(address, reg);
}

//Load byte inside register into memory address (AB), then decrement the 16 bit register a
void CPU::loadByteIntoMemoryDecrement(unsigned char& reg, unsigned char& ms, unsigned char& ls) {
	unsigned short res = (ms << 8) | ls;
	loadByteIntoMemory(res--, reg);
	ms = (res & 0xFF00) >> 8;
	ls = (res & 0x00FF);
}

//Load byte inside register into memory address (AB), then decrement the 16 bit register 
void CPU::loadByteIntoMemoryIncrement(unsigned char& reg, unsigned char& ms, unsigned char& ls) {
	unsigned short res = (ms << 8) | ls;
	loadByteIntoMemory(res++, reg);
	ms = (res & 0xFF00) >> 8;
	ls = (res & 0x00FF);
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
void CPU::loadRegIntoSP(unsigned char& ms, unsigned char& ls) {
	sp = (ms << 8) | ls;
}

//Pushes values inside register pair onto the stack (decrements SP twice)
void CPU::push(unsigned char ms, unsigned char ls) {
	memory.writeByte(--sp, ms);
	memory.writeByte(--sp, ls);
}

//Pops the top two bytes off the stack and stores them inside register pair (increments SP twice)
void CPU::pop(unsigned char& ms, unsigned char& ls) {
	unsigned char n1 = memory.writeByte(sp++, 0);
	unsigned char n2 = memory.writeByte(sp++, 0);
	ms = n2;
	ls = n1;
}

//Adds a register and another value togethers and stores the result into the register
void CPU::add(unsigned char& reg, const unsigned char val) {
	int res = reg + val;

	//Set flags 
	flag.setFlag(ZERO, ((unsigned char)res == 0));
	flag.setFlag(SUB, false);
	flag.setFlag(HALF, ((reg & 0xF) + (val & 0xF) + flag.getFlag(CARRY) > 0xF));
	flag.setFlag(CARRY, (res > 0xFF));
	
	reg = (unsigned char)res;
}

//Adds a register and another value togethers and stores the result into the register
void CPU::addCarry(unsigned char& reg, const unsigned char val) {
	int res = reg + val + flag.getFlag(CARRY);

	//Set flags 
	flag.setFlag(ZERO, ((unsigned char)res == 0));
	flag.setFlag(SUB, false);
	flag.setFlag(HALF, ((reg & 0xF) + (val & 0xF) + flag.getFlag(CARRY) > 0xF));
	flag.setFlag(CARRY, (res > 0xFF));

	reg = (unsigned char)res;
}

void CPU::sub(unsigned char& reg, const unsigned char val) {
	int res = reg - val;

	//Set flags 
	flag.setFlag(ZERO, ((unsigned char)res == 0));
	flag.setFlag(SUB, true);
	flag.setFlag(HALF, ((reg & 0xF) - (val & 0xF) < 0));
	flag.setFlag(CARRY, (res < 0));

	reg = (unsigned char)res;
}

void CPU::subBorrow(unsigned char& reg, const unsigned char val) {
	int res = reg - val - flag.getFlag(CARRY);

	//Set flags 
	flag.setFlag(ZERO, ((unsigned char)res == 0));
	flag.setFlag(SUB, true);
	flag.setFlag(HALF, ((reg & 0xF) - (val & 0xF) - flag.getFlag(CARRY) < 0));
	flag.setFlag(CARRY, (res < 0));

	reg = (unsigned char)res;
}

void CPU::AND(unsigned char& reg, const unsigned char val) {
	unsigned char res = reg & val;

	//Set flags 
	flag.setFlag(ZERO, ((unsigned char)res == 0));
	flag.setFlag(SUB, false);
	flag.setFlag(HALF, true);
	flag.setFlag(CARRY, false);

	reg = res;
}

void CPU::OR(unsigned char& reg, const unsigned val) {
	unsigned char res = reg | val;

	//Set flags 
	flag.setFlag(ZERO, ((unsigned char)res == 0));
	flag.setFlag(SUB, false);
	flag.setFlag(HALF, false);
	flag.setFlag(CARRY, false);

	reg = res;
}

void CPU::XOR(unsigned char& reg, const unsigned val) {
	unsigned char res = reg ^ val;

	//Set flags 
	flag.setFlag(ZERO, ((unsigned char)res == 0));
	flag.setFlag(SUB, false);
	flag.setFlag(HALF, false);
	flag.setFlag(CARRY, false);

	reg = res;
}

void CPU::CP(unsigned char& reg, const unsigned char val) {
	flag.setFlag(ZERO, (reg == val));
	flag.setFlag(SUB, true);
	flag.setFlag(HALF, ((reg & 0xF) < (val & 0xF)));
	flag.setFlag(CARRY, (reg < val));
}


void CPU::INC(unsigned char& reg) {
	int res = reg + 1;
	flag.setFlag(ZERO, (res == 0));
	flag.setFlag(SUB, false);
	flag.setFlag(HALF, ((reg & 0xFF) == 0xFF));

	reg = res;
}

void CPU::INC(const unsigned short address) {
	int res = memory.readByte(address) + 1;
	flag.setFlag(ZERO, (res == 0));
	flag.setFlag(SUB, false);
	flag.setFlag(HALF, ((memory.readByte(address) & 0xFF) == 0xFF));

	memory.writeByte(address, res);
}


void CPU::DEC(unsigned char& reg) {
	int res = reg - 1;
	flag.setFlag(ZERO, (res == 0));
	flag.setFlag(SUB, true);
	flag.setFlag(HALF, ((reg & 0xFF) == 0));

	reg = res;
}

void CPU::DEC(const unsigned short address) {
	int res = memory.readByte(address) + 1;
	flag.setFlag(ZERO, (res == 0));
	flag.setFlag(SUB, false);
	flag.setFlag(HALF, ((memory.readByte(address) & 0xFF) == 0));

	memory.writeByte(address, res);
}

void CPU::add(unsigned char& ms, unsigned char& ls, const unsigned short val) {
	int res = ((ms << 8) | ls) + val;

	flag.setFlag(SUB, false);
	flag.setFlag(HALF, (((ms << 8) | ls) & 0xFFF) + (val & 0xFFF) > 0xFFF);
	flag.setFlag(CARRY, res > 0xFFFF);

	ms = ((unsigned short)res & 0xFF00) >> 8;
	ls = (unsigned short)res & 0xFF;
}

void CPU::add(unsigned short& dest, const unsigned short val) {
	int res = dest + val;
	flag.setFlag(SUB, false);
	flag.setFlag(HALF, (dest & 0xFFF) + (val & 0xFFF) > 0xFFF);
	flag.setFlag(CARRY, res > 0xFFFF);

	dest = (unsigned short)res;
}

void CPU::INC(unsigned char& ms, unsigned char& ls) {
	int res = ((ms << 8) | ls) + 1;
	ms = ((unsigned short)res & 0xFF00) >> 8;
	ls = (unsigned short)res & 0xFF;
}

void CPU::DEC(unsigned char& ms, unsigned char& ls) {
	int res = ((ms << 8) | ls) - 1;
	ms = ((unsigned short)res & 0xFF00) >> 8;
	ls = (unsigned short)res & 0xFF;
}

void CPU::DAA(unsigned char& reg) {
	if (!flag.getFlag(SUB)) {
		if (flag.getFlag(CARRY) || reg > 0x99) {
			reg += 0x60;
			flag.setFlag(CARRY, true);
		}

		if (flag.getFlag(HALF) || (reg & 0xF) > 0x9) 
			reg += 0x6;
		return;
	}

	if (flag.getFlag(CARRY))
		reg -= 0x60;

	if (flag.getFlag(HALF))
		reg -= 0x6;

	flag.setFlag(ZERO, (A == 0));
	flag.setFlag(HALF, false);
}

void CPU::CPL(unsigned char& reg) {
	reg = ~reg;
	flag.setFlag(SUB, true);
	flag.setFlag(HALF, true);
}

void CPU::CCF() {
	flag.setFlag(CARRY, !flag.getFlag(CARRY));
	flag.setFlag(SUB, false);
	flag.setFlag(HALF, false);
}

void CPU::SCF() {
	flag.setFlag(CARRY, true);
	flag.setFlag(SUB, false);
	flag.setFlag(HALF, false);
}


void CPU::RLCA() {
	
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

