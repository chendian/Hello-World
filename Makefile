SRC = hello.c
OBJ = hello.o
CC = gcc

all: $(OBJ)
	$(CC) -o $(OBJ) $(SRC)
	
clean:
	-rm -f *.o $(OBJ)
