// main.cpp : Defines the entry point for the application.
//

#include "cpu/inc/cpu.h"
#include "ppu/inc/ppu.h"
#include "apu/inc/apu.h"
#include "cpubus/inc/cpubus.h"

int main(int argc, int* argv[]) {
	cpu_t cpu;
	cpu_init(&cpu);
	printf("A: 0x%02x\n",  cpu.A);
	printf("X: 0x%02x\n",  cpu.X);
	printf("Y: 0x%02x\n",  cpu.Y);
	printf("SP: 0x%04x\n", cpu.SP);
	printf("PC: 0x%04x\n", cpu.PC);
 	printf("C: 0x%01x\n",  cpu.f_C);
	printf("Z: 0x%01x\n",  cpu.f_Z);
	printf("I: 0x%01x\n",  cpu.f_I);
	printf("D: 0x%01x\n",  cpu.f_D);
	printf("B: 0x%01x\n",  cpu.f_B);
	printf("V: 0x%01x\n",  cpu.f_V);
	printf("N: 0x%01x\n",  cpu.f_N);
	return 0;
}
