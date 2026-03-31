#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
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

MultibootHeader multiboot __attribute__((aligned(4))) __attribute__((section(".multiboot"))){
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

}