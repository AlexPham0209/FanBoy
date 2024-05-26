#include <gtest/gtest.h>
#include "../src/GameBoy.h"
#include "../src/Cartridge/CartridgeFactory.h"

//TEST(SampleTest, Testing1) {
//	//Set value at address 0x101B to 0x26.
//	GameBoy* gameBoy = new GameBoy();
//	gameBoy->write(0x101B, 0x26);
//
//	//Set B to 0xF
//	gameBoy->write(0x100, 0x06);
//	gameBoy->write(0x101, 0x0F);
//
//	//Set H to 0x10
//	gameBoy->write(0x102, 0x26);
//	gameBoy->write(0x103, 0x10);
//
//	//Set L to 0x1B
//	gameBoy->write(0x104, 0x2E);
//	gameBoy->write(0x105, 0x1B);
//
//	//Set B to val in address 0x101B
//	gameBoy->write(0x106, 0x46);
//	gameBoy->write(0x107, 0x48);
//
//
//	//Set B to 0xF
//	gameBoy->write(0x108, 0x06);
//	gameBoy->write(0x109, 0x09);
//
//	//Writing val of B into address 
//	gameBoy->write(0x10A, 0x70);
//	gameBoy->emulate(7);
//
//	EXPECT_EQ(gameBoy->read(0x101B), 9);
//}

TEST(SampleTest, StackTest) {
	std::vector<unsigned char> rom = {
		//Write FF into register H (LD H, n)
		0x26, 0xFF,

		//Write A in register L (LD L, n)
		0x2E, 0x0A,

		//Write A2 in register A (LD A, n)
		0x3E, 0xA2,

		//Load A into memory location (HL) and decrement the HL register (LD (HL), A)
		0x32
	};

	Cartridge* cartridge = CartridgeFactory::getInstance()->createCartridge(rom);
	Memory* memory = new Memory(*cartridge);
	CPU* mCPU = new CPU(*memory);
	mCPU->run(4);

	EXPECT_EQ(memory->readByte(0xFF0A), 0xA2);
	EXPECT_EQ((int)((mCPU->H << 8) | mCPU->L), 0xFF0A - 1);

	delete memory;
	delete mCPU;
	delete cartridge;
}