//TODO: Create Instructions STOP, DI, EL. RETI
#include "CPU.h"
void CPU::executeOpcode(unsigned char opcode) {
	//Executes certain instruction based on 8 bit opcode
	switch (opcode) {
		//LD N, NN
	case 0x06:
		loadByteIntoReg(B, memory.readByte(pc++));
		break;

	case 0x0E:
		loadByteIntoReg(C, memory.readByte(pc++));
		break;

	case 0x16:
		loadByteIntoReg(D, memory.readByte(pc++));
		break;

	case 0x1E:
		loadByteIntoReg(E, memory.readByte(pc++));
		break;

	case 0x26:
		loadByteIntoReg(H, memory.readByte(pc++));
		break;

	case 0x2E:
		loadByteIntoReg(L, memory.readByte(pc++));
		break;


		//LD A, r2
	case 0x7F:
		loadByteIntoReg(A, A);
		break;

	case 0x78:
		loadByteIntoReg(A, B);
		break;

	case 0x79:
		loadByteIntoReg(A, C);
		break;

	case 0x7A:
		loadByteIntoReg(A, D);
		break;

	case 0x7B:
		loadByteIntoReg(A, E);
		break;

	case 0x7C:
		loadByteIntoReg(A, H);
		break;

	case 0x7D:
		loadByteIntoReg(A, L);
		break;

	case 0x7E:
		loadByteIntoReg(A, memory.readByte(HL));
		break;


		//LD B, r2
	case 0x40:
		loadByteIntoReg(B, B);
		break;

	case 0x41:
		loadByteIntoReg(B, C);
		break;

	case 0x42:
		loadByteIntoReg(B, D);
		break;

	case 0x43:
		loadByteIntoReg(B, E);
		break;

	case 0x44:
		loadByteIntoReg(B, H);
		break;

	case 0x45:
		loadByteIntoReg(B, L);
		break;

	case 0x46:
		loadByteIntoReg(B, memory.readByte(HL));
		break;


		//LD C, r2
	case 0x48:
		loadByteIntoReg(C, B);
		break;

	case 0x49:
		loadByteIntoReg(C, C);
		break;

	case 0x4A:
		loadByteIntoReg(C, D);
		break;

	case 0x4B:
		loadByteIntoReg(C, E);
		break;

	case 0x4C:
		loadByteIntoReg(C, H);
		break;

	case 0x4D:
		loadByteIntoReg(C, L);
		break;

	case 0x4E:
		loadByteIntoReg(C, memory.readByte(HL));
		break;


		//LD D, r2
	case 0x50:
		loadByteIntoReg(D, B);
		break;

	case 0x51:
		loadByteIntoReg(D, C);
		break;

	case 0x52:
		loadByteIntoReg(D, D);
		break;

	case 0x53:
		loadByteIntoReg(D, E);
		break;

	case 0x54:
		loadByteIntoReg(D, H);
		break;

	case 0x55:
		loadByteIntoReg(D, L);
		break;

	case 0x56:
		loadByteIntoReg(D, memory.readByte(HL));
		break;


		//LD E, r2
	case 0x58:
		loadByteIntoReg(E, B);
		break;

	case 0x59:
		loadByteIntoReg(E, C);
		break;

	case 0x5A:
		loadByteIntoReg(E, D);
		break;

	case 0x5B:
		loadByteIntoReg(E, E);
		break;

	case 0x5C:
		loadByteIntoReg(E, H);
		break;

	case 0x5D:
		loadByteIntoReg(E, L);
		break;

	case 0x5E:
		loadByteIntoReg(E, memory.readByte(HL));
		break;


		//LD H, r2
	case 0x60:
		loadByteIntoReg(H, B);
		break;

	case 0x61:
		loadByteIntoReg(H, C);
		break;

	case 0x62:
		loadByteIntoReg(H, D);
		break;

	case 0x63:
		loadByteIntoReg(H, E);
		break;

	case 0x64:
		loadByteIntoReg(H, H);
		break;

	case 0x65:
		loadByteIntoReg(H, L);
		break;

	case 0x66:
		loadByteIntoReg(H, memory.readByte(HL));
		break;


		//LD L, r2
	case 0x68:
		loadByteIntoReg(L, B);
		break;

	case 0x69:
		loadByteIntoReg(L, C);
		break;

	case 0x6A:
		loadByteIntoReg(L, D);
		break;

	case 0x6B:
		loadByteIntoReg(L, E);
		break;

	case 0x6C:
		loadByteIntoReg(L, H);
		break;

	case 0x6D:
		loadByteIntoReg(L, L);
		break;

	case 0x6E:
		loadByteIntoReg(L, memory.readByte(HL));
		break;


		//LD (HL), r2
	case 0x70:
		loadByteIntoMemory(HL, B);
		break;

	case 0x71:
		loadByteIntoMemory(HL, C);
		break;

	case 0x72:
		loadByteIntoMemory(HL, D);
		break;

	case 0x73:
		loadByteIntoMemory(HL, E);
		break;

	case 0x74:
		loadByteIntoMemory(HL, H);
		break;

	case 0x75:
		loadByteIntoMemory(HL, L);
		break;

	case 0x36:
		loadByteIntoMemory(HL, memory.readByte(pc++));
		break;


		//LD A, n
	case 0x0A:
		loadByteIntoReg(A, memory.readByte(BC));
		break;

	case 0x1A:
		loadByteIntoReg(A, memory.readByte(DE));
		break;

	case 0xFA:
		loadByteIntoReg(A, memory.readByte((memory.readByte(pc++) | memory.readByte(pc++) << 8)));
		break;

	case 0x3E:
		loadByteIntoReg(A, memory.readByte(pc++));
		break;


		//LD n, A
	case 0x47:
		loadByteIntoReg(B, A);
		break;

	case 0x4F:
		loadByteIntoReg(C, A);
		break;

	case 0x57:
		loadByteIntoReg(D, A);
		break;

	case 0x5F:
		loadByteIntoReg(E, A);
		break;

	case 0x67:
		loadByteIntoReg(H, A);
		break;

	case 0x6F:
		loadByteIntoReg(F, A);
		break;

	case 0x02:
		loadByteIntoMemory(BC, A);
		break;

	case 0x12:
		loadByteIntoMemory(DE, A);
		break;

	case 0x77:
		loadByteIntoMemory(HL, A);
		break;

	case 0xEA:
		loadByteIntoMemory((memory.readByte(pc++) | (memory.readByte(pc++) << 8)), A);
		break;


		//LD A, (C)
	case 0xF2:
		loadByteIntoReg(A, memory.readByte(0xFF00 + C));
		break;

		//LD (C), A
	case 0xE2:
		loadByteIntoMemory(0xFF00 + C, A);
		break;

		//LDD A, (HL)
	case 0x3A:
		loadByteIntoRegDecrement(A, HL);
		break;

		//LDD (HL), A
	case 0x32:
		loadByteIntoMemoryDecrement(HL, A);
		break;

		//LDI A, (HL)
	case 0x2A:
		loadByteIntoRegIncrement(A, HL);
		break;

		//LDI (HL), A
	case 0x22:
		loadByteIntoMemoryIncrement(HL, A);
		break;

		//LDH (n), A
	case 0xE0:
		loadByteIntoMemory(0xFF00 + memory.readByte(pc++), A);
		break;

		//LDH A, (n)
	case 0xF0:
		loadByteIntoReg(A, memory.readByte(0xFF00 + memory.readByte(pc++)));
		break;

		//LD n, nn
	case 0x01:
		loadShortIntoReg(BC, memory.readShort(pc));
		pc += 2;
		break;

	case 0x11:
		loadShortIntoReg(DE, memory.readShort(pc));
		pc += 2;
		break;

	case 0x21:
		loadShortIntoReg(HL, memory.readShort(pc));
		pc += 2;
		break;

	case 0x31:
		sp = memory.readShort(pc);
		pc += 2;
		break;

		//LD SP, HL
	case 0xF9:
		sp = (H << 8) | L;
		break;

		//LD HL, SP+n
	case 0xF8:
		loadHL(memory.readByte(pc++));
		break;

		//LD (nn), SP
	case 0x08:
		loadShortIntoMemory(memory.readByte(pc++), sp);
		break;


		//PUSH nn
	case 0xF5:
		push(AF);
		break;

	case 0xC5:
		push(BC);
		break;

	case 0xD5:
		push(DE);
		break;

	case 0xE5:
		push(HL);
		break;


		//POP nn
	case 0xF1:
		pop(AF);
		break;

	case 0xC1:
		pop(BC);
		break;

	case 0xD1:
		pop(DE);
		break;

	case 0xE1:
		pop(HL);
		break;


		//ADD A, n
	case 0x87:
		add(A, A);
		break;

	case 0x80:
		add(A, B);
		break;

	case 0x81:
		add(A, C);
		break;

	case 0x82:
		add(A, D);
		break;

	case 0x83:
		add(A, E);
		break;

	case 0x84:
		add(A, H);
		break;

	case 0x85:
		add(A, L);
		break;

	case 0x86:
		add(A, memory.readByte(HL));
		break;

	case 0xC6:
		add(A, memory.readByte(pc++));
		break;


		//ADC A, n
	case 0x8F:
		addCarry(A, A);
		break;

	case 0x88:
		addCarry(A, B);
		break;

	case 0x89:
		addCarry(A, C);
		break;

	case 0x8A:
		addCarry(A, D);
		break;

	case 0x8B:
		addCarry(A, E);
		break;

	case 0x8C:
		addCarry(A, H);
		break;

	case 0x8D:
		addCarry(A, L);
		break;

	case 0x8E:
		addCarry(A, memory.readByte(HL));
		break;

	case 0xCE:
		addCarry(A, memory.readByte(pc++));
		break;


		//SUB n
	case 0x97:
		sub(A, A);
		break;

	case 0x90:
		sub(A, B);
		break;

	case 0x91:
		sub(A, C);
		break;

	case 0x92:
		sub(A, D);
		break;

	case 0x93:
		sub(A, E);
		break;

	case 0x94:
		sub(A, H);
		break;

	case 0x95:
		sub(A, L);
		break;

	case 0x96:
		sub(A, memory.readByte(HL));
		break;

	case 0xD6:
		sub(A, memory.readByte(pc++));
		break;


		//SUBC n
	case 0x9F:
		subBorrow(A, A);
		break;

	case 0x98:
		subBorrow(A, B);
		break;

	case 0x99:
		subBorrow(A, C);
		break;

	case 0x9A:
		subBorrow(A, D);
		break;

	case 0x9B:
		subBorrow(A, E);
		break;

	case 0x9C:
		subBorrow(A, H);
		break;

	case 0x9D:
		subBorrow(A, L);
		break;

	case 0x9E:
		subBorrow(A, memory.readByte(HL));
		break;


		//AND n 
	case 0xA7:
		AND(A, A);
		break;

	case 0xA0:
		AND(A, B);
		break;

	case 0xA1:
		AND(A, C);
		break;

	case 0xA2:
		AND(A, D);
		break;

	case 0xA3:
		AND(A, E);
		break;

	case 0xA4:
		AND(A, H);
		break;

	case 0xA5:
		AND(A, L);
		break;

	case 0xA6:
		AND(A, memory.readByte(HL));
		break;

	case 0xE6:
		AND(A, memory.readByte(pc++));
		break;


		//OR operation
	case 0xB7:
		OR(A, A);
		break;

	case 0xB0:
		OR(A, B);
		break;

	case 0xB1:
		OR(A, C);
		break;

	case 0xB2:
		OR(A, D);
		break;

	case 0xB3:
		OR(A, E);
		break;

	case 0xB4:
		OR(A, H);
		break;

	case 0xB5:
		OR(A, L);
		break;

	case 0xB6:
		OR(A, memory.readByte(HL));
		break;

	case 0xF6:
		OR(A, memory.readByte(pc++));
		break;


		//XOR n
	case 0xAF:
		XOR(A, A);
		break;

	case 0xA8:
		XOR(A, B);
		break;

	case 0xA9:
		XOR(A, C);
		break;

	case 0xAA:
		XOR(A, D);
		break;

	case 0xAB:
		XOR(A, E);
		break;

	case 0xAC:
		XOR(A, H);
		break;

	case 0xAD:
		XOR(A, L);
		break;

	case 0xAE:
		XOR(A, memory.readByte(HL));
		break;

	case 0xEE:
		XOR(A, memory.readByte(pc++));
		break;

		//CP n
	case 0xBF:
		CP(A, A);
		break;

	case 0xB8:
		CP(A, B);
		break;

	case 0xB9:
		CP(A, C);
		break;

	case 0xBA:
		CP(A, D);
		break;

	case 0xBB:
		CP(A, E);
		break;

	case 0xBC:
		CP(A, H);
		break;

	case 0xBD:
		CP(A, L);
		break;

	case 0xBE:
		CP(A, memory.readByte(HL));
		break;

	case 0xFE:
		CP(A, memory.readByte(pc++));
		break;


		//INC n
	case 0x3C:
		INC(A);
		break;

	case 0x04:
		INC(B);
		break;

	case 0x0C:
		INC(C);
		break;

	case 0x14:
		INC(D);
		break;

	case 0x1C:
		INC(E);
		break;

	case 0x24:
		INC(H);
		break;

	case 0x2C:
		INC(L);
		break;

	case 0x34:
		INC(HL);
		break;


		//DEC n
	case 0x3D:
		DEC(A);
		break;

	case 0x05:
		DEC(B);
		break;

	case 0x0D:
		DEC(C);
		break;

	case 0x15:
		DEC(D);
		break;

	case 0x1D:
		DEC(E);
		break;

	case 0x25:
		DEC(H);
		break;

	case 0x2D:
		DEC(L);
		break;

	case 0x35:
		DEC(HL);
		break;


		//ADD HL, n
	case 0x09:
		add(HL, BC);
		break;

	case 0x19:
		add(HL, DE);
		break;

	case 0x29:
		add(HL, HL);
		break;

	case 0x39:
		add(HL, sp);
		break;

		//ADD SP, n
	case 0xE8:
		addSP(memory.readByte(pc++));
		break;

		//INC nn
	case 0x03:
		INC(BC);
		break;

	case 0x13:
		INC(DE);
		break;

	case 0x23:
		INC(HL);
		break;

	case 0x33:
		sp++;
		break;

		//DEC nn
	case 0x0B:
		DEC(BC);
		break;

	case 0x1B:
		DEC(DE);
		break;

	case 0x2B:
		DEC(HL);
		break;

	case 0x3B:
		sp--;
		break;

		//DAA
	case 0x27:
		DAA(A);
		break;

		//CPL
	case 0x2F:
		CPL(A);
		break;

		//CCF
	case 0x3F:
		CCF();
		break;

		//SCF
	case 0x37:
		SCF();
		break;

		//HALT
	case 0x76:
		halt = false;
		break;


		//RLCA
	case 0x07:
		RLC(A);
		break;

		//RLA
	case 0x17:
		RL(A);
		break;

		//RRCA
	case 0x0F:
		RRC(A);
		break;

		//RRA
	case 0x1F:
		RR(A);
		break;

		//JP nn
	case 0xC3:
		jump(memory.readShort(pc));
		break;

		//JP cc, nn
	case 0xC2:
		jump(memory.readShort(pc), !F.getFlag(ZERO));
		break;

	case 0xCA:
		jump(memory.readShort(pc), F.getFlag(ZERO));
		break;

	case 0xD2:
		jump(memory.readShort(pc), !F.getFlag(CARRY));
		break;

	case 0xDA:
		jump(memory.readShort(pc), F.getFlag(CARRY));
		break;

		//JP (HL)
	case 0xE9:
		jump((unsigned short)HL);
		break;

		//JR n
	case 0x18:
		jump((char)memory.readByte(pc++));
		break;

		//JR cc, n
	case 0x20:
		jump((char)memory.readByte(pc), !F.getFlag(ZERO));
		break;

	case 0x28:
		jump((char)memory.readByte(pc), F.getFlag(ZERO));
		break;

	case 0x30:
		jump((char)memory.readByte(pc), !F.getFlag(CARRY));
		break;

	case 0x38:
		jump((char)memory.readByte(pc), F.getFlag(CARRY));
		break;

		//CALL nn
	case 0xCD:
		call(memory.readShort(pc));
		break;

		//CALL cc, nn
	case 0xC4:
		call(memory.readShort(pc), !F.getFlag(ZERO));
		break;

	case 0xCC:
		call(memory.readShort(pc), F.getFlag(ZERO));
		break;

	case 0xD4:
		call(memory.readShort(pc), !F.getFlag(CARRY));
		break;

	case 0xDC:
		call(memory.readShort(pc), F.getFlag(CARRY));
		break;

		//RST n
	case 0xC7:
		restart(0x00);
		break;

	case 0xCF:
		restart(0x08);
		break;

	case 0xD7:
		restart(0x10);
		break;

	case 0xDF:
		restart(0x18);
		break;

	case 0xE7:
		restart(0x20);
		break;

	case 0xEF:
		restart(0x28);
		break;

	case 0xF7:
		restart(0x30);
		break;

	case 0xFF:
		restart(0x38);
		break;

		//RET
	case 0xC9:
		ret();
		break;

		//RET cc
	case 0xC0:
		ret(!F.getFlag(ZERO));
		break;

	case 0xC8:
		ret(!F.getFlag(ZERO));
		break;

	case 0xD0:
		ret(F.getFlag(CARRY));
		break;

	case 0xD8:
		ret(!F.getFlag(CARRY));
		break;
	}


}

void CPU::Opcode06() {
	loadByteIntoReg(B, memory.readByte(pc++));
}