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

EventID translateEventSetDiffAndColor(Window* window, SDL_Event event, GUIMemory* memory) {

	if (event.type == SDL_QUIT) {
		return QUIT_EVENT;
	}
	// is user difficulty button pressed
	UITreeNode* difficultyButtonsNode = window->UITreeHead->child;
	Buttons* difficultyButtons = ((Buttons*) difficultyButtonsNode->widget);
	int buttonNumber;
	for (buttonNumber = 0; buttonNumber < difficultyButtons->numOfButtons;
			buttonNumber++) {
		Button* button = difficultyButtons->buttonArray[buttonNumber];
		if (button->isButtonPressed(button, event)) {
			if (buttonNumber == 0)
				return FIRST_PRESSED;
			if (buttonNumber == 1)
				return SECOND_PRESSED;
			if (buttonNumber == 2)
				return THIRD_PRESSED;
			if (buttonNumber == 3)
				return FOURTH_PRESSED;
		}
	}
	// is user user color button pressed
	UITreeNode* userColorButtonsNode = window->UITreeHead->child->child;
	Buttons* userColorButtons = ((Buttons*) userColorButtonsNode->widget);

	for (buttonNumber = 0; buttonNumber < userColorButtons->numOfButtons;
			buttonNumber++) {
		Button* button = userColorButtons->buttonArray[buttonNumber];
		if (button->isButtonPressed(button, event)) {
			if (buttonNumber == 0)
				return FIFTH_PRESSED;
			if (buttonNumber == 1)
				return SIXTH_PRESSED;
		}
	}
	// are user continue or cancel buttons pressed
	UITreeNode* cancelContinueButtonsNode = window->UITreeHead->child->child->child;
	Buttons*  cancelContinueButtons = ((Buttons*) cancelContinueButtonsNode->widget);

	for (buttonNumber = 0; buttonNumber <  cancelContinueButtons->numOfButtons;
			buttonNumber++) {
		Button* button =  cancelContinueButtons->buttonArray[buttonNumber];
		if (button->isButtonPressed(button, event)) {
			if (buttonNumber == 0)
				return SEVENTH_PRESSED;
			if (buttonNumber == 1)
				return EIGHTH_PRESSED;
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
				memory->oldI = memory->newI;
				memory->oldJ = memory->newJ;
				memory->newI = i;
				memory->newJ = j;
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
			if (buttonNumber == 3)
				return FOURTH_PRESSED;
			if (buttonNumber == 4)
				return FIFTH_PRESSED;
			if (buttonNumber == 5)
				return SIXTH_PRESSED;
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
				memory->oldI = memory->newI;
				memory->oldJ = memory->newJ;
				memory->newI = i;
				memory->newJ = j;
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


