##
## EPITECH PROJECT, 2022
## B-PSU-400-STG-4-1-nmobjdump-romanie.de-meyer
## File description:
## Makefile
##

SRCOBJ =	objdump/src/architecture.c \
			objdump/src/check_all.c \
			objdump/src/display.c \
			objdump/src/main.c \
			objdump/src/objdump.c \
			objdump/src/print.c \
			objdump/src/read_file.c \
			objdump/src/section.c

SRCNM =		nm/src/check_all.c \
			nm/src/main.c \
			nm/src/read_file.c \
			nm/src/symbol.c \
			nm/src/find_type_32.c \
			nm/src/find_type_64.c \
			nm/src/sort_symbol.c

OBJOBJ = 	$(SRCOBJ:.c=.o)

OBJNM = 	$(SRCNM:.c=.o)

NAMEOBJ = 	my_objdump

NAMENM = 	my_nm

CC = gcc

CFLAGS = -g

all: 	nm objdump

objdump: 	$(OBJOBJ)
		$(CC) $(CFLAGS) -o $(NAMEOBJ) $(OBJOBJ)

nm:		$(OBJNM)
		$(CC) $(CFLAGS) -o $(NAMENM) $(OBJNM)

clean:
		rm -f $(OBJOBJ) $(OBJNM)

fclean: clean
		rm -f $(NAMEOBJ) $(NAMENM)

re: fclean all

.PHONY: all objdump nm clean fclean re