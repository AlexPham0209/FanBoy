#include "PPU.h"

std::map<unsigned char, Color> palette = {
	{0x00, Color{0, 0, 0}},
	{0x01, Color{84, 84, 84}},
	{0x10, Color{169, 169, 169}},
	{0x11, Color{255, 255, 255}}
};

PPU::PPU(PixelBuffer& buffer, Memory& memory, Interrupts& interrupts) : buffer(buffer), memory(memory), interrupts(interrupts) {}

void PPU::step(int cycles) {
	this->cycles += cycles;

	//State machine that controls the mode the PPU is in
	switch (mode) {
		case HBLANK:
			hBlank();
			break;

		case VBLANK:
			vBlank();
			break;

		case DRAWING:
			drawing();
			break;

		case OAMSCAN:
			OAMScan();
			break;	
	}
}

//After a line finishes drawing, the PPU essentially pauses for 376 cycles (In actual hardware, the PPU waits until all pixels are transfers to the LCD)
//After this pause, if the scanline is currently at row 144, then we go to the VBlank state, otherwise we restart the process
void PPU::hBlank() {
	if (cycles < 376)
		return;

	cycles %= 376;

	//If current scanline is at row 144, then switch to VBlank phase
	if (memory.readByte(0xFF44) == 144) {
		unsigned char prev = memory.readByte(0xFF41) & 0xFC;
		memory.writeByte(0xFF41, prev | 1);
		this->mode = VBLANK;
	}

	//If current scanline is not in row 144, then we switch back to the OAM scan state
	else {
		unsigned char prev = memory.readByte(0xFF41) & 0xFC;
		memory.writeByte(0xFF41, prev | 3);
		this->mode = VBLANK;
	}

	
}

//After the entire screen is drawn, the PPU waits for 10 scanlines until the next frame 
void PPU::vBlank() {
	if (cycles < 4560)
		return;

	//Switch to VBlank mode
	unsigned char prev = memory.readByte(0xFF41) & 0xFC;
	memory.writeByte(0xFF41, prev | 2);
	cycles %= 4560;

	this->mode = OAMSCAN;
}

//For 172 cycles, the PPU draws all layers for one row/scanline
void PPU::drawing() {
	if (cycles < 172)
		return;

	renderScanline();

	//Switch to HBlank mode
	unsigned char prev = memory.readByte(0xFF41) & 0xFC;
	memory.writeByte(0xFF41, prev | 0);
	cycles %= 172;

	this->mode = HBLANK;
}

//For 80 cycles, the PPU scans through memory and puts all objects that follow certain conditions into a buffer
//The sprites in the buffer are then rendered in the drawing state
//However since the rendering functions themselves filter out the invalid sprites, so this phase essentially does nothing
void PPU::OAMScan() {
	if (cycles < 80)
		return;

	//Switch to Drawing mode
	unsigned char prev = memory.readByte(0xFF41) & 0xFC;
	memory.writeByte(0xFF41, prev | 3);
	cycles %= 80;
	
	this->mode = DRAWING;
}

//Renders all 3 layers, background, window, and object, for one scanline, specified by the LY register in memory
//The LY register is then incremented, which represents it going to the next scanline
void PPU::renderScanline() {
	unsigned char y = memory.readByte(0xFF44);

	renderBackground(y);
	renderSprite(y);
	renderWindow(y);

	memory.writeByte(0xFF44, y + 1);
}


void PPU::renderBackground(unsigned char y) {
	//Controls which BG map to use
	unsigned char bgOffset = ((memory.readByte(0xFF40) >> 3) & 1) ? 0x9C00 : 0x9800;

	//Chooses which addressing mode to use for the window and background
	bool wOffset = ((memory.readByte(0xFF40) >> 4) & 1);

	//Get background tile Y position
	unsigned char scrollingY = memory.readByte(0xFF42);
	unsigned char tileY = ((y + scrollingY) / 8) % 32;

	//Iterate through all tiles in current scanline
	for (int x = 0; x < 160; ++x) {

		//From the current pixel in the row, get the specific 8x8 tile
		unsigned char scrollingX = memory.readByte(0xFF43);
		unsigned char tileX = ((x + scrollingX) / 8) % 32;

		//Retrieving which tile to render at background tile i
		unsigned char id = memory.readByte(bgOffset + ((tileY * 32) + tileX));

		//Get address of specfic tile in either $8000 unsigned or $8800 signed method
		unsigned char tileAddress = wOffset ? 0x8000 + (id * 16) : 0x8800 + (char)(id * 16);
		unsigned char yIndex = 2 * ((y + scrollingY) % 8);
		
		//Get high and low tile data from memory
		unsigned char low = memory.readByte(tileAddress + yIndex);
		unsigned char high = memory.readByte(tileAddress + yIndex + 1);

		//Retrieve specific color bit
		unsigned char index = (7 - (x + scrollingX)) % 8;
		unsigned char lowCol = (low >> index) & 1;
		unsigned char highCol = (high >> index) & 1;
		
		unsigned char color = (highCol << 1) | lowCol;

		//Based on 2 bit color value, convert it to RGB struct by inputting it into palette map and retrieving color object
		this->buffer.setPixel(x, y, palette[color]);
	}
}

void PPU::renderWindow(unsigned char y) {
	//Controls which BG map to use
	unsigned char windowY = y - memory.readByte(0xFF4A);

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
		unsigned char yIndex = 2 * ((y + scrollingY) % 8);

		//Get high and low tile data from memory
		unsigned char low = memory.readByte(tileAddress + yIndex);
		unsigned char high = memory.readByte(tileAddress + yIndex + 1);

		//Retrieve specific color bit
		unsigned char index = (7 - windowX) % 8;
		unsigned char lowCol = (low >> index) & 1;
		unsigned char highCol = (high >> index) & 1;

		unsigned char color = (highCol << 1) | lowCol;

		//Based on 2 bit color value, convert it to RGB struct by inputting it into palette map and retrieving color object
		this->buffer.setPixel(x, y, palette[color]);
	}
}

void PPU::renderSprite(unsigned char y) {
	//Bit 2 of the LCD control register specifies the height format of the sprite tiles
	//If they are (8x16) tiles or (8x8) tiles
	unsigned char height = (memory.readByte(0xFF40) >> 2) & 1 ? 16 : 8;

	//Iterate through all sprites in OAM
	for (int i = 0xFE00; i <= 0xFE9F; i += 4) {
		//Get sprite data
		unsigned char yPosition = memory.readByte(i) - 16;
		unsigned char xPosition = memory.readByte(i + 1) - 8;
		unsigned char id = memory.readByte(i + 2);
		unsigned char flags = memory.readByte(i + 3);

		//If sprite doesn't intersect the scanline, then we don't render it
		if (y < yPosition || y >= yPosition + height)
			continue;

		//If out of bounds, don't render
		if (xPosition < 0 || xPosition > 160 || yPosition < 0 || yPosition > 144)
			continue;

		//Get specific address for the current row of the tile
		unsigned char tileAddress = 0x8000 + (id * (2 * height));
		bool yFlip = (flags >> 6) & 1;
		int yIndex = yFlip ? ((2 * height) - 1) - ((y - yPosition) * 2) : ((y - yPosition) * 2);

		//Get high and low tile data from memory for specific scanline		
		unsigned char low = memory.readByte(tileAddress + yIndex);
		unsigned char high = memory.readByte(tileAddress + yIndex + 1);
			
		bool xFlip = (flags >> 5) & 1;

		//Iterate through all pixels of sprite in current row/scanline
		for (int x = 0; x < 8; ++x) {
			int index = xFlip ? x : 7 - x;
			unsigned char lowCol = (low >> index) & 1;
			unsigned char highCol = (high >> index) & 1;

			unsigned color = highCol << 1 | lowCol;
			this->buffer.setPixel(xPosition + x, y, palette[color]);
		}
	}
}

