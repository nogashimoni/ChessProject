#include "HandleFunctions.h"

int handleEventWelcomeWindow(Window* window, EventID eventID, Game* game,
		GUIMemory* memory) {
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

int handleEventSelectionWindow(Window* window, EventID eventID, Game* game,
		GUIMemory* memory) {
	switch (eventID) {
	case (FIRST_PRESSED): //player vs. player
		printf("first pressed\n");
		game->isTwoPlayersMode = 1;
		return TO_SET_WHO_STARTS;
	case (SECOND_PRESSED): //player vs. computer
		game->isTwoPlayersMode = 0;
		printf("2nd pressed\n");
		return SET_DIFFICULTY_AND_COLOR;
	case (THIRD_PRESSED): //cancel
		initGameFields(game, 1);
		printf("3rd pressed\n");
		return WELCOME;
	case (NOTHING_HAPPANED):
		return PLAYER_SELECTION;
	case (QUIT_EVENT):
		return QUIT_WINDOW;
	default:
		return PLAYER_SELECTION;
	}
	return PLAYER_SELECTION;
}

int handleEventSetDiffAndColor(Window* window, EventID eventID, Game* game,
		GUIMemory* memory) {
	switch (eventID) {
	case (FIRST_PRESSED): // difficulty 1
		game->minmaxDepth = 1;
		return SET_DIFFICULTY_AND_COLOR;
	case (SECOND_PRESSED): // difficulty 2
		game->minmaxDepth = 2;
		return SET_DIFFICULTY_AND_COLOR;
	case (THIRD_PRESSED): // difficulty 3
		game->minmaxDepth = 3;
		return SET_DIFFICULTY_AND_COLOR;
		break;
	case (FOURTH_PRESSED): // difficulty 4
		game->minmaxDepth = 4;
		return SET_DIFFICULTY_AND_COLOR;
		break;
	case (FIFTH_PRESSED): // user color black
		game->isUserWhite = 0;
		return SET_DIFFICULTY_AND_COLOR;
		break;
	case (SIXTH_PRESSED): // user color white
		game->isUserWhite = 1;
		return SET_DIFFICULTY_AND_COLOR;
		break;
	case (SEVENTH_PRESSED): //continue
		return TO_SET_WHO_STARTS; //TODO the user should understand that there are default values
	case (EIGHTH_PRESSED): //cancel
		initGameFields(game, 1);
		return WELCOME;
	case (NOTHING_HAPPANED):
		return SET_DIFFICULTY_AND_COLOR;
	case (QUIT_EVENT):
		return QUIT_WINDOW;
	default:
		break;
	}
	return SET_DIFFICULTY_AND_COLOR;
}

int handleEventToSetWhoStarts(Window* window, EventID eventID, Game* game,
		GUIMemory* memory) {
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

int handleEventSetWhoStarts(Window* window, EventID eventID, Game* game,
		GUIMemory* memory) {
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

int handleEventSetBoard(Window* window, EventID eventID, Game* game,
		GUIMemory* memory) {
	int i, j;

	switch (eventID) {
	case (QUIT_EVENT):
		return QUIT_WINDOW;
		break;
	case (FIRST_PRESSED): //move
		memory->commandType = MOVE;
		memory->isScreenUpdated = 0;
		memory->pressedSquarsNum = 0;
		return SET_BOARD;
	case (SECOND_PRESSED): //add
		memory->commandType = ADD;
		memory->isScreenUpdated = 0;
		memory->pressedSquarsNum = 0;
		return SET_BOARD;
	case (THIRD_PRESSED): //remove
		memory->commandType = REMOVE;
		memory->isScreenUpdated = 0;
		memory->pressedSquarsNum = 0;
		return SET_BOARD;
	case (FOURTH_PRESSED): //remove all
		clearBoard(game);
		memory->isScreenUpdated = 0;
		memory->commandType = NO_COMMAND;
		memory->pressedSquarsNum = 0;
		return SET_BOARD;
	case (FIFTH_PRESSED): //cancel
		initGameFields(game, 1);
		return WELCOME;
	case (SIXTH_PRESSED): //start game
		return GAME_WINDOW;
	case (SOME_SQUARE_PRESSED):
		switch (memory->commandType) {
		case (NO_COMMAND):
			break;
		case (REMOVE):
			i = memory->newI;
			j = memory->newJ;
			game->board[getBoardI(i)][getBoardJ(j)] = ' ';
			memory->commandType = NO_COMMAND;
			memory->isScreenUpdated = 0;
			break;
		case (MOVE):
			memory->pressedSquarsNum++;
			if (memory->pressedSquarsNum == 1
					&& game->board[memory->newI][getBoardJ(memory->newJ)]
							== ' ') {
				memory->commandType = NO_COMMAND;
				memory->isScreenUpdated = 0;
			} else if (memory->pressedSquarsNum == 2) {
				game->board[memory->newI][getBoardJ(memory->newJ)] =
						game->board[memory->oldI][getBoardJ(memory->oldJ)];
				game->board[getBoardI(memory->oldI)][getBoardJ(memory->oldJ)] =
						' ';
				memory->commandType = NO_COMMAND;
				memory->pressedSquarsNum = 0;
				memory->isScreenUpdated = 0;
			}
			break;
		}
		break;

	default:
		return SET_BOARD;
	}
	return SET_BOARD;

}

int handleEventToSetBoard(Window* window, EventID eventID, Game* game,
		GUIMemory* memory) {
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

int handleEventGameWindow(Window* window, EventID eventID, Game* game,
		GUIMemory* memory) {
	switch (eventID) {
	case (QUIT_EVENT):
		return QUIT_WINDOW;
	case (SOME_SQUARE_PRESSED):
		printf("%d, %d\n", memory->newI, memory->newJ);
		break;
	case (NOTHING_HAPPANED):
		break;
	default:
		break;
	}
	return GAME_WINDOW;
}
