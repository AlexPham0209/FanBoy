#pragma once
#include "PixelBuffer.h"
#include "../Memory/Memory.h"
#include "../CPU/Interrupts.h"

enum PPUMode {
	HBLANK,
	VBLANK,
	DRAWING,
	OAMSCAN
};

class PPU {
private:
	PixelBuffer& buffer;
	Memory& memory;
	Interrupts& interrupts;

	int cycles = 0;
	PPUMode mode;


	void hBlank();
	void vBlank();
	void drawing();
	void OAMScan();

	void renderScanline();
	void renderBackground(unsigned char y);
	void renderSprite(unsigned char y);
	void renderWindow(unsigned char y);

public:
	PPU(PixelBuffer& buffer, Memory& memory, Interrupts& interrupts);
	void step(int cycles);



};