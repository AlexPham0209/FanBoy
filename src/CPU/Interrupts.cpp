#include "CPU.h"
#include "Interrupts.h"

Interrupts::Interrupts(Memory& memory) : memory(memory), IME(0) {}

//Used to request an interrupt routine to be run
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

//Turn on and off event or interrupt
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

//Turn on and off all events/interrupts
void Interrupts::setIME(bool val) {
	IME = val;
}

bool Interrupts::getIME() {
	return IME;
}

//At the beginning of every step, the system checks if any events/interrupts were requested
void Interrupts::handleInterrupts(CPU& mCPU) {
	if (memory.readByte(0xFFFF) & memory.readByte(0xFF0F) & 0x0F)
		mCPU.halt = false;

	//If master interrupt flag is disabled, then the interrupts aren't handled
	if (!getIME())
		return;

	//VBlank interrupt routine
	if (getInterruptEnabled(VBLANK) && getInterruptFlag(VBLANK))
		triggerInterrupt(VBLANK, 0x40, mCPU);

	//LCD interrupt routine
	if (getInterruptEnabled(LCD) && getInterruptFlag(LCD))
		triggerInterrupt(LCD, 0x48, mCPU);

	//Timer interrupt routine
	if (getInterruptEnabled(TIMER) && getInterruptFlag(TIMER))
		triggerInterrupt(TIMER, 0x50, mCPU);

	//Serial port interrupt routine
	if (getInterruptEnabled(SERIAL) && getInterruptFlag(SERIAL))
		triggerInterrupt(SERIAL, 0x58, mCPU);

	//Joypad input serial routine
	if (getInterruptEnabled(JOYPAD) && getInterruptFlag(JOYPAD))
		triggerInterrupt(JOYPAD, 0x60, mCPU);
}

//Interrupts CPU's execution, pushes current instruction on the stack and jumps to sections dedicated to individual interrupt routine
//
bool Interrupts::triggerInterrupt(unsigned char flag, unsigned short address, CPU& mCPU) {
	mCPU.push(mCPU.pc);
	setIME(false);
	setInterruptFlag(flag, false);
	mCPU.pc = address;
	return false;
}