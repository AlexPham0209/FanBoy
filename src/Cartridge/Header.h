#pragma once

struct Header {
	std::string title;
	std::string newLicense;
	char oldLicense;
	unsigned char version;
	unsigned char SGBFlag;
	int romSize;
	int ramSize;
};