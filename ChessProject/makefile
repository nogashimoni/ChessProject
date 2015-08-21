CFLAGS=-Wall -std=c99 -pedantic-errors -lm -g
OFILES= Chess.o GUI.o ErrorHandling.o
SDL_L=`sdl-config --libs`
SDL_C=`sdl-config --cflags`

all: chessprog test

clean:
	-rm chessprog $(OFILES)

chessprog: $(OFILES)
	gcc -o $@ $^ $(CFLAGS) $(SDL_L)

Chess.o: src/main/Chess.c src/main/Chess.h src/GUI/GUI.h src/services/ErrorHandling.h
	gcc -c $(CFLAGS) src/main/$*.c $(SDL_C) -lSDL_image

GUI.o: src/GUI/GUI.c src/GUI/GUI.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image

ErrorHandling.o: src/services/ErrorHandling.c src/services/ErrorHandling.h
	gcc -c $(CFLAGS) src/services/$*.c $(SDL_C) -lSDL_image

test:
	bash ./tests/Test.sh