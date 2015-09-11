
#include "HandleFunctions.h"

int handleEventWelcomeWindow(Window* window, EventID eventID, Game* game, GUIMemory* memory) {
	switch (eventID) {
		case (FIRST_PRESSED): //new game
			printf("first pressed\n");
			return PLAYER_SELECTION;
			break;
		case (SECOND_PRESSED): //load game
			printf("2nd pressed\n");
			break;
		case (THIRD_PRESSED): //quit
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

int handleEventSelectionWindow(Window* window, EventID eventID, Game* game, GUIMemory* memory) {
	switch (eventID) {
		case (FIRST_PRESSED): //player vs. player
			printf("first pressed\n");
			game->isTwoPlayersMode=1;
			return TO_SET_WHO_STARTS;
			break;
		case (SECOND_PRESSED): //player vs. computer
			game->isTwoPlayersMode=0;
			printf("2nd pressed\n");
			return TO_SET_WHO_STARTS;
			break;
		case (THIRD_PRESSED): //cancel
			initGameFields(game, 1);
			printf("3rd pressed\n");
			return WELCOME;
		case (NOTHING_HAPPANED):
			return PLAYER_SELECTION;
		case (QUIT_EVENT):
			return QUIT_WINDOW;
	}
	return PLAYER_SELECTION;
}

int handleEventToSetWhoStarts(Window* window, EventID eventID, Game* game, GUIMemory* memory) {
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
			initGameFields(game, 1);
			return WELCOME;
		case (NOTHING_HAPPANED):
			return TO_SET_WHO_STARTS;
		case (QUIT_EVENT):
			return QUIT_WINDOW;
	}
	return PLAYER_SELECTION;
}


int handleEventSetWhoStarts(Window* window, EventID eventID, Game* game, GUIMemory* memory) {
	switch (eventID) {
		case (FIRST_PRESSED): //white
			printf("first pressed\n");
			game->isWhiteTurn = 1;
			return TO_SET_BOARD;
			break;
		case (SECOND_PRESSED): //black
			game->isWhiteTurn = 0;
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

int handleEventSetBoard(Window* window, EventID eventID, Game* game, GUIMemory* memory) {
	switch (eventID) {
		case (QUIT_EVENT):
			return QUIT_WINDOW;
			break;
		case (FIRST_PRESSED):
			return GAME_WINDOW;
		default:
			return SET_BOARD;
	}

}

int handleEventToSetBoard(Window* window, EventID eventID, Game* game, GUIMemory* memory) {
	switch (eventID) {
		case (FIRST_PRESSED): //set board
			printf("first pressed\n");
			return SET_BOARD;
			break;
		case (SECOND_PRESSED): //continue
			printf("2nd pressed\n");
			return GAME_WINDOW; //Start game! (continue)
			break;
		case (THIRD_PRESSED): //cancel
			printf("3rd pressed\n");
			return WELCOME;
		case (NOTHING_HAPPANED):
			return TO_SET_BOARD;
		case (QUIT_EVENT):
			return QUIT_WINDOW;
	}
	return TO_SET_BOARD;
}

int handleEventGameWindow(Window* window, EventID eventID, Game* game, GUIMemory* memory) {
	switch (eventID) {
		case (QUIT_EVENT):
			return QUIT_WINDOW;
		case (SOME_SQUARE_PRESSED):
			printf("%d, %d\n", memory->pressedI, memory->pressedJ);
			break;
		case (NOTHING_HAPPANED):
			break;
		default:
			break;
	}
	return GAME_WINDOW;
}
