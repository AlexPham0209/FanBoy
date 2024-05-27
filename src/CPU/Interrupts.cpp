#include "CPU.h"
#include "Interrupts.h"

Interrupts::Interrupts(Memory& memory, CPU& mCPU) : memory(memory), mCPU(mCPU), IME(0) {}

void Interrupts::setInterruptFlag(unsigned char flag, bool condition) {
	unsigned char IF = memory.readByte(0xFF0F);
	unsigned char val = condition ? IF | (1 << flag) : IF & ~(1 << flag);
	memory.writeByte(0xFF0F, val);
}

bool Interrupts::getInterruptFlag(unsigned char flag) {
	unsigned char IF = memory.readByte(0xFF0F);
	bool val = (IF >> flag) & 1;
	return val;
}

void Interrupts::setInterruptEnabled(unsigned char flag, bool condition) {
	unsigned char IF = memory.readByte(0xFFFF);
	unsigned char val = condition ? IF | (1 << flag) : IF & ~(1 << flag);
	memory.writeByte(0xFFFF, val);
}

bool Interrupts::getInterruptEnabled(unsigned char flag) {
	unsigned char IF = memory.readByte(0xFFFF);
	bool val = (IF >> flag) & 1;
	return val;
}

void Interrupts::setIME(bool val) {
	IME = val;
}

bool Interrupts::getIME() {
	return IME;
}


void Interrupts::handleInterrupts() {
	if (memory.readByte(0xFFFF) & memory.readByte(0xFF0F) & 0x0F)
		mCPU.halt = false;

	if (!getIME())
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

bool Interrupts::triggerInterrupt(unsigned char flag, unsigned short address) {
	mCPU.push(mCPU.pc);
	setIME(false);
	setInterruptFlag(flag, false);
	mCPU.pc = address;
	return false;
}