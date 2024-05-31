#include "PPU.h"

std::map<unsigned char, Color> palette = {
	{0x00, Color{0, 0, 0}},
	{0x01, Color{84, 84, 84}},
	{0x10, Color{169, 169, 169}},
	{0x11, Color{255, 255, 255}}
};

PPU::PPU(PixelBuffer& buffer, Memory& memory) : buffer(buffer), memory(memory) {}

void PPU::step(int cycles) {

}

void PPU::renderScanline() {
	std::vector<Color> scanline;
	scanline.resize(buffer.width);
	unsigned char ly = memory.readByte(0xFF44);

	renderBackground(ly, scanline);
	renderSprite(ly, scanline);
	renderWindow(ly, scanline);
	
	buffer.renderScanline(ly, scanline);
}

void PPU::renderBackground(unsigned char scanline, std::vector<Color>& buffer) {
	//Controls which BG map to use
	unsigned char bgOffset = ((memory.readByte(0xFF40) >> 3) & 1) ? 0x9C00 : 0x9800;

	//Chooses which addressing mode to use for the window and background
	bool wOffset = ((memory.readByte(0xFF40) >> 4) & 1);

	//Get background tile Y position
	unsigned char scrollingY = memory.readByte(0xFF42);
	unsigned char tileY = ((scanline + scrollingY) / 8) % 32;

	//Iterate through all tiles in current scanline
	for (int x = 0; x < 160; ++x) {
		unsigned char scrollingX = memory.readByte(0xFF43);
		unsigned char tileX = ((x + scrollingX) / 8) % 32;

		//Retrieving which tile to render at background tile i
		unsigned char id = memory.readByte(bgOffset + ((tileY * 32) + tileX));

		//Get address of specfic tile in either $8000 unsigned or $8800 signed method
		unsigned char tileAddress = wOffset ? 0x8000 + (id * 16) : 0x8800 + (char)(id * 16);
		tileAddress += 2 * ((scanline + scrollingY) % 8);
		
		//Get high and low tile data from memory
		unsigned char low = memory.readByte(tileAddress);
		unsigned char high = memory.readByte(tileAddress + 1);

		//Retrieve specific color bit
		unsigned char index = (7 - (x + scrollingX)) % 8;
		unsigned char lowCol = (low >> index) & 1;
		unsigned char highCol = (high >> index) & 1;
		
		unsigned char color = (highCol << 1) | lowCol;

		//Based on 2 bit color value, convert it to RGB struct by inputting it into palette map and retrieving color object
		buffer[x] = palette[color];
	}
}

void PPU::renderWindow(unsigned char scanline, std::vector<Color>& buffer) {
	//Controls which BG map to use
	unsigned char windowY = scanline - memory.readByte(0xFF4A);

	unsigned char bgOffset = ((memory.readByte(0xFF40) >> 3) & 1) ? 0x9C00 : 0x9800;

	//Chooses which addressing mode to use for the window and background
	bool wOffset = ((memory.readByte(0xFF40) >> 4) & 1);

	//Get background tile Y position
	unsigned char scrollingY = memory.readByte(0xFF42);
	unsigned char tileY = (windowY / 8);

	//Iterate through all tiles in current scanline
	for (int x = 0; x < 160; ++x) {
		if (x < memory.readByte(0xFFB) - 7)
			continue;

		unsigned char windowX = x + memory.readByte(0xFF4B) - 7;
		unsigned char tileX = (windowX / 8);

		//Retrieving which tile to render at background tile i
		unsigned char id = memory.readByte(bgOffset + ((tileY * 32) + tileX));
		
		//Get address of specfic tile in either $8000 unsigned or $8800 signed method
		unsigned char tileAddress = wOffset ? 0x8000 + (id * 16) : 0x8800 + (char)(id * 16);
		tileAddress += 2 * (windowY % 8);

		//Get high and low tile data from memory
		unsigned char low = memory.readByte(tileAddress);
		unsigned char high = memory.readByte(tileAddress + 1);

		//Retrieve specific color bit
		unsigned char index = (7 - windowX) % 8;
		unsigned char lowCol = (low >> index) & 1;
		unsigned char highCol = (high >> index) & 1;

		unsigned char color = (highCol << 1) | lowCol;

		//Based on 2 bit color value, convert it to RGB struct by inputting it into palette map and retrieving color object
		buffer[x] = palette[color];
	}
}

void PPU::renderSprite(unsigned char scanline, std::vector<Color>& buffer) {
	
	//Iterate through all sprites in OAM
	for (int i = 0xFE00; i <= 0xFE9F; i += 4) {
		//Get sprite data
		unsigned char yPosition = memory.readByte(i) + 16;
		unsigned char xPosition = memory.readByte(i + 1) + 8;
		unsigned char id = memory.readByte(i + 2);
		unsigned char flags = memory.readByte(i + 3);

		//If sprite doesn't intersect the scanline, then we don't render it
		if (scanline < yPosition || scanline > yPosition + 16)
			continue;

		//If out of bounds, don't render
		if (xPosition < 0 || xPosition > 160 || yPosition < 0 || yPosition > 44)
			continue;

		unsigned char tileAddress = 0x8000 + (id * 16);
		tileAddress += 2 * (yPosition % 8);
		
		//Get high and low tile data from memory for specific scanline
		bool yFlip = (flags >> 6) & 1;
		int yIndex = yFlip ? 15 - ((scanline - yPosition) * 2) : ((scanline - yPosition) * 2);
		unsigned char low = memory.readByte(tileAddress + yIndex);
		unsigned char high = memory.readByte(tileAddress + yIndex);
			
		bool xFlip = (flags >> 5) & 1;

		//Iterate through all pixels of sprite in current row/scanline
		for (int i = 0; i < 8; ++i) {
			int index = xFlip ? i : 7 - i;
			unsigned char lowCol = (low >> index) & 1;
			unsigned char highCol = (high >> index) & 1;

			unsigned color = highCol << 1 | lowCol;
			buffer[yPosition * 160 + xPosition + i] = palette[color];
		}
	}
}

