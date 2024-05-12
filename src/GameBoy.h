#pragma once
#include "CPU/CPU.h"
#include "Memory/Memory.h"


class GameBoy {
	public:
		GameBoy();
		void emulate();
	private:
		CPU mCPU;
		Memory memory;
};