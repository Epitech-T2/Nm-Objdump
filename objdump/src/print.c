/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** print
*/

#include "../include/objdump.h"

void print_space_hexa(int i)
{
    while (i % 16) {
        printf("  ");
        i += 1;
        if (!(i % 4))
            printf(" ");
        if (!(i % 16))
            printf(" ");
    }
}

void print_char(char c)
{
    if (isprint(c))
        printf("%c", c);
    else
        printf(".");
}

void print_space(int i)
{
    while (i % 16) {
        printf(" ");
        i += 1;
    }
    printf("\n");
}

void print_hexa_32(objdump_t *obj, Elf32_Shdr shdr, int i)
{
    while (i < shdr.sh_size) {
        printf("%02x", (unsigned char)((char *)(obj->map) +
            shdr.sh_offset)[i]);
        i += 1;
        if (i % 16 == 0) {
            printf("  ");
            return;
        }
        if (i % 4 == 0)
            printf(" ");
    }
    if (i >= shdr.sh_size && i % 16 != 0)
        print_space_hexa(i);
}
