#include <iostream>
#include "../src/GameBoy.h"
#include "../src/Cartridge/CartridgeFactory.h"

int main() {
	const char* tetris = "C:/Users/RedAP/Desktop/Tetris.gb";
	const char* test = "C:/Users/RedAP/Downloads/06-ld r,r.gb";
	Cartridge* cartridge = CartridgeFactory::getInstance()->createCartridge(tetris);
	std::cout << cartridge->header.title << std::endl;
	/*Memory* memory = new Memory("C:/Users/RedAP/Downloads/06-ld r,r.gb");
	CPU* mCPU = new CPU(*memory);
	mCPU->run(20);s

	if (memory->readByte(0xFF02) == 0x81) {
		char c = memory->readByte(0xff01);
		printf("%c", c);
		memory->writeByte(0xff02, 0x0);
	}

	delete memory;
	delete mCPU;*/
	delete cartridge;

	return 0;
}