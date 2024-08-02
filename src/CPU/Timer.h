#pragma once
#include "Memory/Memory.h"
#include "Interrupts.h"

class Timer {
private:
	Memory& memory;
	Interrupts& interrupts;
	int clockRate = 4194304;
	int freq = 0;
	int clock = 0;


public:
	Timer(Memory& memory, Interrupts& interrupts);

	void step(int cycles);
	void select();
	void reset();
};