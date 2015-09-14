#include "TranslateFunctions.h"

EventID translateEventGeneralSetup(Window* window, SDL_Event event,
		GUIMemory* memory) {

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

EventID translateEventSetDiffAndColor(Window* window, SDL_Event event,
		GUIMemory* memory) {

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
	UITreeNode* cancelContinueButtonsNode =
			window->UITreeHead->child->child->child;
	Buttons* cancelContinueButtons =
			((Buttons*) cancelContinueButtonsNode->widget);

	for (buttonNumber = 0; buttonNumber < cancelContinueButtons->numOfButtons;
			buttonNumber++) {
		Button* button = cancelContinueButtons->buttonArray[buttonNumber];
		if (button->isButtonPressed(button, event)) {
			if (buttonNumber == 0)
				return SEVENTH_PRESSED;
			if (buttonNumber == 1)
				return EIGHTH_PRESSED;
		}
	}
	return NOTHING_HAPPANED;
}

EventID translateEventSetBoard(Window* window, SDL_Event event,
		GUIMemory* memory) {
	if (event.type == SDL_QUIT) {
		return QUIT_EVENT;
	}

	if ((memory->commandType == ADD) && (memory->pressedSquarsNum == 0)) {
		Buttons* blackButtons =
				(Buttons*) window->UITreeHead->child->child->child->child->child->widget;
		Buttons* whiteButtons =
				(Buttons*) window->UITreeHead->child->child->child->child->child->child->widget;
		// TODO add cancel button

		for (int i = 0; i < blackButtons->numOfButtons; i++) {
			Button* blackButton = blackButtons->buttonArray[i];
			if (blackButton->isButtonPressed(blackButton, event)) {
				char chosenPiece;
				switch (i) {
				case 0:
					chosenPiece = BLACK_R;
					break;
				case 1:
					chosenPiece = BLACK_B;
					break;
				case 2:
					chosenPiece = BLACK_Q;
					break;
				case 3:
					chosenPiece = BLACK_K;
					break;
				case 4:
					chosenPiece = BLACK_N;
					break;
				case 5:
					chosenPiece = BLACK_P;
					break;
				default:
					chosenPiece = EMPTY;
					break;
				}
				memory->pieceChosen = chosenPiece;
				return CHOSE_PIECE;
			}
			Button* whiteButton = whiteButtons->buttonArray[i];
			if (whiteButton->isButtonPressed(whiteButton, event)) {
				char chosenPiece;

				switch (i) {
				case 0:
					chosenPiece = WHITE_R;
					break;
				case 1:
					chosenPiece = WHITE_B;
					break;
				case 2:
					chosenPiece = WHITE_Q;
					break;
				case 3:
					chosenPiece = WHITE_K;
					break;
				case 4:
					chosenPiece = WHITE_N;
					break;
				case 5:
					chosenPiece = WHITE_P;
					break;
				default:
					chosenPiece = EMPTY;
					break;
				}
				memory->pieceChosen = chosenPiece;
				return CHOSE_PIECE;
			}
		}
		// make sure there's nothing to do but choose piece
		return NOTHING_HAPPANED;
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			Matrix* matrix = (Matrix*) window->UITreeHead->child->child->widget;
			if (matrix->isIJPressed(event, matrix, i, j)) {
				printf("%d %d pressed!\n", i, j);
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

EventID translateEventGameWindow(Window* window, SDL_Event event,
		GUIMemory* memory) {
	if (event.type == SDL_QUIT) {
		return QUIT_EVENT;
	}


	if (memory->commandType == GET_BEST_MOVE
			&& memory->minmaxDepthChosen == 0) {
		Buttons* difficultyButtons = (Buttons*) (getMinmaxPanelNodeGameWindow(
				window->UITreeHead)->child->widget);
		// TODO add cancel button
		for (int i = 0; i < difficultyButtons->numOfButtons; i++) {
			Button* button = difficultyButtons->buttonArray[i];
			if (button->isButtonPressed(button, event)) {
				memory->minmaxDepthChosen = i + 1;
				return CHOSE_MINMAX_DEPTH;
			}
		}
		return NOTHING_HAPPANED;
	}

	if (memory->commandType == CHOOSE_PROMOTION_AND_DO_MOVE) {
		UITreeNode* blackPiecesButtonsNode = getMinmaxPanelNodeGameWindow(
				window->UITreeHead)->child->child->child;
		UITreeNode* whitePiecesButtonsNode = getMinmaxPanelNodeGameWindow(
				window->UITreeHead)->child->child->child->child;
		Buttons* blackPiecesButtons = (Buttons*) blackPiecesButtonsNode->widget;
		Buttons* whitePiecesButtons = (Buttons*) whitePiecesButtonsNode->widget;
		for (int i = 0; i < blackPiecesButtons->numOfButtons; i++) {
			Button* blackPieceButton = blackPiecesButtons->buttonArray[i];
			Button* whitePieceButton = whitePiecesButtons->buttonArray[i];
			if (blackPieceButton->isButtonPressed(blackPieceButton, event)
					|| whitePieceButton->isButtonPressed(whitePieceButton, event)) {
				char pieceChosen;
				if ( i==0 )
					pieceChosen = BLACK_R; // will later change it's color to white, if needed
				if ( i==1 )
					pieceChosen = BLACK_B;
				if ( i==2 )
					pieceChosen = BLACK_Q;
				if ( i==3 )
					pieceChosen = BLACK_N;
				memory->pieceChosen = pieceChosen;
				return CHOSE_PIECE;
			}
		}
		return NOTHING_HAPPANED;
	}


	// are buttons pressed
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

	if (memory->isMate || memory->isTie) {
		return NOTHING_HAPPANED;
	}

	// is matrix pressed
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			Matrix* matrix = (Matrix*) window->UITreeHead->child->child->widget;
			if (matrix->isIJPressed(event, matrix, i, j)) {
				memory->oldI = memory->newI;
				memory->oldJ = memory->newJ;
				memory->newI = i;
				memory->newJ = j;
				return SOME_SQUARE_PRESSED;
			}
		}
	}


	UITreeNode* getBestMovesbuttonsNode =
			window->UITreeHead->child->child->child->child;
	Buttons* getBestMoveButtons = ((Buttons*) getBestMovesbuttonsNode->widget);
	Button* getBestMoveButton = getBestMoveButtons->buttonArray[0];
	if (getBestMoveButton->isButtonPressed(getBestMoveButton, event)) {
		return FOURTH_PRESSED;
	}

	return NOTHING_HAPPANED;

}

