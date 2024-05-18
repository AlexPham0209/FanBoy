#include <gtest/gtest.h>
#include "../src/GameBoy.h"

TEST(SampleTest, Testing1) {
	//Set value at address 0x101B to 0x26.
	GameBoy* gameBoy = new GameBoy();
	gameBoy->write(0x101B, 0x26);

	//Set B to 0xF
	gameBoy->write(0x100, 0x06);
	gameBoy->write(0x101, 0x0F);

	//Set H to 0x10
	gameBoy->write(0x102, 0x26);
	gameBoy->write(0x103, 0x10);

	//Set L to 0x1B
	gameBoy->write(0x104, 0x2E);
	gameBoy->write(0x105, 0x1B);

	//Set B to val in address 0x101B
	gameBoy->write(0x106, 0x46);
	gameBoy->write(0x107, 0x48);


	//Set B to 0xF
	gameBoy->write(0x108, 0x06);
	gameBoy->write(0x109, 0x09);

	//Writing val of B into address 
	gameBoy->write(0x10A, 0x70);
	gameBoy->emulate(7);

	EXPECT_EQ(gameBoy->read(0x101B), 9);
}