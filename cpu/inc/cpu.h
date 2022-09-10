#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define i8  int8_t
#define i16 int16_t
#define i32 int32_t

typedef struct {
	//registers
	u8 A;
	u8 X;
	u8 Y;
	u8 SP;
	u16 PC;
	
	//flags
	u8 f_N; //7
	u8 f_V; //6
	u8 ZZZ; //5
	u8 f_B; //4
	u8 f_D; //3
	u8 f_I; //2
	u8 f_Z; //1
	u8 f_C; //0

	//last addr computed by fetch function
	u16 last_addr;

	//clock cycles done so far
	u32 cycles;

	//place holder for sys memory
	u8 ram[0xFFFF];
} cpu_t;

u8 ram[0xFFFF];

enum addrMode {
	NONE, //NO ADDRESSING MODE
	ACC,  //ACCUMULATOR
	ABS,  //ABSOLUTE
	ABSX, //ABSOLUTE X
	ABSY, //ABSOLUTE Y
	IMM,  //IMMEDIATE
	IMP,  //IMPLIED
	IND,  //INDIRECT
	INDX, //INDIRECT X
	INDY, //INDIRECT Y
	REL,  //RELATIVE
	ZER,  //ZERO PAGE
	ZERX, //ZERO PAGE X
	ZERY  //ZERO PAGE Y
};

typedef enum insnName {
	NaN,
	ADC, AND, ASL,
	BCC, BCS, BEQ, BIT, BMI, BNE, BPL, BRK, BVC, BVS,
	CLC, CLD, CLI, CLV, CMP, CPX, CPY,
	DEC, DEX, DEY,
	EOR,
	INC, INX, INY,
	JMP, JSR,
	LDA, LDX, LDY, LSR,
	NOP,
	ORA,
	PHA, PHP, PLA, PLP,
	ROL, ROR, RTI, RTS,
	SBC, SEC, SED, SEI, STA, STX, STY,
	TAX, TAY, TSX, TXA, TXS, TYA
}insn;

static const u8 addrModeMap[256] = {
	IMP,  INDX, NONE, NONE, NONE, ZER,  ZER,  NONE, IMP,  IMM,  ACC,  NONE, NONE, ABS,  ABS,  NONE,
	REL,  INDY, NONE, NONE, NONE, ZERX, ZERX, NONE, IMP,  ABSY, NONE, NONE, NONE, ABSX, ABSX, NONE,
	ABS,  INDX, NONE, NONE, ZER,  ZER,  ZER,  NONE, IMP,  IMM,  ACC,  NONE, ABS,  ABS,  ABS,  NONE,
	REL,  INDY, NONE, NONE, NONE, ZERX, ZERX, NONE, IMP,  ABSY, NONE, NONE, NONE, ABSX, ABSX, NONE,
	IMP,  INDX, NONE, NONE, NONE, ZER,  ZER,  NONE, IMP,  IMM,  ACC,  NONE, ABS,  ABS,  ABS,  NONE,
	REL,  INDY, NONE, NONE, NONE, ZERX, ZERX, NONE, IMP,  ABSY, NONE, NONE, NONE, ABSX, ABSX, NONE,
	IMP,  INDX, NONE, NONE, NONE, ZER,  ZER,  NONE, IMP,  IMM,  ACC,  NONE, IND,  ABS,  ABS,  NONE,
	REL,  INDY, NONE, NONE, NONE, ZERX, ZERX, NONE, IMP,  ABSY, NONE, NONE, NONE, ABSX, ABSX, NONE,
	NONE, INDX, NONE, NONE, ZER,  ZER,  ZER,  NONE, IMP,  NONE, IMP,  NONE, ABS,  ABS,  ABS,  NONE,
	REL,  INDY, NONE, NONE, ZERX, ZERX, ZERY, NONE, IMP,  ABSY, IMP,  NONE, NONE, ABSX, NONE, NONE,
	IMM,  INDX, IMM,  NONE, ZER,  ZER,  ZER,  NONE, IMP,  IMM,  IMP,  NONE, ABS,  ABS,  ABS,  NONE,
	REL,  INDY, NONE, NONE, ZERX, ZERX, ZERY, NONE, IMP,  ABSY, IMP,  NONE, ABSX, ABSX, ABSY, NONE,
	IMM,  INDX, NONE, NONE, ZER,  ZER,  ZER,  NONE, IMP,  IMM,  IMP,  NONE, ABS,  ABS,  ABS,  NONE,
	REL,  INDY, NONE, NONE, NONE, ZERX, ZERX, NONE, IMP,  ABSY, NONE, NONE, NONE, ABSX, ABSX, NONE,
	IMM,  INDX, NONE, NONE, ZER,  ZER,  ZER,  NONE, IMP,  IMM,  IMP,  NONE, ABS,  ABS,  ABS,  NONE,
	REL,  INDY, NONE, NONE, NONE, ZERX, ZERX, NONE, IMP,  ABSY, NONE, NONE, NONE, ABSX, ABSX, NONE
};

static const u8 instrMap[256] = {
	BRK, ORA, NaN, NaN, NaN, ORA, ASL, NaN, PHP, ORA, ASL, NaN, NaN, ORA, ASL, NaN,
	BPL, ORA, NaN, NaN, NaN, ORA, ASL, NaN, CLC, ORA, NaN, NaN, NaN, ORA, ASL, NaN,
	JSR, AND, NaN, NaN, BIT, AND, ROL, NaN, PLP, AND, ROL, NaN, BIT, AND, ROL, NaN,
	BMI, AND, NaN, NaN, NaN, AND, ROL, NaN, SEC, AND, NaN, NaN, NaN, AND, ROL, NaN,
	RTI, EOR, NaN, NaN, NaN, EOR, LSR, NaN, PHA, EOR, LSR, NaN, JMP, EOR, LSR, NaN,
	BVC, EOR, NaN, NaN, NaN, EOR, LSR, NaN, CLI, EOR, NaN, NaN, NaN, EOR, LSR, NaN,
	RTS, ADC, NaN, NaN, NaN, ADC, ROR, NaN, PLA, ADC, ROR, NaN, JMP, ADC, ROR, NaN,
	BVS, ADC, NaN, NaN, NaN, ADC, ROR, NaN, SEI, ADC, NaN, NaN, NaN, ADC, ROR, NaN,
	NaN, STA, NaN, NaN, STY, STA, STX, NaN, DEY, NaN, TXA, NaN, STY, STA, STX, NaN,
	BCC, STA, NaN, NaN, STY, STA, STX, NaN, TYA, STA, TXS, NaN, NaN, STA, NaN, NaN,
	LDY, LDA, LDX, NaN, LDY, LDA, LDX, NaN, TAY, LDA, TAX, NaN, LDY, LDA, LDX, NaN,
	BCS, LDA, NaN, NaN, LDY, LDA, LDX, NaN, CLV, LDA, TSX, NaN, LDY, LDA, LDX, NaN,
	CPY, CMP, NaN, NaN, CPY, CMP, DEC, NaN, INY, CMP, DEX, NaN, CPY, CMP, DEC, NaN,
	BNE, CMP, NaN, NaN, NaN, CMP, DEC, NaN, CLD, CMP, NaN, NaN, NaN, CMP, DEC, NaN,
	CPX, SBC, NaN, NaN, CPX, SBC, INC, NaN, INX, SBC, NOP, NaN, CPX, SBC, INC, NaN,
	BEQ, SBC, NaN, NaN, NaN, SBC, INC, NaN, SED, SBC, NaN, NaN, NaN, SBC, INC, NaN
};

static const u8 clkCyclesMap[256] = {
	7, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 0, 4, 6, 0,
	2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
	6, 6, 0, 0, 3, 3, 5, 0, 4, 2, 2, 0, 4, 4, 6, 0,
	2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
	6, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 3, 4, 6, 0,
	2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
	6, 6, 0, 0, 0, 3, 5, 0, 4, 2, 2, 0, 5, 4, 6, 0,
	2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
	0, 6, 0, 0, 3, 3, 3, 0, 2, 0, 2, 0, 4, 4, 4, 0,
	2, 6, 0, 0, 4, 4, 4, 0, 2, 5, 2, 0, 0, 5, 0, 0,
	2, 6, 2, 0, 3, 3, 3, 0, 2, 2, 2, 0, 4, 4, 4, 0,
	2, 5, 0, 0, 4, 4, 4, 0, 2, 4, 2, 0, 4, 4, 4, 0,
	2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 6, 0,
	2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
	2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 2, 4, 4, 6, 0,
	2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
};

void cpu_init(cpu_t* cpu);
void cpu_run(cpu_t* cpu);
void cpu_nmi(cpu_t* cpu);

u8 fetch(cpu_t* cpu);

set_Nflag(cpu_t* cpu, bool state);
set_Vflag(cpu_t* cpu, bool state);
set_Bflag(cpu_t* cpu, bool state);
set_Dflag(cpu_t* cpu, bool state);
set_Iflag(cpu_t* cpu, bool state);
set_Zflag(cpu_t* cpu, bool state);
set_Cflag(cpu_t* cpu, bool state);

void i_ADC(cpu_t* cpu); //add with carry
void i_AND(cpu_t* cpu); //and (with accumulator)
void i_ASL(cpu_t* cpu); //arithmetic shift left
void i_BCC(cpu_t* cpu); //branch on carry clear
void i_BCS(cpu_t* cpu); //branch on carry set
void i_BEQ(cpu_t* cpu); //branch on zero set
void i_BIT(cpu_t* cpu); //bit test
void i_BMI(cpu_t* cpu); //branch on negative set
void i_BNE(cpu_t* cpu); //branch on zero clear
void i_BPL(cpu_t* cpu); //branch o negative clear
void i_BRK(cpu_t* cpu); //break/interrupt
void i_BVC(cpu_t* cpu); //branch on overflow clear
void i_BVS(cpu_t* cpu); //branch on overflow set
void i_CLC(cpu_t* cpu); //clear carry
void i_CLD(cpu_t* cpu); //clear decimal
void i_CLI(cpu_t* cpu); //clear interrupt disable
void i_CLV(cpu_t* cpu); //clear overflow
void i_CMP(cpu_t* cpu); //compare (with accumulator)
void i_CPX(cpu_t* cpu); //compare with X
void i_CPY(cpu_t* cpu); //compare with Y
void i_DEC(cpu_t* cpu); //decrement
void i_DEX(cpu_t* cpu); //decrement X
void i_DEY(cpu_t* cpu); //decrement Y
void i_EOR(cpu_t* cpu); //XOR (with accumulator)
void i_INC(cpu_t* cpu); //increment
void i_INX(cpu_t* cpu); //increment X
void i_INY(cpu_t* cpu); //increment Y
void i_JMP(cpu_t* cpu); //jump
void i_JSR(cpu_t* cpu); //jump subroutine
void i_LDA(cpu_t* cpu); //load accumulator
void i_LDX(cpu_t* cpu); //load X
void i_LDY(cpu_t* cpu); //load Y
void i_LSR(cpu_t* cpu); //logical shift right
void i_NOP(cpu_t* cpu); //no operation
void i_ORA(cpu_t* cpu); //or (with accumulator)
void i_PHA(cpu_t* cpu); //push accumulator
void i_PHP(cpu_t* cpu); //push processor status
void i_PLA(cpu_t* cpu); //pull accumulator
void i_PLP(cpu_t* cpu); //pull processor status
void i_ROL(cpu_t* cpu); //rotate left
void i_ROR(cpu_t* cpu); //rotate right
void i_RTI(cpu_t* cpu); //return from interrupt
void i_RTS(cpu_t* cpu); //return from subroutine
void i_SBC(cpu_t* cpu); //subtract with carry
void i_SEC(cpu_t* cpu); //set carry
void i_SED(cpu_t* cpu); //set decimal
void i_SEI(cpu_t* cpu); //set interrupt disable
void i_STA(cpu_t* cpu); //store accumulator
void i_STX(cpu_t* cpu); //store X
void i_STY(cpu_t* cpu); //store Y
void i_TAX(cpu_t* cpu); //transfer accumulator to X
void i_TAY(cpu_t* cpu); //transfer accumulator to Y
void i_TSX(cpu_t* cpu); //transfer stack pointer to X
void i_TXA(cpu_t* cpu); //transfer X to accumulator
void i_TXS(cpu_t* cpu); //transfer X to stack pointer
void i_TYA(cpu_t* cpu); //transfer Y to accumulator

#endif CPU_H
