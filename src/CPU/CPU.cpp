#include "CPU.h"
#include <iostream>
#include "OpcodeCycles.h"

CPU::CPU(Memory& memory) : memory(memory), F(FlagRegister()), 
AF(Register16(A, F)), BC(Register16(B, C)), DE(Register16(D, E)), HL(Register16(H, L)), interrupts(Interrupts(this->memory, *this)) {
	pc = 0x100;
	sp = 0xFFFE;

	A = 0x01;
	B = 0x00;
	C = 0x13;
	D = 0x00;
	E = 0xD8;
	F = 0xB0;
	H = 0x01;
	L = 0x4D;

	cycles = 0;
}

int CPU::step() {
	//interrupts.handleInterrupts();
	//std::cout << debug() << std::endl;
	unsigned char opcode = fetchOpcode();
	executeOpcode(opcode);
	cycles = opcodeCycles[opcode];
	return cycles;
}

void CPU::run(int iterations) {
	std::ofstream file;
	file.open("C:/Users/RedAP/Desktop/Output.txt");
	for (int i = 0; i < iterations; ++i) {	
		if (i == 16507)
			std::cout << std::hex << (int)memory.readByte(0xFF00 + memory.readByte(pc + 1)) << std::dec << std::endl;
		file << i << ": ";
		file << debug() << std::endl;
		//std::cout << debug() << std::endl;
		step();
	}
	file.close();
}

void CPU::run() {
	while(!halt)
		step();
}

unsigned char CPU::fetchOpcode() {
	return memory.readByte(pc++);
}

void CPU::reset() {
	pc = 0x100;
	sp = 0xFFFE;

	A = 0x0000;
	B = 0x0000;
	C = 0x0000;
	D = 0x0000;
	E = 0x0000;
	F = 0x0000;
	H = 0x0000;
	L = 0x0000;
}

std::string CPU::debug() {
	std::stringstream ss;

	ss << "A: " << std::hex << (int)A << "  ";
	ss << "F: " << std::hex << (int)F << "  ";
	ss << "B: " << std::hex << (int)B << "  ";
	ss << "C: " << std::hex << (int)C << "  ";
	ss << "D: " << std::hex << (int)D << "  ";
	ss << "E: " << std::hex << (int)E << "  ";
	ss << "H: " << std::hex << (int)H << "  ";
	ss << "L: " << std::hex << (int)L << "  ";

	ss << "SP: " << std::hex << (int)sp << "  ";
	ss << "PC: " << std::hex << (int)pc << "  ";

	ss << std::hex << "(" << (int)memory.readByte(pc) << " " << (int)memory.readByte(pc + 1) << " " << (int)memory.readByte(pc + 2) << " " << (int)memory.readByte(pc + 3) << ")";

	return ss.str();
}


