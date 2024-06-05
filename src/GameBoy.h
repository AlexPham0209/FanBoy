#pragma once
#include "CPU/CPU.h"
#include "Memory/Memory.h"
#include "Cartridge/Cartridge.h"
#include "Graphics/PPU.h"
#include "Joypad.h"

class GameBoy {
	public:
		GameBoy(const char* path);
		GameBoy(Cartridge& cartridge);
		void pressButton(unsigned char input, SELECT mode);
		void releaseButton(unsigned char input, SELECT mode);
		unsigned int* getFrame();

		~GameBoy();
		void step();
		bool canRender();
		

	private:
		Cartridge& cartridge;
		Joypad joypad;
		Memory memory;
		Interrupts interrupts;
		Timer timer;
		PixelBuffer buffer;
		CPU mCPU;
		PPU mPPU;
		

		Cartridge& generateCartridge(const char* path);
};