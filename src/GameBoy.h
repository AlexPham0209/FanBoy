#include "CPU.h"
#include "Memory.h"

class GameBoy {
	public:
		GameBoy();
		void loadGame(const char* rom);
		void emulate();

	private:
		CPU mCpu;
		Memory memory;
};