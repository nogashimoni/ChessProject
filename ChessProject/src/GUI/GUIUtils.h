
#ifndef GUIUTILS_H_
#define GUIUTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
//#include <SDL_image.h>
#include <SDL/SDL_image.h>
#include "GUIDefinitions.h"

SDL_Surface* createScreen();
SDL_Surface* loadImage(char* imagePath);
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

//Buttons functions
Button* createButton(SDL_Rect relevantArea);
Button** createVerticalButtonsArray(int numOfButtons, int xForButtons,
		int yFirstButton, SDL_Surface* buttonsImages, SDL_Rect* clip, int relevantFirstClipIndex, SDL_Surface* screen);
int isButtonPressed(Button *button, SDL_Event sdlEvent);
int isXYInRelevantArea(Button *button, int x, int y);


// Tree functions
UITreeNode* createNode(void* headData, WidgetType widgetType);
UITreeNode* addChildNode(UITreeNode* parent, void * data, WidgetType widgetType);
//int isEmpty(UITreeNode* list);
UITreeNode* append(UITreeNode* list, void* data, WidgetType widgetType);
void freeWidget(void* widget, WidgetType widgetType) ;
void freeTree(UITreeNode* root);
void freeButton(Button* button);
void freeWindow(Window* window);

#endif /* GUIUTILS_H_ */
