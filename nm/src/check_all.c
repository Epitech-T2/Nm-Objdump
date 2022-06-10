/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmnmdump-romanie.de-meyer
** File description:
** check_all
*/

#include "../include/nm.h"

static int check_ident(const char *ident)
{
    if (ident[EI_MAG0] == ELFMAG0 && ident[EI_MAG1] == ELFMAG1
        && ident[EI_MAG2] == ELFMAG2 && ident[EI_MAG3] == ELFMAG3
        && (ident[EI_CLASS] == ELFCLASS64 || ident[EI_CLASS] == ELFCLASS32))
        return (0);
    return (1);
}

int check_types_nm(nm_t *nm)
{
    if (nm->data_64->ehdr->e_type != ET_EXEC &&
        nm->data_64->ehdr->e_type != ET_REL &&
        nm->data_64->ehdr->e_type != ET_DYN ||
        check_ident(nm->data_64->ehdr->e_ident) == 1) {
        printf("%s: %s: File format not recognized\n",
            nm->binary_name, nm->filename);
        return (1);
    }
    return (0);
}
