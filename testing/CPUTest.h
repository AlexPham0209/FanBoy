#include <gtest/gtest.h>
#include "../src/CPU/CPU.h"
#include "../src/Memory/Memory.h"

struct CPUTest : public ::testing::Test {
	Memory* memory;
	CPU* mCPU;

	virtual void SetUp() override {
		memory = new Memory();
		mCPU = new CPU(*memory);
	}

	virtual void TearDown() override {
		delete memory;
		delete mCPU;
	}

	Memory* getMemory() {
		return memory;
	}

	CPU* getCPU() {
		return mCPU;
	}
};
