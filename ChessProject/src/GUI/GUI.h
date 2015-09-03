#ifndef GUI_H_
#define GUI_H_


//includes

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
//#include <SDL_image.h>
#include <SDL/SDL_image.h>
#include "../services/ErrorHandling.h"
#include "GUIDefinitions.h"
#include "GUIUtils.h"
#include "WindowFactory.h"

//funcs
int GUIMain();
//Window initWindow(WindowId id);

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

