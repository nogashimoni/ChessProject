
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
Buttons* createButtons(Button** buttonsArray, SDL_Surface* image, int numOfButtons, SDL_Rect* clip);
Panel* createPanel(SDL_Rect relevantArea, char* backgroundPath);

//Buttons functions
Button*** createButtonsForMatrix(int matrixTopLeftX, int matrixTopLeftY,
		int squareSize, int n, int m);
Button** createVerticalButtonsArrayAndApplyToScreen(int numOfButtons,
		int xForButtons, int yFirstButton, int weidth, int height, SDL_Surface* buttonsImages,
		SDL_Rect* clipArray, int relevantFirstClipIndex, SDL_Surface* screen);
Button** createHorizontalButtonsArrayAndApplyToScreen(int numOfButtons,
		int xFirsButton, int yForButtons, int buttonWidth, SDL_Surface* buttonsImage,
		SDL_Rect* clipArray, int relevantFirstClipIndex, SDL_Surface* screen, int toApply);
void drawButtons(Buttons* buttons, SDL_Surface* screen);
int isButtonPressed(Button *button, SDL_Event sdlEvent);
int isXYInRelevantArea(Button *button, int x, int y);

//Panel Functions
void applyOnPanel(SDL_Surface* screen,Panel* panel, SDL_Surface* whatToApply, int relativeX, int relativeY);

//Matrix functions
Matrix* createChessBoardMatrix(Panel* fatherPanel, SDL_Rect* clip, Game* game);
void updateMatrixByGame(Matrix* matrix, Game* game);
int isIJPressed(SDL_Event event, Matrix* matrix, int i, int j) ;
void drawMatrix(Matrix* matrix, SDL_Surface* screen);
int getBoardI(int i);
int getBoardJ(int j);

// Tree functions
UITreeNode* createNode(void* headData, TreeWidgetType widgetType);
UITreeNode* addChildNode(UITreeNode* parent, void * data, TreeWidgetType widgetType);
UITreeNode* appendChild(UITreeNode* list, void* data, TreeWidgetType widgetType);
int treeDFS(UITreeNode* root, int (* treeNodePreFunction) (UITreeNode* node), int (* treeNodePostFunction)(UITreeNode* node, SDL_Surface* screen), SDL_Surface* screen);

//draw functions
void drawGUI(Window* window);
int drawNode(UITreeNode* UITreeNode, SDL_Surface* screen);

//free functions
void freeWidget(void* widget, TreeWidgetType widgetType) ;
void freeTree(UITreeNode* root);
void freeButtons(Buttons* buttons);
void freeBackground(Background* background);
void freePanel(Panel* panel);
void freeMatrix(Matrix* panel);

//GUIMemory utils
void initMemory(GUIMemory* memory);
#endif /* GUIUTILS_H_ */
