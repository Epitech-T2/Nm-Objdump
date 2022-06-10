/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** architecture
*/

#include "../include/objdump.h"

static int architecture_32(objdump_t *obj)
{
    obj->a32->shdr = obj->map + obj->a32->ehdr->e_shoff;
    obj->a32->str_32 = (char *)obj->map +
        obj->a32->shdr[obj->a32->ehdr->e_shstrndx].sh_offset;
    if (obj->a32->shdr == NULL || obj->a32->str_32 == NULL)
        return (-1);
    if ((void *)obj->a32->shdr >= obj->end_map ||
        (void *)obj->a32->str_32 >= obj->end_map)
        return (-1);
    objdump_32(obj);
    section_32(obj);
    return (0);
}

static int architecture_64(objdump_t *obj)
{
    obj->a64->shdr = obj->map + obj->a64->ehdr->e_shoff;
    obj->a64->str_64 = (char *)obj->map +
        obj->a64->shdr[obj->a64->ehdr->e_shstrndx].sh_offset;
    if (obj->a64->shdr == NULL || obj->a64->str_64 == NULL)
        return (-1);
    if ((void *)obj->a64->shdr >= obj->end_map ||
        (void *)obj->a64->str_64 >= obj->end_map)
        return (-1);
    objdump_64(obj);
    section_64(obj);
    return (0);
}

int architecture(objdump_t *obj)
{
    if (obj->a64->ehdr->e_ident[EI_CLASS] == ELFCLASS32) {
        if (architecture_32(obj) == -1)
            return (-1);
    } else if (obj->a64->ehdr->e_ident[EI_CLASS] == ELFCLASS64) {
        if (architecture_64(obj) == -1)
            return (-1);
    }
    return (0);
}
