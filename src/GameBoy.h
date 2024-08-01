#pragma once
#include "CPU/CPU.h"
#include "Memory/Memory.h"
#include "Cartridge/Cartridge.h"
#include "Graphics/PPU.h"
#include "Joypad.h"

class GameBoy {
	public:
		GameBoy(const char* path);
		GameBoy(Cartridge* cartridge);
		GameBoy();
		~GameBoy();

		void step();
		void pressButton(unsigned char input);
		void releaseButton(unsigned char input);

		void loadGame(const char* path);
		void unloadGame();
		unsigned int* getFrame();
		bool canRender();
		bool isRunning();

	private:
		bool running = false;
		Cartridge* cartridge;
		Joypad joypad;
		Memory memory;
		Interrupts interrupts;
		Timer timer;
		PixelBuffer buffer;
		CPU mCPU;
		PPU mPPU;
		
		Cartridge* loadCartridge(const char* path);
};