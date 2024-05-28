#include "Timer.h"

Timer::Timer(Memory& memory, Interrupts& interrupts) : memory(memory), interrupts(interrupts) {
	this->select();
}

void Timer::step(int cycles) {
	//Increment Divider Register
	memory.writeByte(0xFF04, memory.readByte(0xFF04) + (clockRate/16384));
	//Return if interrupt is not valid 
	if (!interrupts.getInterruptEnabled(TIMER))
		return;

	this->clock += cycles * 4;
	this->select();

	//Increment the timer counter register once the number of cycles collected exceeds the clockRate divided by the 
	//Meaning that the bottom for loop will only run in intervals
	//Reason for a while loop is in cases where the frequency is changed, which means that the clock has to be decremented multiple times
	while (clock >= clockRate/freq) {
		//If TIMA register overflows or exceeds 0xFF, then write timer modulus value into it and trigger timer interrupt
		if (memory.readByte(0xFF05) == 0xFF) {
			memory.writeByte(0xFF05, memory.readByte(0xFF06));
			interrupts.setInterruptFlag(TIMER, true);
		}
		else
			memory.writeByte(0xFF05, memory.readByte(0xFF05) + 1);

		clock -= clockRate / freq;
	}
}

//Selects 
void Timer::select() {
	unsigned char tac = memory.readByte(0xFF07);
	switch (tac & 0x03) {
		case 0:
			freq = 4096;
			break;

		case 1: 
			freq = 262144;
			break;

		case 2:
			freq = 65536;
			break;

		case 3:
			freq = 16384;
			break;
	}
}
