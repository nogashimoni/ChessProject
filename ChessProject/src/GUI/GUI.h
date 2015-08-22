#ifndef GUI_H_
#define GUI_H_

#define SCREEN_WIDTH = 640;
#define SCREEN_HEIGHT = 480;
#define SCREEN_BPP = 32;
#define WINDOWS_COUNT 2
#define POLLING_DELAY 10


//macros for files
#define BACKGROUND "images/background.png"

//includes
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
//#include <SDL_image.h>
#include <SDL/SDL_image.h>
#include "../main/Chess.h"
#include "../services/ErrorHandling.h"
#include "WindowFactory.h"

typedef enum {
	MAIN_MENU,
	SETUP,
	QUIT
} WindowId;

typedef enum {
	PRESS_FIRST,
	PRESS_SECOND,
	PRESS_THIRD,
} LogicalEvent;


typedef struct Button Button;

struct Button {

	/* data members */
	//The attributes of the button
	SDL_Rect box; //The part of the button sprite sheet that will be shown
	SDL_Rect *clip;//*sprite_map;

	/* methods */
	char (*handle_events)(Button *control, int x_offset, int y_offset,
			char board[BOARD_SIZE][BOARD_SIZE]);
	void (*show)(Button *control, SDL_Surface *parent,
			char board[BOARD_SIZE][BOARD_SIZE]);
};

typedef struct Window Window;
typedef struct Node Node;

struct Node {
	Node** next;
};

struct Window {
	/* data members */
//	Game* game;
	Node* UITreeHead; //ui tree
	WindowId windowId;
	/* methods */
	LogicalEvent (*translateEvent)(Window* window, SDL_Event* event);
	int (*handleEvent)(Window* window, LogicalEvent event);
	void (*start) (Window* window, void* initData);
	void* (*stop) (Window* window);
};

//funcs
int GUIMain();
Window initWindow(WindowId id);

//int initGUI();
//int createWelcomePage();
//int loadFiles();
//int closeImage(SDL_Surface* image);
//int quitSDL();
////int applyImageOnScreen(SDL_Surface* screen, SDL_Surface* image);
//SDL_Surface* loadImage(char* imagePath);
//int GUIMain();
//void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
//void setClips();
//void handleEvents(Button *control, int x_offset, int y_offset, char board[BOARD_SIZE][BOARD_SIZE]);
//void setClip();

#endif /* GUI_H_ */

