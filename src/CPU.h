#include "Memory.h"
class CPU {
public:
	int step();
	CPU();
	CPU(Memory& memory);

private:
	unsigned char A, B, C, D, E, F, H, L;
	unsigned short sp, pc;
	Memory memory;
	int cycles;

	unsigned char fetchOpcode();
	void executeOpcode(unsigned char opcode);

};