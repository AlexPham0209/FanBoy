#pragma once
#include "CPU/CPU.h"
#include "Memory/Memory.h"
#include "Cartridge/Cartridge.h"
#include "Graphics/PPU.h"

enum INPUT {
	START,
	SELECT,
	A,
	B,
	DOWN,
	UP,
	LEFT,
	RIGHT
};

class GameBoy {
	public:
		GameBoy(const char* path);
		GameBoy(Cartridge& cartridge);
		void setInput(INPUT input);
		int* getFrame();

		~GameBoy();
		void step();
		

	private:
		Cartridge& cartridge;
		Memory memory;
		Interrupts interrupts;
		Timer timer;
		PixelBuffer buffer;
		CPU mCPU;
		PPU mPPU;

		Cartridge& generateCartridge(const char* path);
};