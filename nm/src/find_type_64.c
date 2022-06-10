/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** find_type_64
*/

#include "../include/nm.h"

static char find_other_64(nm_t *nm, Elf64_Sym sym, char c)
{
    if (nm->data_64->shdr[sym.st_shndx].sh_type == SHT_NOBITS &&
	    nm->data_64->shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        return (c = 'B');
    else if (nm->data_64->shdr[sym.st_shndx].sh_type == SHT_PROGBITS &&
	    nm->data_64->shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
        return (c = 'R');
    else if (nm->data_64->shdr[sym.st_shndx].sh_type == SHT_PROGBITS &&
	    nm->data_64->shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE) ||
        nm->data_64->shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
        return (c = 'D');
    return (0);
}

static char find_other_type_64(nm_t *nm, Elf64_Sym sym, char c)
{
    if (sym.st_shndx == SHN_UNDEF)
        return (c = 'U');
    else if (sym.st_shndx == SHN_ABS)
        return (c = 'A');
    else if (sym.st_shndx == SHN_COMMON)
        return (c = 'C');
    return (0);
}

static char find_type_lower_64(nm_t *nm, Elf64_Sym sym, char c)
{
    if (ELF64_ST_BIND(sym.st_info) == STB_WEAK)
        return (c = (sym.st_shndx == SHN_UNDEF) ? 'w' : 'W');
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK &&
	    ELF64_ST_TYPE(sym.st_info) == STT_OBJECT)
        return (c = (sym.st_shndx == SHN_UNDEF) ? 'v' : 'V');
    else if (nm->data_64->shdr[sym.st_shndx].sh_type ==
        SHT_PROGBITS && nm->data_64->shdr[sym.st_shndx].sh_flags ==
        (SHF_ALLOC | SHF_EXECINSTR) ||
        nm->data_64->shdr[sym.st_shndx].sh_type == SHT_INIT_ARRAY ||
        nm->data_64->shdr[sym.st_shndx].sh_type == SHT_FINI_ARRAY)
        return (c = 'T');
    return (0);
}

char find_type_64(nm_t *nm, Elf64_Sym sym)
{
    char c;

    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        return (c = 'u');
    c = find_type_lower_64(nm, sym, c);
    c = find_other_type_64(nm, sym, c);
    c = find_other_64(nm, sym, c);
    return (c);
}
