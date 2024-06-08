#include "Joypad.h"

Joypad::Joypad(Interrupts& interrupts) : interrupts(interrupts) {
	this->selects = 0x3F;
	this->buttons = 0xF;
	this->directions = 0xF;
}

void Joypad::pressButton(unsigned char state) {
	if (state > 0xF) {
		setButton(state >> 4, true);
		return;
	}

	setDirections(state, true);
}

void Joypad::releaseButton(unsigned char state) {
	if (state > 0xF) {
		setButton(state >> 4, false);
		return;
	}

	setDirections(state, false);
}

//When the CPU writes to the joypad register, it should only be able to set the 5th and 6th bit of the register
void Joypad::writeByte(unsigned char val) {
	selects = val & 0x30;
}

unsigned char Joypad::readByte() {
	unsigned char res = 0x0;
	bool buttonsSet = (selects >> 5) & 1;
	bool directionsSet = (selects >> 4) & 1;

	//If both are set, then we release all buttons 
	if (selects == 0x30)
		return 0x3F;

	//If 5th bit of Joypad register is not set, then we interpret the lower nibble as the button inputs
	if (!buttonsSet)
		res |= buttons;

	//If gth bit of Joypad register is not set, then we interpret the lower nibble as the dpad inputs
	if (!directionsSet)
		res |= directions;

	return (selects | res);
}

//Sets certain button on the controller (which is determined by a certain bit on Joypad Register) to 1 or 0
//0 represents button being pressed.  1 is button released
void Joypad::setButton(unsigned char state, bool set) {
	unsigned char val = !set ? buttons | state : buttons & ~state;
	buttons = val;
	interrupts.setInterruptFlag(JOYPAD, true);
}

//Same thing as set button but for the direction inputs
void Joypad::setDirections(unsigned char state, bool set) {
	unsigned char val = !set ? directions | state : directions & ~state;
	directions = val;
	interrupts.setInterruptFlag(JOYPAD, true);
}

void Joypad::reset() {
	this->selects = 0x3F;
	this->buttons = 0xF;
	this->directions = 0xF;
}
