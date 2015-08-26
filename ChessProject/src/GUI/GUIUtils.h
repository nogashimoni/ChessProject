
#ifndef GUIUTILS_H_
#define GUIUTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
//#include <SDL_image.h>
#include <SDL/SDL_image.h>
#include "GUIDefinitions.h"

SDL_Surface* loadImage(char* imagePath);
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

#endif /* GUIUTILS_H_ */
