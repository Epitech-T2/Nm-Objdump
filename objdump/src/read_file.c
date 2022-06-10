/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
** File description:
** read_file
*/

#include "../include/objdump.h"

static int map_file(objdump_t *obj, struct stat sb, int fd)
{
    if ((obj->map = mmap(NULL, sb.st_size,
        PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
        return (-1);
    obj->a64->ehdr = (Elf64_Ehdr *)obj->map;
    obj->end_map = obj->map + (lseek(fd, 0, SEEK_END));
    if (check_types(obj) == 1 ||
        (void *)obj->a64->ehdr >= (void *)obj->end_map)
        return (-1);
    if (architecture(obj) == -1)
        return (-1);
    return (0);
}

static int open_file(char *filename, objdump_t *obj)
{
    int fd;
    void *buffer;
    struct stat sb;

    obj->filename = filename;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (close(fd));
    if (fstat(fd, &sb) != -1 || S_ISREG(sb.st_mode))
        if (map_file(obj, sb, fd) == -1)
            return (close(fd));
    if (munmap(obj->map, sb.st_size) == -1)
        return (close(fd));
    return (close(fd));
}

int files(int ac, char **av, objdump_t *obj)
{
    int nbr_files = 0;

    for (int i = 1; i < ac; i++) {
        if (strncmp(av[i], "-", 1) != 0) {
            if (open_file(av[i], obj) == -1) {
                printf("%s: '%s': No such file\n", av[0], av[i]);
                return (-1);
            }
            nbr_files++;
        }
    }
    if (nbr_files == 0) {
        if (open_file("a.out", obj) == -1) {
            printf("%s: 'a.out': No such file\n", av[0]);
            return (-1);
        }
    }
    return (0);
}
