#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "CPU.h"

struct Instruction {
	std::string type;
	void (*Execute)();
	int cycles;
};
