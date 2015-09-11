#include "TranslateFunctions.h"


EventID translateEventGeneralSetup(Window* window, SDL_Event event, GUIMemory* memory) {

	UITreeNode* buttonsNode = window->UITreeHead->child;
	Buttons* buttons = ((Buttons*) buttonsNode->widget);

	int buttonNumber;

	if (event.type == SDL_QUIT) {
		return QUIT_EVENT;
	}

	for (buttonNumber = 0; buttonNumber < buttons->numOfButtons;
			buttonNumber++) {
		Button* button = buttons->buttonArray[buttonNumber];
		if (button->isButtonPressed(button, event)) {
			if (buttonNumber == 0)
				return FIRST_PRESSED;
			if (buttonNumber == 1)
				return SECOND_PRESSED;
			if (buttonNumber == 2)
				return THIRD_PRESSED;
		}
	}
	return NOTHING_HAPPANED;
}

EventID translateEventSetBoard(Window* window, SDL_Event event, GUIMemory* memory) {
	if (event.type == SDL_QUIT) {
		return QUIT_EVENT;
	}

	for (int i=0; i<BOARD_SIZE; i++) {
		for (int j=0; j<BOARD_SIZE; j++) {
			Matrix* matrix = (Matrix*)window->UITreeHead->child->child->widget ;
			if ( matrix->isIJPressed(event, matrix,i,j) ) {
				printf("%d %d pressed!\n",i,j);
				return FIRST_PRESSED;
			}
		}
	}
	// are buttons pressed (from previous function)

	UITreeNode* buttonsNode = window->UITreeHead->child->child->child;
	Buttons* buttons = ((Buttons*) buttonsNode->widget);

	int buttonNumber;
	for (buttonNumber = 0; buttonNumber < buttons->numOfButtons;
			buttonNumber++) {
		Button* button = buttons->buttonArray[buttonNumber];
		if (button->isButtonPressed(button, event)) {
			if (buttonNumber == 0)
				return FIRST_PRESSED;
			if (buttonNumber == 1)
				return SECOND_PRESSED;
			if (buttonNumber == 2)
				return THIRD_PRESSED;
		}
	}
	return NOTHING_HAPPANED;

}

EventID translateEventGameWindow(Window* window, SDL_Event event, GUIMemory* memory) {
	if (event.type == SDL_QUIT) {
		return QUIT_EVENT;
	}

	for (int i=0; i<BOARD_SIZE; i++) {
		for (int j=0; j<BOARD_SIZE; j++) {
			Matrix* matrix = (Matrix*)window->UITreeHead->child->child->widget ;
			if ( matrix->isIJPressed(event, matrix,i,j) ) {
				memory->pressedI = i;
				memory->pressedJ = j;
				return SOME_SQUARE_PRESSED;
			}
		}
	}
	// are buttons pressed (from previous function)

	UITreeNode* buttonsNode = window->UITreeHead->child->child->child;
	Buttons* buttons = ((Buttons*) buttonsNode->widget);

	int buttonNumber;
	for (buttonNumber = 0; buttonNumber < buttons->numOfButtons;
			buttonNumber++) {
		Button* button = buttons->buttonArray[buttonNumber];
		if (button->isButtonPressed(button, event)) {
			if (buttonNumber == 0)
				return FIRST_PRESSED;
			if (buttonNumber == 1)
				return SECOND_PRESSED;
			if (buttonNumber == 2)
				return THIRD_PRESSED;
		}
	}
	return NOTHING_HAPPANED;


}


