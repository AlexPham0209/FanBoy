#include "GameBoy.h"
#include "Cartridge/Cartridge.h"
#include <iostream>
#include "Cartridge/CartridgeFactory.h"

GameBoy::GameBoy(Cartridge* cartridge) : cartridge(cartridge), joypad(Joypad(interrupts)), memory(Memory(cartridge, joypad)),
interrupts(Interrupts(memory)), mCPU(CPU(memory, interrupts)), timer(Timer(memory, interrupts)), buffer(PixelBuffer(160, 144)), mPPU(buffer, memory, interrupts) {
	running = true;
}

GameBoy::GameBoy(const char* path) : cartridge(this->loadCartridge(path)), joypad(Joypad(interrupts)), memory(Memory(cartridge, joypad)),
interrupts(Interrupts(memory)), mCPU(CPU(memory, interrupts)), timer(Timer(memory, interrupts)), buffer(PixelBuffer(160, 144)), mPPU(buffer, memory, interrupts) {
	running = true;
}

GameBoy::GameBoy() : cartridge(nullptr), joypad(Joypad(interrupts)), memory(Memory(joypad)),
interrupts(Interrupts(memory)), mCPU(CPU(memory, interrupts)), timer(Timer(memory, interrupts)), buffer(PixelBuffer(160, 144)), mPPU(buffer, memory, interrupts) {}

GameBoy::~GameBoy() {
	unloadGame();
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

Cartridge* GameBoy::loadCartridge(const char* path) {
	CartridgeFactory* factory = CartridgeFactory::getInstance();
	Cartridge* cartridge = factory->createCartridge(path);
	return cartridge;
}

void GameBoy::loadGame(const char* path) {
	unloadGame();
	
	Cartridge* cartridge = loadCartridge(path);
	this->cartridge = cartridge;
	memory.loadCartridge(cartridge);
	running = true;
}

void GameBoy::unloadGame() {
	if (cartridge != nullptr) 
		delete cartridge;
	
	cartridge = nullptr;
	buffer.reset();
	mCPU.resetBoot();
	mPPU.reset();
	timer.reset();
	interrupts.reset();
	memory.reset();
	joypad.reset();

	running = false;
}


bool GameBoy::canRender() {
	return mPPU.canRender;
}

bool GameBoy::isRunning() {
	return running;
}
