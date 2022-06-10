/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** sort_symbol
*/

#include "../include/nm.h"

int size_struct_32(sym_32_t *tab)
{
    int i = 0;

    for (; tab[i].index != -1; i++);
    return (i);
}

int size_struct_64(sym_64_t *tab)
{
    int i = 0;

    for (; tab[i].index != -1; i++);
    return (i);
}

int sort_symbol_32(nm_t *nm)
{
    int end = size_struct_32(nm->data_32->sym_32);
}

int sort_symbol_64(nm_t *nm)
{
    int end = size_struct_64(nm->data_64->sym_64);

    for (int i = 0; i < end; i++) {
        //
    }
}

int get_symbol_32(nm_t *nm)
{
    nm->data_32->sym_32 = malloc(sizeof(sym_32_t) *
        nm->data_32->size);
    int idx = 0;

    if (nm->data_32->sym_32 == NULL)
        return (-1);
    for (int i = 0; i < nm->data_32->size; i++) {
        if ((nm->data_32->name_symbol + nm->data_32->sym[i].st_name)[0] != '\0') {
            nm->data_32->sym_32[idx].index = idx;
            nm->data_32->sym_32[idx].name = nm->data_32->name_symbol +
                nm->data_32->sym[i].st_name;
            nm->data_32->sym_32[idx].value = nm->data_32->sym[i].st_value;
            nm->data_32->sym_32[idx].type = find_type_32(nm);
            idx += 1;
        }
    }
    nm->data_32->sym_32[idx].index = -1;
    return (0);
}

sym_64_t *get_symbol_64(nm_t *nm)
{
    sym_64_t *arr = malloc(sizeof(sym_64_t) * nm->data_64->size);
    int idx = 0;

    if (nm->data_64->sym == NULL || nm->data_64->name_symbol == NULL || nm->data_64->size == 0)
        return (NULL);
    if (arr == NULL)
        return (NULL);
    for (int i = 0; i < nm->data_64->size; i++) {
        if ((nm->data_64->name_symbol + nm->data_64->sym[i].st_name)[0] != '\0') {
            arr[idx].index = idx;
            arr[idx].name = nm->data_64->name_symbol +
                nm->data_64->sym[i].st_name;
            arr[idx].value = nm->data_64->sym[i].st_value;
            arr[idx].type = find_type_64(nm, nm->data_64->sym[i]);
            idx += 1;
            printf("%c\n", arr[idx].type);
        }
    }
    arr[idx].index = -1;
    return (arr);
}
