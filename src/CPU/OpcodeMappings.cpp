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
			loadByteIntoReg(A, memory.readByte(memory.readShort(pc)));
			pc += 2;
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
			loadByteIntoReg(L, A);
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
			loadShortIntoMemory(memory.readShort(pc), sp);
			pc += 2;
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
			F = F & 0xF0;
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

		case 0xDE:
			subBorrow(A, memory.readByte(pc++));
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
			INC((unsigned short)HL);
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
			DEC((unsigned short)HL);
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
			halt = true;
			break;

		//DI
		case 0xF3:
			interrupts.setIME(false);
			break;

		//EI
		case 0xFB:
			interrupts.setIME(true);
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
			F.setFlag(ZERO, false);
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
			jump((char)memory.readByte(pc++), !F.getFlag(ZERO));
			break;

		case 0x28:
			jump((char)memory.readByte(pc++), F.getFlag(ZERO));
			break;

		case 0x30:
			jump((char)memory.readByte(pc++), !F.getFlag(CARRY));
			break;

		case 0x38:
			jump((char)memory.readByte(pc++), F.getFlag(CARRY));
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
			ret(F.getFlag(ZERO));
			break;

		case 0xD0:
			ret(!F.getFlag(CARRY));
			break;

		case 0xD8:
			ret(F.getFlag(CARRY));
			break;

		//RETI
		case 0xD9:
			reti();
			break;
	}
}

void CPU::executeCBOpcodes(unsigned char opcode) {
	switch (opcode) {
		//SWAP n
		case 0x37:
			swap(A);
			break;
		
		case 0x30:
			swap(B);
			break;

		case 0x31:
			swap(C);
			break;

		case 0x32:
			swap(D);
			break;

		case 0x33:
			swap(E);
			break;

		case 0x34:
			swap(H);
			break;

		case 0x35:
			swap(L);
			break;

		case 0x36:
			swap(HL);
			break;

		//RLC n
		case 0x07:
			RLC(A);
			break;

		case 0x00:
			RLC(B);
			break;

		case 0x01:
			RLC(C);
			break;

		case 0x02:
			RLC(D);
			break;

		case 0x03:
			RLC(E);
			break;

		case 0x04:
			RLC(H);
			break;

		case 0x05:
			RLC(L);
			break;

		case 0x06:
			RLC(HL);
			break;

		//RL n
		case 0x17:
			RL(A);
			break;

		case 0x10:
			RL(B);
			break;

		case 0x11:
			RL(C);
			break;

		case 0x12:
			RL(D);
			break;

		case 0x13:
			RL(E);
			break;

		case 0x14:
			RL(H);
			break;

		case 0x15:
			RL(L);
			break;

		case 0x16:
			RL(HL);
			break;

		//RRC n
		case 0x0F:
			RRC(A);
			break;

		case 0x08:
			RRC(B);
			break;

		case 0x09:
			RRC(C);
			break;

		case 0x0A:
			RRC(D);
			break;

		case 0x0B:
			RRC(E);
			break;

		case 0x0C:
			RRC(H);
			break;

		case 0x0D:
			RRC(L);
			break;

		case 0x0E:
			RRC(HL);
			break;


		//RR n
		case 0x1F:
			RR(A);
			break;

		case 0x18:
			RR(B);
			break;

		case 0x19:
			RR(C);
			break;

		case 0x1A:
			RR(D);
			break;

		case 0x1B:
			RR(E);
			break;

		case 0x1C:
			RR(H);
			break;

		case 0x1D:
			RR(L);
			break;

		case 0x1E:
			RR(HL);
			break;

		//SLA n
		case 0x27:
			SLA(A);
			break;

		case 0x20:
			SLA(B);
			break;

		case 0x21:
			SLA(C);
			break;

		case 0x22:
			SLA(D);
			break;

		case 0x23:
			SLA(E);
			break;

		case 0x24:
			SLA(H);
			break;

		case 0x25:
			SLA(L);
			break;

		case 0x26:
			SLA(HL);
			break;


		//SRA n
		case 0x2F:
			SRA(A);
			break;

		case 0x28:
			SRA(B);
			break;

		case 0x29:
			SRA(C);
			break;

		case 0x2A:
			SRA(D);
			break;

		case 0x2B:
			SRA(E);
			break;

		case 0x2C:
			SRA(H);
			break;

		case 0x2D:
			SRA(L);
			break;

		case 0x2E:
			SRA(HL);
			break;

		//SRL n
		case 0x3F:
			SRL(A);
			break;

		case 0x38:
			SRL(B);
			break;

		case 0x39:
			SRL(C);
			break;

		case 0x3A:
			SRL(D);
			break;

		case 0x3B:
			SRL(E);
			break;

		case 0x3C:
			SRL(H);
			break;

		case 0x3D:
			SRL(L);
			break;

		case 0x3E:
			SRL(HL);
			break;

		//BIT 0, r
		case 0x47:
			BIT(0, A);
			break;

		case 0x40:
			BIT(0, B);
			break;

		case 0x41:
			BIT(0, C);
			break;

		case 0x42:
			BIT(0, D);
			break;

		case 0x43:
			BIT(0, E);
			break;

		case 0x44:
			BIT(0, H);
			break;

		case 0x45:
			BIT(0, L);
			break;

		case 0x46:
			BIT(0, HL);
			break;
		
		//BIT 1, r
		case 0x4F:
			BIT(1, A);
			break;

		case 0x48:
			BIT(1, B);
			break;

		case 0x49:
			BIT(1, C);
			break;

		case 0x4A:
			BIT(1, D);
			break;

		case 0x4B:
			BIT(1, E);
			break;

		case 0x4C:
			BIT(1, H);
			break;

		case 0x4D:
			BIT(1, L);
			break;

		case 0x4E:
			BIT(1, HL);
			break;

		//BIT 2, r
		case 0x57:
			BIT(2, A);
			break;

		case 0x50:
			BIT(2, B);
			break;

		case 0x51:
			BIT(2, C);
			break;

		case 0x52:
			BIT(2, D);
			break;

		case 0x53:
			BIT(2, E);
			break;

		case 0x54:
			BIT(2, H);
			break;

		case 0x55:
			BIT(2, L);
			break;

		case 0x56:
			BIT(2, HL);
			break;

		//BIT 3, r
		case 0x5F:
			BIT(3, A);
			break;

		case 0x58:
			BIT(3, B);
			break;

		case 0x59:
			BIT(3, C);
			break;

		case 0x5A:
			BIT(3, D);
			break;

		case 0x5B:
			BIT(3, E);
			break;

		case 0x5C:
			BIT(3, H);
			break;

		case 0x5D:
			BIT(3, L);
			break;

		case 0x5E:
			BIT(3, HL);
			break;

		//BIT 4, r
		case 0x67:
			BIT(4, A);
			break;

		case 0x60:
			BIT(4, B);
			break;

		case 0x61:
			BIT(4, C);
			break;

		case 0x62:
			BIT(4, D);
			break;

		case 0x63:
			BIT(4, E);
			break;

		case 0x64:
			BIT(4, H);
			break;

		case 0x65:
			BIT(4, L);
			break;

		case 0x66:
			BIT(4, HL);
			break;

		//BIT 5, r
		case 0x6F:
			BIT(5, A);
			break;

		case 0x68:
			BIT(5, B);
			break;

		case 0x69:
			BIT(5, C);
			break;

		case 0x6A:
			BIT(5, D);
			break;

		case 0x6B:
			BIT(5, E);
			break;

		case 0x6C:
			BIT(5, H);
			break;

		case 0x6D:
			BIT(5, L);
			break;

		case 0x6E:
			BIT(5, HL);
			break;

		//BIT 6, r
		case 0x77:
			BIT(6, A);
			break;

		case 0x70:
			BIT(6, B);
			break;

		case 0x71:
			BIT(6, C);
			break;

		case 0x72:
			BIT(6, D);
			break;

		case 0x73:
			BIT(6, E);
			break;

		case 0x74:
			BIT(6, H);
			break;

		case 0x75:
			BIT(6, L);
			break;

		case 0x76:
			BIT(6, HL);
			break;

		//RES 7, r
		case 0x7F:
			BIT(7, A);
			break;

		case 0x78:
			BIT(7, B);
			break;

		case 0x79:
			BIT(7, C);
			break;

		case 0x7A:
			BIT(7, D);
			break;

		case 0x7B:
			BIT(7, E);
			break;

		case 0x7C:
			BIT(7, H);
			break;

		case 0x7D:
			BIT(7, L);
			break;

		case 0x7E:
			BIT(7, HL);
			break;

		//RES 0, r
		case 0x87:
			RES(0, A);
			break;

		case 0x80:
			RES(0, B);
			break;

		case 0x81:
			RES(0, C);
			break;

		case 0x82:
			RES(0, D);
			break;

		case 0x83:
			RES(0, E);
			break;

		case 0x84:
			RES(0, H);
			break;

		case 0x85:
			RES(0, L);
			break;

		case 0x86:
			RES(0, HL);
			break;

		//RES 1, r
		case 0x8F:
			RES(1, A);
			break;

		case 0x88:
			RES(1, B);
			break;

		case 0x89:
			RES(1, C);
			break;

		case 0x8A:
			RES(1, D);
			break;

		case 0x8B:
			RES(1, E);
			break;

		case 0x8C:
			RES(1, H);
			break;

		case 0x8D:
			RES(1, L);
			break;

		case 0x8E:
			RES(1, HL);
			break;


		//RES 2, r
		case 0x97:
			RES(2, A);
			break;

		case 0x90:
			RES(2, B);
			break;

		case 0x91:
			RES(2, C);
			break;

		case 0x92:
			RES(2, D);
			break;

		case 0x93:
			RES(2, E);
			break;

		case 0x94:
			RES(2, H);
			break;

		case 0x95:
			RES(2, L);
			break;

		case 0x96:
			RES(2, HL);
			break;

		//RES 3, r
		case 0x9F:
			RES(3, A);
			break;

		case 0x98:
			RES(3, B);
			break;

		case 0x99:
			RES(3, C);
			break;

		case 0x9A:
			RES(3, D);
			break;

		case 0x9B:
			RES(3, E);
			break;

		case 0x9C:
			RES(3, H);
			break;

		case 0x9D:
			RES(3, L);
			break;

		case 0x9E:
			RES(3, HL);
			break;

		//RES 4, r
		case 0xA7:
			RES(4, A);
			break;

		case 0xA0:
			RES(4, B);
			break;

		case 0xA1:
			RES(4, C);
			break;

		case 0xA2:
			RES(4, D);
			break;

		case 0xA3:
			RES(4, E);
			break;

		case 0xA4:
			RES(4, H);
			break;

		case 0xA5:
			RES(4, L);
			break;

		case 0xA6:
			RES(4, HL);
			break;

		//RES 5, r
		case 0xAF:
			RES(5, A);
			break;

		case 0xA8:
			RES(5, B);
			break;

		case 0xA9:
			RES(5, C);
			break;

		case 0xAA:
			RES(5, D);
			break;

		case 0xAB:
			RES(5, E);
			break;

		case 0xAC:
			RES(5, H);
			break;

		case 0xAD:
			RES(5, L);
			break;

		case 0xAE:
			RES(5, HL);
			break;

		//RES 6, r
		case 0xB7:
			RES(6, A);
			break;

		case 0xB0:
			RES(6, B);
			break;

		case 0xB1:
			RES(6, C);
			break;

		case 0xB2:
			RES(6, D);
			break;

		case 0xB3:
			RES(6, E);
			break;

		case 0xB4:
			RES(6, H);
			break;

		case 0xB5:
			RES(6, L);
			break;

		case 0xB6:
			RES(6, HL);
			break;

		//RES 7, r
		case 0xBF:
			RES(7, A);
			break;

		case 0xB8:
			RES(7, B);
			break;

		case 0xB9:
			RES(7, C);
			break;

		case 0xBA:
			RES(7, D);
			break;

		case 0xBB:
			RES(7, E);
			break;

		case 0xBC:
			RES(7, H);
			break;

		case 0xBD:
			RES(7, L);
			break;

		case 0xBE:
			RES(7, HL);
			break;

		//SET 0, r
		case 0xC7:
			SET(0, A);
			break;

		case 0xC0:
			SET(0, B);
			break;

		case 0xC1:
			SET(0, C);
			break;

		case 0xC2:
			SET(0, D);
			break;

		case 0xC3:
			SET(0, E);
			break;

		case 0xC4:
			SET(0, H);
			break;

		case 0xC5:
			SET(0, L);
			break;

		case 0xC6:
			SET(0, HL);
			break;

		//SET 1, r
		case 0xCF:
			SET(1, A);
			break;

		case 0xC8:
			SET(1, B);
			break;

		case 0xC9:
			SET(1, C);
			break;

		case 0xCA:
			SET(1, D);
			break;

		case 0xCB:
			SET(1, E);
			break;

		case 0xCC:
			SET(1, H);
			break;

		case 0xCD:
			SET(1, L);
			break;

		case 0xCE:
			SET(1, HL);
			break;
		
		//SET 2, r
		case 0xD7:
			SET(2, A);
			break;

		case 0xD0:
			SET(2, B);
			break;

		case 0xD1:
			SET(2, C);
			break;

		case 0xD2:
			SET(2, D);
			break;

		case 0xD3:
			SET(2, E);
			break;

		case 0xD4:
			SET(2, H);
			break;

		case 0xD5:
			SET(2, L);
			break;

		case 0xD6:
			SET(2, HL);
			break;

		//SET 3, r
		case 0xDF:
			SET(3, A);
			break;

		case 0xD8:
			SET(3, B);
			break;

		case 0xD9:
			SET(3, C);
			break;

		case 0xDA:
			SET(3, D);
			break;

		case 0xDB:
			SET(3, E);
			break;

		case 0xDC:
			SET(3, H);
			break;

		case 0xDD:
			SET(3, L);
			break;

		case 0xDE:
			SET(3, HL);
			break;

		//SET 4, r
		case 0xE7:
			SET(4, A);
			break;

		case 0xE0:
			SET(4, B);
			break;

		case 0xE1:
			SET(4, C);
			break;

		case 0xE2:
			SET(4, D);
			break;

		case 0xE3:
			SET(4, E);
			break;

		case 0xE4:
			SET(4, H);
			break;

		case 0xE5:
			SET(4, L);
			break;

		case 0xE6:
			SET(4, HL);
			break;

		//SET 5, r
		case 0xEF:
			SET(5, A);
			break;

		case 0xE8:
			SET(5, B);
			break;

		case 0xE9:
			SET(5, C);
			break;

		case 0xEA:
			SET(5, D);
			break;

		case 0xEB:
			SET(5, E);
			break;

		case 0xEC:
			SET(5, H);
			break;

		case 0xED:
			SET(5, L);
			break;

		case 0xEE:
			SET(5, HL);
			break;

		//SET 6, r
		case 0xF7:
			SET(6, A);
			break;

		case 0xF0:
			SET(6, B);
			break;

		case 0xF1:
			SET(6, C);
			break;

		case 0xF2:
			SET(6, D);
			break;

		case 0xF3:
			SET(6, E);
			break;

		case 0xF4:
			SET(6, H);
			break;

		case 0xF5:
			SET(6, L);
			break;

		case 0xF6:
			SET(6, HL);
			break;

		//SET 7, r
		case 0xFF:
			SET(7, A);
			break;

		case 0xF8:
			SET(7, B);
			break;

		case 0xF9:
			SET(7, C);
			break;

		case 0xFA:
			SET(7, D);
			break;

		case 0xFB:
			SET(7, E);
			break;

		case 0xFC:
			SET(7, H);
			break;

		case 0xFD:
			SET(7, L);
			break;

		case 0xFE:
			SET(7, HL);
			break;
	}
}
