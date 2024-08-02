#include "PixelBuffer.h"


PixelBuffer::PixelBuffer(unsigned char width, unsigned char height) : width(width), height(height) {
	buffer.resize(width * height);
	reset();
}

bool PixelBuffer::setPixel(unsigned char x, unsigned char y, Color color) {
	unsigned short index = y * width + x;
	if (index < 0 || index >= buffer.size())
		return false;

	unsigned int r = (unsigned int)(color.r * 255);
	unsigned int g = (unsigned int)(color.g * 255);
	unsigned int b = (unsigned int)(color.b * 255);

	buffer[index] = (r << 16) | (g << 8) | (b);
	return true;
} 

Color PixelBuffer::getPixel(unsigned char x, unsigned char y) {
	unsigned short index = y * width + x;

	int color = buffer[index];
	float r = (color & 0xFF0000) >> 16;
	float g = (color & 0xFF00) >> 8;
	float b = (color & 0xFF);

	return Color{r * 255, g * 255, b * 255};
}

void PixelBuffer::reset() {
	for (int y = 0; y < height; ++y) { 
		for (int x = 0; x < width; ++x)
			setPixel(x, y, Color{1, 1, 1});
	}
}

unsigned int* PixelBuffer::getFrame() {
	return buffer.data();
}