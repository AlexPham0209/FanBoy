#include <iostream>
#include "../src/GameBoy.h"
#include "../src/Cartridge/CartridgeFactory.h"

int main() {
	const char* tetris = "C:/Users/RedAP/Desktop/Tetris.gb";
	const char* test = "C:/Users/RedAP/Downloads/06-ld r,r.gb";

	//Creates Cartridge
	CartridgeFactory* cartridgeFactory = CartridgeFactory::getInstance();
	Cartridge* cartridge = cartridgeFactory->createCartridge(test);

	Memory* memory = new Memory(*cartridge);
	CPU* mCPU = new CPU(*memory);
	mCPU->run(1035);


	delete cartridge;
	delete memory;
	delete mCPU;
	return 0;
}