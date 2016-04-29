SRC = hello_world.c
OBJ = hello_world.o
CC = gcc

all: hello_world.c
	$(CC) -o $(OBJ) $(SRC)
	
clean:
	-rm -f *.o $(OBJ)
