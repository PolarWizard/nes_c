// main.cpp : Defines the entry point for the application.
//

#include <stdio.h>

#include "cpu/inc/cpu.h"
#include "ppu/inc/ppu.h"
#include "apu/inc/apu.h"
#include "cpubus/inc/cpubus.h"

u8* loadfile(cpu_t* cpu, const char* path) {
	FILE* fp;
	fp = fopen(path, "rb");
	fread(ram, 1, 16, fp);
	fread(ram, 1, 65520, fp);
	fclose(fp);
}

int main(int argc, int* argv[]) {
	cpu_t cpu;
	cpu_init(&cpu);
	loadfile(&cpu, "C:/Users/domin/OneDrive/Desktop/nestest.nes");
	while (1) {
		cpu_run(&cpu);
	}
	return 0;
}
