#include "PPU.h"

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
		
		//Get high and low tile data from memory
		unsigned char low = memory.readByte(tileAddress);
		unsigned char high = memory.readByte(tileAddress + 1);

		//Retrieve specific color bit
		unsigned char index = (7 - (x + scrollingX)) % 8;
		unsigned char lowCol = (low >> index) & 1;
		unsigned char highCol = (high >> index) & 1;
		
		unsigned char color = (highCol << 1) | lowCol;

		buffer[x] = 
	}
}

void PPU::renderSprite(unsigned char scanline, std::vector<Color>& buffer) {

}

void PPU::renderWindow(unsigned char scanline, std::vector<Color>& buffer) {
}