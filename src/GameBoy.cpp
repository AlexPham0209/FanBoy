#include "GameBoy.h"
#include "Cartridge/Cartridge.h"
#include <iostream>
#include "Cartridge/CartridgeFactory.h"

GameBoy::GameBoy(Cartridge& cartridge) : cartridge(cartridge), joypad(Joypad(interrupts)), memory(Memory(cartridge, joypad)),
interrupts(Interrupts(memory)), mCPU(CPU(memory, interrupts)), timer(Timer(memory, interrupts)), buffer(PixelBuffer(160, 144)), mPPU(buffer, memory, interrupts) {}

GameBoy::GameBoy(const char* path) : cartridge(this->loadCartridge(path)), joypad(Joypad(interrupts)), memory(Memory(cartridge, joypad)),
interrupts(Interrupts(memory)), mCPU(CPU(memory, interrupts)), timer(Timer(memory, interrupts)), buffer(PixelBuffer(160, 144)), mPPU(buffer, memory, interrupts) {}

GameBoy::~GameBoy() {
	delete &cartridge;
}

void GameBoy::step() {
	if (!running)
		return;

	interrupts.handleInterrupts(mCPU);
	int cycles = mCPU.step();
	timer.step(cycles);
	mPPU.step(cycles);
}

void GameBoy::pressButton(unsigned char input) {
	joypad.pressButton(input);
}

void GameBoy::releaseButton(unsigned char input) {
	joypad.releaseButton(input);
}

unsigned int* GameBoy::getFrame() {
	return buffer.getFrame();
}

Cartridge& GameBoy::loadCartridge(const char* path) {
	running = true;
	CartridgeFactory* factory = CartridgeFactory::getInstance();
	Cartridge* cartridge = factory->createCartridge(path);
	return *cartridge;
}

void GameBoy::removeCartridge() {
	delete& cartridge;
	buffer.reset();
	mCPU.reset();
	mPPU.reset();
	timer.reset();
	interrupts.reset();
	joypad.reset();

	running = false;
}


bool GameBoy::canRender() {
	return mPPU.canRender;
}