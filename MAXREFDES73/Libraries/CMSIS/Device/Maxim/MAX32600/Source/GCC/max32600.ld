/******************************************************************************
 *
 * Linker configuration file, default ARM Cortex M3 produced by Maxim Integrated Inc.
 *
 *****************************************************************************/

MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x00040000 /* start from 0x0, fullsize flash, 256k */
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00008000 /* full-size SRAM, 32k */
}

SECTIONS
{
    .text :
    {
        _text = .;
	KEEP(*(.isr_vector))
        *(.text*)    /* program code */
        *(.rodata*)  /* read-only data: "const" variable */
    } > FLASH

    /* it's used for C++ exception handling      */
    /* we need to keep this to avoid overlapping */
    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    } > FLASH

    _etext = ALIGN(., 4);

    .data : AT(_etext)
    {
        _data = .;
        *(.data*)    /*read-write initialized data: initialized global variable*/
        _edata = ALIGN(., 4);
    } > SRAM

    .bss :
    {
	. = ALIGN(4);
        _bss = .; 
        *(.bss*)     /*read-write zero initialized data: uninitialzed global variable*/
        *(COMMON)
	_ebss = ALIGN(., 4);
    } > SRAM

    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */
     __StackTop = ORIGIN(SRAM) + LENGTH(SRAM);
     __StackLimit = __StackTop - SIZEOF(.stack_dummy);

    /* .stack_dummy section doesn't contains any symbols. It is only
     * used for linker to calculate size of stack sections, and assign
     * values to stack symbols later */
    .stack_dummy (COPY):
    {
        *(.stack*)
    } > SRAM

    .heap (COPY):
    {
	. = ALIGN(4);
	*(.heap*)
	__HeapLimit = ABSOLUTE(__StackLimit);
    } > SRAM

    PROVIDE(__stack = __StackTop);

    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(__StackLimit >= _ebss, "region RAM overflowed with stack")
}
