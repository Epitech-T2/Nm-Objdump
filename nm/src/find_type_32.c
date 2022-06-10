/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** find_type_32
*/

#include "../include/nm.h"

static char find_other_32(nm_t *nm, char c)
{
    data_32_t *tmp = nm->data_32;

    if (tmp->shdr[tmp->sym->st_shndx].sh_type == SHT_NOBITS &&
	    tmp->shdr[tmp->sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        return (c = 'B');
    else if (tmp->shdr[tmp->sym->st_shndx].sh_type == SHT_PROGBITS &&
	    tmp->shdr[tmp->sym->st_shndx].sh_flags == SHF_ALLOC)
        return (c = 'R');
    else if (tmp->shdr[tmp->sym->st_shndx].sh_type == SHT_PROGBITS &&
	    tmp->shdr[tmp->sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE) ||
        tmp->shdr[tmp->sym->st_shndx].sh_type == SHT_DYNAMIC)
        return (c = 'D');
    return (0);
}

static char find_other_type_32(nm_t *nm, char c)
{
    data_32_t *tmp = nm->data_32;

    if (tmp->sym->st_shndx == SHN_UNDEF)
        return (c = 'U');
    else if (tmp->sym->st_shndx == SHN_ABS)
        return (c = 'A');
    else if (tmp->sym->st_shndx == SHN_COMMON)
        return (c = 'C');
    return (0);
}

static char find_type_lower_32(nm_t *nm, char c)
{
    data_32_t *tmp = nm->data_32;

    if (ELF32_ST_BIND(tmp->sym->st_info) == STB_WEAK)
        return (c = (tmp->sym->st_shndx == SHN_UNDEF) ? 'w' : 'W');
    else if (ELF32_ST_BIND(tmp->sym->st_info) == STB_WEAK &&
	    ELF32_ST_TYPE(tmp->sym->st_info) == STT_OBJECT)
        return (c = (tmp->sym->st_shndx == SHN_UNDEF) ? 'v' : 'V');
    else if (tmp->shdr[tmp->sym->st_shndx].sh_type ==
        SHT_PROGBITS && tmp->shdr[tmp->sym->st_shndx].sh_flags ==
        (SHF_ALLOC | SHF_EXECINSTR) ||
        tmp->shdr[tmp->sym->st_shndx].sh_type == SHT_INIT_ARRAY ||
        tmp->shdr[tmp->sym->st_shndx].sh_type == SHT_FINI_ARRAY)
        return (c = 'T');
    return (0);
}

char find_type_32(nm_t *nm)
{
    char c;

    if (ELF32_ST_BIND(nm->data_32->sym->st_info) == STB_GNU_UNIQUE)
        return (c = 'u');
    c = find_type_lower_32(nm, c);
    c = find_other_type_32(nm, c);
    c = find_other_32(nm, c);
    return (c);
}
