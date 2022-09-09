#include "../inc/cpubus.h"

u8 cpubus_read(u16 addr) {
	if (addr < 0x2000) { //2KiB Internal RAM, range: 0000-07FF, mirrored until 1FFF
		return BRAM[addr & 0x07FF];
	}
	else if (addr < 0x4000) {
		//ppu registers start here and mirrored till 0x4000
	}
	else if (addr < 0x4018) {
		//APU and IO registers
	}
	else if (addr < 0x4020) {
		//test mode stuff
	}
	else if (addr < 0x6000) {
		//expansion ROM
	}
	else if (addr < 0x8000) {
		//SRAM
	}
	else { //addr < 0xFFFF
		//Cartridge Space
		return 0;
	}
}

void cpubus_write(u8 data, u16 addr) {
	if (addr < 0x2000) { //2KiB Internal RAM, range: 0000-07FF, mirrored until 1FFF
		 BRAM[addr & 0x07FF] = data;
	}
	else if (addr < 0x4000) {
		//ppu registers start here and mirrored till 0x4000
	}
	else if (addr < 0x4018) {
		//APU and IO registers
	}
	else if (addr < 0x4020) {
		//test mode stuff
	}
	else if (addr < 0x6000) {
		//expansion ROM
	}
	else if (addr < 0x8000) {
		//SRAM
	}
	else { //addr < 0xFFFF
		//Cartridge Space
	}
}