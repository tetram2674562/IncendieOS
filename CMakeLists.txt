cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(tools ${CMAKE_SOURCE_DIR}/toolchain)

set(CMAKE_C_COMPILER ${tools}/bin/i686-elf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/i686-elf-g++)
set(CMAKE_ASM_COMPILER ${tools}/bin/i686-elf-as)
set(CMAKE_AR ${tools}/bin/i686-elf-ar)
set(CMAKE_RANLIB ${tools}/bin/i686-elf-ranlib)

set(COMPILE_FLAGS "-ffreestanding -O2 -Wall -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS} -fno-exceptions -fno-rtti")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ffreestanding -O2 -nostdlib -T${CMAKE_SOURCE_DIR}/kernel.ld")

project(ArcticFoxOS LANGUAGES CXX C ASM)

file(GLOB_RECURSE SOURCES
		LIST_DIRECTORIES true
		${CMAKE_SOURCE_DIR}/src/**)

add_executable(kernel.elf ${SOURCES})
target_include_directories(kernel.elf PRIVATE include)
target_link_directories(kernel.elf PRIVATE include)


add_custom_command(TARGET kernel.elf POST_BUILD
	COMMAND ${tools}/bin/i686-elf-objcopy -O binary kernel.elf kernel.bin
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Creating elf executable !")


add_custom_command(TARGET kernel.elf POST_BUILD
		COMMAND cp -f kernel.elf ${CMAKE_SOURCE_DIR}/iso/boot/kernel
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Copying kernel file...")

add_custom_command(TARGET kernel.elf POST_BUILD
		COMMAND grub-mkrescue -o ArcticFoxOS.iso iso
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMENT "Creating bootable iso with grub")
