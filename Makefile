CC=gcc -Wall -Wextra -std=c11 -O2
VAL=valgrind --error-exitcode=15 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all 

all: main

main: main.c parser.o operations.o lists.o tree.o 
	$(CC) parser.o operations.o lists.o tree.o main.c -o main
operations.o: operations.c operations.h lists.h tree.h
	$(CC) -c operations.c
parser.o: parser.c parser.h operations.h
	$(CC) -c parser.c
lists.o: lists.c lists.h
	$(CC) -c lists.c
tree.o: tree.c tree.h
	$(CC) -c tree.c
clean:
	rm -f *.o
valgrind:
	$(VAL) ./main 
