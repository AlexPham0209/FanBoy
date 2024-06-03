#include "Joypad.h"

Joypad::Joypad(Memory& memory, Interrupts& interrupts) : memory(memory), interrupts(interrupts) {
	memory.writeByte(0xFF00, 0xF);
}

void Joypad::pressButton(unsigned char state) {

}

void Joypad::releaseButton(unsigned char state) {

}