/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** read_file
*/

#include "../include/nm.h"

static int map_file(nm_t *nm, struct stat sb, int fd)
{
    if ((nm->map = mmap(NULL, sb.st_size,
        PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
        return (-1);
    nm->data_64->ehdr = (Elf64_Ehdr *)nm->map;
    nm->end_map = nm->map + (lseek(fd, 0, SEEK_END));
    if (check_types_nm(nm) == 1 ||
        (void *)nm->data_64->ehdr >= (void *)nm->end_map)
        return (-1);
    if (symbol(nm) == -1)
        return (-1);
    return (0);
}

static int open_file(char *filename, nm_t *nm)
{
    int fd;
    void *buffer;
    struct stat sb;

    nm->filename = filename;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (close(fd));
    if (fstat(fd, &sb) != -1 || S_ISREG(sb.st_mode))
        if (map_file(nm, sb, fd) == -1)
            return (close(fd));
    if (munmap(nm->map, sb.st_size) == -1)
        return (close(fd));
    return (close(fd));
}

int file(int ac, char **av, nm_t *nm)
{
    int nbr_files = 0;

    for (int i = 1; i < ac; i++) {
        if (open_file(av[i], nm) == -1) {
            printf("%s: '%s': No such file\n", av[0], av[i]);
            return (-1);
        }
        nbr_files++;
    }
    if (nbr_files == 0) {
        if (open_file("a.out", nm) == -1) {
            printf("%s: 'a.out': No such file\n", av[0]);
            return (-1);
        }
    }
    return (0);
}
