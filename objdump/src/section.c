/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** section
*/

#include "../include/objdump.h"

static void print_sections_32(objdump_t *obj, Elf32_Shdr shdr)
{
    int addr = shdr.sh_addr;
    int i = 0;
    char c;

    while (i < shdr.sh_size) {
        if (i % 16 == 0) {
            printf(" %04x ", addr);
            print_hexa_32(obj, shdr, i);
            addr += 16;
        }
        c = (unsigned char)((char *)(obj->map) + shdr.sh_offset)[i];
        print_char(c);
        i += 1;
        if (i % 16 == 0)
            printf("\n");
    }
    if (i >= shdr.sh_size && i % 16 != 0)
        print_space(i);
}

void section_32(objdump_t *obj)
{
    for (int i = 0; i < obj->a32->ehdr->e_shnum; i++) {
        if (check_section(obj->a32->str_32 + obj->a32->shdr[i].sh_name) == 1) {
            printf("Contents of section %s:\n", obj->a32->str_32 +
                obj->a32->shdr[i].sh_name);
            print_sections_32(obj, obj->a32->shdr[i]);
        }
    }
}

static void print_hexa(objdump_t *obj, Elf64_Shdr shdr, int i)
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

static void print_sections_64(objdump_t *obj, Elf64_Shdr shdr)
{
    int addr = shdr.sh_addr;
    int i = 0;
    char c;

    while (i < shdr.sh_size) {
        if (i % 16 == 0) {
            printf(" %04x ", addr);
            print_hexa(obj, shdr, i);
            addr += 16;
        }
        c = (unsigned char)((char *)(obj->map) + shdr.sh_offset)[i];
        print_char(c);
        i += 1;
        if (i % 16 == 0)
            printf("\n");
    }
    if (i >= shdr.sh_size && i % 16 != 0)
        print_space(i);
}

void section_64(objdump_t *obj)
{
    for (int i = 1; i < obj->a64->ehdr->e_shnum; i++) {
        if (check_section(obj->a64->str_64 + obj->a64->shdr[i].sh_name)) {
            printf("Contents of section %s:\n", obj->a64->str_64 +
                obj->a64->shdr[i].sh_name);
            print_sections_64(obj, obj->a64->shdr[i]);
        }
    }
}
