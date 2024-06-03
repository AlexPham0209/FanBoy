#include "CPU/Interrupts.h"
#include "Memory/Memory.h"

class Joypad {
private:
	Memory& memory;
	Interrupts& interrupts;

public:
	Joypad(Memory& memory, Interrupts& interrupts);
	void pressButton(unsigned char state);
	void releaseButton(unsigned char state);


};