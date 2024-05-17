#pragma once
#include "../Memory/Memory.h"
#include "Flag.h"
class CPU {
	public:
		unsigned char A, B, C, D, E, F, H, L;
		Flag flag;
		unsigned short sp, pc;
		int cycles;

		bool running;

		CPU(Memory& memory);
		int step();
		void run(int iterations);
		void reset();

	private:
		Memory& memory;

		void executeOpcode(unsigned char opcode);
		unsigned char fetchOpcode();

		void loadByteIntoReg(unsigned char& reg, const unsigned char& val);
		void loadByteIntoRegDecrement(unsigned char& reg, unsigned char& a, unsigned char& b);
		void loadByteIntoRegIncrement(unsigned char& reg, unsigned char& a, unsigned char& b);

		void loadByteIntoMemory(const unsigned short& address, const unsigned char& val);
		void loadByteIntoMemoryDecrement(unsigned char& reg, unsigned char& a, unsigned char& b);
		void loadByteIntoMemoryIncrement(unsigned char& reg, unsigned char& a, unsigned char& b);

		void loadShortIntoReg(unsigned char& reg1, unsigned char& reg2);
		void loadShortIntoReg(unsigned char& reg1, unsigned char& reg2, const unsigned short& val);

		void loadShortIntoMemory(const unsigned short& address, const unsigned short& val);

		void loadRegIntoSP(unsigned char& a, unsigned char& b);

		void push(unsigned char a, unsigned char b);
		void pop(unsigned char& a, unsigned char& b);

		void add(unsigned char& reg, const unsigned char val);
		void add(unsigned char& ms, unsigned char& ls, const unsigned short val);
		void add(unsigned short& dest, const unsigned short val);
			
		void addCarry(unsigned char& reg, const unsigned char val);

		void sub(unsigned char& reg, const unsigned char val);
		void subBorrow(unsigned char& reg, const unsigned char val);

		void AND(unsigned char& reg, const unsigned char val);
		void OR(unsigned char& reg, const unsigned val);
		void XOR(unsigned char& reg, const unsigned val);
		void CP(unsigned char& reg, const unsigned char val);

		void INC(unsigned char& reg);
		void INC(const unsigned short address);
		void INC(unsigned char& ms, unsigned char& ls);

		void DEC(unsigned char& reg);
		void DEC(const unsigned short address);
		void DEC(unsigned char& ms, unsigned char& ls);

		void DAA(unsigned char& reg);
		void CPL(unsigned char& reg);
		void CCF();
		void SCF();

		void RLC(unsigned char& reg);
		void RL(unsigned char& reg);

		void RRC(unsigned char& reg);
		void RR(unsigned char& reg);
};