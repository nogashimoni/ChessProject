#include "StartFunctions.h"

int startWelcomeOrPlayerSelection(Window* window, void* initData) {
	window->background = NULL;
	SDL_Surface* buttonsImages = NULL;
	window->UITreeHead = NULL;

	// create UI Tree root
	window->UITreeHead = createNode(window, BUTTON); // TODO UI TREE!
	if ( window->UITreeHead == NULL ) {
		//TODO
	}
	// create screen
	SDL_Surface* screen = createScreen();

	// Apply background
	window->background  = loadImage(window->windowId == WELCOME ? WELCOME_BACKGROUND: PLAYER_SELECTION_BACKGROUND);
	if( window->background == NULL ) {
		printf("Error");
		return 0;
	}
	applySurface( 0, 0, window->background, screen, NULL );

	// create arguments for buttons creaton
	SDL_Rect clip[ 4 ];
	clipWelcomeOrPlayerSelection(clip);
	int xForButtons = 0.5*SCREEN_WIDTH-0.5*BUTTON_WIDTH;
	int yFirstButton = 0.5*SCREEN_HEIGHT-1.5*BUTTON_HEIGHT;
	buttonsImages = loadImage(window->windowId == WELCOME ? WELCOME_SPRITE : PLAYER_SELECTION_SPRITE);
	if( buttonsImages == NULL )
		return 0; //TOODO

	// Create buttons
	Button** buttonsArray = createVerticalButtonsArray(3, xForButtons, yFirstButton, buttonsImages, clip, 0, screen);
	buttonsArray[0]->buttonsImages = buttonsImages; // Save the SDL_Surface that needs to be freed, only on the first button
	// insert buttons to UI Tree
	UITreeNode* currButtonNode = addChildNode(window->UITreeHead, buttonsArray[0], BUTTON);
	for ( int i = 1; i<3; i++ ) {
		currButtonNode = append(currButtonNode, buttonsArray[i], BUTTON);
		currButtonNode->widgetType = BUTTON;
	}

	// Update what we see on screen
	if ( SDL_Flip(screen) ==  -1 ) {
	 	printf("ERROR \n");
		return 0;
	}
	return 1;
}

void clipWelcomeOrPlayerSelection( SDL_Rect* clip ){
	//Clip range for the top left
	clip[ 0 ].x = 0;
	clip[ 0 ].y = 0;
	clip[ 0 ].w = 220;
	clip[ 0 ].h = 50;

	//Clip range for the top right
	clip[ 1 ].x = 0;
	clip[ 1 ].y = 50;
	clip[ 1 ].w = 220;
	clip[ 1 ].h = 50;

	//Clip range for the bottom left
	clip[ 2 ].x = 0;
	clip[ 2 ].y = 100;
	clip[ 2 ].w = 220;
	clip[ 2 ].h = 50;

}





