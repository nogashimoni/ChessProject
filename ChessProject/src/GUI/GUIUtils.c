#include "GUIUtils.h"

SDL_Surface* loadImage(char* imagePath) {
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage= NULL;
	//The optimized image that will be used
	SDL_Surface* optimizedImage=NULL;
	loadedImage = IMG_Load(imagePath);//IMG_Load( imagePath );
	 //If nothing went wrong in loading the image
	if( loadedImage != NULL ) {
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );
		//Free the old image
		SDL_FreeSurface( loadedImage );
	}
	else {
		return loadedImage; // returns NULL
	}
	//TODO make image transparent
	 //Return the optimized image
	return optimizedImage;
}

void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, clip, destination, &offset );
 	//Update Screen? outside..

}

Button* createButton(SDL_Rect relevantArea) {

	Button* button = NULL;

	button = (Button*) malloc(sizeof(Button));
	if ( button == NULL ) {
		//TODO standardFunctionFailure("malloc"); /* exit unavoidable */
		return NULL;
	}

	button->relevantArea = relevantArea;
	button->isButtonPressed = isButtonPressed;
	return button;
}



int isButtonPressed(Button *button, SDL_Event sdlEvent) {
	int xOfEvent, yOfEvent;

	if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
	/* If the left mouse button was pressed */
		if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
			/* Get the mouse offsets */
			xOfEvent = sdlEvent.button.x;
			yOfEvent = sdlEvent.button.y;
			/* If the mouse is over the button */
			if (isXYInRelevantArea(button, xOfEvent, yOfEvent)) {
				return 1;
			}
		}
	}

	return 0;
}

int isXYInRelevantArea(Button *button, int x, int y) {
	return (x > button->relevantArea.x) && (x < button->relevantArea.x + button->relevantArea.w)
			&& (y > button->relevantArea.y) && (y < button->relevantArea.y + button->relevantArea.h);
}


// Tree utilities

UITreeNode* createNode(void* headData){
	UITreeNode* newTree = (UITreeNode*)malloc(sizeof(UITreeNode));
	if (newTree == NULL){
//		perrorPrint("malloc"); TODO
	    return NULL;
	}
	/* data and next will point to NULL: */
	newTree->data = NULL;
	newTree->next = NULL;
	newTree->child = NULL;
	newTree->parent = NULL;

	/* if headData is not NULL, put it in the list data field */
	if (headData != NULL){
		newTree->data = headData;
	}
	return newTree;
}
