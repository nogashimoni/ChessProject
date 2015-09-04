
#ifndef GUIUTILS_H_
#define GUIUTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
//#include <SDL_image.h>
#include <SDL/SDL_image.h>
#include "GUIDefinitions.h"

SDL_Surface* openScreen();
SDL_Surface* loadImage(char* imagePath);
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

//Widgets creators
Background* createBackground();
Button* createButton(SDL_Rect relevantArea);
Buttons* createButtons(Button** buttonsArray, SDL_Surface* image, int numOfButtons);

//Buttons functions
Button** createVerticalButtonsArrayAndApplayToScreen(int numOfButtons, int xForButtons,
		int yFirstButton, SDL_Surface* buttonsImages, SDL_Rect* clip, int relevantFirstClipIndex, SDL_Surface* screen);
int isButtonPressed(Button *button, SDL_Event sdlEvent);
int isXYInRelevantArea(Button *button, int x, int y);


// Tree functions
UITreeNode* createNode(void* headData, TreeWidgetType widgetType);
UITreeNode* addChildNode(UITreeNode* parent, void * data, TreeWidgetType widgetType);
//int isEmpty(UITreeNode* list);
UITreeNode* append(UITreeNode* list, void* data, TreeWidgetType widgetType);
void freeWidget(void* widget, TreeWidgetType widgetType) ;
void freeTree(UITreeNode* root);
void freeButtons(Buttons* buttons);
void freeBackground(Background* background);

#endif /* GUIUTILS_H_ */
