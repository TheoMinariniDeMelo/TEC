SRC=$(wildcard ./src/*.c);
OBJ=$(SRC:.c=.o)
CC=gcc
CFLAGS=-Wall -g

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)

