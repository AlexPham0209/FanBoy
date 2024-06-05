#include "Joypad.h"

Joypad::Joypad(Interrupts& interrupts) : interrupts(interrupts) {
	this->selects = 0x3F;
	this->buttons = 0xF;
	this->directions = 0xF;
}

void Joypad::pressButton(unsigned char state, SELECT mode) {
	if (mode == BUTTON)
		setButton(state, true);
	else if (mode == DPAD)
		setDirections(state, true);
}

void Joypad::releaseButton(unsigned char state, SELECT mode) {
	if (mode == BUTTON)
		setButton(state, false);
	else if (mode == DPAD)
		setDirections(state, false);
}

unsigned char Joypad::writeByte(unsigned char val) {
	selects = val & 0x30;
	return selects;
}

unsigned char Joypad::readByte() {
	unsigned char res = 0x0;
	bool buttonsSet = (selects >> 5) & 1;
	bool directionsSet = (selects >> 4) & 1;

	if (selects == 0x30)
		return 0x3F;

	if (!buttonsSet)
		res |= buttons;

	if (!directionsSet)
		res |= directions;

	return (selects | res);
}

void Joypad::setButton(unsigned char state, bool set) {
	unsigned char val = !set ? buttons | state : buttons & ~state;
	buttons = val;
	interrupts.setInterruptFlag(JOYPAD, true);
}

void Joypad::setDirections(unsigned char state, bool set) {
	unsigned char val = !set ? directions | state : directions & ~state;
	directions = val;
	interrupts.setInterruptFlag(JOYPAD, true);
}
