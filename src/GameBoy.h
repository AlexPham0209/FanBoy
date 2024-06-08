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
		GameBoy();
		~GameBoy();

		void step();
		Cartridge& loadCartridge(const char* path);
		void removeCartridge();

		void pressButton(unsigned char input);
		void releaseButton(unsigned char input);
		unsigned int* getFrame();
		bool canRender();
		

	private:
		bool running = false;
		Cartridge& cartridge;
		Joypad joypad;
		Memory memory;
		Interrupts interrupts;
		Timer timer;
		PixelBuffer buffer;
		CPU mCPU;
		PPU mPPU;
	
};