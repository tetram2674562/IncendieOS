ENTRY(_start)

SECTIONS
{
    /* Multinooy header start :D */
    . = 0x00100000;

    /* Multiboot header */
    .multiboot :
    {
        *(.multiboot)
    }

    .text :
    {
        *(.text)
    }

    .rodata :
    {
        *(.rodata)
    }

    .data :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
}
