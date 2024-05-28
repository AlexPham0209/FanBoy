#pragma once
#include "CPU/CPU.h"
#include "Memory/Memory.h"
#include "Cartridge/Cartridge.h"

class GameBoy {
	public:
		GameBoy(const char* path);
		GameBoy(Cartridge& cartridge);
		~GameBoy();
		void step();
		

	private:
		Cartridge& cartridge;
		Memory memory;
		Interrupts interrupts;
		Timer timer;
		CPU mCPU;

		Cartridge& generateCartridge(const char* path);
};