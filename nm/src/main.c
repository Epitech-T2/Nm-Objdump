/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** main
*/

#include "../include/nm.h"

static data_32_t *init_32(void)
{
    data_32_t *data_32 = malloc(sizeof(data_32_t));

    data_32->sym_32 = malloc(sizeof(sym_32_t));

    data_32->ehdr = NULL;
    data_32->shdr = NULL;
    data_32->sym = NULL;
    data_32->str_32 = '\0';

    data_32->sym_32->index = 0;
    data_32->sym_32->name = '\0';
    return (data_32);
}

static data_64_t *init_64(void)
{
    data_64_t *data_64 = malloc(sizeof(data_64_t));

    data_64->sym_64 = malloc(sizeof(sym_64_t));

    data_64->ehdr = NULL;
    data_64->shdr = NULL;
    data_64->sym = NULL;
    data_64->str_64 = '\0';

    data_64->sym_64->index = 0;
    data_64->sym_64->name = '\0';
    return (data_64);
}

static nm_t *init_struct(void)
{
    nm_t *nm = malloc(sizeof(nm_t));

    nm->data_32 = init_32();
    nm->data_64 = init_64();

    nm->data_64->str_64 = '\0';
    nm->data_64->sym = NULL;
    nm->data_64->ehdr = NULL;
    nm->data_64->shdr = NULL;

    nm->binary_name = '\0';
    nm->filename = '\0';
    return (nm);
}

int main(int ac, char **av)
{
    nm_t *nm = init_struct();

    nm->binary_name = av[0];
    if (file(ac, av, nm) == -1)
        return (84);
    return (0);
}
