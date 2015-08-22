#ifndef GUI_H_
#define GUI_H_

#define SCREEN_WIDTH = 640;
#define SCREEN_HEIGHT = 480;
#define SCREEN_BPP = 32;


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

typedef struct control_t control_t;

struct control_t {

	/* data members */
	//The attributes of the button
	SDL_Rect box;
	//The part of the button sprite sheet that will be shown
	SDL_Rect *clip;//*sprite_map;
//	SDL_Surface *image;
//	int current_sprite;
//	int sattelite_data;

	/* methods */
	char (*handle_events)(control_t *control, int x_offset, int y_offset,
			char board[BOARD_SIZE][BOARD_SIZE]);
	void (*show)(control_t *control, SDL_Surface *parent,
			char board[BOARD_SIZE][BOARD_SIZE]);
};

//funcs
int initGUI();
int createWelcomePage();
int loadFiles();
int closeImage(SDL_Surface* image);
int quitSDL();
//int applyImageOnScreen(SDL_Surface* screen, SDL_Surface* image);
SDL_Surface* loadImage(char* imagePath);
int GUIMain();
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void setClips();
void handleEvents(control_t *control, int x_offset, int y_offset, char board[BOARD_SIZE][BOARD_SIZE]);
void setClip();

#endif /* GUI_H_ */

