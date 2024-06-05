#pragma once
#include "../Memory/Memory.h"
#include "Register.h"
#include "Interrupts.h"
#include "Timer.h"

class CPU {
	public:
		//General purpose registers
		unsigned char A, B, C, D, E, H, L;
		FlagRegister F;
		
		Register16 AF, BC, DE, HL;

		unsigned char IF;
		unsigned short sp, pc;
		int cycles;

		bool halt = false;
		bool branchTaken = false;

		CPU(Memory& memory, Interrupts& interrupts);
		int step();
		void reset();
		void resetBoot();

		//Stack operation
		void push(Register16& reg);
		void push(unsigned short val);
		void pop(Register16& reg);
		void pop(unsigned short& val);
		std::string debug();

	private:
		Memory& memory;
		Interrupts& interrupts;

		void executeOpcode(unsigned char opcode);
		void executeCBOpcodes(unsigned char opcode);
		unsigned char fetchOpcode();

		void loadByteIntoReg(unsigned char& dest, const unsigned char& src);
		void loadByteIntoRegDecrement(unsigned char& src, Register16& dest);
		void loadByteIntoRegIncrement(unsigned char& src, Register16& dest);

		void loadByteIntoMemory(const unsigned short& dest, const unsigned char& src);
		void loadByteIntoMemoryDecrement(Register16& dest, unsigned char& src);
		void loadByteIntoMemoryIncrement(Register16& dest, unsigned char& src);

		void loadShortIntoReg(unsigned char& reg1, unsigned char& reg2);
		void loadShortIntoReg(Register16& reg, const unsigned short& val);

		void loadShortIntoMemory(const unsigned short& address, const unsigned short& val);

		void loadRegIntoSP(Register16& reg);
		void loadHL(char val);

		void add(unsigned char& reg, const unsigned char val);
		void add(Register16& reg, const unsigned short val);
		void addCarry(unsigned char& reg, const unsigned char val);

		void addSP(char val);

		void sub(unsigned char& reg, const unsigned char val);
		void subBorrow(unsigned char& reg, const unsigned char val);

		void AND(unsigned char& reg, const unsigned char val);
		void OR(unsigned char& reg, const unsigned val);
		void XOR(unsigned char& reg, const unsigned val);
		void CP(unsigned char& reg, const unsigned char val);

		void INC(unsigned char& reg);
		void INC(Register16& reg);
		void INC(const unsigned short address);
	

		void DEC(unsigned char& reg);
		void DEC(Register16& reg);
		void DEC(const unsigned short address);
		

		void DAA(unsigned char& reg);
		void CPL(unsigned char& reg);
		void CCF();
		void SCF();

		unsigned char rotateLeftCarry(unsigned char val);
		void RLC(unsigned char& reg);
		void RLC(unsigned short address);
		
		unsigned char rotateLeft(unsigned char val);
		void RL(unsigned char& reg);
		void RL(unsigned short address);

		unsigned char rotateRightCarry(unsigned char val);
		void RRC(unsigned char& reg);
		void RRC(unsigned short address);
		
		unsigned char rotateRight(unsigned char val);
		void RR(unsigned char& reg);
		void RR(unsigned short address);

		void jump(unsigned short address);
		void jump(unsigned short address, bool condition);

		void jump(char val);
		void jump(char val, bool condition);

		void call(unsigned short address);
		void call(unsigned short address, bool condition);

		void restart(unsigned char val);

		void ret();
		void ret(bool condition);
		void reti();

		void swap(unsigned char& reg);
		void swap(unsigned short address);

		unsigned char shiftLeft(unsigned char val);
		void SLA(unsigned char& reg);
		void SLA(unsigned short address);

		unsigned char shiftRight(unsigned char val);
		void SRA(unsigned char& reg);
		void SRA(unsigned short address);

		void SRL(unsigned char& reg);
		void SRL(unsigned short address);
		
		unsigned char testBit(unsigned char bit, unsigned char val);
		void BIT(unsigned char bit, unsigned char& reg);
		void BIT(unsigned char bit, unsigned short address);

		unsigned char setBit(unsigned char bit, unsigned char val);
		void SET(unsigned char bit, unsigned char& reg);
		void SET(unsigned char bit, unsigned short address);

		unsigned char resetBit(unsigned char bit, unsigned char val);
		void RES(unsigned char bit, unsigned char& reg);
		void RES(unsigned char bit, unsigned short address);
};
