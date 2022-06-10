/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** nm
*/

#ifndef NM_H_
#define NM_H_

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

    typedef struct sym_64
    {
        char *name;
        Elf64_Addr value;
        char type;
        int index;
    } sym_64_t;

    typedef struct sym_32
    {
        char *name;
        Elf32_Addr value;
        char type;
        int index;
    } sym_32_t;

    typedef struct data_32
    {
        Elf32_Ehdr *ehdr;
        Elf32_Shdr *shdr;
        Elf32_Sym *sym;
        char *str_32;
        char *name_symbol;
        int size;
        sym_32_t *sym_32;
    } data_32_t;

    typedef struct data_64
    {
        Elf64_Ehdr *ehdr;
        Elf64_Shdr *shdr;
        Elf64_Sym *sym;
        char *str_64;
        char *name_symbol;
        int size;
        sym_64_t *sym_64;
    } data_64_t;

    typedef struct nm
    {
        data_32_t *data_32;
        data_64_t *data_64;
        char *filename;
        char *binary_name;
        void *map;
        void *end_map;
    } nm_t;


    int file(int ac, char **av, nm_t *nm);
    int symbol(nm_t *nm);
    int find_symbol(nm_t *nm);
    int check_types_nm(nm_t *nm);

    int get_symbol_32(nm_t *nm);
    sym_64_t *get_symbol_64(nm_t *nm);
    char find_type_32(nm_t *nm);
    char find_type_64(nm_t *nm, Elf64_Sym sym);

#endif /* !NM_H_ */
