/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** symbol
*/

#include "../include/nm.h"

static void	display_symbol_array(sym_64_t *tab)
{
  unsigned int	idx;

  idx = 0;
  while (tab[idx].index != -1)
    {
        printf("ici1\n");
        if (tab[idx].type == 'w' || tab[idx].type == 'U')
	        printf("                 %c %s\n", tab[idx].type, tab[idx].name);
        else if (tab[idx].value != 0
	        || tab[idx].type == 't'
	        || tab[idx].type == 'n'
	        || tab[idx].type == 'T')
	        printf("%016x %c %s\n", tab[idx].value, tab[idx].type, tab[idx].name);
        idx += 1;
    }
}

static int find_symbol_32(nm_t *nm)
{
    for (int i = 0; i < nm->data_32->ehdr->e_shnum; i++) {
        if (strcmp(nm->data_32->str_32 + nm->data_32->shdr[i].sh_name, ".symtab") == 0) {
            nm->data_32->sym = (Elf32_Sym *)(nm->map +
                (nm->data_32->shdr + i)->sh_offset);
            nm->data_32->size = (nm->data_32->shdr + i)->sh_size /
                sizeof(Elf32_Sym);
        } else if ((strcmp(nm->data_32->str_32 +nm->data_32->shdr[i].sh_name, ".strtab")
            == 0) && nm->data_64->shdr[i].sh_flags == SHF_ALLOC) {
            nm->data_32->name_symbol = nm->map +
                ((nm->data_32->shdr + i)->sh_offset);
        }
    }
    if (get_symbol_32(nm) == -1)
        return (-1);
    return (0);
}

static int find_symbol_64(nm_t *nm)
{
    sym_64_t *tab;

    for (int i = 0; i < nm->data_64->ehdr->e_shnum; i++) {
        if (strcmp(nm->data_64->str_64 + nm->data_64->shdr[i].sh_name, ".symtab") == 0) {
            nm->data_64->sym = (Elf64_Sym *)(nm->map +
                (nm->data_64->shdr + i)->sh_offset);
            nm->data_64->size = (nm->data_64->shdr + i)->sh_size /
                sizeof(Elf64_Sym);
        }
        if ((strcmp(nm->data_64->str_64 + nm->data_64->shdr[i].sh_name, ".strtab") == 0)) {
            nm->data_64->name_symbol = nm->map +
                ((nm->data_64->shdr + i)->sh_offset);
        }
    }
    if (tab = get_symbol_64(nm) == NULL)
        return (-1);
    printf("ici\n");
    display_symbol_array(tab);
    return (0);
}

static int symbol_32(nm_t *nm)
{
    nm->data_32->shdr = nm->map + nm->data_32->ehdr->e_shoff;
    nm->data_32->str_32 = (char *)nm->map +
        nm->data_32->shdr[nm->data_32->ehdr->e_shstrndx].sh_offset;
    if (nm->data_32->shdr == NULL || nm->data_32->str_32 == NULL)
        return (-1);
    if ((void *)nm->data_32->shdr >= nm->end_map ||
        (void *)nm->data_32->str_32 >= nm->end_map)
        return (-1);
    if (find_symbol_32(nm) == -1)
        return (-1);
    return (0);
}

static int symbol_64(nm_t *nm)
{
    nm->data_64->shdr = nm->map + nm->data_64->ehdr->e_shoff;
    nm->data_64->str_64 = (char *)nm->map +
        nm->data_64->shdr[nm->data_64->ehdr->e_shstrndx].sh_offset;
    if (nm->data_64->shdr == NULL || nm->data_64->str_64 == NULL)
        return (-1);
    if ((void *)nm->data_64->shdr >= nm->end_map ||
        (void *)nm->data_64->str_64  >= nm->end_map)
        return (-1);
    if (find_symbol_64(nm) == -1)
        return (-1);
    return (0);
}

int symbol(nm_t *nm)
{
    if (nm->data_64->ehdr->e_ident[EI_CLASS] == ELFCLASS32) {
        if (symbol_32(nm) == -1)
            return (-1);
    } else if (nm->data_64->ehdr->e_ident[EI_CLASS] == ELFCLASS64) {
        if (symbol_64(nm) == -1)
            return (-1);
    }
    return (0);
}
