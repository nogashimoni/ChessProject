/*
 * StartFunctions.c
 *
 *  Created on: Aug 29, 2015
 *      Author: nogalavi1
 */

#include "TranslateFunctions.h"

EventID welcomeOrSelectionTranslateEvent(Window* window, SDL_Event event) {

	UITreeNode* currentButtonNode = window->UITreeHead->child;
	int buttonNumber = 0;
	while ( currentButtonNode != NULL) {
		Button* button = (Button*)currentButtonNode->widget;
		if ( button->isButtonPressed(button,event) ) {
			if ( buttonNumber == 0) return FIRST_PRESSED;
			if ( buttonNumber == 1) return SECOND_PRESSED;
			if ( buttonNumber == 2) return THIRD_PRESSED;
		}
		currentButtonNode = currentButtonNode->next;
		buttonNumber ++;
	}
	return NOTHING_HAPPANED;
}

