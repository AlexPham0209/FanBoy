#include "GameBoy.h"
#include "Cartridge/Cartridge.h"
#include <iostream>
#include "Cartridge/CartridgeFactory.h"

GameBoy::GameBoy(Cartridge& cartridge) : cartridge(cartridge), memory(Memory(cartridge)), 
interrupts(Interrupts(memory)), mCPU(CPU(memory, interrupts)), timer(Timer(memory, interrupts)) {}

GameBoy::GameBoy(const char* path) : cartridge(this->generateCartridge(path)), memory(cartridge), 
interrupts(Interrupts(memory)), mCPU(CPU(memory, interrupts)), timer(Timer(memory, interrupts)) {}

GameBoy::~GameBoy() {
	delete &cartridge;
}

void GameBoy::step() {
	interrupts.handleInterrupts(mCPU);
	int cycles = mCPU.step();
	timer.step(cycles);
}

Cartridge& GameBoy::generateCartridge(const char* path) {
	CartridgeFactory* factory = CartridgeFactory::getInstance();
	Cartridge* cartridge = factory->createCartridge(path);
	return *cartridge;
}
