/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** objdump
*/

#include "../include/objdump.h"

static int flag_32(objdump_t *obj)
{
    if (obj->a32->ehdr->e_type == ET_EXEC)
        obj->flag->bin_flag += EXEC_P + HAS_SYMS + D_PAGED;
    else if (obj->a32->ehdr->e_type == ET_DYN)
        obj->flag->bin_flag += DYNAMIC + HAS_SYMS + D_PAGED;
    else if (obj->a32->ehdr->e_type == ET_REL)
        obj->flag->bin_flag += HAS_RELOC + HAS_SYMS;
}

static int flag_64(objdump_t *obj)
{
    if (obj->a64->ehdr->e_type == ET_EXEC)
        obj->flag->bin_flag += EXEC_P + HAS_SYMS + D_PAGED;
    else if (obj->a64->ehdr->e_type == ET_DYN)
        obj->flag->bin_flag += DYNAMIC + HAS_SYMS + D_PAGED;
    else if (obj->a64->ehdr->e_type == ET_REL)
        obj->flag->bin_flag += HAS_RELOC + HAS_SYMS;
}

void objdump_32(objdump_t *obj)
{
    obj->flag->bin_flag = BFD_NO_FLAGS;
    flag_32(obj);
    printf("\n%s:\t file format elf32-i386\n", obj->filename);
    printf("architecture: i386:x86-32, flags 0x%08x:\n", obj->flag->bin_flag);
    display_flags(obj);
    printf("start address 0x%08x\n\n", obj->a32->ehdr->e_entry);
}

void objdump_64(objdump_t *obj)
{
    obj->flag->bin_flag = BFD_NO_FLAGS;
    flag_64(obj);
    printf("\n%s:\t file format elf64-x86-64\n", obj->filename);
    printf("architecture: i386:x86-64, flags 0x%08x:\n", obj->flag->bin_flag);
    display_flags(obj);
    printf("start address 0x%016lx\n\n", obj->a64->ehdr->e_entry);
}
