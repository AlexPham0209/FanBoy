#pragma once
#include "../Memory/Memory.h"
#include "Interrupts.h"

class Timer {
private:
	Memory& memory;
	Interrupts& interrupts;
	int clockRate = 4194304;
	int freq;
	int clock;


public:
	Timer(Memory& memory, Interrupts& interrupts);

	void step(int cycles);
	void select();

};