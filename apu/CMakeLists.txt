set(apu_src
	src/apu.c
)

set(apu_h
	inc/apu.h
)

add_library(apu ${apu_src} ${apu_h})