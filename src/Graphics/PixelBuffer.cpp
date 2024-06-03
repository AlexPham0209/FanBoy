#include "PixelBuffer.h"

PixelBuffer::PixelBuffer(unsigned char width, unsigned char height) : width(width), height(height) {
	buffer.resize(width * height);
}

bool PixelBuffer::setPixel(unsigned char x, unsigned char y, Color color) {
	unsigned char index = y * width + x;
	if (index < 0 || index >= width * height)
		return false;

	buffer[index] = color.r << 16 | color.g << 8 | color.b;
	return true;
}

Color PixelBuffer::getPixel(unsigned char x, unsigned char y) {
	unsigned char index = y * width + x;
	if (index < 0 || index >= width * height)
		return Color{0, 0, 0};

	int color = buffer[index];
	unsigned char r = (color & 0xFF0000) >> 16;
	unsigned char g = (color & 0xFF00) >> 8;
	unsigned char b = (color & 0xFF);

	return Color{r, g, b};
}

void PixelBuffer::reset() {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x)
			setPixel(x, y, Color{255, 255, 255});
	}
}

int* PixelBuffer::getFrame() {
	return &buffer[0];
}