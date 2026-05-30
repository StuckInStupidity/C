CC=gcc
SRC = villager.c demon.c weapons.c print.c main.c
CFLAGS= -Wall -Wextra -Werror 
LDFLAGS= -fsanitize=address -g -lm

# Computes the basic main for tests
main: ${SRC} 
	gcc $(CFLAGS) $^ -o main -lm

#Check for memory errors/leaks and to use gdb
debug: ${SRC} 
	gcc $(CFLAGS) $^ -o debug $(LDFLAGS)

clean:
	$(RM) main debug 

