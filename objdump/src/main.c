/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** main
*/

#include "../include/objdump.h"

static objdump_t *init_struct(void)
{
    objdump_t *obj = malloc(sizeof(objdump_t));

    obj->flag = malloc(sizeof(flags_t));
    obj->a32 = malloc(sizeof(archi_32_t));
    obj->a64 = malloc(sizeof(archi_64_t));
    obj->a32->str_32 = '\0';
    obj->a64->str_64 = '\0';
    obj->binary_name = '\0';
    obj->filename = '\0';
    obj->flag->flag_name = '\0';
    return (obj);
}

int main(int ac, char **av)
{
    objdump_t *obj = init_struct();

    obj->binary_name = av[0];
    check_flags(ac, av);
    if (files(ac, av, obj) == -1)
        return (84);
    return (0);
}
