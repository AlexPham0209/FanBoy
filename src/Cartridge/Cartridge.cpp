#include "Cartridge.h"

Cartridge::Cartridge(Header& header, MBC& memory) : header(header), memory(memory) {
	std::cout << getInfo() << std::endl;
}

unsigned char Cartridge::readByte(unsigned short address) {
	return memory.readByte(address);
}

void Cartridge::writeByte(unsigned short address, unsigned char val) {
	memory.writeByte(address, val);
}

std::string Cartridge::getInfo() {
	std::stringstream ss;

	ss << "\nCartridge Information: " << "\n";
	ss << "Title: " << header.title << "\n";
	ss << "Version: " << (int)header.version << "\n";
	ss << "New License Code: " << header.newLicense << "\n";
	ss << "Old License Code: " << std::hex << (int)header.oldLicense << "\n";
	ss << "SGB Flag: " << (int)header.SGBFlag << "\n";
	ss << "ROM Size: " << std::dec << header.romSize<< "\n";
	ss << "RAM Size: " << header.ramSize << "\n";

	return ss.str();
}