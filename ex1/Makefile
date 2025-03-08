# Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = calc.o operations.o

all: calc

calc: $(OBJ)
	$(CC) $(CFLAGS) -o calc $(OBJ)

calc.o: calc.c operations.h
	$(CC) $(CFLAGS) -c calc.c

operations.o: operations.c operations.h
	$(CC) $(CFLAGS) -c operations.c

clean:
	rm -f $(OBJ) calc

