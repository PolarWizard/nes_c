#ifndef CPUBUS_H
#define CPUBUS_H

#include <stdint.h>

#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define i8  int8_t
#define i16 int16_t
#define i32 int32_t

static u8 BRAM[0x2000];

u8 cpubus_read(u16 addr);

void cpubus_write(u8 data, u16 addr);

#endif CPUBUS_H