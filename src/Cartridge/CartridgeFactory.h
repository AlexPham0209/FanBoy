#include "Cartridge.h"
#include <map>
#include <iostream>

class CartridgeFactory {
public:
	static inline CartridgeFactory* instance;
	Cartridge* createCartridge(const char* path);
	static CartridgeFactory* getInstance();

	CartridgeFactory();
	CartridgeFactory(const CartridgeFactory&) = delete;
	CartridgeFactory(CartridgeFactory&&) = delete;
	CartridgeFactory& operator=(const CartridgeFactory&) = delete;
	CartridgeFactory& operator=(CartridgeFactory&&) = delete;

private:
	std::vector<unsigned char> loadROM(const char* path);
	Header generateHeader(std::vector<unsigned char> ROM);
	MBC* generateMBC(std::vector<unsigned char> ROM, Header header);


};