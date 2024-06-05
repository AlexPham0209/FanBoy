#pragma once
#include "CPU/Interrupts.h"
#define GAMEBOY_DOWN       1 << 3
#define GAMEBOY_UP         1 << 2
#define GAMEBOY_LEFT       1 << 1
#define GAMEBOY_RIGHT      1 << 0

#define GAMEBOY_START    1 << 3
#define GAMEBOY_SELECT   1 << 2
#define GAMEBOY_B        1 << 1
#define GAMEBOY_A        1 << 0

enum SELECT {
	DPAD,
	BUTTON
};

class Joypad {
private:
	Interrupts& interrupts;
	unsigned char buttons;
	unsigned char directions;
	unsigned char selects;

public:
	Joypad(Interrupts& interrupts);
	void pressButton(unsigned char state, SELECT mode);
	void releaseButton(unsigned char state, SELECT mode);
	unsigned char writeByte(unsigned char val);
	unsigned char readByte();
	void setButton(unsigned char state, bool val);
	void setDirections(unsigned char state, bool set);


};