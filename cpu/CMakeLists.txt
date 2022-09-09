set(cpu_src
	src/cpu.c
)

set(cpu_h
	inc/cpu.h
)

add_library(cpu ${cpu_src} ${cpu_h})
