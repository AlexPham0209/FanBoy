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

TEST(SampleTest, LoadOffsetTest) {
	Memory* memory = new Memory();
	CPU* mCPU = new CPU(*memory);

	//Write 10 (hex) into register C
	memory->writeByte(0x100, 0xE);
	memory->writeByte(0x101, 0xA);

	//Write 12 (hex) into register A
	memory->writeByte(0x102, 0x3E);
	memory->writeByte(0x103, 0xC);

	//Load value in register A into memory address (0xFF00 + C)
	memory->writeByte(0x104, 0xE2);

	mCPU->run(3);

	EXPECT_EQ((int)(memory->readByte(0xFF00 + 0xA)), 0xC);

	delete memory;
	delete mCPU;
}


TEST(SampleTest, ReadOffsetTest) {
	Memory* memory = new Memory();
	CPU* mCPU = new CPU(*memory);

	//Write 0xA2 in memory address (0xFF00 + C)
	memory->writeByte(0xFF00 + 0xA, 0xA2);

	//Write 10 (hex) into register C
	memory->writeByte(0x100, 0xE);
	memory->writeByte(0x101, 0xA);

	//Load value in register A into memory address (0xFF00 + C)
	memory->writeByte(0x103, 0xF2);

	mCPU->run(3);

	EXPECT_EQ((int)(mCPU->A), 0xA2);

	delete memory;
	delete mCPU;
}

TEST(SampleTest, LoadRegDecrementTest) {
	Memory* memory = new Memory();
	CPU* mCPU = new CPU(*memory);

	//Write 0xA2 in memory address 0xFF0A
	memory->writeByte(0xFF0A, 0xA2);

	//Write 0xFF into register H
	memory->writeByte(0x100, 0x26);
	memory->writeByte(0x101, 0xFF);

	//Write 0xA into register C
	memory->writeByte(0x102, 0x2E);
	memory->writeByte(0x103, 0x0A);

	//LDD instruction
	memory->writeByte(0x104, 0x3A);

	mCPU->run(4);

	EXPECT_EQ((int)mCPU->A, 0xA2);
	EXPECT_EQ((int)((mCPU->H << 8) | mCPU->L), 0xFF0A - 1);

	delete memory;
	delete mCPU;
}

TEST(SampleTest, LoadMemoryDecrementTest) {
	Memory* memory = new Memory();
	CPU* mCPU = new CPU(*memory);

	//Write 0xFF into register H
	memory->writeByte(0x100, 0x26);
	memory->writeByte(0x101, 0xFF);

	//Write 0xA into register C
	memory->writeByte(0x102, 0x2E);
	memory->writeByte(0x103, 0x0A);

	//Write 0xA2 into register A
	memory->writeByte(0x104, 0x3E);
	memory->writeByte(0x105, 0xA2);

	//LDD (HL), A instruction
	memory->writeByte(0x106, 0x32);

	mCPU->run(4);

	EXPECT_EQ(memory->readByte(0xFF0A), 0xA2);
	EXPECT_EQ((int)((mCPU->H << 8) | mCPU->L), 0xFF0A - 1);

	delete memory;
	delete mCPU;
}


TEST(SampleTest, StackTest) {
	Memory* memory = new Memory();
	CPU* mCPU = new CPU(*memory);

	//Write 0xFF into register H
	memory->writeByte(0x100, 0x26);
	memory->writeByte(0x101, 0xFF);

	//Write 0xA into register C
	memory->writeByte(0x102, 0x2E);
	memory->writeByte(0x103, 0x0A);

	//Write 0xA2 into register A
	memory->writeByte(0x104, 0x3E);
	memory->writeByte(0x105, 0xA2);

	//LDD (HL), A instruction
	memory->writeByte(0x106, 0x32);

	mCPU->run(4);

	EXPECT_EQ(memory->readByte(0xFF0A), 0xA2);
	EXPECT_EQ((int)((mCPU->H << 8) | mCPU->L), 0xFF0A - 1);

	delete memory;
	delete mCPU;
}


TEST(SampleTest, AdderTest) {
	Memory* memory = new Memory();
	CPU* mCPU = new CPU(*memory);

	//Write 0xFA into register B
	memory->writeByte(0x100, 0x06);
	memory->writeByte(0x101, 0b11110000);

	//Write 0xA into register A
	memory->writeByte(0x102, 0x3E);
	memory->writeByte(0x103, 0b00000000);

	//Add registers A and B
	memory->writeByte(0x104, 0x80);

	mCPU->run(3);

	EXPECT_EQ((int)mCPU->A, 240);
	EXPECT_EQ((int)(mCPU->flag.getFlag()), (0b0000 << 4));

	delete mCPU;
	delete memory;
}

TEST(SampleTest, AdderCarryTest) {
	Memory* memory = new Memory();
	CPU* mCPU = new CPU(*memory);
	mCPU->flag.setFlag(CARRY, true);

	//Write 0xFA into register B
	memory->writeByte(0x100, 0x06);
	memory->writeByte(0x101, 5);

	//Write 0xA into register A
	memory->writeByte(0x102, 0x3E);
	memory->writeByte(0x103, 2);

	//Add registers A and B
	memory->writeByte(0x104, 0x88);

	mCPU->run(3);

	EXPECT_EQ((int)mCPU->A, 8);
	EXPECT_EQ((int)(mCPU->flag.getFlag()), (0b0000 << 4));

	delete mCPU;
	delete memory;
}