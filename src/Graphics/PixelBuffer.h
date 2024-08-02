#pragma once
#include <vector>
#include <iostream>

struct Color {
	float r, g, b;
};

class PixelBuffer {
private:
	std::vector<unsigned int> buffer;

public:
	unsigned char width, height;

	PixelBuffer(unsigned char width, unsigned char height);
	bool setPixel(unsigned char x, unsigned char y, Color color);
	Color getPixel(unsigned char x, unsigned char y);
	unsigned int* getFrame();
	void reset();
	void renderScanline(unsigned char scanline, std::vector<Color> data);
};