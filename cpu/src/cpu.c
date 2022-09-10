#include <stdio.h>
#include <stdlib.h>

#include "../inc/cpu.h"
#include "../../cpubus/inc/cpubus.h"

#define DBG 1

void myfunc() {
	printf("Hello from CPU!\n");
}

void cpu_init(cpu_t* cpu) {
	cpu->A = 0;
	cpu->X = 0;
	cpu->Y = 0;
	cpu->SP = 0xFD;
	cpu->PC = 0xC000;
	cpu->f_N = 0; //0x34
	cpu->f_V = 0;
	cpu->ZZZ = 1;
	cpu->f_B = 0;
	cpu->f_D = 0;
	cpu->f_I = 1;
	cpu->f_Z = 0;
	cpu->f_C = 0;

	cpu->cycles = 7;
}

#if DBG
void getOPs(cpu_t* cpu, enum addrMode addr) {
	switch (addr) {
	case NONE: printf("FATAL ERROR!!!\n"); break;
	case ACC:  printf("       "); break;
	case ABS:  printf("%02x %02x  ", ram[(cpu->PC & 0x3FFF) + 1], ram[(cpu->PC & 0x3FFF) + 2]); break;
	case ABSX: printf("%02x %02x  ", ram[(cpu->PC & 0x3FFF) + 1], ram[(cpu->PC & 0x3FFF) + 2]); break;
	case ABSY: printf("%02x %02x  ", ram[(cpu->PC & 0x3FFF) + 1], ram[(cpu->PC & 0x3FFF) + 2]); break;
	case IMM:  printf("%02x     ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case IMP:  printf("       "); break;
	case IND:  printf("%02x     ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case INDX: printf("%02x     ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case INDY: printf("%02x     ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case REL:  printf("%02x     ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case ZER:  printf("%02x     ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case ZERX: printf("%02x     ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case ZERY: printf("%02x     ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	}
}
#endif

#if DBG
void getInstrOPs(cpu_t* cpu, enum addrMode addr) {
	switch (addr) {
	case NONE: printf("FATAL ERROR!!!\n"); break;
	case ACC:  printf("        "); break;
	case ABS:  printf(" $%02x%02x  ", ram[(cpu->PC & 0x3FFF) + 2], ram[(cpu->PC & 0x3FFF) + 1]); break;
	case ABSX: printf(" $%02x%02x  ", ram[(cpu->PC & 0x3FFF) + 2], ram[(cpu->PC & 0x3FFF) + 1]); break;
	case ABSY: printf(" $%02x%02x  ", ram[(cpu->PC & 0x3FFF) + 2], ram[(cpu->PC & 0x3FFF) + 1]); break;
	case IMM:  printf(" #$%02x   ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case IMP:  printf("        "); break;
	case IND:  printf(" $%02x    ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case INDX: printf(" $%02x    ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case INDY: printf(" $%02x    ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case REL:  printf(" $%04x  ", ram[(cpu->PC & 0x3FFF) + 1] + cpu->PC + 2); break;
	case ZER:  printf(" $%02x    ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case ZERX: printf(" $%02x    ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	case ZERY: printf(" $%02x    ", ram[(cpu->PC & 0x3FFF) + 1]); break;
	}
}
#endif

#if DBG 
void getInstr(cpu_t* cpu, enum insnName insn, enum addrMode addr) {
	switch (insn) {
	case ADC: printf("ADC"); getInstrOPs(cpu, addr); break;
	case AND: printf("AND"); getInstrOPs(cpu, addr); break;
	case ASL: printf("ASL"); getInstrOPs(cpu, addr); break;
	case BCC: printf("BCC"); getInstrOPs(cpu, addr); break;
	case BCS: printf("BCS"); getInstrOPs(cpu, addr); break;
	case BEQ: printf("BEQ"); getInstrOPs(cpu, addr); break;
	case BIT: printf("BIT"); getInstrOPs(cpu, addr); break;
	case BMI: printf("BMI"); getInstrOPs(cpu, addr); break;
	case BNE: printf("BNE"); getInstrOPs(cpu, addr); break;
	case BPL: printf("BPL"); getInstrOPs(cpu, addr); break;
	case BRK: printf("BRK"); getInstrOPs(cpu, addr); break;
	case BVC: printf("BVC"); getInstrOPs(cpu, addr); break;
	case BVS: printf("BVS"); getInstrOPs(cpu, addr); break;
	case CLC: printf("CLC"); getInstrOPs(cpu, addr); break;
	case CLD: printf("CLD"); getInstrOPs(cpu, addr); break;
	case CLI: printf("CLI"); getInstrOPs(cpu, addr); break;
	case CLV: printf("CLV"); getInstrOPs(cpu, addr); break;
	case CMP: printf("CMP"); getInstrOPs(cpu, addr); break;
	case CPX: printf("CPX"); getInstrOPs(cpu, addr); break;
	case CPY: printf("CPY"); getInstrOPs(cpu, addr); break;
	case DEC: printf("DEC"); getInstrOPs(cpu, addr); break;
	case DEX: printf("DEX"); getInstrOPs(cpu, addr); break;
	case DEY: printf("DEY"); getInstrOPs(cpu, addr); break;
	case EOR: printf("EOR"); getInstrOPs(cpu, addr); break;
	case INC: printf("INC"); getInstrOPs(cpu, addr); break;
	case INX: printf("INX"); getInstrOPs(cpu, addr); break;
	case INY: printf("INY"); getInstrOPs(cpu, addr); break;
	case JMP: printf("JMP"); getInstrOPs(cpu, addr); break;
	case JSR: printf("JSR"); getInstrOPs(cpu, addr); break;
	case LDA: printf("LDA"); getInstrOPs(cpu, addr); break;
	case LDX: printf("LDX"); getInstrOPs(cpu, addr); break;
	case LDY: printf("LDY"); getInstrOPs(cpu, addr); break;
	case LSR: printf("LSR"); getInstrOPs(cpu, addr); break;
	case NOP: printf("NOP"); getInstrOPs(cpu, addr); break;
	case ORA: printf("ORA"); getInstrOPs(cpu, addr); break;
	case PHA: printf("PHA"); getInstrOPs(cpu, addr); break;
	case PHP: printf("PHP"); getInstrOPs(cpu, addr); break;
	case PLA: printf("PLA"); getInstrOPs(cpu, addr); break;
	case PLP: printf("PLP"); getInstrOPs(cpu, addr); break;
	case ROL: printf("ROL"); getInstrOPs(cpu, addr); break;
	case ROR: printf("ROR"); getInstrOPs(cpu, addr); break;
	case RTI: printf("RTI"); getInstrOPs(cpu, addr); break;
	case RTS: printf("RTS"); getInstrOPs(cpu, addr); break;
	case SBC: printf("SBC"); getInstrOPs(cpu, addr); break;
	case SEC: printf("SEC"); getInstrOPs(cpu, addr); break;
	case SED: printf("SED"); getInstrOPs(cpu, addr); break;
	case SEI: printf("SEI"); getInstrOPs(cpu, addr); break;
	case STA: printf("STA"); getInstrOPs(cpu, addr); break;
	case STX: printf("STX"); getInstrOPs(cpu, addr); break;
	case STY: printf("STY"); getInstrOPs(cpu, addr); break;
	case TAX: printf("TAX"); getInstrOPs(cpu, addr); break;
	case TAY: printf("TAY"); getInstrOPs(cpu, addr); break;
	case TSX: printf("TSX"); getInstrOPs(cpu, addr); break;
	case TXA: printf("TXA"); getInstrOPs(cpu, addr); break;
	case TXS: printf("TXS"); getInstrOPs(cpu, addr); break;
	case TYA: printf("TYA"); getInstrOPs(cpu, addr); break;
	}
}
#endif

void cpu_run(cpu_t* cpu) {
#if DBG
	u8 sts = (cpu->f_N << 7) | (cpu->f_V << 6) |
			 (cpu->ZZZ << 5) | (cpu->f_B << 4) |
			 (cpu->f_D << 3) | (cpu->f_I << 2) |
			 (cpu->f_Z << 1) | (cpu->f_C << 0);
	printf("%04x  ", cpu->PC);
	printf("%02x ", cpubus_read(cpu->PC));
	getOPs(cpu, addrModeMap[cpubus_read(cpu->PC)]);
	getInstr(cpu, instrMap[cpubus_read(cpu->PC)], addrModeMap[cpubus_read(cpu->PC)]);
	printf("A:%02x X:%02x Y:%02x P:%02x SP:%02x ", cpu->A, cpu->X, cpu->Y, sts, cpu->SP);
	printf("CYC:%d\n", cpu->cycles);
#endif
	switch (instrMap[cpubus_read(cpu->PC)]) {
	case ADC: i_ADC(cpu); break;
	case AND: i_AND(cpu); break;
	case ASL: i_ASL(cpu); break;
	case BCC: i_BCC(cpu); break;
	case BCS: i_BCS(cpu); break;
	case BEQ: i_BEQ(cpu); break;
	case BIT: i_BIT(cpu); break;
	case BMI: i_BMI(cpu); break;
	case BNE: i_BNE(cpu); break;
	case BPL: i_BPL(cpu); break;
	case BRK: i_BRK(cpu); break;
	case BVC: i_BVC(cpu); break;
	case BVS: i_BVS(cpu); break;
	case CLC: i_CLC(cpu); break;
	case CLD: i_CLD(cpu); break;
	case CLI: i_CLI(cpu); break;
	case CLV: i_CLV(cpu); break;
	case CMP: i_CMP(cpu); break;
	case CPX: i_CPX(cpu); break;
	case CPY: i_CPY(cpu); break;
	case DEC: i_DEC(cpu); break;
	case DEX: i_DEX(cpu); break;
	case DEY: i_DEY(cpu); break;
	case EOR: i_EOR(cpu); break;
	case INC: i_INC(cpu); break;
	case INX: i_INX(cpu); break;
	case INY: i_INY(cpu); break;
	case JMP: i_JMP(cpu); break;
	case JSR: i_JSR(cpu); break;
	case LDA: i_LDA(cpu); break;
	case LDX: i_LDX(cpu); break;
	case LDY: i_LDY(cpu); break;
	case LSR: i_LSR(cpu); break;
	case NOP: i_NOP(cpu); break;
	case ORA: i_ORA(cpu); break;
	case PHA: i_PHA(cpu); break;
	case PHP: i_PHP(cpu); break;
	case PLA: i_PLA(cpu); break;
	case PLP: i_PLP(cpu); break;
	case ROL: i_ROL(cpu); break;
	case ROR: i_ROR(cpu); break;
	case RTI: i_RTI(cpu); break;
	case RTS: i_RTS(cpu); break;
	case SBC: i_SBC(cpu); break;
	case SEC: i_SEC(cpu); break;
	case SED: i_SED(cpu); break;
	case SEI: i_SEI(cpu); break;
	case STA: i_STA(cpu); break;
	case STX: i_STX(cpu); break;
	case STY: i_STY(cpu); break;
	case TAX: i_TAX(cpu); break;
	case TAY: i_TAY(cpu); break;
	case TSX: i_TSX(cpu); break;
	case TXA: i_TXA(cpu); break;
	case TXS: i_TXS(cpu); break;
	case TYA: i_TYA(cpu); break;
	case NaN: printf("FATAL ERROR: bad instruction given!\n"); break;
	}
}

void cpu_nmi(cpu_t* cpu) {
	//DO LATER
}

u8 fetch(cpu_t* cpu) {
	u8 buffer8 = 0;
	u16 buffer16 = 0;
	u16 buffer16_1 = 0;
	cpu->cycles += clkCyclesMap[cpubus_read(cpu->PC)];
	switch (addrModeMap[cpubus_read(cpu->PC)]) {
	case ACC:
		cpu->PC += 1;
		return cpu->A;
	case ABS:
		buffer16 = (cpubus_read(cpu->PC + 2) << 8) | cpubus_read(cpu->PC + 1);
		cpu->last_addr = buffer16;
		cpu->PC += 3;
		return cpubus_read(buffer16);
	case ABSX:
		buffer16 = ((cpubus_read(cpu->PC + 2) << 8) | cpubus_read(cpu->PC + 1));
		buffer16_1 = buffer16 + cpu->X;
		if ((buffer16 & 0xFF00) != (buffer16_1 & 0xFF00)) {
			if (instrMap[cpubus_read(cpu->PC)] != ASL && instrMap[cpubus_read(cpu->PC)] != DEC &&
				instrMap[cpubus_read(cpu->PC)] != INC && instrMap[cpubus_read(cpu->PC)] != LSR &&
				instrMap[cpubus_read(cpu->PC)] != ROL && instrMap[cpubus_read(cpu->PC)] != ROR &&
				instrMap[cpubus_read(cpu->PC)] != STA)
			{
				cpu->cycles += 1;
			}
		}
		cpu->last_addr = buffer16_1;
		cpu->PC += 3;
		return cpubus_read(buffer16_1);
	case ABSY:
		buffer16 = ((cpubus_read(cpu->PC + 2) << 8) | cpubus_read(cpu->PC + 1));
		buffer16_1 = buffer16 + cpu->Y;
		if ((buffer16 & 0xFF00) != (buffer16_1 & 0xFF00)) {
			if (instrMap[cpubus_read(cpu->PC)] != STA) {
				cpu->cycles += 1;
			}
		}
		cpu->last_addr = buffer16_1;
		cpu->PC += 3;
		return cpubus_read(buffer16_1);
	case IMM:
		cpu->PC += 2;
		return cpubus_read(cpu->PC - 1); //-1 because we are pointing to next instruction, but we need data that is behind it
	case IMP:
		cpu->PC += 1;
		return 0;
	case IND:
		buffer16 = (cpubus_read(cpu->PC + 2) << 8) | cpubus_read(cpu->PC + 1);
		if ((buffer16 & 0xFF) == 0xFF) {
			cpu->last_addr = (cpubus_read(buffer16 & 0xFF00) << 8) | cpubus_read(buffer16);
		}
		else {
			cpu->last_addr = (cpubus_read(buffer16 + 1) << 8) | cpubus_read(buffer16);
		}
		return 0;
	case INDX:
		buffer8  = cpubus_read(cpu->PC + 1) + cpu->X;
		buffer16 = (cpubus_read((buffer8 + 1) & 0xFF) << 8) | cpubus_read(buffer8);
		cpu->last_addr = buffer16;
		cpu->PC += 2;
		return cpubus_read(buffer16);
	case INDY:
		buffer8 = cpubus_read(cpu->PC + 1);
		buffer16 = (cpubus_read((buffer8 + 1) & 0xFF) << 8) | cpubus_read(buffer8);
		buffer16_1 = buffer16 + cpu->Y;
		if ((buffer16 & 0xFF00) != (buffer16_1 & 0xFF00)) {
			if (instrMap[cpubus_read(cpu->PC)] != STA) {
				cpu->cycles += 1;
			}
		}
		cpu->last_addr = buffer16_1;
		cpu->PC += 2;
		return cpubus_read(buffer16_1);
	case REL:
		buffer8 = cpubus_read(cpu->PC + 1);
		cpu->last_addr = buffer8;
		cpu->PC += 2;
		return buffer8;
	case ZER:
		buffer8 = cpubus_read(cpu->PC + 1);
		cpu->last_addr = buffer8;
		cpu->PC += 2;
		return cpubus_read(buffer8);
	case ZERX:
		buffer8 = cpubus_read(cpu->PC + 1) + cpu->X;
		cpu->last_addr = buffer8;
		cpu->PC += 2;
		return cpubus_read(buffer8);
	case ZERY:
		buffer8 = cpubus_read(cpu->PC + 1) + cpu->Y;
		cpu->last_addr = buffer8;
		cpu->PC += 2;
		return cpubus_read(buffer8);
	}
}

set_Nflag(cpu_t* cpu, bool state) {
	cpu->f_N = state;
}
set_Vflag(cpu_t* cpu, bool state) {
	cpu->f_V = state;
}
set_Bflag(cpu_t* cpu, bool state) {
	cpu->f_B = state;
}
set_Dflag(cpu_t* cpu, bool state) {
	cpu->f_D = state;
}
set_Iflag(cpu_t* cpu, bool state) {
	cpu->f_I = state;
}
set_Zflag(cpu_t* cpu, bool state) {
	cpu->f_Z = state;
}
set_Cflag(cpu_t* cpu, bool state) {
	cpu->f_C = state;
}

void i_ADC(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = cpu->A + tmp + cpu->f_C;
	set_Cflag(cpu, buffer > 0xFF);
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Vflag(cpu, (~((u16)cpu->A ^ (u16)tmp) & ((u16)cpu->A ^ buffer)) & 0x80);
	set_Nflag(cpu, buffer & 0x80);
	cpu->A = buffer;
}
void i_AND(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpu->A = cpu->A & tmp;
	set_Zflag(cpu, (cpu->A & 0xFF) == 0);
	set_Nflag(cpu, cpu->A & 0x80);
}
void i_ASL(cpu_t* cpu) {
	u8 addrMode = addrModeMap[cpubus_read(cpu->PC)];
	u8 tmp = fetch(cpu);
	u16 buffer = tmp << 1;
	set_Cflag(cpu, buffer > 0xFF);
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
	if (addrMode == ACC) {
		cpu->A = buffer;
	}
	else {
		cpubus_write(buffer, cpu->last_addr);
	}
}
void i_BCC(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	if (!cpu->f_C) {
		if ((cpu->PC & 0xFF00) != ((cpu->PC + tmp) & 0xFF00)) {
			cpu->cycles += 1;
		}
		cpu->PC = cpu->PC + tmp;
		cpu->cycles += 1;
	}
}
void i_BCS(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	if (cpu->f_C) {
		if ((cpu->PC & 0xFF00) != ((cpu->PC + tmp) & 0xFF00)) {
			cpu->cycles += 1;
		}
		cpu->PC = cpu->PC + tmp;
		cpu->cycles += 1;
	}
}
void i_BEQ(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	if (cpu->f_Z) {
		if ((cpu->PC & 0xFF00) != ((cpu->PC + tmp) & 0xFF00)) {
			cpu->cycles += 1;
		}
		cpu->PC = cpu->PC + tmp;
		cpu->cycles += 1;
	}
}
void i_BIT(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = cpu->A & tmp;
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Vflag(cpu, tmp & 0x40);
	set_Nflag(cpu, tmp & 0x80);
}
void i_BMI(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	if (cpu->f_N) {
		if ((cpu->PC & 0xFF00) != ((cpu->PC + tmp) & 0xFF00)) {
			cpu->cycles += 1;
		}
		cpu->PC = cpu->PC + tmp;
		cpu->cycles += 1;
	}
}
void i_BNE(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	if (!cpu->f_Z) {
		if ((cpu->PC & 0xFF00) != ((cpu->PC + tmp) & 0xFF00)) {
			cpu->cycles += 1;
		}
		cpu->PC = cpu->PC + tmp;
		cpu->cycles += 1;
	}
}
void i_BPL(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	if (!cpu->f_N) {
		if ((cpu->PC & 0xFF00) != ((cpu->PC + tmp) & 0xFF00)) {
			cpu->cycles += 1;
		}
		cpu->PC = cpu->PC + tmp;
		cpu->cycles += 1;
	}
}
void i_BRK(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	set_Iflag(cpu, 1);
	cpubus_write(cpu->PC >> 8, 0x0100 + cpu->SP--);
	cpubus_write(cpu->PC,      0x0100 + cpu->SP--);
	set_Bflag(cpu, 1);
	u8 sts = (cpu->f_N << 7) | (cpu->f_V << 6) |
			 (cpu->ZZZ << 5) | (cpu->f_B << 4) |
			 (cpu->f_D << 3) | (cpu->f_I << 2) |
			 (cpu->f_Z << 1) | (cpu->f_C << 0);
	cpubus_write(sts, 0x0100 + cpu->SP--);
}
void i_BVC(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	if (!cpu->f_V) {
		if ((cpu->PC & 0xFF00) != ((cpu->PC + tmp) & 0xFF00)) {
			cpu->cycles += 1;
		}
		cpu->PC = cpu->PC + tmp;
		cpu->cycles += 1;
	}
}
void i_BVS(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	if (cpu->f_V) {
		if ((cpu->PC & 0xFF00) != ((cpu->PC + tmp) & 0xFF00)) {
			cpu->cycles += 1;
		}
		cpu->PC = cpu->PC + tmp;
		cpu->cycles += 1;
	}
}
void i_CLC(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	set_Cflag(cpu, 0);
}
void i_CLD(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	set_Dflag(cpu, 0);
}
void i_CLI(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	set_Iflag(cpu, 0);
}
void i_CLV(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	set_Vflag(cpu, 0);
}
void i_CMP(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = cpu->A - tmp;
	set_Cflag(cpu, cpu->A >= tmp);
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
}
void i_CPX(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = cpu->X - tmp;
	set_Cflag(cpu, cpu->X >= tmp);
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
}
void i_CPY(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = cpu->Y - tmp;
	set_Cflag(cpu, cpu->Y >= tmp);
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
}
void i_DEC(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = tmp - 1;
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
	cpubus_write(buffer, cpu->last_addr);
}
void i_DEX(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = cpu->X - 1;
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
	cpu->X = buffer;
}
void i_DEY(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = cpu->Y - 1;
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
	cpu->Y = buffer;
}
void i_EOR(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = cpu->A ^ tmp;
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
	cpu->A = buffer;
}
void i_INC(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = tmp + 1;
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
	cpubus_write(buffer, cpu->last_addr);
}
void i_INX(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = cpu->X + 1;
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
	cpu->X = buffer;
}
void i_INY(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = cpu->Y + 1;
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
	cpu->Y = buffer;
}
void i_JMP(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpu->PC = cpu->last_addr;
}
void i_JSR(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpu->PC--;
	cpubus_write(cpu->PC >> 8, 0x0100 + cpu->SP--);
	cpubus_write(cpu->PC, 0x0100 + cpu->SP--);
	cpu->PC = cpu->last_addr;
}
void i_LDA(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	set_Zflag(cpu, (tmp & 0xFF) == 0);
	set_Nflag(cpu, tmp & 0x80);
	cpu->A = tmp;
}
void i_LDX(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	set_Zflag(cpu, (tmp & 0xFF) == 0);
	set_Nflag(cpu, tmp & 0x80);
	cpu->X = tmp;
}
void i_LDY(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	set_Zflag(cpu, (tmp & 0xFF) == 0);
	set_Nflag(cpu, tmp & 0x80);
	cpu->Y = tmp;
}
void i_LSR(cpu_t* cpu) {
	u8 addrMode = addrModeMap[cpubus_read(cpu->PC)];
	u8 tmp = fetch(cpu);
	set_Cflag(cpu, tmp & 0x01);
	u16 buffer = tmp >> 1;
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, 0);
	if (addrMode == ACC) {
		cpu->A = buffer;
	}
	else {
		cpubus_write(buffer, cpu->last_addr);
	}
}
void i_NOP(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
}
void i_ORA(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpu->A = cpu->A | tmp;
	set_Zflag(cpu, (cpu->A & 0xFF) == 0);
	set_Nflag(cpu, cpu->A & 0x80);
}
void i_PHA(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpubus_write(cpu->A, 0x0100 + cpu->SP--);
}
void i_PHP(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u8 sts = (cpu->f_N << 7) | (cpu->f_V << 6) |
			 (1 << 5)        | (1 << 4) |
			 (cpu->f_D << 3) | (cpu->f_I << 2) |
			 (cpu->f_Z << 1) | (cpu->f_C << 0);
	cpubus_write(sts, 0x0100 + cpu->SP--);
}
void i_PLA(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpu->A = cpubus_read(0x0100 + ++cpu->SP);
	set_Zflag(cpu, cpu->A == 0x00);
	set_Nflag(cpu, cpu->A & 0x80);
}
void i_PLP(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u8 sts = cpubus_read(0x0100 + ++cpu->SP);
	cpu->f_N = sts >> 7 & 0x01;
	cpu->f_V = sts >> 6 & 0x01;
	cpu->ZZZ = 1;
	cpu->f_B = 0;
	cpu->f_D = sts >> 3 & 0x01;
	cpu->f_I = sts >> 2 & 0x01;
	cpu->f_Z = sts >> 1 & 0x01;
	cpu->f_C = sts >> 0 & 0x01;
}
void i_ROL(cpu_t* cpu) {
	u8 addrMode = addrModeMap[cpubus_read(cpu->PC)];
	u8 tmp = fetch(cpu);
	u8 tmpC = cpu->f_C;
	u16 buffer = (tmp << 1) | cpu->f_C;
	set_Cflag(cpu, buffer > 0xFF);
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
	if (addrMode == ACC) {
		cpu->A = buffer;
	}
	else {
		cpubus_write(buffer, cpu->last_addr);
	}
}
void i_ROR(cpu_t* cpu) {
	u8 addrMode = addrModeMap[cpubus_read(cpu->PC)];
	u8 tmp = fetch(cpu);
	u8 tmpC = cpu->f_C;
	set_Cflag(cpu, tmp & 0x01);
	u16 buffer = (tmpC << 7) | (tmp >> 1);
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Nflag(cpu, buffer & 0x80);
	if (addrMode == ACC) {
		cpu->A = buffer;
	}
	else {
		cpubus_write(buffer, cpu->last_addr);
	}
}
void i_RTI(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u8 sts = cpubus_read(0x0100 + ++cpu->SP);
	cpu->f_N = sts >> 7 & 0x01;
	cpu->f_V = sts >> 6 & 0x01;
	cpu->ZZZ = 1;
	cpu->f_B = 0;
	cpu->f_D = sts >> 3 & 0x01;
	cpu->f_I = sts >> 2 & 0x01;
	cpu->f_Z = sts >> 1 & 0x01;
	cpu->f_C = sts >> 0 & 0x01;
	u8 lo = cpubus_read(0x0100 + ++cpu->SP);
	u8 hi = cpubus_read(0x0100 + ++cpu->SP);
	cpu->PC = (hi << 8) | lo;
}
void i_RTS(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u8 lo = cpubus_read(0x0100 + ++cpu->SP);
	u8 hi = cpubus_read(0x0100 + ++cpu->SP);
	cpu->PC = ((hi << 8) | lo) + 1;
}
void i_SBC(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	u16 buffer = cpu->A - tmp - (1 - cpu->f_C);
	set_Cflag(cpu, buffer < 0x100);
	set_Zflag(cpu, (buffer & 0xFF) == 0);
	set_Vflag(cpu, ((cpu->A ^ tmp) & 0x80) & ((cpu->A ^ buffer) & 0x80));
	set_Nflag(cpu, buffer & 0x80);
	cpu->A = buffer;
}
void i_SEC(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	set_Cflag(cpu, 1);
}
void i_SED(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	set_Dflag(cpu, 1);
}
void i_SEI(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	set_Iflag(cpu, 1);
}
void i_STA(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpubus_write(cpu->A, cpu->last_addr);
}
void i_STX(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpubus_write(cpu->X, cpu->last_addr);
}
void i_STY(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpubus_write(cpu->Y, cpu->last_addr);
}
void i_TAX(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpu->X = cpu->A;
	set_Zflag(cpu, (cpu->X & 0xFF) == 0);
	set_Nflag(cpu, cpu->X & 0x80);
}
void i_TAY(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpu->Y = cpu->A;
	set_Zflag(cpu, (cpu->Y & 0xFF) == 0);
	set_Nflag(cpu, cpu->Y & 0x80);
}
void i_TSX(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpu->X = cpu->SP;
	set_Zflag(cpu, (cpu->X & 0xFF) == 0);
	set_Nflag(cpu, cpu->X & 0x80);
}
void i_TXA(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpu->A = cpu->X;
	set_Zflag(cpu, (cpu->A & 0xFF) == 0);
	set_Nflag(cpu, cpu->A & 0x80);
}
void i_TXS(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpu->SP = cpu->X;
}
void i_TYA(cpu_t* cpu) {
	u8 tmp = fetch(cpu);
	cpu->A = cpu->Y;
	set_Zflag(cpu, (cpu->A & 0xFF) == 0);
	set_Nflag(cpu, cpu->A & 0x80);
}

