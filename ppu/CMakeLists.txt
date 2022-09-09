set(ppu_src
	src/ppu.c
)

set(ppu_h
	inc/ppu.h
)

add_library(ppu ${ppu_src} ${ppu_h})
