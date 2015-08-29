CFLAGS=-Wall -std=c99 -pedantic-errors -lm -g
OFILES= ErrorHandling.o GUIDefinitions.o GUIUtils.o StartFunctions.o TranslateFunctions.o HandleFunctions.o StopFunctions.o WindowFactory.o GUI.o Chess.o  
SDL_L=`sdl-config --libs` 
SDL_C=`sdl-config --cflags`

all: chessprog #test

clean:
	-rm chessprog $(OFILES)

chessprog: $(OFILES)
	gcc -o $@ $^ $(CFLAGS) $(SDL_L) -lSDL_image
	
ErrorHandling.o: src/services/ErrorHandling.c src/services/ErrorHandling.h
	gcc -c $(CFLAGS) src/services/$*.c $(SDL_C) -lSDL_image
	
GUIUtils.o: src/GUI/GUIUtils.c src/GUI/GUIUtils.h src/GUI/GUIDefinitions.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image

Chess.o: src/main/Chess.c src/main/Chess.h src/GUI/GUI.h src/services/ErrorHandling.h 
	gcc -c $(CFLAGS) src/main/$*.c $(SDL_C) -lSDL_image

GUI.o: src/GUI/GUI.c src/GUI/GUI.h src/main/Chess.h src/GUI/WindowFactory.h src/GUI/GUIDefinitions.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image
	
WindowFactory.o: src/GUI/WindowFactory.c src/GUI/WindowFactory.h src/GUI/GUIUtils.h src/GUI/GUIDefinitions.h src/GUI/StartFunctions.h src/GUI/TranslateFunctions.h src/GUI/HandleFunctions.h src/GUI/StopFunctions.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image
	
GUIDefinitions.o: src/GUI/GUIDefinitions.c src/GUI/GUIDefinitions.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image

StartFunctions.o: src/GUI/StartFunctions.c src/GUI/StartFunctions.h src/GUI/GUIUtils.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image

TranslateFunctions.o: src/GUI/TranslateFunctions.c src/GUI/TranslateFunctions.h src/GUI/GUIUtils.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image
	
HandleFunctions.o: src/GUI/HandleFunctions.c src/GUI/HandleFunctions.h src/GUI/GUIUtils.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image
	
StopFunctions.o: src/GUI/StopFunctions.c src/GUI/StopFunctions.h src/GUI/GUIUtils.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image
	
test:
	bash ./tests/Test.sh