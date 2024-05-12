#pragma once
#include "../Memory/Memory.h"
class CPU {
	public:
		CPU(Memory& memory);
		int step();
		void run(int iterations);
	private:
		unsigned char A, B, C, D, E, F, H, L;
		unsigned short sp, pc;
		int cycles;
		
		Memory& memory;

		void executeOpcode(unsigned char opcode);
		unsigned char fetchOpcode();
		void LDNN(unsigned char& reg, const unsigned char& val);
		void LDR(unsigned char& reg, const unsigned char& val);
		void LDR(const unsigned short& address, const unsigned char& reg);
};