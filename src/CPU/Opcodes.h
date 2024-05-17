#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "CPU.h"

struct Instruction {
	std::string type;
	void (*Instruction)();
	int cycles;
};

class Opcodes {
public:
	int execute(unsigned char opcode);

private:
	std::vector<Instruction> instructions;
	CPU CPU;
	

};
