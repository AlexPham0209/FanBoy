#include "GameBoy.h"
#include "Cartridge/Cartridge.h"
#include <iostream>
#include "Cartridge/CartridgeFactory.h"

GameBoy::GameBoy(Cartridge& cartridge) : cartridge(cartridge), memory(Memory(cartridge)), 
interrupts(Interrupts(memory)), mCPU(CPU(memory, interrupts)), timer(Timer(memory, interrupts)), buffer(PixelBuffer(160, 144)), mPPU(buffer, memory, interrupts) {}

GameBoy::GameBoy(const char* path) : cartridge(this->generateCartridge(path)), memory(cartridge), 
interrupts(Interrupts(memory)), mCPU(CPU(memory, interrupts)), timer(Timer(memory, interrupts)), buffer(PixelBuffer(160, 144)), mPPU(buffer, memory, interrupts) {}

GameBoy::~GameBoy() {
	delete &cartridge;
}

void GameBoy::step() {
	interrupts.handleInterrupts(mCPU);
	int cycles = mCPU.step();
	timer.step(cycles);
	mPPU.step(cycles);
}

void GameBoy::setInput(INPUT input) {
	unsigned char joypad = memory.readByte(0xFF00);
	joypad |= 0xF;

	switch (input) {
		case START:
			joypad = joypad &  ~(1 << 5);
			joypad = joypad & ~(1 << 3);
			break;
		
		case SELECT:
			joypad = joypad & ~(1 << 5);
			joypad = joypad & ~(1 << 2);
			break;

		case A:
			joypad = joypad & ~(1 << 5);
			joypad = joypad & ~(1 << 1);
			break;

		case B:
			joypad = joypad & ~(1 << 5);
			joypad = joypad & ~1;
			break;

		case DOWN:
			joypad = joypad & ~(1 << 4);
			joypad = joypad & ~(1 << 3);
			break;

		case UP:
			joypad = joypad & ~(1 << 4);
			joypad = joypad & ~(1 << 2);
			break;

		case LEFT:
			joypad = joypad & ~(1 << 4);
			joypad = joypad & ~(1 << 1);
			break;

		case RIGHT:
			joypad = joypad & ~(1 << 4);
			joypad = joypad & ~1;
			break;
	}

	memory.writeByte(0xFF00, joypad);
	interrupts.setInterruptFlag(JOYPAD, true);
}

unsigned int* GameBoy::getFrame() {
	return buffer.getFrame();
}



Cartridge& GameBoy::generateCartridge(const char* path) {
	CartridgeFactory* factory = CartridgeFactory::getInstance();
	Cartridge* cartridge = factory->createCartridge(path);
	return *cartridge;
}


bool GameBoy::canRender() {
	return mPPU.canRender;
}