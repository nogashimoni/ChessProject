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
			printf("first pressed\n");
			return PLAYER_SELECTION;
			break;
		case (SECOND_PRESSED):
			printf("2nd pressed\n");
			break;
		case (THIRD_PRESSED):
			printf("3rd pressed\n");
			break;
		case (NOTHING_HAPPANED):
			return WELCOME;
	}
	return WELCOME;
}

int handleEventSelectionWindow(Window* window, EventID eventID) {
	switch (eventID) {
		case (FIRST_PRESSED): //new game
			printf("first pressed\n");
			break;
		case (SECOND_PRESSED):
			printf("2nd pressed\n");
			break;
		case (THIRD_PRESSED):
			printf("3rd pressed\n");
			return WELCOME;
		case (NOTHING_HAPPANED):
			return PLAYER_SELECTION;
	}
	return PLAYER_SELECTION;
}