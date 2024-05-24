#include "CPU.h"
#include <iostream>
#include "OpcodeCycles.h"

CPU::CPU(Memory& memory) : memory(memory), F(FlagRegister()), 
AF(Register16(A, F)), BC(Register16(B, C)), DE(Register16(D, E)), HL(Register16(H, L)), interrupts(Interrupts(memory, *this)) {
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
	interrupts.handleInterrupts();
	unsigned char opcode = fetchOpcode();
	executeOpcode(opcode);
	cycles = opcodeCycles[opcode];
	return cycles;
}

void CPU::run(int iterations) {
	std::ofstream file;
	file.open("C:/Users/RedAP/Desktop/Output.txt");
	for (int i = 0; i < iterations; ++i) {	
		file << i << ": ";
		file << debug() << std::endl;
		step();
	}
	file.close();
}

void CPU::run() {
	std::ofstream file;
	file.open("C:/Users/RedAP/Desktop/Output.txt");

	while (!halt) {
		//file << debug() << std::endl;
		step();
	}

	file.close();
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

	//ss << std::hex << "(" << (int)memory.readByte(pc) << ")" << std::endl;

	return ss.str();
}


