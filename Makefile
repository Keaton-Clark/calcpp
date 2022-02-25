SRC = $(wildcard ./src/*.c)
INC = $(wildcard ./src/*.h)
OBJ = $(SRC:.c=.o)
CFLAGS =-ggdb -g3 
CC = gcc
TGT = $(shell basename `pwd`)

$(TGT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses
.PHONY: clean

clean:
	rm -f $(wildcard ./src/*.o) $(TGT) 
