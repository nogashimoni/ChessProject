CFLAGS=-Wall -std=c99 -pedantic-errors -lm -g
OFILES= ErrorHandling.o ChessDefinitions.o  XMLFileHandler.o ChessLogic.o Minmax.o GUIDefinitions.o GUIUtils.o StartFunctions.o TranslateFunctions.o HandleFunctions.o StopFunctions.o WindowFactory.o GUI.o GameFlow.o 
SDL_L=`sdl-config --libs` 
SDL_C=`sdl-config --cflags`

all: chessprog #test

clean:
	-rm chessprog $(OFILES)

chessprog: $(OFILES)
	gcc -o $@ $^ $(CFLAGS) $(SDL_L) -lSDL_image
	
ErrorHandling.o: src/services/ErrorHandling.c src/services/ErrorHandling.h
	gcc -c $(CFLAGS) src/services/$*.c $(SDL_C) -lSDL_image

XMLFileHandler.o: src/services/XMLFileHandler.c src/services/XMLFileHandler.c src/main/ChessDefinitions.h
	gcc -c $(CFLAGS) src/services/$*.c $(SDL_C) -lSDL_image
	
GUIDefinitions.o: src/GUI/GUIDefinitions.c src/GUI/GUIDefinitions.h src/main/ChessDefinitions.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image

GUIUtils.o: src/GUI/GUIUtils.c src/GUI/GUIUtils.h src/GUI/GUIDefinitions.h src/services/ErrorHandling.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image

StartFunctions.o: src/GUI/StartFunctions.c src/GUI/StartFunctions.h src/GUI/GUIUtils.h src/services/ErrorHandling.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image

TranslateFunctions.o: src/GUI/TranslateFunctions.c src/GUI/TranslateFunctions.h src/GUI/GUIUtils.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image
	
HandleFunctions.o: src/GUI/HandleFunctions.c src/GUI/HandleFunctions.h src/GUI/GUIUtils.h src/main/ChessLogic.h src/main/Minmax.h src/services/ErrorHandling.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image
	
StopFunctions.o: src/GUI/StopFunctions.c src/GUI/StopFunctions.h src/GUI/GUIUtils.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image
	
ChessDefinitions.o: src/main/ChessDefinitions.c src/main/ChessDefinitions.h
	gcc -c $(CFLAGS) src/main/$*.c $(SDL_C) -lSDL_image

ChessLogic.o: src/main/ChessLogic.c src/main/ChessLogic.h src/main/ChessDefinitions.h src/services/XMLFileHandler.h 
	gcc -c $(CFLAGS) src/main/$*.c $(SDL_C) -lSDL_image

Minmax.o: src/main/Minmax.c src/main/Minmax.h src/main/ChessDefinitions.h src/main/ChessLogic.h src/services/ErrorHandling.h
	gcc -c $(CFLAGS) src/main/$*.c $(SDL_C) -lSDL_image

GameFlow.o: src/main/GameFlow.c src/main/GameFlow.h src/main/ChessDefinitions.h src/main/ChessLogic.h src/main/Minmax.h src/GUI/GUI.h src/services/ErrorHandling.h
	gcc -c $(CFLAGS) src/main/$*.c $(SDL_C) -lSDL_image

GUI.o: src/GUI/GUI.c src/GUI/GUI.h src/GUI/WindowFactory.h src/GUI/GUIDefinitions.h src/main/ChessDefinitions.h #src/main/ChessLogic.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image
	
WindowFactory.o: src/GUI/WindowFactory.c src/GUI/WindowFactory.h src/GUI/GUIUtils.h src/GUI/GUIDefinitions.h src/GUI/StartFunctions.h src/GUI/TranslateFunctions.h src/GUI/HandleFunctions.h src/GUI/StopFunctions.h
	gcc -c $(CFLAGS) src/GUI/$*.c $(SDL_C) -lSDL_image
	
test:
	bash ./tests/Test.sh
