#pragma once
#include "PixelBuffer.h"

class PPU {
private:
	PixelBuffer& buffer;
	int cycles = 0;

public:
	PPU(PixelBuffer& buffer);
	void step(int cycles);


};