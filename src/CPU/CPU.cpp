#include "CPU.h"
#include <iostream>
#include "OpcodeCycles.h"
#include <algorithm>
#include <iomanip>


CPU::CPU(Memory& memory, Interrupts& interrupts) : memory(memory), F(FlagRegister()), 
AF(Register16(A, F)), BC(Register16(B, C)), DE(Register16(D, E)), HL(Register16(H, L)), interrupts(interrupts) {
	resetBoot();
}

//Executes for a single frame
int CPU::step() {
	//If system is halted, stop execution of CPU (takes 1 cycles)
	if (halt)
		return 1;
	branchTaken = false;
	unsigned char opcode = fetchOpcode();

	//Execute extended CB prefixed instructions
	if (opcode == 0xCB) {	
		unsigned char extended = fetchOpcode();
		executeCBOpcodes(extended);
		return opcodeCyclesCB[extended];
	}
	
	//Execute regular instructions
	executeOpcode(opcode);
	return branchTaken ? opcodeCyclesBranch[opcode] : opcodeCycles[opcode];
}

//Fetches opcode from memory at address stated inside of program counter
unsigned char CPU::fetchOpcode() {
	return memory.readByte(pc++);
}

//Reset CPU to original values (after boot rom)
void CPU::reset() {
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

void CPU::resetBoot() {
	pc = 0;
	sp = 0;

	A = 0;
	B = 0;
	C = 0;
	D = 0;
	E = 0;
	F = 0;
	H = 0;
	L = 0;

	cycles = 0;
}

//Prints current register values in hex as well as the current and next 4 instructions in memory
std::string CPU::debug() {
	std::stringstream ss;

	ss << "A:" << std::setfill('0') << std::setw(2) << std::hex << (int)A << " ";
	ss << "F:" << std::setfill('0') << std::setw(2) << std::hex << (int)F << " ";
	ss << "B:" << std::setfill('0') << std::setw(2) << std::hex << (int)B << " ";
	ss << "C:" << std::setfill('0') << std::setw(2)  << std::hex << (int)C << " ";
	ss << "D:" << std::setfill('0') << std::setw(2) << std::hex << (int)D << " ";
	ss << "E:" << std::setfill('0') << std::setw(2) << std::hex << (int)E << " ";
	ss << "H:" << std::setfill('0') << std::setw(2) << std::hex << (int)H << " ";
	ss << "L:" << std::setfill('0') << std::setw(2) << std::hex << (int)L << " ";

	ss << "SP:" << std::setfill('0') << std::setw(4) << std::hex << (int)sp << " ";
	ss << "PC:" << std::setfill('0') << std::setw(4) << std::hex << (int)pc << " ";

	ss << "PCMEM:";
	ss << std::setfill('0') << std::setw(2) << std::hex << (int)memory.readByte(pc) << ",";
	ss << std::setfill('0') << std::setw(2) << std::hex << (int)memory.readByte(pc + 1) << ",";
	ss << std::setfill('0') << std::setw(2) << std::hex << (int)memory.readByte(pc + 2) << ",";
	ss << std::setfill('0') << std::setw(2) << std::hex << (int)memory.readByte(pc + 3) << " ";
	//ss << std::hex << "(" << (int)memory.readByte(pc) << ")" << std::endl;

	return ss.str();
}


