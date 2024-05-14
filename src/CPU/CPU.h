#pragma once
#include "../Memory/Memory.h"
class CPU {
	public:
		unsigned char A, B, C, D, E, F, H, L;
		unsigned short sp, pc;
		int cycles;

		CPU(Memory& memory);
		int step();
		void run(int iterations);

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
};