/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** display
*/

#include "../include/objdump.h"

void display_flags(objdump_t *obj)
{
    long tab[] = {BFD_NO_FLAGS, HAS_RELOC, EXEC_P, HAS_LINENO, HAS_DEBUG,
        HAS_SYMS, HAS_LOCALS, DYNAMIC, WP_TEXT, D_PAGED};
    char *flags[10] = {"NO_FLAGS", "HAS_RELOC", "EXEC_P", "HAS_LINENO",
        "HAS_DEBUG", "HAS_SYMS", "HAS_LOCALS", "DYNAMIC", "WP_TEXT",
        "D_PAGED"};
    char *separator = "";

    for (int i = 0; i < 10; i++) {
        if (obj->flag->bin_flag & tab[i]) {
            printf ("%s%s", separator, flags[i]);
            separator = ", ";
        }
    }
    printf("\n");
}
