#include "HandleFunctions.h"

//TODO DELETE!!!
int isValidMoveIJCopy(Game* game, int i1, int j1, int i2, int j2);

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
		initMemory(memory);
		initGameFields(game, 1);
		return WELCOME;
	case (SIXTH_PRESSED): //start game
		if ( (countPeices(game, WHITE_K) == 1) && (countPeices(game, BLACK_K) == 1) ) {
			return GAME_WINDOW;
		} else {
			memory->pathOfBubbleToShow = WRONG_INIT_BUBBLE;
			memory->isScreenUpdated = 0;
			memory->commandType = NO_COMMAND;
			print_message(WROND_BOARD_INITIALIZATION);
			return SET_BOARD;
		}
	case (CHOSE_PIECE):
		memory->pressedSquarsNum = 1; // not really a square
		memory->isScreenUpdated = 0;
		break;
	case (SOME_SQUARE_PRESSED):
		switch (memory->commandType) {
		case (NO_COMMAND):
			break;
		case (REMOVE):
			i = memory->newI;
			j = memory->newJ;
			game->board[i][j] = EMPTY;
			memory->commandType = NO_COMMAND;
			memory->isScreenUpdated = 0;
			break;
		case (MOVE):
			memory->pressedSquarsNum++;
			int newPlaceTaken = memory->pressedSquarsNum == 2
					&& game->board[memory->newI][memory->newJ] != EMPTY;
			int wantToMoveEmptySquare = memory->pressedSquarsNum == 1
					&& game->board[memory->newI][memory->newJ]
							== EMPTY;

			if (newPlaceTaken || wantToMoveEmptySquare) {
				memory->commandType = NO_COMMAND;
				memory->isScreenUpdated = 0;
			} else if (memory->pressedSquarsNum == 2) {
				game->board[memory->newI][memory->newJ] =
						game->board[memory->oldI][memory->oldJ];
				game->board[memory->oldI][memory->oldJ] =
						EMPTY;
				memory->commandType = NO_COMMAND;
				memory->pressedSquarsNum = 0;
				memory->isScreenUpdated = 0;
			}
			break;
			case (ADD):
				memory->pressedSquarsNum++;
				int isPlaceTaken = (memory->pressedSquarsNum == 2 )
							&& (game->board[memory->newI][memory->newJ] != EMPTY);

				int isWrongInitialization = (memory->pressedSquarsNum == 2) && !isLegalPeiceAddition(game, memory->pieceChosen);
				if ( !isPlaceTaken && isWrongInitialization ) {
					memory->pathOfBubbleToShow = WRONG_INIT_BUBBLE;
				}
				memory->commandType = NO_COMMAND;
				memory->pressedSquarsNum = 0;
				memory->isScreenUpdated = 0;
				// addition is legal
				if ( !isPlaceTaken && !isWrongInitialization ) {
					game->board[memory->newI][memory->newJ] = memory->pieceChosen;
				}
				memory->pieceChosen = -1;
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
	case (FIRST_PRESSED): //save game
		memory->commandType = SAVE;
		memory->isScreenUpdated = 0;
//		memory->pressedSquarsNum = 0;
		return GAME_WINDOW;
	case (SECOND_PRESSED): // main menu
		initMemory(memory);
		initGameFields(game, 1);
		return WELCOME;
	case (THIRD_PRESSED): //quit
		return QUIT_WINDOW;
	case (FOURTH_PRESSED): //get best moves
		memory->commandType = GET_BEST_MOVE;
		memory->isScreenUpdated = 0;
//		memory->pressedSquarsNum = 0;
		return GAME_WINDOW;

	case (SOME_SQUARE_PRESSED):
//		memory->pressedSquarsNum ++;

		if (memory->commandType == NO_COMMAND) {
			// Player chose an empty square or an opponent square
			int whitePlayerChoosesWhite = (game->isWhiteTurn == 1 && getPieceColor(game,memory->newI,memory->newJ) == 1);
			int blackPlayerChoosesBlack = (game->isWhiteTurn == 0 && getPieceColor(game,memory->newI,memory->newJ) == 0);
			if ( !(whitePlayerChoosesWhite || blackPlayerChoosesBlack) ) {
//				memory->pressedSquarsNum = 0;
				memory->isScreenUpdated = 0;
				return GAME_WINDOW;
			}
			// will paint yellow the soldier itself and it's possible moves
			memory->commandType = DO_MOVE;
			memory->isScreenUpdated = 0;
			return GAME_WINDOW;
		}
		else if (memory->commandType == DO_MOVE) {
			if (isValidMoveIJCopy(game,memory->oldI,memory->oldJ,memory->newI, memory->newJ)) {
				doMoveIJ(game, memory->oldI,memory->oldJ,memory->newI, memory->newJ,EMPTY );
			}
			memory->commandType = NO_COMMAND;
			memory->isScreenUpdated = 0;
			return GAME_WINDOW;
		}

		break;
//		printf("%d, %d\n", memory->newI, memory->newJ);


	case (NOTHING_HAPPANED):
		return GAME_WINDOW;

	default:
		break;
	}
	return GAME_WINDOW;
}

// update functions
int updateWindow(Window* activeWindow, Game* game, GUIMemory* memory) {
	if (memory->isScreenUpdated == 1)
		return 1;

	if (activeWindow->windowId == SET_BOARD) {
		updateSetBoard(activeWindow, game, memory);
	}

	if (activeWindow->windowId == GAME_WINDOW) {
		updateGameBoard(activeWindow, game, memory);
	}

	SDL_Flip(activeWindow->screen);
	memory->isScreenUpdated = 1;

	return 1;
}


int updateSetBoard(Window* activeWindow, Game* game, GUIMemory* memory) {
	if ( memory->pathOfBubbleToShow != NULL ) {
		showBubble(memory, activeWindow->screen);
		memory->pathOfBubbleToShow = NULL;
		// redraw background when time is over
		Background* background = (Background*)activeWindow->UITreeHead->widget;
		applySurface(0,0,background->image, activeWindow->screen, NULL );
	}

	// update matrix
	Matrix* matrix = (Matrix*) activeWindow->UITreeHead->child->child->widget;
	updateMatrixByGame(matrix, game);
	Panel* panel = (Panel*) activeWindow->UITreeHead->child->widget;
	applySurface(X_FOR_PANEL, Y_FOR_PANEL, panel->panelBackground,
			activeWindow->screen, NULL);
	drawMatrix(matrix, activeWindow->screen);

	// draw add panel and buttons if needed
	if ( (memory->commandType == ADD) && (memory->pressedSquarsNum == 0) ){
		Panel* panel = (Panel*) activeWindow->UITreeHead->child->child->child->child->widget;
		applySurface(panel->relevantArea.x, panel->relevantArea.y, panel->panelBackground,
				activeWindow->screen, NULL);
		drawButtons(activeWindow->UITreeHead->child->child->child->child->child->widget, activeWindow->screen);
		drawButtons(activeWindow->UITreeHead->child->child->child->child->child->child->widget, activeWindow->screen);
	}

	//update buttons display
	Buttons* buttons =
			(Buttons*) activeWindow->UITreeHead->child->child->child->widget;
	// clear all yellow marks (redraw them if needed)
	for (int i = 0; i < 6; i++) {
		applySurface(SET_BOARD_MENU_X, SET_BOARD_MENU_Y + i * BUTTON_HEIGHT,
				buttons->buttonsImages, activeWindow->screen,
				&buttons->clipArray[i]);
	}
	// draw yellow marks if needed
	if (memory->commandType == REMOVE) {
		applySurface(SET_BOARD_MENU_X, SET_BOARD_MENU_Y + 2 * BUTTON_HEIGHT,
				buttons->buttonsImages, activeWindow->screen,
				&buttons->clipArray[8]);
	}
	if (memory->commandType == ADD) {
		applySurface(SET_BOARD_MENU_X, SET_BOARD_MENU_Y + BUTTON_HEIGHT,
				buttons->buttonsImages, activeWindow->screen,
				&buttons->clipArray[7]);
	}
	if (memory->commandType == MOVE) {
		applySurface(SET_BOARD_MENU_X, SET_BOARD_MENU_Y, buttons->buttonsImages,
				activeWindow->screen, &buttons->clipArray[6]);
	}
	return 1;
}

int updateGameBoard(Window* activeWindow,Game* game,GUIMemory* memory) {
	if ( memory->pathOfBubbleToShow != NULL ) {
		showBubble(memory, activeWindow->screen);
		memory->pathOfBubbleToShow = NULL;
		// redraw background when time is over
		Background* background = (Background*)activeWindow->UITreeHead->widget;
		applySurface(0,0,background->image, activeWindow->screen, NULL );
	}


	// redraw matrix by game
	Matrix* matrix = (Matrix*) activeWindow->UITreeHead->child->child->widget;
	updateMatrixByGame(matrix, game);
	Panel* panel = (Panel*) activeWindow->UITreeHead->child->widget;
	applySurface(X_FOR_PANEL, Y_FOR_PANEL, panel->panelBackground,
			activeWindow->screen, NULL);
	drawMatrix(matrix, activeWindow->screen);

//	// draw save game panel and buttons if needed
//	if ( (memory->commandType == SAVE) && (memory->pressedSquarsNum == 0) ){
//		Panel* panel = (Panel*) activeWindow->UITreeHead->child->child->child->child->widget;
//		applySurface(panel->relevantArea.x, panel->relevantArea.y, panel->panelBackground,
//				activeWindow->screen, NULL);
//		drawButtons(activeWindow->UITreeHead->child->child->child->child->child->widget, activeWindow->screen);
//		drawButtons(activeWindow->UITreeHead->child->child->child->child->child->child->widget, activeWindow->screen);
//	}

	//update yellow marks

	Buttons* getBestMoveButton =
			(Buttons*)activeWindow->UITreeHead->child->child->child->child->widget;
	// clear best move yellow mark
	if (memory->commandType != GET_BEST_MOVE) {
			applySurface(GET_BEST_MOVE_BUTTON_X, GET_BEST_MOVE_BUTTON_Y,
					getBestMoveButton->buttonsImages, activeWindow->screen,
					&getBestMoveButton->clipArray[0]);
	}
	// draw best move yellow mark if needed
	if (memory->commandType == GET_BEST_MOVE) {
		applySurface(GET_BEST_MOVE_BUTTON_X, GET_BEST_MOVE_BUTTON_Y,
				getBestMoveButton->buttonsImages, activeWindow->screen,
					&getBestMoveButton->clipArray[1]);
	}
	if (memory->commandType == DO_MOVE) {
		displayAllPossibleMoves(matrix,memory, game, activeWindow->screen);
	}
	return 1;
}


// helper functions

void displayAllPossibleMoves(Matrix* matrix,GUIMemory* memory, Game* game, SDL_Surface* screen) {

	for (int i=0; i<BOARD_SIZE; i++) {
		for (int j=0; j<BOARD_SIZE; j++) {
			Button* button = matrix->buttonsMatrix[getBoardJ(j)][i];
			if (isValidMoveIJCopy(game, memory->newI, memory->newJ, i, j )) {
				SDL_Rect clip;
				clip.x = 0;
				clip.y = 0;
				clip.w = BOARD_MATRIX_SQUARE_SIZE;
				clip.h = BOARD_MATRIX_SQUARE_SIZE;
				applySurface(button->relevantArea.x, button->relevantArea.y, matrix->highlightImage, screen, &clip);
			}
		}
	}
	SDL_Flip(screen);
}

// TO DELETE !!!
int isValidMoveIJCopy(Game* game, int i1, int j1, int i2, int j2){

	Move* move = creatNewMove(i1, j1, i2, j2);
	int result = isValidMove(game, move);
	freeMove(move);
	return result;

}
