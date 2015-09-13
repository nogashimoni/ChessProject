#include "StartFunctions.h"

int startGeneralSetup(Window* window, Game* game) {

	// create background widget, which is Tree head, apply it to screen and add to UITree
	Background* background = createBackground(window->windowId);
	applySurface(0, 0, background->image, window->screen, NULL);
	window->UITreeHead = NULL;
	window->UITreeHead = createNode(background, BACKGROUND);
	if (window->UITreeHead == NULL) {
		//TODO
	}

	// create arguments for buttons creation
	SDL_Rect* clip = (SDL_Rect*) malloc(4 * sizeof(SDL_Rect));
	clipGeneralSetup(clip);
	int xForButtons = 0.5 * SCREEN_WIDTH - 0.5 * BUTTON_WIDTH;
	int yFirstButton = 0.5 * SCREEN_HEIGHT - 1.5 * BUTTON_HEIGHT - 30;
	SDL_Surface* buttonsImages = NULL;
	char* imagePath = getSpriteByWindowID(window->windowId);
	buttonsImages = loadImage(imagePath);
	if (buttonsImages == NULL)
		return 0; //TOODO
	Button** buttonsArray = createVerticalButtonsArrayAndApplyToScreen(3,
			xForButtons, yFirstButton, BUTTON_WIDTH, BUTTON_HEIGHT,
			buttonsImages, clip, 0, window->screen);

	// create buttons widget and add to UITree
	Buttons* buttons = createButtons(buttonsArray, buttonsImages, 3, clip);
	addChildNode(window->UITreeHead, buttons, BUTTONS);

	// Update what we see on screen
	if (SDL_Flip(window->screen) == -1) {
		printf("ERROR \n");
		return 0;
	}
	return 1;
}

int startSetDifficultyAndColor(Window* window, Game* game) {

	// create background widget, which is Tree head, apply it to screen and add to UITree
	Background* background = createBackground(window->windowId);
	applySurface(0, 0, background->image, window->screen, NULL);
	window->UITreeHead = NULL;
	window->UITreeHead = createNode(background, BACKGROUND);
	if (window->UITreeHead == NULL) {
		//TODO
	}

	// create arguments for difficulty buttons creation
	SDL_Rect* difficultyClip = (SDL_Rect*) malloc(4 * sizeof(SDL_Rect));
	clipDifficulty(difficultyClip);
	int xFirstButton = AI_SETTINGS_BUTTONS_X;
	int yForButtons = AI_SETTINGS_BUTTONS_FIRST_Y;
	SDL_Surface* difficultyButtonsImage = NULL;
	difficultyButtonsImage = loadImage(DIFFICULTY_SPRITE);
	if (difficultyButtonsImage == NULL)
		return 0; //TOODO
	Button** buttonsArrayDifficulty =
			createHorizontalButtonsArrayAndApplyToScreen(4, xFirstButton,
					yForButtons, SIZE_OF_DIFFICULTY_SQUARE,
					difficultyButtonsImage, difficultyClip, 0, window->screen, 1);
	// create buttons widget and add to UITree
	Buttons* difficultyButtons = createButtons(buttonsArrayDifficulty,
			difficultyButtonsImage, 4, difficultyClip);
	appendChild(window->UITreeHead, difficultyButtons, BUTTONS);

	// create arguments for user color buttons creation
	SDL_Rect* userColorClip = (SDL_Rect*) malloc(2 * sizeof(SDL_Rect));
	clipUserColor(userColorClip);
	int yForColorButtons = AI_SETTINGS_BUTTONS_FIRST_Y
			+ SIZE_OF_DIFFICULTY_SQUARE;
	SDL_Surface* buttonsImageColor = NULL;
	buttonsImageColor = loadImage(USER_COLOR_SPRITE);
	if (buttonsImageColor == NULL)
		return 0; //TOODO
	Button** buttonsArrayColor = createHorizontalButtonsArrayAndApplyToScreen(
			2, xFirstButton, yForColorButtons, WIDTH_OF_COLOR_BUTTON,
			buttonsImageColor, userColorClip, 0, window->screen, 1);
	// create buttons widget and add to UITree
	Buttons* colorButtons = createButtons(buttonsArrayColor, buttonsImageColor,
			2, userColorClip);
	appendChild(window->UITreeHead, colorButtons, BUTTONS);

	// create arguments for cancel and continue buttons
	SDL_Rect* cancelContinueClip = (SDL_Rect*) malloc(2 * sizeof(SDL_Rect));
	clipCancelContinue(cancelContinueClip);
	int yForCancelButtons = AI_SETTINGS_BUTTONS_FIRST_Y
			+ 2 * SIZE_OF_DIFFICULTY_SQUARE;
	SDL_Surface* buttonsImageCancelContinue = NULL;
	buttonsImageCancelContinue = loadImage(CANCEL_CONTINUE_SPRITE);
	if (buttonsImageCancelContinue == NULL)
		return 0; //TOODO
	Button** buttonsArray = createVerticalButtonsArrayAndApplyToScreen(2,
			xFirstButton, yForCancelButtons, 2 * WIDTH_OF_COLOR_BUTTON,
			SIZE_OF_DIFFICULTY_SQUARE, buttonsImageCancelContinue,
			cancelContinueClip, 0, window->screen);

	// create buttons widget and add to UITree
	Buttons* cancelContinueButtons = createButtons(buttonsArray,
			buttonsImageCancelContinue, 2, cancelContinueClip);
	appendChild(window->UITreeHead, cancelContinueButtons, BUTTONS);

	// Update what we see on screen
	if (SDL_Flip(window->screen) == -1) {
		printf("ERROR \n");
		return 0;
	}
	return 1;
}

int startSetBoard(Window* window, Game* game) {

	// create background widget, which is Tree head, apply it to screen and add to UITree
	Background* background = createBackground(window->windowId);
	applySurface(0, 0, background->image, window->screen, NULL);
	window->UITreeHead = NULL;
	window->UITreeHead = createNode(background, BACKGROUND);
	if (window->UITreeHead == NULL) {
		//TODO
	}

	// create panel (containing the game matrix)
	SDL_Rect box = { X_FOR_PANEL, Y_FOR_PANEL, PANEL_WIDTH, PANEL_HEIGHT };
	Panel* panel = createPanel(box, BOARD_PANEL_BACKGROUND);
	appendChild(window->UITreeHead, panel, PANEL);
	applySurface(X_FOR_PANEL, Y_FOR_PANEL, panel->panelBackground,
			window->screen, NULL);

	// create matrix
	SDL_Rect* clip = (SDL_Rect*) malloc(sizeof(SDL_Rect) * 12);
	clipPeices(clip);
	Matrix* matrix = createChessBoardMatrix(panel, clip, game);
	appendChild(window->UITreeHead, matrix, MATRIX);
	drawMatrix(matrix, window->screen);

	// create buttons
	int xForGameButtons = SET_BOARD_MENU_X;
	int yFirstButtonGame = SET_BOARD_MENU_Y;
	SDL_Rect* menuClip = (SDL_Rect*) malloc(sizeof(SDL_Rect) * 9);
	clipSetBoard(menuClip);
	SDL_Surface* buttonsImages = NULL;
	buttonsImages = loadImage(SET_BOARD_BUTTONS_SPRITE);
	if (buttonsImages == NULL)
		return 0; //TOODO
	Button** buttonsArray = createVerticalButtonsArrayAndApplyToScreen(6,
			xForGameButtons, yFirstButtonGame, BUTTON_WIDTH, BUTTON_HEIGHT,
			buttonsImages, menuClip, 0, window->screen);
	// create buttons widget and add to UITree
	Buttons* buttons = createButtons(buttonsArray, buttonsImages, 6, menuClip);
	appendChild(window->UITreeHead, buttons, BUTTONS);

	// create panel for add panel - we will only show it later
	SDL_Rect box2 = { X_FOR_ADD_PANEL, Y_FOR_ADD_PANEL, ADD_PANEL_WIDTH, ADD_PANEL_HEIGHT };
	Panel* panel2 = createPanel(box2, CHOOSE_PIECE_PANEL_BACKGROUND);
	appendChild(window->UITreeHead, panel2, PANEL);


	// create buttons for add panel - we will only show it later
	SDL_Rect* blackPiecesClip = (SDL_Rect*) malloc(sizeof(SDL_Rect) * 6);
	clipSixPeices(blackPiecesClip, 0);
	SDL_Surface* blackButtonsImage = NULL;
	blackButtonsImage = loadImage(PIECES_SPRITE);
	if (blackButtonsImage == NULL)
		return 0; //TODO
	// we call the next function with a flag saying not to apply on screen
	Button** blackPeicesButtonsArray = createHorizontalButtonsArrayAndApplyToScreen(6,
			FIRST_X_FOR_PEICES_ON_PANEL, FIRST_Y_FOR_PEICES_ON_PANEL, BOARD_MATRIX_SQUARE_SIZE,
			blackButtonsImage, blackPiecesClip, 0, window->screen, 0);
	// create buttons widget and add to UITree
	Buttons* peicesButtons = createButtons(blackPeicesButtonsArray, blackButtonsImage, 6, blackPiecesClip);
	appendChild(window->UITreeHead, peicesButtons, BUTTONS);

	SDL_Rect* whitePiecesClip = (SDL_Rect*) malloc(sizeof(SDL_Rect) * 6);
	clipSixPeices(whitePiecesClip, 1);
	SDL_Surface* whiteButtonsImage = NULL;
	whiteButtonsImage = loadImage(PIECES_SPRITE);
	if (whiteButtonsImage == NULL)
		return 0; //TOODO
	// we call the next function with a flag saying not to apply on screen
	Button** whitePeicesButtonsArray = createHorizontalButtonsArrayAndApplyToScreen(6,
			FIRST_X_FOR_PEICES_ON_PANEL, BOARD_MATRIX_SQUARE_SIZE +FIRST_Y_FOR_PEICES_ON_PANEL, BOARD_MATRIX_SQUARE_SIZE,
			whiteButtonsImage, whitePiecesClip, 0, window->screen, 0);
	// create buttons widget and add to UITree
	Buttons* whitePeicesButtons = createButtons(whitePeicesButtonsArray, whiteButtonsImage, 6, whitePiecesClip);
	appendChild(window->UITreeHead, whitePeicesButtons, BUTTONS);

	SDL_Flip(window->screen);
	return 1;
}

int startGameWindow(Window* window, Game* game) {

	// create background widget, which is Tree head, apply it to screen and add to UITree
	Background* background = createBackground(window->windowId);
	applySurface(0, 0, background->image, window->screen, NULL);
	window->UITreeHead = NULL;
	window->UITreeHead = createNode(background, BACKGROUND);
	if (window->UITreeHead == NULL) {
		//TODO
	}

	// create panel (containing the game matrix)
	SDL_Rect box = { X_FOR_PANEL, Y_FOR_PANEL, PANEL_WIDTH, PANEL_HEIGHT };
	Panel* panel = createPanel(box, BOARD_PANEL_BACKGROUND);
	appendChild(window->UITreeHead, panel, PANEL);
	applySurface(X_FOR_PANEL, Y_FOR_PANEL, panel->panelBackground,
			window->screen, NULL);

	// create matrix
	SDL_Rect* clip = (SDL_Rect*) malloc(sizeof(SDL_Rect) * 12);
	clipPeices(clip);
	Matrix* matrix = createChessBoardMatrix(panel, clip, game);
	appendChild(window->UITreeHead, matrix, MATRIX);
	drawMatrix(matrix, window->screen);

	// create buttons
	int xForGameButtons = SET_BOARD_MENU_X;
	int yFirstButtonGame = SET_BOARD_MENU_Y;
	SDL_Rect* gameMenuClip = (SDL_Rect*) malloc(sizeof(SDL_Rect) * 3);
	clipGeneralSetup(gameMenuClip);
	SDL_Surface* menuButtonsImage = NULL;
	menuButtonsImage = loadImage(GAME_MENU_BUTTONS_SPRITE);
	if (menuButtonsImage == NULL)
		return 0; //TODO
	Button** buttonsArray = createVerticalButtonsArrayAndApplyToScreen(3,
			xForGameButtons, yFirstButtonGame, BUTTON_WIDTH, BUTTON_HEIGHT,
			menuButtonsImage, gameMenuClip, 0, window->screen);
	Buttons* buttons = createButtons(buttonsArray, menuButtonsImage, 3, gameMenuClip);
	appendChild(window->UITreeHead, buttons, BUTTONS);

	// crate get best move button (as a buttons widget)
	int xForBestMoveButton = GET_BEST_MOVE_BUTTON_X;
	int yForBestMoveButton = GET_BEST_MOVE_BUTTON_Y;
	SDL_Rect* bestMovelip = (SDL_Rect*) malloc(sizeof(SDL_Rect) * 2);
	clipBestMove(bestMovelip);
	SDL_Surface* bestMoveImage = NULL;
	bestMoveImage = loadImage(GET_BEST_MOVE_SPRITE);
	if (bestMoveImage == NULL)
		return 0; //TODO
	Button** bestMoveButtonsArray = createVerticalButtonsArrayAndApplyToScreen(1,
			xForBestMoveButton, yForBestMoveButton, BUTTON_WIDTH, BUTTON_HEIGHT,
			bestMoveImage, bestMovelip, 0, window->screen);
	Buttons* bestMovesButtons = createButtons(bestMoveButtonsArray, bestMoveImage, 1, bestMovelip);
	appendChild(window->UITreeHead, bestMovesButtons, BUTTONS);


	// create panel for choose minmax depth - we will only show it later
	SDL_Rect minMaxBox = { X_FOR_ADD_PANEL, Y_FOR_ADD_PANEL, ADD_PANEL_WIDTH, ADD_PANEL_HEIGHT };
	Panel* minMaxPanel = createPanel(minMaxBox, CHOOSE_DIFFICULTY_PANEL_BACKGROUND);
	appendChild(window->UITreeHead, minMaxPanel, PANEL);


	// create buttons for choose minmax depth - we will only show it later
	SDL_Rect* difficaltyClip = (SDL_Rect*) malloc(sizeof(SDL_Rect) * 4);
	clipDifficulty(difficaltyClip);
	SDL_Surface* difficultyImage = NULL;
	difficultyImage = loadImage(DIFFICULTY_SPRITE);
	if (difficultyImage == NULL)
		return 0; //TOODO
	// we call the next function with a flag saying not to apply on screen
	Button** difficultyButtonsArray = createHorizontalButtonsArrayAndApplyToScreen(4,
				FIRST_X_FOR_DIFFICULTY_ON_PANEL, Y_FOR_DIFFICULTY_ON_PANEL, SIZE_OF_DIFFICULTY_SQUARE,
				difficultyImage, difficaltyClip, 0, window->screen, 0);
	Buttons* difficultyButtons = createButtons(difficultyButtonsArray, difficultyImage, 4, difficaltyClip);
	appendChild(window->UITreeHead, difficultyButtons, BUTTONS);


	// create panel for promotion - we will only show it later
	SDL_Rect promotionBox = { X_FOR_ADD_PANEL, Y_FOR_ADD_PANEL, ADD_PANEL_WIDTH, ADD_PANEL_HEIGHT };
	Panel* promotionPanel = createPanel(promotionBox, CHOOSE_PIECE_PANEL_BACKGROUND);
	appendChild(window->UITreeHead, promotionPanel, PANEL);
	// create buttons for promotion panel - we will only show it later
	// black buttons
	SDL_Rect* blackPiecesClip = (SDL_Rect*) malloc(sizeof(SDL_Rect) * 4);
	clipPromotionPeices(blackPiecesClip, 0);
	SDL_Surface* blackButtonsImage = NULL;
	blackButtonsImage = loadImage(PIECES_SPRITE);
	if (blackButtonsImage == NULL)
		return 0; //TODO
	// we call the next function with a flag saying not to apply on screen
	Button** blackPeicesButtonsArray = createHorizontalButtonsArrayAndApplyToScreen(4,
			FIRST_X_FOR_PEICES_ON_PANEL+20, FIRST_Y_FOR_PEICES_ON_PANEL+BOARD_MATRIX_SQUARE_SIZE/2, BOARD_MATRIX_SQUARE_SIZE,
			blackButtonsImage, blackPiecesClip, 0, window->screen, 0);
	Buttons* blackPeicesButtons = createButtons(blackPeicesButtonsArray, blackButtonsImage, 4, blackPiecesClip);
	appendChild(window->UITreeHead, blackPeicesButtons, BUTTONS);
	// white buttons
	SDL_Rect* whitePiecesClip = (SDL_Rect*) malloc(sizeof(SDL_Rect) * 4);
	clipPromotionPeices(whitePiecesClip, 1);
	SDL_Surface* whiteButtonsImage = NULL;
	whiteButtonsImage = loadImage(PIECES_SPRITE);
	if (whiteButtonsImage == NULL)
		return 0; //TODO
		// we call the next function with a flag saying not to apply on screen
	Button** whitePeicesButtonsArray = createHorizontalButtonsArrayAndApplyToScreen(4,
			FIRST_X_FOR_PEICES_ON_PANEL+20, FIRST_Y_FOR_PEICES_ON_PANEL+BOARD_MATRIX_SQUARE_SIZE/2, BOARD_MATRIX_SQUARE_SIZE,
			whiteButtonsImage, whitePiecesClip, 0, window->screen, 0);
	Buttons* whitePeicesButtons = createButtons(whitePeicesButtonsArray, whiteButtonsImage, 4, whitePiecesClip);
	appendChild(window->UITreeHead, whitePeicesButtons, BUTTONS);

	SDL_Flip(window->screen);
	return 1;


}



void clipBestMove(SDL_Rect* clip) {
	for (int i=0; i<2; i++) {
		clip[i].x = i*BUTTON_WIDTH;
		clip[i].y = 0;
		clip[i].w = BUTTON_WIDTH;
		clip[i].h = BUTTON_HEIGHT;
	}
}

void clipGeneralSetup(SDL_Rect* clip) {
	//Clip range for the top left
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = 220;
	clip[0].h = 50;

	//Clip range for the top right
	clip[1].x = 0;
	clip[1].y = 50;
	clip[1].w = 220;
	clip[1].h = 50;

	//Clip range for the bottom left
	clip[2].x = 0;
	clip[2].y = 100;
	clip[2].w = 220;
	clip[2].h = 50;

}

void clipPeices(SDL_Rect* clip) {
	//Clip range for the top left
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			clip[i * 6 + j].x = j * BOARD_MATRIX_SQUARE_SIZE;
			clip[i * 6 + j].y = i * BOARD_MATRIX_SQUARE_SIZE;
			clip[i * 6 + j].w = BOARD_MATRIX_SQUARE_SIZE;
			clip[i * 6 + j].h = BOARD_MATRIX_SQUARE_SIZE;

		}
	}
}

void clipSixPeices(SDL_Rect* clip, int isWhitePieces) {
	int toAddToY = 0;
	if  ( isWhitePieces )
		toAddToY = BOARD_MATRIX_SQUARE_SIZE;
	for (int i = 0; i<6; i++) {
		clip[i].x = i*BOARD_MATRIX_SQUARE_SIZE;
		clip[i].y = toAddToY;
		clip[i].w = BOARD_MATRIX_SQUARE_SIZE;
		clip[i].h = BOARD_MATRIX_SQUARE_SIZE;
	}
}

void clipPromotionPeices(SDL_Rect* clip, int isWhitePieces) {
	int toAddToY = 0;
	if  ( isWhitePieces )
		toAddToY = BOARD_MATRIX_SQUARE_SIZE;
	for (int i = 0; i<3; i++) {
		clip[i].x = i*BOARD_MATRIX_SQUARE_SIZE;
		clip[i].y = toAddToY;
		clip[i].w = BOARD_MATRIX_SQUARE_SIZE;
		clip[i].h = BOARD_MATRIX_SQUARE_SIZE;
	}
	clip[3].x = 4*BOARD_MATRIX_SQUARE_SIZE;
	clip[3].y = toAddToY;
	clip[3].w = BOARD_MATRIX_SQUARE_SIZE;
	clip[3].h = BOARD_MATRIX_SQUARE_SIZE;
}

void clipDifficulty(SDL_Rect* clip) {
	for (int i = 0; i < 4; i++) {
		clip[i].x = i * SIZE_OF_DIFFICULTY_SQUARE;
		clip[i].y = 0;
		clip[i].w = SIZE_OF_DIFFICULTY_SQUARE;
		clip[i].h = SIZE_OF_DIFFICULTY_SQUARE;
	}
}

void clipCancelContinue(SDL_Rect* clip) {
	for (int i = 0; i < 2; i++) {
		clip[i].x = 0;
		clip[i].y = i * SIZE_OF_DIFFICULTY_SQUARE;
		clip[i].w = 2 * WIDTH_OF_COLOR_BUTTON;
		clip[i].h = SIZE_OF_DIFFICULTY_SQUARE;
	}
}

void clipSetBoard(SDL_Rect* clip) {
	/** colored squares will be last **/
	int i;
	for (i = 0; i < 6; i++) {
		clip[i].x = 0;
		clip[i].y = i * BUTTON_HEIGHT;
		clip[i].w = BUTTON_WIDTH;
		clip[i].h = BUTTON_HEIGHT;
	}
	for (int j = 0; j < 3; j++) {
		clip[i + j].x = BUTTON_WIDTH;
		clip[i + j].y = j * BUTTON_HEIGHT;
		clip[i + j].w = BUTTON_WIDTH;
		clip[i + j].h = BUTTON_HEIGHT;
	}
}
void clipUserColor(SDL_Rect* clip) {
	for (int i = 0; i < 2; i++) {
		clip[i].x = 0;
		clip[i].y = i * HEIGHT_OF_COLOR_BUTTON;
		clip[i].w = WIDTH_OF_COLOR_BUTTON;
		clip[i].h = HEIGHT_OF_COLOR_BUTTON;
	}
}


char* getSpriteByWindowID(WindowId windowID) {
	switch (windowID) {
	case (WELCOME):
		return WELCOME_SPRITE;
	case (PLAYER_SELECTION):
		return PLAYER_SELECTION_SPRITE;
	case (TO_SET_WHO_STARTS):
		return TO_SET_WHO_STARTS_SPRITE;
	case (SET_WHO_STARTS):
		return SET_WHO_STARTS_SPRITE;
	case (TO_SET_BOARD):
		return TO_SET_BOARD_SPRITE;
	default:
		break;
	}
	return PLAYER_SELECTION_SPRITE;
}
