#include "CartridgeFactory.h"


Cartridge* CartridgeFactory::createCartridge(const char* path) {
	std::vector<unsigned char> ROM = this->loadROM(path);

	if (ROM.size() <= 0)
		return nullptr;

	Header header = this->generateHeader(ROM);
	MBC MBC = this->generateMBC(ROM);
	
	Cartridge* cartridge = new Cartridge(header, MBC);
	return cartridge;
}

std::vector<unsigned char> CartridgeFactory::loadROM(const char* path) {
	std::cout << "Loading ROM: " << path << std::endl;
	std::ifstream file(path, std::ios::binary);

	if (file.fail()) {
		std::cout << "File failed to load or doesn't exist" << std::endl;
		std::cout << "Error: " << strerror(errno);
		return std::vector<unsigned char>();
	}

	// Stop eating new lines in binary mode!!!
	file.unsetf(std::ios::skipws);

	// get its size:
	std::streampos fileSize;

	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);


	// reserve capacity
	std::vector<unsigned char> vec;
	vec.resize(fileSize);

	// read the data:
	vec.insert(vec.begin(),
		std::istream_iterator<unsigned char>(file),
		std::istream_iterator<unsigned char>());

	return vec;
}

Header CartridgeFactory::generateHeader(std::vector<unsigned char> ROM) {
	std::cout << "Generating Header" << std::endl;

	std::string title;
	std::string newLicense;
	char oldLicense;

	//Read title
	for (int i = 0; i < 16; ++i) 
		title.push_back((char)ROM[i + 0x0134]);
	
	
	//Read license codes

	newLicense = std::to_string((int)ROM[0x0144]) + std::to_string((int)ROM[0x145]);
	oldLicense = (char)ROM[0x014B];
	
	unsigned char version = ROM[0x14C];
	unsigned char SGBFlag = ROM[0x0146];
	int romSize = 32 * (1 << ROM[0x0148]);
	int ramSize = ROM[0x149] <= 0x01 ? 0 : 8 * pow(4,(ROM[0x149] - 2));
	

	//Create header object to be injected into resulting cartidge
	Header header = {title, newLicense, oldLicense, version, SGBFlag, romSize, ramSize};
	return header;
}

MBC CartridgeFactory::generateMBC(std::vector<unsigned char> ROM) {
	std::cout << "Generating Memory Bank Controller" << std::endl;
	unsigned char type = ROM[0x147];
	switch (type) {

		//ROM only
		case 0x00:
			return MBC();
	
		//MBC1
		case 0x01: case 0x02: case 0x03:
			return MBC();
		
		//MBC2
		case 0x05: case 0x06:
			return MBC();

		//MBC3
		case 0x0F: case 0x10: case 0x11: case 0x12: case 0x13:
			return MBC();
	}
}

CartridgeFactory* CartridgeFactory::getInstance() {
	if (instance == nullptr)
		instance = new CartridgeFactory();
	return instance;
}

CartridgeFactory::CartridgeFactory()
{
}
