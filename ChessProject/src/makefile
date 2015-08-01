all: chessprog 

clean:
	-rm Chess.o chessprog

chessprog: Chess.o
	gcc  -o chessprog Chess.o -lm -std=c99 -pedantic-errors -g  `sdl-config --libs`

Chess.o: Chess.h Chess.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm Chess.c `sdl-config --cflags`

