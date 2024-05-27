#include <iostream>
#include "../src/GameBoy.h"
#include "../src/Cartridge/CartridgeFactory.h"

int main() {
	const char* tetris = "C:/Users/RedAP/Desktop/Tetris.gb";
	const char* specialTest = "C:/Users/RedAP/Desktop/01-special.gb";
	const char* loadTest = "C:/Users/RedAP/Downloads/06-ld r,r.gb";

	//Creates Cartridge
	CartridgeFactory* cartridgeFactory = CartridgeFactory::getInstance();
	Cartridge* cartridge = cartridgeFactory->createCartridge("C:/Users/RedAP/Downloads/07-jr,jp,call,ret,rst.gb");

	Memory* memory = new Memory(*cartridge);
	CPU* mCPU = new CPU(*memory);
	mCPU->run();

	delete cartridge;
	delete memory;
	delete mCPU;
	return 0;
}