#include <vector>
#include <iostream>


class MBC {
protected:
	unsigned char romBankSize, ramBankSize;
	unsigned char ramBank, romBank;
	std::vector<unsigned char> rom;
	std::vector<unsigned char> ram;

public:
	MBC(unsigned char ramBankSize, unsigned char romBankSize, std::vector<unsigned char> rom, std::vector<unsigned char> ram);
	virtual unsigned char readByte(unsigned short address) = 0;
	virtual unsigned char writeByte(unsigned short address, unsigned char val) = 0;
		
	virtual unsigned short readShort(unsigned short address) = 0;
	virtual unsigned short writeShort(unsigned short address, unsigned short val) = 0;
};

class MBC0 : public MBC {
public:
	MBC0(unsigned char ramBankSize, unsigned char romBankSize, std::vector<unsigned char> rom, std::vector<unsigned char> ram);
	unsigned char readByte(unsigned short address) override;
	unsigned char writeByte(unsigned short address, unsigned char val) override;

	unsigned short readShort(unsigned short address) override;
	unsigned short writeShort(unsigned short address, unsigned short val) override;
};