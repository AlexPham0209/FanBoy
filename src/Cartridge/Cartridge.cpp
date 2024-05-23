#include "Cartridge.h"

Cartridge::Cartridge() : header(*(new Header())), memory(*(new MBC0(0, 0, std::vector<unsigned char>(), std::vector<unsigned char>()))) {}
Cartridge::Cartridge(Header& header, MBC& memory) : header(header), memory(memory) {
	std::cout << this->getInfo() << std::endl;
}


unsigned char Cartridge::readByte(unsigned short address) {
	return memory.readByte(address);
}

unsigned char Cartridge::writeByte(unsigned short address, unsigned char val) {
	return memory.writeByte(address, val);
}

unsigned short Cartridge::readShort(unsigned short address) {
	return memory.readShort(address);
}

unsigned short Cartridge::writeShort(unsigned short address, unsigned short val) {
	return memory.writeShort(address, val);
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