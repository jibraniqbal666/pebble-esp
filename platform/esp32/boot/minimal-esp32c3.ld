/* minimal-esp32c3.ld */

ENTRY(call_start_cpu0)

MEMORY
{
  iram (rx)  : ORIGIN = 0x42000000, LENGTH = 0x40000   /* IRAM: 256KB */
  dram (rw)  : ORIGIN = 0x3FC80000, LENGTH = 0x20000   /* DRAM: 128KB */
}

SECTIONS
{
  .text : ALIGN(4)
  {
    *(.entry.text)
    *(.init)
    *(.text)
    *(.text.*)
    *(.rodata)
    *(.rodata.*)
    *(.literal*)
    *(.init.literal)
    *(.fini.literal)
    *(.fini)
  } > iram

  .data : ALIGN(4)
  {
    *(.data)
    *(.data.*)
    *(.sdata)
    *(.sdata.*)
  } > dram AT > iram

  .bss (NOLOAD) : ALIGN(4)
  {
    *(.bss)
    *(.bss.*)
    *(.sbss)
    *(.sbss.*)
    *(COMMON)
  } > dram

  . = ALIGN(4);
  _end = .;
}