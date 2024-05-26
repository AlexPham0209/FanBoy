#include <gtest/gtest.h>
#include "../src/CPU/CPU.h"
#include "../src/Memory/Memory.h"

//struct CPUTest : public ::testing::Test {
//	Memory* memory;
//	CPU* mCPU;
//	Cartridge* cartridge;
//
//	virtual void SetUp() override {
//		cartridge = new Cartridge();
//		memory = new Memory(*cartridge);
//		mCPU = new CPU(*memory);
//	}
//
//	virtual void TearDown() override {
//		delete memory;
//		delete mCPU;
//		delete cartridge;
//	}
//
//	Memory* getMemory() {
//		return memory;
//	}
//
//	CPU* getCPU() {
//		return mCPU;
//	}
//};
