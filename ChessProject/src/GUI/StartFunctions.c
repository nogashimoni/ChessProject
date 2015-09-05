#include "StartFunctions.h"

int startGeneralSetup(Window* window, void* initData) {

	// create background widget, which is Tree head, apply it to screen and add to UITree
	Background* background = createBackground(window->windowId);
	applySurface(0, 0, background->image, window->screen, NULL);
	window->UITreeHead = NULL;
	window->UITreeHead = createNode(background, BACKGROUND);
	if (window->UITreeHead == NULL) {
		//TODO
	}

	// create arguments for buttons creation
	SDL_Rect clip[4];
	clipGeneralSetup(clip);
	int xForButtons = 0.5 * SCREEN_WIDTH - 0.5 * BUTTON_WIDTH;
	int yFirstButton = 0.5 * SCREEN_HEIGHT - 1.5 * BUTTON_HEIGHT;
	SDL_Surface* buttonsImages = NULL;
	char* imagePath = getSpriteByWindowID(window->windowId);
	buttonsImages = loadImage(imagePath);
	if (buttonsImages == NULL)
		return 0; //TOODO
	Button** buttonsArray = createVerticalButtonsArrayAndApplayToScreen(3,
			xForButtons, yFirstButton, buttonsImages, clip, 0, window->screen);

	// create buttons widget and add to UITree
	Buttons* buttons = createButtons(buttonsArray, buttonsImages, 3);
	addChildNode(window->UITreeHead, buttons, BUTTONS);

	// Update what we see on screen
	if (SDL_Flip(window->screen) == -1) {
		printf("ERROR \n");
		return 0;
	}
	return 1;
}

void clipGeneralSetup(SDL_Rect* clip) {
	//Clip range for the top left
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = 220;
	clip[0].h = 50;

	//Clip range for the top right
	clip[1].x = 0;
	clip[1].y = 50;
	clip[1].w = 220;
	clip[1].h = 50;

	//Clip range for the bottom left
	clip[2].x = 0;
	clip[2].y = 100;
	clip[2].w = 220;
	clip[2].h = 50;

}
char* getSpriteByWindowID(WindowId windowID) {
	switch(windowID) {
		case (WELCOME):
			return WELCOME_SPRITE;
		case (PLAYER_SELECTION):
			return PLAYER_SELECTION_SPRITE;
		case (TO_SET_WHO_STARTS):
			return TO_SET_WHO_STARTS_SPRITE;
		case (SET_WHO_STARTS):
			return SET_WHO_STARTS_SPRITE;
		case (TO_SET_BOARD):
			return TO_SET_BOARD_SPRITE;
		default:
			break;
	}
	return PLAYER_SELECTION_SPRITE;
}
