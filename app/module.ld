
virt = 0x1000;
phys = 0x1000;

PHDRS
{
    text_phdr PT_LOAD PHDRS FILEHDR;
    data_phdr PT_LOAD;
}

SECTIONS
{
    . = 0x1000;
    .text  :  { *(.text*)} : text_phdr

    .hash      :  { *(.hash) } : text_phdr
    .dynstr    :  { *(.dynstr) } : text_phdr
    .dynsym    :  { *(.dynsym) } : text_phdr
    .dynamic   :  { *(.dynamic) } : text_phdr
    .data      :  { *(.data .rodata* .bss* COMMON) } : data_phdr
    .rela.text :  { *(.rela.text) } : data_phdr
    .rela.dyn  :  { *(.rela.dyn) } : data_phdr
}
