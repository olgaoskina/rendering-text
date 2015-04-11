OUTPUT_FORMAT("elf64-x86-64")
OUTPUT_ARCH("i386:x86-64")

ENTRY(mod_entry)
virt = 0x100;
phys = 0x100;

PHDRS
{
    text_phdr PT_LOAD PHDRS FILEHDR;
    data_phdr PT_LOAD;
}

SECTIONS
{
    . = virt + SIZEOF_HEADERS;
    
    .text     : AT (phys + (ADDR (.text) - virt)) 
    {
        . = ALIGN(0x8);
        ___CTOR_LIST__ = .;
        LONG((___CTOR_END__ - ___CTOR_LIST__) / 8 - 1) /* total number of constructors */
        KEEP(*(.ctors)) KEEP(*(.init_array))
        LONG(0)
        ___CTOR_END__  = .;

        *(.text*)
    } : text_phdr

    .hash      : AT (phys + (ADDR (.hash) - virt)) { *(.hash) } : text_phdr
    .dynstr    : AT (phys + (ADDR (.dynstr) - virt)) { *(.dynstr) } : text_phdr
    .dynsym    : AT (phys + (ADDR (.dynsym) - virt)) { *(.dynsym) } : text_phdr
    .dynamic   : AT (phys + (ADDR (.dynamic) - virt)) { *(.dynamic) } : text_phdr
    .data      : AT (phys + (ADDR (.data) - virt)) 
    { *(.data .rodata* .bss* COMMON) } : data_phdr
    .rela.text : AT (phys + (ADDR (.rela.text) - virt)) { *(.rela.text) } : data_phdr
    .rela.dyn  : AT (phys + (ADDR (.rela.dyn) - virt)) { *(.rela.dyn) } : data_phdr
	
	/DISCARD/ :
    {
        *(.igot.plt)
        *(.gcc_except_table)
        *(.eh_frame)
        *(.note*)
        *(.interp)
        *(.smp_locks)
        *(.comment)
    }
}
