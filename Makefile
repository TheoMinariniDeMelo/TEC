SRC=./src
OBJ=./obj
CC=gcc
CCFLAGS=-Wall -g

all: %.o
	$(CC) $(CCFLAGS) $(OBJ)/@< 

