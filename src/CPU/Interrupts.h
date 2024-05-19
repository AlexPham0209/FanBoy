#pragma once
#include "CPU.h"
#include "../Memory/Memory.h"


enum IFLAGS {
	VBLANK = 0,
	LCD = 1,
	TIMER = 2,
	SERIAL = 3,
	JOYPAD = 4
};

class Interrupts {
private:
	bool IME;
	CPU& mCPU;
	Memory& memory;
	
public:
	Interrupts(Memory& memory, CPU& mCPU) : mCPU(mCPU), memory(memory), IME(0) {}

	void setInterruptFlag(unsigned char flag, bool condition) {
		unsigned char IF = memory.readByte(0xFF0F);
		unsigned char val = condition ? IF | (1 << flag) : IF & ~(1 << flag);
		memory.writeByte(0xFF0F, val);
	}

	bool getInterruptFlag(unsigned char flag) {
		unsigned char IF = memory.readByte(0xFF0F);
		bool val = (IF >> flag) & 1;
		return val;
	}

	void setInterruptEnabled(unsigned char flag, bool condition) {
		unsigned char IF = memory.readByte(0xFFFF);
		unsigned char val = condition ? IF | (1 << flag) : IF & ~(1 << flag);
		memory.writeByte(0xFFFF, val);
	}

	bool getInterruptEnabled(unsigned char flag) {
		unsigned char IF = memory.readByte(0xFFFF);
		bool val = (IF >> flag) & 1;
		return val;
	}

	void setIME(bool val) {
		IME = val;
	}

	bool getIME() {
		return IME;
	}


	void handleInterrupts() {
		if (mCPU.halt)
			return;

		if (getInterruptEnabled(VBLANK) && getInterruptFlag(VBLANK))
			triggerInterrupt(VBLANK, 0x40);

		if (getInterruptEnabled(LCD) && getInterruptFlag(LCD))
			triggerInterrupt(LCD, 0x48);

		if (getInterruptEnabled(TIMER) && getInterruptFlag(TIMER))
			triggerInterrupt(TIMER, 0x50);

		if (getInterruptEnabled(SERIAL) && getInterruptFlag(SERIAL))
			triggerInterrupt(SERIAL, 0x58);

		if (getInterruptEnabled(JOYPAD) && getInterruptFlag(JOYPAD))
			triggerInterrupt(JOYPAD, 0x60);
	}

	bool triggerInterrupt(unsigned char flag, unsigned short address) {
		mCPU.push(mCPU.pc);
		setIME(false);
		setInterruptFlag(flag, false);
		mCPU.pc = address;
	}
};