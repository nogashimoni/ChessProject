/*
 * StartFunctions.c
 *
 *  Created on: Aug 29, 2015
 *      Author: nogalavi1
 */

#include "TranslateFunctions.h"

EventID translateEventWelcomeOrSelection(Window* window, SDL_Event event) {

	UITreeNode* buttonsNode = window->UITreeHead->child;
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

