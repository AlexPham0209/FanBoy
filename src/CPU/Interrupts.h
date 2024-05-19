#pragma once

enum IFLAGS {
	VBLANK = 0,
	LCD = 1,
	TIMER = 2,
	SERIAL = 3,
	JOYPAD = 4
};

class CPU;
class Interrupts {
private:
	CPU& mCPU;
	bool IME;
	Memory& memory;
	
public:
	Interrupts(Memory& memory, CPU& mCPU);

	void setInterruptFlag(unsigned char flag, bool condition);

	bool getInterruptFlag(unsigned char flag);

	void setInterruptEnabled(unsigned char flag, bool condition);

	bool getInterruptEnabled(unsigned char flag);

	void setIME(bool val);

	bool getIME();


	void handleInterrupts();

	bool triggerInterrupt(unsigned char flag, unsigned short address);
};