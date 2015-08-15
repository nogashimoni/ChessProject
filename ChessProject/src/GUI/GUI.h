#ifndef GUI_H_
#define GUI_H_

#define SCREEN_WIDTH = 640;
#define SCREEN_HEIGHT = 480;
#define SCREEN_BPP = 32;
#define IMG_W 240
#define IMG_H 296

//macros for files
#define WELCOME_WINDOW "images/welcome_window.bmp"


//includes
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>

//funcs
SDL_Surface* initGUI();
int createWelcomePage(SDL_Surface* screen);
int closeImage(SDL_Surface* image);
int quitSDL();
int applyImageOnScreen(SDL_Surface* screen, SDL_Surface* image);
SDL_Surface* openImage(char* imagePath);
int GUIMain();

#endif /* GUI_H_ */


