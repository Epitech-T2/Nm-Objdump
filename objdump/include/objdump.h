/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** objdump
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

    #include <elf.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/stat.h>
    #include <sys/mman.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <string.h>
    #include <ctype.h>

    #define BFD_NO_FLAGS    0x00
    #define HAS_RELOC       0x01
    #define EXEC_P          0x02
    #define HAS_LINENO      0x04
    #define HAS_DEBUG       0x08
    #define HAS_SYMS        0x10
    #define HAS_LOCALS      0x20
    #define DYNAMIC         0x40
    #define WP_TEXT         0x80
    #define D_PAGED         0x100

    typedef struct flags {
        char *flag_name;
        int bin_flag;
    } flags_t;

    typedef struct architecture_32 {
        Elf32_Ehdr *ehdr;
        Elf32_Shdr *shdr;
        char *str_32;
    } archi_32_t;

    typedef struct architecture_64 {
        Elf64_Ehdr *ehdr;
        Elf64_Shdr *shdr;
        char *str_64;
    } archi_64_t;

    typedef struct objdump {
        archi_32_t *a32;
        archi_64_t *a64;
        flags_t *flag;
        char *binary_name;
        char *filename;
        void *map;
        void *end_map;
    } objdump_t;

    //architecture.c
    int architecture(objdump_t *obj);

    //check_all.c
    int check_types(objdump_t *obj);
    int check_section(char *section);
    int check_flags(int ac, char **av);

    //display.c
    void display_flags(objdump_t *obj);

    //objdump.c
    void objdump_32(objdump_t *obj);
    void objdump_64(objdump_t *obj);

    //print.c
    void print_space_hexa(int i);
    void print_char(char c);
    void print_space(int i);
    void print_hexa_32(objdump_t *obj, Elf32_Shdr shdr, int i);

    //read_map.c
    int files(int ac, char **av, objdump_t *obj);

    //section.c
    void section_32(objdump_t *obj);
    void section_64(objdump_t *obj);

#endif /* !OBJDUMP_H_ */
