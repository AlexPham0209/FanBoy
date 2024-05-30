#pragma once
#include "PixelBuffer.h"
#include "../Memory/Memory.h"

class PPU {
private:
	PixelBuffer& buffer;
	Memory& memory;

	int cycles = 0;

	void renderScanline();
	void renderBackground(unsigned char scanline, std::vector<Color>& buffer);
	void renderSprite(unsigned char scanline, std::vector<Color>& buffer);
	void renderWindow(unsigned char scanline, std::vector<Color>& buffer);

public:
	PPU(PixelBuffer& buffer, Memory& memory);
	void step(int cycles);


};