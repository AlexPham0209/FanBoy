#pragma once
#include "CPU/CPU.h"
#include "Memory/Memory.h"

class GameBoy {
	public:

		GameBoy(const char* file);
		void emulate();
		void emulate(int iterations);
		void write(unsigned short address, unsigned char val);
		void clear();
		unsigned char read(unsigned short address);
	private:
		CPU mCPU;
		Memory memory;
};