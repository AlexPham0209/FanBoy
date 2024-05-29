#pragma once
#include <vector>

struct Color {
	unsigned char r, g, b;
};

class PixelBuffer {
private:
	unsigned char width, height;
	std::vector<Color> buffer;

public:
	PixelBuffer(unsigned char width, unsigned char height);
	bool setPixel(unsigned char x, unsigned char y, Color color);
	Color getPixel(unsigned char x, unsigned char y);
};