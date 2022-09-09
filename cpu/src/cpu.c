#include <stdio.h>
#include <stdlib.h>

#include "../inc/cpu.h"
#include "../../cpubus/inc/cpubus.h"

void myfunc() {
	printf("Hello from CPU!\n");
}

void cpu_init(cpu_t* cpu) {
	cpu->A = 0xDE;
	cpu->X = 0xAD;
	cpu->Y = 0xBE;
	cpu->SP = 0xFD;
	cpu->PC = 0xACCE;
	cpu->f_C = 1;
	cpu->f_Z = 0;
	cpu->f_I = 1;
	cpu->f_D = 0;
	cpu->f_B = 1;
	cpu->f_V = 0;
	cpu->f_N = 1;
}

void cpu_run(cpu_t* cpu) {
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

u8 fetch(cpu_t* cpu) {
	switch (addrModeMap[cpubus_read(cpu->PC++)]) {
	case ACC:
		printf("FATAL ERROR: should not have been able to get here on this instruction!\n")
		break;
	case ABS:
		break;
	case ABSX:
		break;
	case ABSY:
		break;
	case IMM:
		break;
	case IMP:
		break;
	case IND:
		break;
	case INDX:
		break;
	case INDY:
		break;
	case REL:
		break;
	case ZER:
		break;
	case ZERX:
		break;
	case ZERY:
		break;
	}
}

void i_ADC(cpu_t* cpu) {
	fetch(cpu);
}
void i_AND(cpu_t* cpu);
void i_ASL(cpu_t* cpu);
void i_BCC(cpu_t* cpu);
void i_BCS(cpu_t* cpu);
void i_BEQ(cpu_t* cpu);
void i_BIT(cpu_t* cpu);
void i_BMI(cpu_t* cpu);
void i_BNE(cpu_t* cpu);
void i_BPL(cpu_t* cpu);
void i_BRK(cpu_t* cpu);
void i_BVC(cpu_t* cpu);
void i_BVS(cpu_t* cpu);
void i_CLC(cpu_t* cpu);
void i_CLD(cpu_t* cpu);
void i_CLI(cpu_t* cpu);
void i_CLV(cpu_t* cpu);
void i_CMP(cpu_t* cpu);
void i_CPX(cpu_t* cpu);
void i_CPY(cpu_t* cpu);
void i_DEC(cpu_t* cpu);
void i_DEX(cpu_t* cpu);
void i_DEY(cpu_t* cpu);
void i_EOR(cpu_t* cpu);
void i_INC(cpu_t* cpu);
void i_INX(cpu_t* cpu);
void i_INY(cpu_t* cpu);
void i_JMP(cpu_t* cpu);
void i_JSR(cpu_t* cpu);
void i_LDA(cpu_t* cpu);
void i_LDX(cpu_t* cpu);
void i_LDY(cpu_t* cpu);
void i_LSR(cpu_t* cpu);
void i_NOP(cpu_t* cpu);
void i_ORA(cpu_t* cpu);
void i_PHA(cpu_t* cpu);
void i_PHP(cpu_t* cpu);
void i_PLA(cpu_t* cpu);
void i_PLP(cpu_t* cpu);
void i_ROL(cpu_t* cpu);
void i_ROR(cpu_t* cpu);
void i_RTI(cpu_t* cpu);
void i_RTS(cpu_t* cpu);
void i_SBC(cpu_t* cpu);
void i_SEC(cpu_t* cpu);
void i_SED(cpu_t* cpu);
void i_SEI(cpu_t* cpu);
void i_STA(cpu_t* cpu);
void i_STX(cpu_t* cpu);
void i_STY(cpu_t* cpu);
void i_TAX(cpu_t* cpu);
void i_TAY(cpu_t* cpu);
void i_TSX(cpu_t* cpu);
void i_TXA(cpu_t* cpu);
void i_TXS(cpu_t* cpu);
void i_TYA(cpu_t* cpu);

