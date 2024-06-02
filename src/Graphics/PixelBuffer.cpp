#include "PixelBuffer.h"

PixelBuffer::PixelBuffer(unsigned char width, unsigned char height) : width(width), height(height) {
	buffer.resize(width * height);
}

bool PixelBuffer::setPixel(unsigned char x, unsigned char y, Color color) {
	unsigned char index = y * width + x;
	if (index < 0 || index >= width * height)
		return false;

	buffer[index] = color;
	return true;
}

Color PixelBuffer::getPixel(unsigned char x, unsigned char y) {
	unsigned char index = y * width + x;
	if (index < 0 || index >= width * height)
		return Color{0, 0, 0};

	return buffer[index];
}

void PixelBuffer::reset() {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x)
			setPixel(x, y, Color{255, 255, 255});
	}
}

void PixelBuffer::renderScanline(unsigned char scanline, std::vector<Color> data) {
	for (int i = 0; i < width; ++i)
		this->setPixel(scanline, i, data[scanline * width + i]);
}
