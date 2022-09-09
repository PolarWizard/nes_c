cmake_minimum_required(VERSION 3.8)

project(nes_c)

add_subdirectory(cpu)
add_subdirectory(ppu)
add_subdirectory(apu)
add_subdirectory(cpubus)

set(nes_source_files main.c)
add_executable(nes ${nes_source_files})

target_link_libraries(nes cpubus)
