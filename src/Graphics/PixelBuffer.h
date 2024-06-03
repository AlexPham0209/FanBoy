#pragma once
#include <vector>

struct Color {
	unsigned char r, g, b;
};

class PixelBuffer {
private:
	std::vector<int> buffer;

public:
	unsigned char width, height;

	PixelBuffer(unsigned char width, unsigned char height);
	bool setPixel(unsigned char x, unsigned char y, Color color);
	Color getPixel(unsigned char x, unsigned char y);
	int* getFrame();
	void reset();
	void renderScanline(unsigned char scanline, std::vector<Color> data);
};