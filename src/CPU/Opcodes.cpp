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

void CPU::loadHL(char val) {
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
	unsigned char n1 = memory.readByte(sp++);
	unsigned char n2 = memory.readByte(sp++);
	reg = (n2 << 8) | n1;
}

//Pops the top two bytes off the stack and stores them inside register pair (increments SP twice)
void CPU::pop(unsigned short& val) {
	unsigned char n1 = memory.readByte(sp++);
	unsigned char n2 = memory.readByte(sp++);
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
	unsigned char res = reg + 1;
	F.setFlag(ZERO, ((unsigned char)res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, ((reg & 0x0F) == 0x0F));

	reg = res;
}

void CPU::INC(const unsigned short address) {
	unsigned char res = memory.readByte(address) + 1;
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, ((memory.readByte(address) & 0x0F) == 0x0F));

	memory.writeByte(address, res);
}


void CPU::DEC(unsigned char& reg) {
	unsigned char res = reg - 1;
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, true);
	F.setFlag(HALF, (reg & 0x0F) == 0);

	reg = res;
}

void CPU::DEC(const unsigned short address) {
	unsigned char res = memory.readByte(address) - 1;
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, true);
	F.setFlag(HALF, (memory.readByte(address) & 0x0F) == 0);

	memory.writeByte(address, res);
}


void CPU::addSP(const char val) {
	int res = sp + val;
	F.setFlag(ZERO, false);
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
	unsigned char val = reg;
	if (F.getFlag(SUB)) {
		if (F.getFlag(CARRY))
			val -= 0x60;

		if (F.getFlag(HALF))
			val -= 0x6;

	}
	else {
		if (F.getFlag(CARRY) || val > 0x99) {
			val += 0x60;
			F.setFlag(CARRY, true);
		}

		if (F.getFlag(HALF) || (val & 0xF) > 0x9)
			val += 0x6;
	}
	
	reg = val;
	F.setFlag(ZERO, (reg == 0));
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

unsigned char CPU::rotateLeftCarry(unsigned char val) {
	unsigned char res = (val << 1) | ((val >> 7) & 1);
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, (val >> 7) & 1);
	return res;
}

void CPU::RLC(unsigned char& reg) {
	reg = rotateLeftCarry(reg);
}

void CPU::RLC(unsigned short address) {
	unsigned char res = rotateLeftCarry(memory.readByte(address));
	memory.writeByte(address, res);
}

unsigned char CPU::rotateLeft(unsigned char val) {
	unsigned char res = (val << 1) | F.getFlag(CARRY);
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, (val >> 7) & 1);
	return res;
}

void CPU::RL(unsigned char& reg) {
	reg = rotateLeft(reg);
}

void CPU::RL(unsigned short address) {
	unsigned char res = rotateLeft(memory.readByte(address));
	memory.writeByte(address, res);
}

unsigned char CPU::rotateRightCarry(unsigned char val) {
	unsigned char res = (val >> 1) | ((val & 1) << 7);
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, val & 1);
	return res;
}

void CPU::RRC(unsigned char& reg) {
	reg = rotateRightCarry(reg);
}

void CPU::RRC(unsigned short address) {
	unsigned char res = rotateRightCarry(memory.readByte(address));
	memory.writeByte(address, res);
}

unsigned char CPU::rotateRight(unsigned char val) {
	unsigned char res = (val >> 1) | (F.getFlag(CARRY) << 7);
	F.setFlag(ZERO, (res == 0));
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, val & 1);
	return res;
}

void CPU::RR(unsigned char& reg) {
	reg = rotateRight(reg);
}

void CPU::RR(unsigned short address) {
	unsigned char res = rotateRight(memory.readByte(address));
	memory.writeByte(address, res);
}

void CPU::jump(unsigned short address) {
	pc = address;
}

void CPU::jump(char val) {
	pc += val;
}

void CPU::jump(unsigned short address, bool condition) {
	branchTaken = condition;
	if (condition)
		pc = address;
	else
		pc += 2;
}

void CPU::jump(char val, bool condition) {
	branchTaken = condition;
	if (condition)
		pc += val;
}

void CPU::call(unsigned short address) {
	push(pc + 2);
	jump(address);
}

void CPU::call(unsigned short address, bool condition) {
	branchTaken = condition;
	if (condition)
		call(address);
	else
		pc += 2;
}

void CPU::restart(unsigned char val) {
	push(pc);
	jump((unsigned short)(0x00 + val));
}

void CPU::ret() {
	pop(pc);
}

void CPU::ret(bool condition) {
	branchTaken = condition;
	if (condition)
		ret();
}

void CPU::reti() {
	ret();
	interrupts.setIME(true);
}

void CPU::swap(unsigned char& reg) {
	unsigned char upper = (reg & 0xF0) >> 4;
	unsigned char lower = (reg & 0xF);
	reg = (lower << 4) | upper;

	F.setFlag(ZERO, reg == 0);
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, false);
}

void CPU::swap(unsigned short address) {
	unsigned char val = memory.readByte(address);
	unsigned char upper = (val & 0xF0) >> 4;
	unsigned char lower = (val & 0xF);
	unsigned char res = (lower << 4) | upper;

	memory.writeByte(address, res);

	F.setFlag(ZERO, res == 0);
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, false);
}

unsigned char CPU::shiftLeft(unsigned char val) {
	unsigned char res = val << 1;

	F.setFlag(ZERO, res == 0);
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, (val >> 7) & 1);

	return res;
}

unsigned char CPU::shiftRight(unsigned char val) {
	unsigned char res = val >> 1;

	F.setFlag(ZERO, res == 0);
	F.setFlag(SUB, false);
	F.setFlag(HALF, false);
	F.setFlag(CARRY, val & 1);

	return res;
}

void CPU::SLA(unsigned char& reg) {
	reg = shiftLeft(reg);
	reg = reg & ~1;
}
void CPU::SLA(unsigned short address) {
	unsigned char res = shiftLeft(memory.readByte(address));
	res = res & ~1;
	memory.writeByte(address, res);
}

void CPU::SRL(unsigned char& reg) {
	reg = shiftRight(reg);
	reg = reg & ~(1 << 7);
}

void CPU::SRL(unsigned short address) {
	unsigned char res = shiftRight(memory.readByte(address));
	res = res & ~(1 << 7);
	memory.writeByte(address, res);
}


void CPU::SRA(unsigned char& reg) {
	unsigned char res = shiftRight(reg);
	res = res | (((reg >> 7) & 1) << 7);
	reg = res;
}

void CPU::SRA(unsigned short address) {
	unsigned char res = shiftRight(memory.readByte(address));
	res = res | (((memory.readByte(address) >> 7) & 1) << 7);
	memory.writeByte(address, res);
}

unsigned char CPU::testBit(unsigned char bit, unsigned char val) {
	if (bit < 0 || bit > 7)
		return 0x0;
	unsigned char res = (val >> bit) & 1;

	F.setFlag(ZERO, !res);
	F.setFlag(SUB, false);
	F.setFlag(HALF, true);
	return res;
}

void CPU::BIT(unsigned char bit, unsigned char& reg) {
	testBit(bit, reg);
}
void CPU::BIT(unsigned char bit, unsigned short address) {
	testBit(bit, memory.readByte(address));
}

unsigned char CPU::setBit(unsigned char bit, unsigned char val) {
	if (bit < 0 || bit > 7)
		return 0x0;
	unsigned char res = val | (1 << bit);
	return res;
}

void CPU::SET(unsigned char bit, unsigned char& reg) {
	reg = setBit(bit, reg);
}

void CPU::SET(unsigned char bit, unsigned short address) {
	unsigned char res = setBit(bit, memory.readByte(address));
	memory.writeByte(address, res);
}

unsigned char CPU::resetBit(unsigned char bit, unsigned char val) {
	if (bit < 0 || bit > 7)
		return 0x0;
	unsigned char res = val & ~(1 << bit);
	return res;
}

void CPU::RES(unsigned char bit, unsigned char& reg) {
	reg = resetBit(bit, reg);
}
void CPU::RES(unsigned char bit, unsigned short address) {
	unsigned char res = resetBit(bit, memory.readByte(address));
	memory.writeByte(address, res);
}