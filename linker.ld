/* nrf5340 */
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")

STACK_SIZE = 0x2000;

MEMORY
{
    flash (rx) : ORIGIN = 0x08000000, LENGTH = 32K
    ram (rwx) : ORIGIN = 0x20000000, LENGTH = 6K
}

ENTRY(Reset_Handler)

SECTIONS {
  
  .text : 
  {
    /*!< Basics: initial stack pointer, interrupts vector table, text, rodata >!*/
    . = ALIGN(4);
    sfixed = .;
    LONG(ORIGIN(ram) + LENGTH(ram))
    KEEP(*(.isr_vector .isr_vector.*))
    *(.text .text.* .gnu.linkonce.t.*)
    *(.rodata .rodata* .gnu.linkonce.r.*)

    /*!< Initializers for C++ static variables >!*/
    . = ALIGN(4);
    KEEP(*(.init))
    . = ALIGN(4);
    preinit_array_start = .;
    KEEP(*(.preinit_array))
    preinit_array_end = .;
    . = ALIGN(4);
    init_array_start = .;
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
    init_array_end = .;

    /*!< Finalizers for C++ static variables >!*/
    . = ALIGN(4);
    KEEP(*(.fini))
    . = ALIGN(4);
    fini_array_start = .;
    KEEP(*(.fini_array))
    KEEP(*(SORT(.fini_array.*)))
    fini_array_end = .;

    /*!< Run-time C++ static constructors >!*/
    . = ALIGN(4);
    sctors = .;
    KEEP(*crtbegin.o(.ctors))
    KEEP(*crtbegin?.o(.ctors))
    KEEP(*(EXCLUDE_FILE (*crtend?.o *crtend.o) .ctors))
    KEEP(*(SORT(.ctors.*)))
    KEEP(*crtend.o(.ctors))
    ectors = .;

    /*!< Run-time C++ static destructors >!*/
    . = ALIGN(4);
    KEEP(*crtbegin.o(.dtors))
    KEEP(*(EXCLUDE_FILE(*crtend.o) .dtors))
    KEEP(*(SORT(.dtors.*)))
    KEEP(*crtend.o(.dtors))

    . = ALIGN(4);
    efixed = .;
  } > flash

  /*!< Exceptions >!*/
  /*.ARM.extab : {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > flash

  .ARM.exidx : {
    PROVIDE(__exidx_start = .);
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    PROVIDE(__exidx_end = .);
  } > flash*/

  /*!< Relocate code (executed from ram) and data>!*/

  .data :
  {
    . = ALIGN(4);
    sdata = .;
    *(.data .data.*);
    . = ALIGN(4);
    edata = .;
  } > ram AT > flash

  


  .bss (NOLOAD) :
  {
    . = ALIGN(4);
    szero = .;
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(4);
    ezero = .;
  } > ram

  
  .stack (NOLOAD):
  {
    . = ALIGN(4);
    sstack = .;
    estack = STACK_SIZE;
  } > ram

  
  .heap (NOLOAD):
  {
    . = ALIGN(4);
    sheap = .;
    PROVIDE(_heap_start = .);
    end = .;
  } > ram

  .shstrtab : { *(.shstrtab) }
  /DISCARD/ : {*(.ARM.exidx)}
}
