#pragma once
#include "CPU/Interrupts.h"
#define GAMEBOY_DOWN       1 << 3
#define GAMEBOY_UP         1 << 2
#define GAMEBOY_LEFT       1 << 1
#define GAMEBOY_RIGHT      1 << 0

#define GAMEBOY_START    1 << 7
#define GAMEBOY_SELECT   1 << 6
#define GAMEBOY_B        1 << 5
#define GAMEBOY_A        1 << 4

class Joypad {
private:
	Interrupts& interrupts;
	unsigned char buttons;
	unsigned char directions;
	unsigned char selects;

public:
	Joypad(Interrupts& interrupts);
	void pressButton(unsigned char state);
	void releaseButton(unsigned char state);
	void writeByte(unsigned char val);
	unsigned char readByte();
	void setButton(unsigned char state, bool val);
	void setDirections(unsigned char state, bool set);
	void reset();
};