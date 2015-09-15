#include "HandleFunctions.h"


int handleEventWelcomeWindow(Window* window, EventID eventID, Game* game,
		GUIMemory* memory) {
	switch (eventID) {
	case (FIRST_PRESSED): //new game
		return PLAYER_SELECTION;
		break;
	case (SECOND_PRESSED): //load game
		memory->commandType = CHOOSE_SLOT;
		memory->isScreenUpdated = 0;
		break;
	case (THIRD_PRESSED): //quit
		return QUIT_WINDOW;
		break;
	case (NOTHING_HAPPANED):
		return WELCOME;
	case (QUIT_EVENT):
		return QUIT_WINDOW;
	case (SOME_SLOT_CHOSEN):
		if (memory->numOfSlotPressed != -1) {
			memory->isScreenUpdated = 0; // will draw yellow mark
		}
		return WELCOME;
	case (LOADED_GAME):
		if (!doesSlotContainFile(memory->numOfSlotPressed)) {
			printf("Slot is empty\n");
			return WELCOME;
		}
		else {
			loadFromAFullSlot(game, memory->numOfSlotPressed);
			return TO_SET_WHO_STARTS;
		}
	default:
		break;

	}
	return WELCOME;
}

int handleEventSelectionWindow(Window* window, EventID eventID, Game* game,
		GUIMemory* memory) {
	switch (eventID) {
	case (FIRST_PRESSED): //player vs. player
		game->isTwoPlayersMode = 1;
		return TO_SET_WHO_STARTS;
	case (SECOND_PRESSED): //player vs. computer
		game->isTwoPlayersMode = 0;
		return SET_DIFFICULTY_AND_COLOR;
	case (THIRD_PRESSED): //cancel
		initGameFields(game, 1);
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
	case (NINTH_PRESSED): //difficulty best
		game->minmaxDepth = 4;
		return SET_DIFFICULTY_AND_COLOR;
	case (FIFTH_PRESSED): // user color black
		game->isUserWhite = 0;
		return SET_DIFFICULTY_AND_COLOR;
		break;
	case (SIXTH_PRESSED): // user color white
		game->isUserWhite = 1;
		return SET_DIFFICULTY_AND_COLOR;
		break;
	case (SEVENTH_PRESSED): //continue
		return TO_SET_WHO_STARTS;
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
		return SET_WHO_STARTS;
		break;
	case (SECOND_PRESSED): //continue
		return TO_SET_BOARD;
		break;
	case (THIRD_PRESSED): //cancel
		initGameFields(game, 1);
		return WELCOME;
	case (NOTHING_HAPPANED):
		return TO_SET_WHO_STARTS;
	case (QUIT_EVENT):
		return QUIT_WINDOW;
	default:
		return PLAYER_SELECTION;
	}
	return PLAYER_SELECTION;
}

int handleEventSetWhoStarts(Window* window, EventID eventID, Game* game,
		GUIMemory* memory) {
	switch (eventID) {
	case (FIRST_PRESSED): //white
		game->isWhiteTurn = 1;
		return TO_SET_BOARD;
		break;
	case (SECOND_PRESSED): //black
		game->isWhiteTurn = 0;
		return TO_SET_BOARD;
		break;
	case (THIRD_PRESSED): //back
		return TO_SET_WHO_STARTS;
	case (NOTHING_HAPPANED):
		return SET_WHO_STARTS;
	case (QUIT_EVENT):
		return QUIT_WINDOW;
	default:
		break;
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
			setIsComputerTurn(game);
			// check if the game starts with mate/ tie
			memory->isTie = isTie(game);
			if (memory->isTie) {
				memory->pathOfBubbleToShow = TIE_BUBBLE;
				memory->isInitialEvent = 1;
			}
			int isWhiteOrBlackWin = initializedMate(game);// 1 white wins, 2 black wins
			if ( isWhiteOrBlackWin == 1 ) {
				memory->isMate = 1;
				memory->pathOfBubbleToShow = MATE_WHITE_WON_BUBBLE;
				memory->isInitialEvent = 1;
			}
			if ( isWhiteOrBlackWin == 2 ) {
				memory->isMate = 1;
				memory->pathOfBubbleToShow = MATE_BLACK_WON_BUUBLE;
				memory->isInitialEvent = 1;
			}

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

			default:
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
		return SET_BOARD;
		break;
	case (SECOND_PRESSED): //continue (start game)
		setIsComputerTurn(game);
		// check if the game starts with mate/ tie
		memory->isTie = isTie(game);
		if (memory->isTie) {
			memory->isInitialEvent = 1;
			memory->pathOfBubbleToShow = TIE_BUBBLE;
		}
		int isWhiteOrBlackWin = initializedMate(game);// 1 white wins, 2 black wins
		if ( isWhiteOrBlackWin == 1 ) {
			memory->isMate = 1;
			memory->pathOfBubbleToShow = MATE_WHITE_WON_BUBBLE;
			memory->isInitialEvent = 1;
		}
		if ( isWhiteOrBlackWin == 2 ) {
			memory->isMate = 1;
			memory->pathOfBubbleToShow = MATE_BLACK_WON_BUUBLE;
			memory->isInitialEvent = 1;
		}

		return GAME_WINDOW; //Start game! (continue)
		break;
	case (THIRD_PRESSED): //cancel
		return WELCOME;
	case (NOTHING_HAPPANED):
		return TO_SET_BOARD;
	case (QUIT_EVENT):
		return QUIT_WINDOW;
	default:
		break;
	}
	return TO_SET_BOARD;
}

int handleEventGameWindow(Window* window, EventID eventID, Game* game,
		GUIMemory* memory) {
	if (memory->isInitialEvent) {
		memory->isScreenUpdated = 0;
		updateWindow(window, game, memory);
	}
	switch (eventID) {
	case (QUIT_EVENT):
		return QUIT_WINDOW;
	case (FIRST_PRESSED): //save game
		memory->commandType = SAVE;
		memory->isScreenUpdated = 0;
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
		return GAME_WINDOW;

	case (CHOSE_MINMAX_DEPTH):
		memory->isScreenUpdated = 0;
		return GAME_WINDOW;

	case (SOME_SLOT_CHOSEN):
		saveToSlot(game,memory->numOfSlotPressed);
		memory->commandType = NO_COMMAND;
		memory->isScreenUpdated = 0;
		return GAME_WINDOW;
	case (CHOSE_PIECE):
		if (game->isWhiteTurn) {
			switchChosenPieceToWhite(memory);
		}
		doMoveIJ(game, memory->oldI,memory->oldJ,memory->newI, memory->newJ,memory->pieceChosen );
		switchTurns(game);

		// check if a check / mate/ tie event
		int isCheckBubbleNeeded = isCheck(game);
		if  ( isCheckBubbleNeeded ) {
			memory->pathOfBubbleToShow = CHECK_BUUBLE_IMAGE;
		}
		memory->isTie = isTie(game);
		if (memory->isTie) {
			memory->pathOfBubbleToShow = TIE_BUBBLE;
		}

		int isMate = isCurrentPlayerLose(game);
		if ( isMate ) {
			memory->isMate = 1;
			if (game->isWhiteTurn) {
				memory->pathOfBubbleToShow = MATE_BLACK_WON_BUUBLE;
			} else {
				memory->pathOfBubbleToShow = MATE_WHITE_WON_BUBBLE;
			}
		}


		memory->commandType = NO_COMMAND;
		memory->pieceChosen = 'a';
		memory->isScreenUpdated = 0;
		return GAME_WINDOW;

	case (SOME_SQUARE_PRESSED):

		if (memory->commandType == NO_COMMAND) {
			// Player chose an empty square or an opponent square
			int whitePlayerChoosesWhite = (game->isWhiteTurn == 1 && getPieceColor(game,memory->newI,memory->newJ) == 1);
			int blackPlayerChoosesBlack = (game->isWhiteTurn == 0 && getPieceColor(game,memory->newI,memory->newJ) == 0);
			if ( !(whitePlayerChoosesWhite || blackPlayerChoosesBlack) ) {
				memory->isScreenUpdated = 0;
				return GAME_WINDOW;
			}
			// will paint yellow the soldier itself and it's possible moves
			memory->commandType = DO_MOVE;
			memory->isScreenUpdated = 0;
			return GAME_WINDOW;
		}
		else if (memory->commandType == DO_MOVE) {
			if (isValidMoveIJ(game,memory->oldI,memory->oldJ,memory->newI, memory->newJ)) {
				if (isPromotionMove(game, memory->oldI,memory->oldJ,memory->newI, memory->newJ)) {
					memory->commandType = CHOOSE_PROMOTION_AND_DO_MOVE;
					memory->isScreenUpdated = 0;
					return GAME_WINDOW;
					// will do move later
				}
				doMoveIJ(game, memory->oldI,memory->oldJ,memory->newI, memory->newJ,EMPTY );
				switchTurns(game);
				// check if a check / mate/ tie event
				int isCheckBubbleNeeded = isCheck(game);
				if  ( isCheckBubbleNeeded ) {
					memory->pathOfBubbleToShow = CHECK_BUUBLE_IMAGE;
				}
				memory->isTie = isTie(game);
				if (memory->isTie) {
					memory->pathOfBubbleToShow = TIE_BUBBLE;
				}

				int isMate = isCurrentPlayerLose(game);
				if ( isMate ) {
					memory->isMate = 1;
					if (game->isWhiteTurn) {
						memory->pathOfBubbleToShow = MATE_BLACK_WON_BUUBLE;
					} else {
						memory->pathOfBubbleToShow = MATE_WHITE_WON_BUBBLE;
					}
				}
			}
			memory->commandType = NO_COMMAND;
			memory->isScreenUpdated = 0;
			return GAME_WINDOW;
		}

		break;


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
	int isError;

	if (activeWindow->windowId == WELCOME) {
		isError = !updateWelcomeWindow(activeWindow, game, memory);
	}

	if (activeWindow->windowId == SET_BOARD) {
		isError = !updateSetBoard(activeWindow, game, memory);
	}

	if (activeWindow->windowId == TO_SET_BOARD) {
		return 1;
	}

	if (activeWindow->windowId == GAME_WINDOW) {
		isError = !updateGameBoard(activeWindow, game, memory);
	}

	if ( (SDL_Flip(activeWindow->screen) == -1) || isError ) {
		notifyFunctionFailure("updateWindow");
		return 0;
	}
	memory->isInitialEvent = 0;
	memory->isScreenUpdated = 1;

	return 1;
}

int updateWelcomeWindow(Window* activeWindow,Game* game, GUIMemory* memory) {

	if ( memory->commandType == CHOOSE_SLOT ) {
		Panel* panel = (Panel*) activeWindow->UITreeHead->child->child->widget;
			applySurface(panel->relevantArea.x, panel->relevantArea.y, panel->panelBackground,
					activeWindow->screen, NULL);
			// slots buttons
			drawButtons(activeWindow->UITreeHead->child->child->child->widget, activeWindow->screen);
			// continue button
			drawButtons(activeWindow->UITreeHead->child->child->child->child->widget, activeWindow->screen);
			if (memory->numOfSlotPressed != -1) {
				Buttons* slotsButtons = (Buttons*)activeWindow->UITreeHead->child->child->child->widget;
				Button* pressedButton = (slotsButtons)->buttonArray[memory->numOfSlotPressed];
				if (doesSlotContainFile(memory->numOfSlotPressed)) {
					applySurface(pressedButton->relevantArea.x, pressedButton->relevantArea.y, slotsButtons->buttonsImages, activeWindow->screen, &(slotsButtons->clipArray[memory->numOfSlotPressed+NUM_OF_SLOTS]));

				}
			}
	}
	else {
		// remove choose slot panel
		UITreeNode* backgroundNode =  activeWindow->UITreeHead;
		Background* background = (Background*)backgroundNode->widget;
		applySurface(0,0,background->image, activeWindow->screen,NULL);
		drawButtons(activeWindow->UITreeHead->child->widget, activeWindow->screen);
	}

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
	// redraw matrix by game
	Matrix* matrix = (Matrix*) activeWindow->UITreeHead->child->child->widget;
	updateMatrixByGame(matrix, game);
	// delete matrix yellow marks
	Panel* panel = (Panel*) activeWindow->UITreeHead->child->widget;
	applySurface(X_FOR_PANEL, Y_FOR_PANEL, panel->panelBackground,
			activeWindow->screen, NULL);
	drawMatrix(matrix, activeWindow->screen);

	// draw save game panel and buttons if needed
	if ( memory->commandType == SAVE ){
		UITreeNode* minmaxPanelNode = getMinmaxPanelNodeGameWindow(activeWindow->UITreeHead);
		UITreeNode* savePanelNode = minmaxPanelNode->child->child->child->child->child;
		Panel* savePanel = (Panel*) savePanelNode->widget;
		applySurface(savePanel->relevantArea.x, savePanel->relevantArea.y, savePanel->panelBackground,
				activeWindow->screen, NULL);
		drawButtons(savePanelNode->child->widget, activeWindow->screen);
	}

	// draw choose minmax depth panel if needed
	if ( (memory->commandType == GET_BEST_MOVE) && (memory->minmaxDepthChosen == 0) ){
			UITreeNode* mimaxPanelNode = getMinmaxPanelNodeGameWindow(activeWindow->UITreeHead);
			Panel* minmaxPanel = (Panel*) mimaxPanelNode->widget;
			applySurface(minmaxPanel->relevantArea.x, minmaxPanel->relevantArea.y, minmaxPanel->panelBackground,
					activeWindow->screen, NULL);
			drawButtons(mimaxPanelNode->child->widget, activeWindow->screen);
	}
	// draw promotion panel if needed
	if ( memory->commandType == CHOOSE_PROMOTION_AND_DO_MOVE ) {
		UITreeNode* piecesPanelNode = getMinmaxPanelNodeGameWindow(activeWindow->UITreeHead)->child->child;
		UITreeNode* blackPiecesButtonsNode = getMinmaxPanelNodeGameWindow(activeWindow->UITreeHead)->child->child->child;
		UITreeNode* whitePiecesButtonsNode = getMinmaxPanelNodeGameWindow(activeWindow->UITreeHead)->child->child->child->child;
		Panel* piecesPanel = (Panel*)piecesPanelNode->widget;
		Buttons* blackPiecesButtons = (Buttons*)blackPiecesButtonsNode->widget;
		Buttons* whitePiecesButtons = (Buttons*)whitePiecesButtonsNode->widget;
		applySurface(X_FOR_ADD_PANEL, Y_FOR_ADD_PANEL, piecesPanel->panelBackground,
				activeWindow->screen, NULL);
		if ( game->isWhiteTurn == 1 ) {
			drawButtons(whitePiecesButtons, activeWindow->screen);
		}
		else {
			drawButtons(blackPiecesButtons, activeWindow->screen);
		}
	}

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
	// draw matrix yellow marks if needed
	if (memory->commandType == DO_MOVE) {
		displayAllPossibleMoves(matrix,memory, game, activeWindow->screen);
	}

	if (memory->commandType == GET_BEST_MOVE && memory->minmaxDepthChosen != 0) {
		displayBestMove(matrix, memory, game, activeWindow->screen);
		memory->commandType = NO_COMMAND;
		memory->minmaxDepthChosen = 0;
	}

	if ( SDL_Flip(activeWindow->screen) == -1 ){
		notifyFunctionFailure("window's update function");
		return 0;
	}


	if ( memory->pathOfBubbleToShow != NULL ) {
		showBubble(memory, activeWindow->screen);
		memory->pathOfBubbleToShow = NULL;
		// redraw background when time is over
		Background* background = (Background*)activeWindow->UITreeHead->widget;
		applySurface(0,0,background->image, activeWindow->screen, NULL );
		//update buttons display
		Buttons* buttons =
				(Buttons*) activeWindow->UITreeHead->child->child->child->widget;
		for (int i = 0; i < buttons->numOfButtons; i++) {
			applySurface(SET_BOARD_MENU_X, SET_BOARD_MENU_Y + i * BUTTON_HEIGHT,
					buttons->buttonsImages, activeWindow->screen,
					&buttons->clipArray[i]);
		}
		// redraw matrix by game
		Matrix* matrix = (Matrix*) activeWindow->UITreeHead->child->child->widget;
		updateMatrixByGame(matrix, game);
		// delete matrix yellow marks
		Panel* panel = (Panel*) activeWindow->UITreeHead->child->widget;
		applySurface(X_FOR_PANEL, Y_FOR_PANEL, panel->panelBackground,
				activeWindow->screen, NULL);
		drawMatrix(matrix, activeWindow->screen);
		// redraw get best move button
		applySurface(GET_BEST_MOVE_BUTTON_X, GET_BEST_MOVE_BUTTON_Y,
					getBestMoveButton->buttonsImages, activeWindow->screen,
					&getBestMoveButton->clipArray[0]);

		if ( SDL_Flip(activeWindow->screen) == -1 ){
			notifyFunctionFailure("window's update function");
			return 0;
		}
	}
	return 1;
}


// helper functions

void displayAllPossibleMoves(Matrix* matrix,GUIMemory* memory, Game* game, SDL_Surface* screen) {

	for (int i=0; i<BOARD_SIZE; i++) {
		for (int j=0; j<BOARD_SIZE; j++) {
			Button* button = matrix->buttonsMatrix[getBoardJ(j)][i];
			if (isValidMoveIJ(game, memory->newI, memory->newJ, i, j )) {
				SDL_Rect clip;
				clip.x = 0;
				clip.y = 0;
				clip.w = BOARD_MATRIX_SQUARE_SIZE;
				clip.h = BOARD_MATRIX_SQUARE_SIZE;
				applySurface(button->relevantArea.x, button->relevantArea.y+1, matrix->highlightImage, screen, &clip);
			}
		}
	}
	if ( SDL_Flip(screen) == -1 ){
		notifyFunctionFailure("displayAllPossibleMoves function");
	}
}

void displayBestMove(Matrix* matrix,GUIMemory* memory, Game* game, SDL_Surface* screen) {
	SDL_Rect clip;
	clip.x = 0;
	clip.y = 0;
	clip.w = BOARD_MATRIX_SQUARE_SIZE;
	clip.h = BOARD_MATRIX_SQUARE_SIZE;

	Move* move = getBestMoveForUser(game);
	int i1 = getBestMoveI1(move);
	int j1 = getBestMoveJ1(move);
	int i2 = getBestMoveI2(move);
	int j2 = getBestMoveJ2(move);

	freeMove(move);

	Button* button1 = matrix->buttonsMatrix[getBoardJ(j1)][i1];
	Button* button2 = matrix->buttonsMatrix[getBoardJ(j2)][i2];
	applySurface(button1->relevantArea.x, button1->relevantArea.y+1, matrix->highlightImage, screen, &clip);
	applySurface(button2->relevantArea.x, button2->relevantArea.y+1, matrix->highlightImage, screen, &clip);

	if ( SDL_Flip(screen) == -1 ){
		notifyFunctionFailure("displayBestMove function");
	}
}

void switchChosenPieceToWhite(GUIMemory* memory) {
	if (memory->pieceChosen == BLACK_B)
		memory->pieceChosen = WHITE_B;
	if (memory->pieceChosen == BLACK_N)
		memory->pieceChosen = WHITE_N;
	if (memory->pieceChosen == BLACK_Q)
		memory->pieceChosen = WHITE_Q;
	if (memory->pieceChosen == BLACK_R)
		memory->pieceChosen = WHITE_R;
}

int isPromotionMove(Game* game, int i1, int j1, int i2, int j2) {
	Position position1;
	Position position2;

	position1.x = i1;
	position1.y = j1;
	position2.x = i2;
	position2.y = j2;

	int result = isSpecialPawnMove(game, &position1, &position2);

	return result;
}

void updateComputerTurnIfNeeded(Window* window, Game* game , GUIMemory* memory) {
	if (memory->isMate || memory->isTie) {
		return;
	}
	if ( (!game->isTwoPlayersMode) && game->isComputerTurn && !(memory->isMate) && !(memory->isTie)) {
		computerTurn(game);

		switchTurns(game);

		// check if a check / mate/ tie event
		int isCheckBubbleNeeded = isCheck(game);
		if  ( isCheckBubbleNeeded ) {
			memory->pathOfBubbleToShow = CHECK_BUUBLE_IMAGE;
		}
		memory->isTie = isTie(game);
		if (memory->isTie) {
			memory->pathOfBubbleToShow = TIE_BUBBLE;
		}

		int isMate = isCurrentPlayerLose(game);
		if ( isMate ) {
			memory->isMate = 1;
			if (game->isWhiteTurn) {
				memory->pathOfBubbleToShow = MATE_BLACK_WON_BUUBLE;
			} else {
				memory->pathOfBubbleToShow = MATE_WHITE_WON_BUBBLE;
			}
		}
		memory->isScreenUpdated = 0;
		updateGameBoard(window, game, memory);
	}
}
