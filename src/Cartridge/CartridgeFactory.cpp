#include "CartridgeFactory.h"

CartridgeFactory::CartridgeFactory() {}

//Creates a heap-allocated cartridge object from binary file
Cartridge* CartridgeFactory::createCartridge(const char* path) {
	//Load in data from binary file 
	std::vector<unsigned char> rom = loadROM(path);

	//Check if rom is valid 
	if (rom.size() <= 0)
		return nullptr;

	//Generate the header data and the memory bank controllers of the string
	Header* header = generateHeader(rom);
	MBC* MBC = generateMBC(rom, *header);
	
	Cartridge* cartridge = new Cartridge(*header, *MBC);
	return cartridge;
}

//Creates a heap-allocated cartridge object from vector object
Cartridge* CartridgeFactory::createCartridge(std::vector<unsigned char> memory) {
	//Load in data from binary file 
	std::vector<unsigned char> rom = loadROM(memory);

	//Check if rom is valid 
	if (rom.size() <= 0)
		return nullptr;

	//Generate the header data and the memory bank controllers of the string
	Header* header = new Header{"Test Cartridge", "F", 0, 0, 0, 0, 0};
	MBC* MBC = new MBC0(rom, std::vector<unsigned char>(0), *header);

	Cartridge* cartridge = new Cartridge(*header, *MBC);
	return cartridge;
}

std::vector<unsigned char> CartridgeFactory::loadROM(const char* path) {
	std::cout << "Loading ROM: " << path << std::endl;
	std::ifstream file(path, std::ios::binary);

	//If file failed to load, return empty vector
	if (file.fail()) {
		std::cout << "File failed to load or doesn't exist" << std::endl;
		std::cout << "Error: " << strerror(errno);
		return std::vector<unsigned char>();
	}

	// Stop eating new lines in binary mode!!!
	file.unsetf(std::ios::skipws);

	// get its size:
	std::streampos fileSize;

	//Read file from start to end to get the file size
	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);


	// reserve capacity
	std::vector<unsigned char> vec;
	vec.resize(fileSize);

	// read the data:
	vec.insert(vec.begin(), std::istream_iterator<unsigned char>(file), std::istream_iterator<unsigned char>());

	return vec;
}

std::vector<unsigned char> CartridgeFactory::loadROM(std::vector<unsigned char> rom) {
	std::cout << "Loading ROM" << std::endl;
	
	// reserve capacity
	std::vector<unsigned char> vec;
	vec.resize(0x8000);

	// read the data:
	for (int i = 0; i < rom.size(); ++i)
		vec[0x100 + i] = rom[i];

	return vec;
}

//Reads data from Cartridge's header and generates a struct containing all necessary information 
Header* CartridgeFactory::generateHeader(std::vector<unsigned char> rom) {
	std::cout << "Generating Header" << std::endl;

	std::string title;
	std::string newLicense;
	char oldLicense;

	//Read title
	for (int i = 0; i < 16; ++i) 
		title.push_back((char)rom[i + 0x0134]);
	
	
	//Read license codes
	newLicense = std::to_string((int)rom[0x0144]) + std::to_string((int)rom[0x145]);
	oldLicense = (char)rom[0x014B];
	
	unsigned char version = rom[0x14C];
	unsigned char SGBFlag = rom[0x0146];

	int romSize = 32 * (1 << rom[0x0148]);

	int ramSize = 0;

	switch (rom[0x0149]) {
		case 0x00:
			ramSize = 0;
			break;

		case 0x02:
			ramSize = 8;
			break;

		case 0x03:
			ramSize = 32;
			break;

		case 0x04:
			ramSize = 128;
			break;

		case 0x05:
			ramSize = 64;
			break;
	}
	

	//Create header object to be injected into resulting cartidge
	Header* header = new Header {title, newLicense, oldLicense, version, SGBFlag, romSize, ramSize};
	return header;
}


//Reads address 0x147 in ROM and generate its corresponding Memory Bank Controller
MBC* CartridgeFactory::generateMBC(std::vector<unsigned char> rom, Header& header) {
	std::cout << "Generating Memory Bank Controller" << std::endl;
	unsigned char type = rom[0x147];

	//Resizes the ROM and RAM to ensure that its the right size
	//rom.resize(header.romSize * 1024);

	switch (type) {
		//ROM only
		case 0x00:
			return new MBC0(rom, std::vector<unsigned char>(header.ramSize * 1024), header);
		
		//MBC1
		case 0x01: case 0x02: case 0x03:
			std::cout << "MBC 1" << std::endl;
			return new MBC1(rom, std::vector<unsigned char>(header.ramSize * 1024), header);
		
		//MBC2
		case 0x05: case 0x06:
			return new MBC0(rom, std::vector<unsigned char>(header.ramSize * 1024), header);

		//MBC3
		case 0x0F: case 0x10: case 0x11: case 0x12: case 0x13:
			return new MBC0(rom, std::vector<unsigned char>(header.ramSize * 1024), header);
	}

	return new MBC0(rom, std::vector<unsigned char>(header.ramSize), header);
}

CartridgeFactory* CartridgeFactory::getInstance() {
	if (instance == nullptr)
		instance = new CartridgeFactory();
	return instance;
}
