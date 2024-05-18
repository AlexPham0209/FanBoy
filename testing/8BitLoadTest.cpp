#include "CPUTest.h";
#include "../src/GameBoy.h"
#include <gtest/gtest.h>

int iterations = 1000;

template< typename T >
std::string int_to_hex(T i)
{
	std::stringstream stream;
	stream << "0x"
		<< std::setfill('0') << std::setw(sizeof(T) * 2)
		<< std::hex << i;
	return stream.str();
}

unsigned char LDTest(unsigned char& reg, unsigned char instruction, unsigned char val, CPU* CPU, Memory* memory) {
	std::vector<unsigned char> ROM = {
	instruction, val
	};
	
	//Run program
	memory->loadProgram(ROM);
	CPU->run(1);

	unsigned char temp = reg;
	//Clear memory
	memory->clear();
	CPU->reset();

	return temp;
}

unsigned char LDRegisterTest(unsigned char& dest, unsigned char& src, unsigned char instruction, unsigned char val, CPU* CPU, Memory* memory) {
	src = val;
	std::vector<unsigned char> ROM = {
	instruction
	};

	//Run program
	memory->loadProgram(ROM);
	CPU->run(1);

	unsigned char temp = dest;
	//Clear memory
	memory->clear();
	CPU->reset();
	return temp;
}

unsigned char LDRegisterMemoryTest(unsigned char& dest, unsigned char instruction, unsigned short address, unsigned char val, CPU* CPU, Memory* memory) {
	memory->writeByte(address, val);
	CPU->H = (address & 0xFF00) >> 8;
	CPU->L = address & 0xFF;

	std::vector<unsigned char> ROM = {
	instruction
	};

	//Run program
	memory->loadProgram(ROM);
	CPU->run(1);

	unsigned char temp = dest;
	//Clear memory
	memory->clear();
	CPU->reset();
	return temp;
}

void LDRegisterTest(CPU* CPU, Memory* memory) {
	unsigned char* registers[7] = {
		&CPU->B, &CPU->C, &CPU->D, &CPU->E, &CPU->H, &CPU->L
	};
	
	for (unsigned char i = 0; i < 48; i+=8) {
		unsigned char expected = rand() % 0xFF;
		EXPECT_EQ(LDRegisterTest(*registers[i/8], CPU->B, (0x40 + i), expected, CPU, memory), expected);
		EXPECT_EQ(LDRegisterTest(*registers[i/8], CPU->C, (0x40 + i + 1), expected, CPU, memory), expected);
		EXPECT_EQ(LDRegisterTest(*registers[i/8], CPU->D, (0x40 + i + 2), expected, CPU, memory), expected);
		EXPECT_EQ(LDRegisterTest(*registers[i/8], CPU->E, (0x40 + i + 3), expected, CPU, memory), expected);
		EXPECT_EQ(LDRegisterTest(*registers[i/8], CPU->H, (0x40 + i + 4), expected, CPU, memory), expected);
		EXPECT_EQ(LDRegisterTest(*registers[i/8], CPU->L, (0x40 + i + 5), expected, CPU, memory), expected);
		EXPECT_EQ(LDRegisterMemoryTest(*registers[i/8], (0x40 + i + 6), rand() % 0xFF, expected, CPU, memory), expected);
	}
}



TEST_F(CPUTest, LDTest) {
	for (int i = 0; i < iterations; i++) {
		unsigned char expected = rand() % 0xFF;
		EXPECT_EQ(LDTest(mCPU->B, 0x06, expected, mCPU, memory), expected);
		EXPECT_EQ(LDTest(mCPU->C, 0x0E, expected, mCPU, memory), expected);
		EXPECT_EQ(LDTest(mCPU->D, 0x16, expected, mCPU, memory), expected);
		EXPECT_EQ(LDTest(mCPU->E, 0x1E, expected, mCPU, memory), expected);
		EXPECT_EQ(LDTest(mCPU->H, 0x26, expected, mCPU, memory), expected);
		EXPECT_EQ(LDTest(mCPU->L, 0x2E, expected, mCPU, memory), expected);
	}
}

TEST_F(CPUTest, LDRegisterTest) {
	LDRegisterTest(mCPU, memory);
	for (int i = 0; i < iterations; i++) {
		unsigned char expected = rand() % 0xFF;
		EXPECT_EQ(LDRegisterTest(mCPU->A, mCPU->A, 0x7F, expected, mCPU, memory), expected);
		EXPECT_EQ(LDRegisterTest(mCPU->A, mCPU->B, 0x78, expected, mCPU, memory), expected);
		EXPECT_EQ(LDRegisterTest(mCPU->A, mCPU->C, 0x79, expected, mCPU, memory), expected);
		EXPECT_EQ(LDRegisterTest(mCPU->A, mCPU->D, 0x7A, expected, mCPU, memory), expected);
		EXPECT_EQ(LDRegisterTest(mCPU->A, mCPU->E, 0x7B, expected, mCPU, memory), expected);
		EXPECT_EQ(LDRegisterTest(mCPU->A, mCPU->H, 0x7C, expected, mCPU, memory), expected);
		EXPECT_EQ(LDRegisterTest(mCPU->A, mCPU->L, 0x7D, expected, mCPU, memory), expected);
		EXPECT_EQ(LDRegisterMemoryTest(mCPU->A, 0x7E, rand() % 0xFF, expected, mCPU, memory), expected);

		LDRegisterTest(mCPU, memory);
	}
}

void test(int i) {
	std::cout << i << std::endl;
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



TEST(SampleTest, ShortLoadTest) {
	Memory* memory = new Memory();
	CPU* mCPU = new CPU(*memory);

	memory->writeByte(0x100, 0x01);
	memory->writeByte(0x101, 0x31);
	memory->writeByte(0x102, 0xF0);

	mCPU->run(1);

	EXPECT_EQ((int)((mCPU->B << 8) | mCPU->C), 0xF031);

	delete memory;
	delete mCPU;
}