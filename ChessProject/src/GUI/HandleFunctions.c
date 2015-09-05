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
			return QUIT_WINDOW;
			break;
		case (NOTHING_HAPPANED):
			return WELCOME;
		case (QUIT_EVENT):
			return QUIT_WINDOW;
	}
	return WELCOME;
}

int handleEventSelectionWindow(Window* window, EventID eventID) {
	switch (eventID) {
		case (FIRST_PRESSED): //player vs. player
			printf("first pressed\n");
			return TO_SET_WHO_STARTS;
			break;
		case (SECOND_PRESSED): //player vs. computer
			printf("2nd pressed\n");
			return TO_SET_WHO_STARTS;
			break;
		case (THIRD_PRESSED): //cancel
			printf("3rd pressed\n");
			return WELCOME;
		case (NOTHING_HAPPANED):
			return PLAYER_SELECTION;
		case (QUIT_EVENT):
			return QUIT_WINDOW;
	}
	return PLAYER_SELECTION;
}

int handleEventToSetWhoStarts(Window* window, EventID eventID) {
	switch (eventID) {
		case (FIRST_PRESSED): //set who starts
			printf("first pressed\n");
			return SET_WHO_STARTS;
			break;
		case (SECOND_PRESSED): //continue
			printf("2nd pressed\n");
			return TO_SET_BOARD;
			break;
		case (THIRD_PRESSED): //cancel
			printf("3rd pressed\n");
			return WELCOME;
		case (NOTHING_HAPPANED):
			return TO_SET_WHO_STARTS;
		case (QUIT_EVENT):
			return QUIT_WINDOW;
	}
	return PLAYER_SELECTION;
}


int handleEventSetWhoStarts(Window* window, EventID eventID) {
	switch (eventID) {
		case (FIRST_PRESSED): //white
			printf("first pressed\n");
			return TO_SET_BOARD;
			break;
		case (SECOND_PRESSED): //black
			printf("2nd pressed\n");
			return TO_SET_BOARD;
			break;
		case (THIRD_PRESSED): //back
			printf("3rd pressed\n");
			return TO_SET_WHO_STARTS;
		case (NOTHING_HAPPANED):
			return SET_WHO_STARTS;
		case (QUIT_EVENT):
			return QUIT_WINDOW;
	}
	return SET_WHO_STARTS;
}

int handleEventSetBoard(Window* window, EventID eventID) {
	switch (eventID) {
		case (QUIT_EVENT):
			return QUIT_WINDOW;
	}
	return PLAYER_SELECTION;
}

int handleEventToSetBoard(Window* window, EventID eventID) {
	switch (eventID) {
		case (FIRST_PRESSED): //set board
			printf("first pressed\n");
			return SET_BOARD;
			break;
		case (SECOND_PRESSED): //continue
			printf("2nd pressed\n");
			return TO_SET_BOARD; //TODO start game!
			break;
		case (THIRD_PRESSED): //cancel
			printf("3rd pressed\n");
			return WELCOME;
		case (NOTHING_HAPPANED):
			return TO_SET_BOARD;
		case (QUIT_EVENT):
			return QUIT_WINDOW;
	}
	return PLAYER_SELECTION;
}
