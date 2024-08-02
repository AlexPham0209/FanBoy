#pragma once
#include "PixelBuffer.h"
#include "Memory/Memory.h"
#include "CPU/Interrupts.h"

enum PPUMode {
	HBLANK,
	VBlank,
	DRAWING,
	OAMSCAN
};

class PPU {
private:
	PixelBuffer& buffer;
	Memory& memory;
	Interrupts& interrupts;

	Color colors[4] = {
		Color{ 1, 1, 1 },
		Color{ 0.66, 0.66, 0.66 },
		Color{ 0.32, 0.32, 0.32 },
		Color{ 0, 0, 0 }
	};

	std::map<unsigned char, Color*> palette = {
		{0, colors},
		{1, colors + 1},
		{2, colors + 2},
		{3, colors + 3}
	};

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
	bool canRender = false;
	PPU(PixelBuffer& buffer, Memory& memory, Interrupts& interrupts);
	void step(int cycles);
	void reset();
	Color* getColors();
};