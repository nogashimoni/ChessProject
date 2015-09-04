/*
 * StartFunctions.c
 *
 *  Created on: Aug 29, 2015
 *      Author: nogalavi1
 */

#include "HandleFunctions.h"

int handleEventWelcomeWindow(Window* window, EventID eventID) {
	switch (eventID) {
		case (FIRST_PRESSED): //new game
			return PLAYER_SELECTION;
	}
	return WELCOME;
}
int handleEventSelectionWindow(Window* window, EventID eventID) {
	//TODO
	return WELCOME;
}
