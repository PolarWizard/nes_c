set(cpubus_src
	src/cpubus.c
)

set(cpubus_h
	inc/cpubus.h
)

add_library(cpubus ${cpubus_src} ${cpubus_h})

target_link_libraries(cpubus cpu ppu apu)
