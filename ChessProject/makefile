all: chessprog test

clean:
	-rm Chess.o chessprog

chessprog: Chess.o
	gcc  -o chessprog Chess.o -lm -std=c99 -pedantic-errors -g  `sdl-config --libs`

Chess.o: src/Chess.h src/Chess.c
	gcc -std=c99 -pedantic-errors -c -Wall -g -lm src/Chess.c `sdl-config --cflags`

test:
	bash tests/Test.sh