#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "kernel/drivers/vga/VgaTextMode.h"
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "You need a ix86 cross compiler to compile this kernel"
#endif

/* Multiboot header constant :D */
const uint32_t MB_HEADER_MAGIC = 0x1BADB002;
const uint32_t MB_FLAG_ALIGN = 1 << 0;
const uint32_t MB_FLAG_MEMINFO = 1 << 1;
const uint32_t FLAGS = MB_FLAG_ALIGN | MB_FLAG_MEMINFO;


typedef struct __attribute__((packed)) {
	uint32_t magic;
	uint32_t flags;
	uint32_t checksum;
	uint32_t padding;
} MultibootHeader;

MultibootHeader multiboot __attribute__((aligned(4))) __attribute__((section(".multiboot"))) {
	.magic = MB_HEADER_MAGIC,
	.flags = FLAGS,
	.checksum = (uint32_t) -(MB_HEADER_MAGIC + FLAGS),
	.padding = 0,
};

uint8_t stack_bytes[16 * 1024] __attribute__((aligned(16))) __attribute__((section(".bss")));

void kernel_main();

extern "C" {

void _start() {
	asm volatile (
		"mov %[stack_top], %%esp\n"
		"mov %%esp, %%ebp\n"
		"call *%[kmain]\n"
		"cli\n"
		"hlt\n"
		"1: jmp 1b\n"
		:
		: [stack_top] "r" ((uint32_t) stack_bytes + sizeof(stack_bytes)),
		[kmain] "r" (kernel_main)
	);
}
}
void kernel_main() {
	kernel::driver::vga::VgaTextMode textMode;
	textMode.writeString("Test text >:D from VGA TEXT DRIVER !!!", 38);
	textMode.setBackground(kernel::driver::vga::VgaTextMode::VGA_COLOR_BLUE);
	textMode.writeString("\nTest text >:D from VGA TEXT DRIVER !!!", 39);
}