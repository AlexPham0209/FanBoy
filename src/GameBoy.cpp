#include "GameBoy.h"
#include "Cartridge/Cartridge.h"
#include <iostream>
#include "Cartridge/CartridgeFactory.h"

GameBoy::GameBoy(Cartridge& cartridge) : cartridge(cartridge), joypad(Joypad(interrupts)), memory(Memory(cartridge, joypad)),
interrupts(Interrupts(memory)), mCPU(CPU(memory, interrupts)), timer(Timer(memory, interrupts)), buffer(PixelBuffer(160, 144)), mPPU(buffer, memory, interrupts) {}

GameBoy::GameBoy(const char* path) : cartridge(this->generateCartridge(path)), joypad(Joypad(interrupts)), memory(Memory(cartridge, joypad)),
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

void GameBoy::pressButton(unsigned char input, SELECT mode) {
	joypad.pressButton(input, mode);
}

void GameBoy::releaseButton(unsigned char input, SELECT mode) {
	joypad.releaseButton(input, mode);
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