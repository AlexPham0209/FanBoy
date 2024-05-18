#include "Opcodes.h"

//Put byte into register
void CPU::loadByteIntoReg(unsigned char& reg, const unsigned char& val) {
	reg = val;
}

//Put byte inside address (AB) into register, then decrement the 16 bit register
void CPU::loadByteIntoRegDecrement(unsigned char& dest, Register16& src) {
	loadByteIntoReg(dest, memory.readByte(src--));
}

//Put byte inside address (AB) into register, then increment the 16 bit register
void CPU::loadByteIntoRegIncrement(unsigned char& dest, Register16& src) {
	loadByteIntoReg(dest, memory.readByte(src++));
}


//Load value inside register into memory location
void CPU::loadByteIntoMemory(const unsigned short& address, const unsigned char& reg) {
	memory.writeByte(address, reg);
}

//Load byte inside register into memory address (AB), then decrement the 16 bit register 
void CPU::loadByteIntoMemoryDecrement(Register16& dest, unsigned char& src) {
	loadByteIntoMemory(dest--, src);
}


//Load byte inside register into memory address (AB), then decrement the 16 bit register 
void CPU::loadByteIntoMemoryIncrement(Register16& dest, unsigned char& src) {
	loadByteIntoMemory(dest++, src);
}

//Load short into the 16 bit register which is just 2 8 bit registers
void CPU::loadShortIntoReg(Register16& reg, const unsigned short& val) {
	reg = val;
}

//Load short into memory location
void CPU::loadShortIntoMemory(const unsigned short& address, const unsigned short& val) {
	memory.writeShort(address, val);
}

//Load 16 bit register pair into the stack pointer
void CPU::loadRegIntoSP(Register16& reg) {
	sp = reg;
};

void CPU::loadHL(unsigned char val) {
	unsigned short offset = sp + val;
	loadShortIntoReg(HL, offset);

	F.setFlag(ZERO, false);
	F.setFlag(SUB, false);
	F.setFlag(HALF, ((sp ^ val ^ (offset & 0xFFFF)) & 0x10) == 0x10);
	F.setFlag(CARRY, ((sp ^ val ^ (offset & 0xFFFF)) & 0x100) == 0x100);
}

//Pushes values inside register pair onto the stack (decrements SP twice)
void CPU::push(Register16& reg) {
	memory.writeByte(--sp, reg.getHigh());
	memory.writeByte(--sp, reg.getLow());
}

//Pushes values inside register pair onto the stack (decrements SP twice)
void CPU::push(unsigned short val) {
	memory.writeByte(--sp, (val & 0xFF00) >> 8);
	memory.writeByte(--sp, (val & 0xFF));
}


//Pops the top two bytes off the stack and stores them inside register pair (increments SP twice)
void CPU::pop(Register16& reg) {
	unsigned char n1 = memory.writeByte(sp++, 0);
	unsigned char n2 = memory.writeByte(sp++, 0);
	reg = (n2 << 8) | n1;
}

//Pops the top two bytes off the stack and stores them inside register pair (increments SP twice)
void CPU::pop(unsigned short& val) {
	unsigned char n1 = memory.writeByte(sp++, 0);
	unsigned char n2 = memory.writeByte(sp++, 0);
	val = (n2 << 8) | n1;
}

//Adds a register and another value togethers and stores the result into the register
void CPU::add(unsigned char& reg, const unsigned char val) {
	int res = reg + val;

	//Set flags 
	F.setFlag(ZERO, ((unsigned char)res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, ((reg & 0xF) + (val & 0xF) > 0xF));
	F.setFlag(CARRY, (res > 0xFF));

	reg = (unsigned char)res;
}

void CPU::add(Register16& reg, const unsigned short val) {
	int res = reg + val;

	F.setFlag(SUB, false);
	F.setFlag(HALF, (reg & 0xFFF) + (val & 0xFFF) > 0xFFF);
	F.setFlag(CARRY, res > 0xFFFF);

	reg = res;
}

//Adds a register and another value togethers and stores the result into the register
void CPU::addCarry(unsigned char& reg, const unsigned char val) {
	int res = reg + val + F.getFlag(CARRY);

	//Set flags 
	F.setFlag(ZERO, ((unsigned char)res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, ((reg & 0xF) + (val & 0xF) + F.getFlag(CARRY) > 0xF));
	F.setFlag(CARRY, (res > 0xFF));

	reg = (unsigned char)res;
}

void CPU::sub(unsigned char& reg, const unsigned char val) {
	int res = reg - val;

	//Set flags 
	F.setFlag(ZERO, ((unsigned char)res == 0));
	F.setFlag(SUB, true);
	F.setFlag(HALF, ((reg & 0xF) - (val & 0xF) < 0));
	F.setFlag(CARRY, (res < 0));

	reg = (unsigned char)res;
}

void CPU::subBorrow(unsigned char& reg, const unsigned char val) {
	int res = reg - val - F.getFlag(CARRY);

	//Set flags 
	F.setFlag(ZERO, ((unsigned char)res == 0));
	F.setFlag(SUB, true);
	F.setFlag(HALF, ((reg & 0xF) - (val & 0xF) - F.getFlag(CARRY) < 0));
	F.setFlag(CARRY, (res < 0));

	reg = (unsigned char)res;
}

void CPU::AND(unsigned char& reg, const unsigned char val) {
	unsigned char res = reg & val;

	//Set flags 
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, true);
	F.setFlag(CARRY, false);

	reg = res;
}

void CPU::OR(unsigned char& reg, const unsigned val) {
	unsigned char res = reg | val;

	//Set flags 
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, false);

	reg = res;
}

void CPU::XOR(unsigned char& reg, const unsigned val) {
	unsigned char res = reg ^ val;

	//Set flags 
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, false);

	reg = res;
}

void CPU::CP(unsigned char& reg, const unsigned char val) {
	F.setFlag(ZERO, (reg == val));
	F.setFlag(SUB, true);
	F.setFlag(HALF, ((reg & 0xF) < (val & 0xF)));
	F.setFlag(CARRY, (reg < val));
}


void CPU::INC(unsigned char& reg) {
	int res = reg + 1;
	F.setFlag(ZERO, ((unsigned char)res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, ((reg & 0x0F) == 0x0F));

	reg = (unsigned char)res;
}

void CPU::INC(const unsigned short address) {
	int res = memory.readByte(address) + 1;
	F.setFlag(ZERO, ((unsigned char)res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, ((memory.readByte(address) & 0x0F) == 0x0F));

	memory.writeByte(address, (unsigned char)res);
}


void CPU::DEC(unsigned char& reg) {
	int res = reg - 1;
	F.setFlag(ZERO, ((unsigned char)res == 0));
	F.setFlag(SUB, true);
	F.setFlag(HALF, ((reg & 0x0F) == 0));

	reg = res;
}

void CPU::DEC(const unsigned short address) {
	int res = memory.readByte(address) + 1;
	F.setFlag(ZERO, ((unsigned char)res == 0));
	F.setFlag(SUB, true);
	F.setFlag(HALF, ((memory.readByte(address) & 0x0F) == 0));

	memory.writeByte(address, res);
}


void CPU::addSP(const char val) {
	int res = sp + val;
	F.setFlag(SUB, false);
	F.setFlag(HALF, ((sp ^ val ^ (res & 0xFFFF)) & 0x10) == 0x10);
	F.setFlag(CARRY, ((sp ^ val ^ (res & 0xFFFF)) & 0x100) == 0x100);

	sp = (unsigned short)res;
}

void CPU::INC(Register16& reg) {
	reg++;
}

void CPU::DEC(Register16& reg) {
	reg--;
}

void CPU::DAA(unsigned char& reg) {
	if (!F.getFlag(SUB)) {
		if (F.getFlag(CARRY) || reg > 0x99) {
			reg += 0x60;
			F.setFlag(CARRY, true);
		}

		if (F.getFlag(HALF) || (reg & 0xF) > 0x9)
			reg += 0x6;
		return;
	}

	if (F.getFlag(CARRY))
		reg -= 0x60;

	if (F.getFlag(HALF))
		reg -= 0x6;

	F.setFlag(ZERO, (A == 0));
	F.setFlag(HALF, false);
}

void CPU::CPL(unsigned char& reg) {
	reg = ~reg;
	F.setFlag(SUB, true);
	F.setFlag(HALF, true);
}

void CPU::CCF() {
	F.setFlag(CARRY, !F.getFlag(CARRY));
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
}

void CPU::SCF() {
	F.setFlag(CARRY, true);
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
}


void CPU::RLC(unsigned char& reg) {
	unsigned char res = (reg << 1) | ((reg >> 7) & 1);
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, (reg >> 7) & 1);
	reg = res;
}

void CPU::RL(unsigned char& reg) {
	unsigned char res = (reg << 1) | F.getFlag(CARRY);
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, (reg >> 7) & 1);
	reg = res;
}

void CPU::RRC(unsigned char& reg) {
	unsigned char res = (reg >> 1) | ((reg & 1) << 7);
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, (reg >> 7) & 1);
	reg = res;
}

void CPU::RR(unsigned char& reg) {
	unsigned char res = (reg >> 1) | (F.getFlag(CARRY) << 7);
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, (reg >> 7) & 1);
	reg = res;
}

void CPU::jump(unsigned short address) {
	pc = address;
}

void CPU::jump(char val) {
	pc += val;
}

void CPU::jump(unsigned short address, bool condition) {
	if (condition)
		pc += address;
	else
		pc += 2;
}

void CPU::jump(char val, bool condition) {
	if (condition)
		pc += val;
	else
		pc += 2;
}

void CPU::call(unsigned short address) {
	push(pc + 2);
	jump(address);
}

void CPU::call(unsigned short address, bool condition) {
	if (condition)
		call(address);
	else
		pc += 2;
}

void CPU::restart(unsigned char val) {
	push(pc);
	jump((char)(0x0000 + val));
}

void CPU::ret() {
	pop(pc);
}

void CPU::ret(bool condition) {
	if (condition)
		ret();
}
