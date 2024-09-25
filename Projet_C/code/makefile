CC = gcc

CF = -Wall -Wextra #flags

prog: main.o engine.o matrix.o list.o list_opacity.o
	$(CC) $(CF) -o prog $^

main.o: main.c engine.h
	gcc -o main.o -c main.c $(CF)
engine.o:  engine.c engine.h matrix.h list_opacity.h
	gcc -o engine.o -c engine.c $(CF)
matrix.o: matrix.c matrix.h list.h
	gcc -o matrix.o -c matrix.c $(CF)
list.o: list.c list.h
	gcc -o list.o -c list.c $(CF)
list_opacity.o: list_opacity.c list_opacity.h
	gcc -o list_opacity.o -c list_opacity.c $(CF)

nettoyer:
	rm -rf *.o