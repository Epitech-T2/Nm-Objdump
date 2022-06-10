/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** check_all
*/

#include "../include/objdump.h"

int check_section(char *section)
{
    char tab[4][10] = {".bss", ".shstrtab", ".symtab", ".strtab"};

    for (int i = 0; i < 5; i++)
        if (!section || !strcmp(tab[i], section))
            return (0);
    return (1);
}

static int check_ident(const char *ident)
{
    if (ident[EI_MAG0] == ELFMAG0 && ident[EI_MAG1] == ELFMAG1
        && ident[EI_MAG2] == ELFMAG2 && ident[EI_MAG3] == ELFMAG3
        && (ident[EI_CLASS] == ELFCLASS64 || ident[EI_CLASS] == ELFCLASS32))
        return (0);
    return (1);
}

int check_types(objdump_t *obj)
{
    if (obj->a64->ehdr->e_type != ET_EXEC &&
        obj->a64->ehdr->e_type != ET_REL &&
        obj->a64->ehdr->e_type != ET_DYN ||
        check_ident(obj->a64->ehdr->e_ident) == 1) {
        printf("%s: %s: File format not recognized\n",
            obj->binary_name, obj->filename);
        return (1);
    }
    return (0);
}

int check_flags(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
        if (strcmp(av[i], "-H") == 0 || strcmp(av[i], "--help") == 0)
            printf("Usage: objdump <option(s)> <file(s)> (a.out by default)");
    return (0);
}
