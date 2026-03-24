cmake_minimum_required(VERSION 3.5)

project(IncendieOS LANGUAGES CXX C)
ENABLE_LANGUAGE(ASM-ATT)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(tools ${CMAKE_SOURCE_DIR}/toolchain)
set(CMAKE_C_COMPILER ${tools}/bin/i686-elf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/i686-elf-g++)
set(CMAKE_ASM-ATT_COMPILER ${tools}/bin/i686-elf-as)
set(CMAKE_LINKER ${tools}/bin/i686-elf-ld)

set(GCC_COVERAGE_COMPILE_FLAGS "-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti")
set(LINK_FLAGS "-ffreestanding -O2 -nostdlib")

ADD_EXECUTABLE(kernel src/kernel/boot.s src/kernel/kernel.c)
set_target_properties(kernel PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/src/kernel/link.ld)
