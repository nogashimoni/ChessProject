#include "GUIUtils.h"


Button** createVerticalButtonsArrayAndApplyToScreen(int numOfButtons,
		int xForButtons, int yFirstButton, int weidth, int height, SDL_Surface* buttonsImages,
		SDL_Rect* clipArray, int relevantFirstClipIndex, SDL_Surface* screen) {
	/** For general setup screens **/

	Button** buttons = (Button**) malloc(sizeof(Button*) * numOfButtons);
	int i;
	for (i = 0; i < numOfButtons; i++) {
		Button* button = NULL;
		SDL_Rect box = { xForButtons, yFirstButton + i * height,
				weidth, height };
		button = createButton(box);
		applySurface(xForButtons, yFirstButton + i * height,
				buttonsImages, screen, &clipArray[i]);

		if (button == NULL) {
			//quitGUI(); TODO
		}
		buttons[i] = button;
	}
	return buttons;
}



Button** createHorizontalButtonsArrayAndApplyToScreen(int numOfButtons,
		int xFirsButton, int yForButtons, int buttonWidth, SDL_Surface* buttonsImage,
		SDL_Rect* clipArray, int relevantFirstClipIndex, SDL_Surface* screen, int toApply) {
	/** For difficulty screen **/

	Button** buttons = (Button**) malloc(sizeof(Button*) * numOfButtons);
	int i;
	for (i = 0; i < numOfButtons; i++) {
		Button* button = NULL;
		SDL_Rect box = { xFirsButton + i*buttonWidth, yForButtons, buttonWidth, HEIGHT_OF_COLOR_BUTTON };
		button = createButton(box); //should the relevantArea also be alloced?
		if ( toApply ) {
			applySurface(xFirsButton + i*buttonWidth, yForButtons, buttonsImage, screen, &clipArray[i]);
		}
		if (button == NULL) {
				//quitGUI(); TODO
		}
		buttons[i] = button;
	}
	return buttons;
}

void drawButtons(Buttons* buttons, SDL_Surface* screen) {
	for (int i=0; i<buttons->numOfButtons; i++) {
		int x = buttons->buttonArray[i]->relevantArea.x;
		int y = buttons->buttonArray[i]->relevantArea.y;
		applySurface(x,y,buttons->buttonsImages, screen, &buttons->clipArray[i]);
	}
}

SDL_Surface* loadImage(char* imagePath) {
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;
	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load(imagePath); //IMG_Load( imagePath );
	//If nothing went wrong in loading the image
	if (loadedImage != NULL) {
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);
		Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0, 0xFF );
		SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
		//Free the old image
		SDL_FreeSurface(loadedImage);
	} else {
		return loadedImage; // returns NULL
	}
	//TODO make image transparent
	//Return the optimized image
	return optimizedImage;
}

void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination,
		SDL_Rect* clip) {
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface(source, clip, destination, &offset);
	//Update Screen? outside..

}

Background* createBackground(WindowId windowID) {
	// open background (which will be the tree root)
	Background* background = NULL;
	background = (Background*) malloc(sizeof(background));
	if (background == NULL) {
		//TODO
		printf("error loading background");
		exit(0);
	}
	char* imagePath;
	switch (windowID) {
	case (WELCOME):
		imagePath = WELCOME_BACKGROUND;
		break;
	case (PLAYER_SELECTION):
		imagePath = PLAYER_SELECTION_BACKGROUND;
		break;
	case (SET_DIFFICULTY_AND_COLOR):
		imagePath = SET_DIFFICULTY_AND_COLOR_BACKGROUND;
		break;
	case (TO_SET_WHO_STARTS):
		imagePath = TO_SET_WHO_STARTS_BACKGROUND;
		break;
	case (TO_SET_BOARD):
		imagePath = TO_SET_BOARD_BACKGROUND;
		break;
	case (SET_BOARD):
		imagePath = SET_BOARD_BACKGROUND;
		break;
	case (SET_WHO_STARTS):
		imagePath = SET_WHO_STARTS_BACKGROUND;
		break;
	case (GAME_WINDOW):
		imagePath = SET_BOARD_BACKGROUND;
		break;
	case (QUIT_WINDOW):
		break;
	}

	background->image = loadImage(imagePath);
	if (background->image == NULL) {
		//TODO
	}
	return background;
}


void showBubble(GUIMemory* memory, SDL_Surface* screen) {
	if ( memory-> pathOfBubbleToShow == NULL ) {
		return;
	}
	SDL_Surface* image = loadImage(memory->pathOfBubbleToShow);
	applySurface(BUBBLE_X, BUBBLE_Y, image, screen, NULL);
	SDL_Flip(screen);
	SDL_Delay(BUBBLE_TIME);
	memory->pathOfBubbleToShow = NULL;
	SDL_FreeSurface(image);
}

Panel* createPanel(SDL_Rect relevantArea, char* backgroundPath) {
	Panel* panel = NULL;

	panel = (Panel*) malloc(sizeof(Panel));
	if (panel == NULL) {
		//TODO standardFunctionFailure("malloc"); /* exit unavoidable */
		return NULL;
	}
	panel->widgetType = PANEL;
	panel->relevantArea = relevantArea;
	panel->panelBackground = loadImage(backgroundPath);
	if (panel->panelBackground == NULL) {
		//TODO
	}
	panel->applyOnPanel = applyOnPanel;
	return panel;

}

void applyOnPanel(SDL_Surface* screen, Panel* panel, SDL_Surface* whatToApply,
		int relativeX, int relativeY) {
}

Button* createButton(SDL_Rect relevantArea) {
	Button* button = NULL;

	button = (Button*) malloc(sizeof(Button));
	if (button == NULL) {
		//TODO standardFunctionFailure("malloc"); /* exit unavoidable */
		return NULL;
	}
	button->clip = NULL;
	button->relevantArea = relevantArea;
	button->isButtonPressed = isButtonPressed;
	return button;
}

Button*** createButtonsForMatrix(int matrixTopLeftX, int matrixTopLeftY,
		int squareSize, int n, int m) {
	Button*** buttons = (Button***) malloc(sizeof(Button**) * n);
	for (int i = 0; i < n; i++) {
		buttons[i] = (Button**) malloc(sizeof(Button*) * n);
		for (int j = 0; j < n; j++) {
			SDL_Rect box = { matrixTopLeftX + j * squareSize, matrixTopLeftY
					+ i * squareSize, squareSize, squareSize };
			Button* button = createButton(box);
			buttons[i][j] = button;
		}
	}
	return buttons;
}

Matrix* createChessBoardMatrix(Panel* fatherPanel, SDL_Rect* clip, Game* game) {
	Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));
	matrix->buttonsMatrix = createButtonsForMatrix(BOARD_MATRIX_TOP_LEFT_X,
			BOARD_MATRIX_TOP_LEFT_Y, BOARD_MATRIX_SQUARE_SIZE, BOARD_SIZE,
			BOARD_SIZE);
	matrix->piecesClipArray = clip;
	matrix->piecesImages = loadImage(PIECES_SPRITE);
	matrix->highlightImage = loadImage(HIGHLIGHT_CELL);
	matrix->m = BOARD_SIZE;
	matrix->n = BOARD_SIZE;
//	matrix->drawIJ
	matrix->isIJPressed = isIJPressed;

	updateMatrixByGame(matrix, game);

//	matrix->fatherPanel
//	int (*drawIJ)(Panel* panel, Matrix* matrix, PieceID PIECEType, int i, int j);
	return matrix;
}

void updateMatrixByGame(Matrix* matrix, Game* game) {
	for (int i=0; i<BOARD_SIZE; i++ ) {
		for (int j=0; j<BOARD_SIZE; j++ ) {
			((matrix->buttonsMatrix)[i][j])->pieceToDraw = game->board[j][getBoardJ(i)];
		}
	}
}

void drawMatrix(Matrix* matrix, SDL_Surface* screen) {
	for (int i=0; i<BOARD_SIZE; i++ ) {
		for (int j=0; j<BOARD_SIZE; j++ ) {
			char pieceChar = (matrix->buttonsMatrix[i][j])->pieceToDraw;
			SDL_Rect* relevantClip;
			switch (pieceChar){
				case ('m'):
					relevantClip = &matrix->piecesClipArray[11];
					break;
				case ('b'):
					relevantClip = &matrix->piecesClipArray[7];
					break;
				case ('n'):
					relevantClip = &matrix->piecesClipArray[10];
					break;
				case ('r'):
					relevantClip = &matrix->piecesClipArray[6];
					break;
				case ('q'):
					relevantClip = &matrix->piecesClipArray[8];
					break;
				case ('k'):
					relevantClip = &matrix->piecesClipArray[9];
					break;
				case ('M'):
					relevantClip = &matrix->piecesClipArray[5];
					break;
				case ('B'):
					relevantClip = &matrix->piecesClipArray[1];
					break;
				case ('N'):
					relevantClip = &matrix->piecesClipArray[4];
					break;
				case ('R'):
					relevantClip = &matrix->piecesClipArray[0];
					break;
				case ('Q'):
					relevantClip = &matrix->piecesClipArray[2];
					break;
				case ('K'):
					relevantClip = &matrix->piecesClipArray[3];
					break;
				case (' '):
					relevantClip = NULL;
					break;
			}
			if ( relevantClip != NULL ) {
				applySurface(matrix->buttonsMatrix[i][j]->relevantArea.x,matrix->buttonsMatrix[i][j]->relevantArea.y,matrix->piecesImages,screen,relevantClip);
				SDL_Flip(screen);
			}
		}
	}
}

int getBoardJ(int j) {
	/** translates from game point of view 'i' to board point of view 'i'. 0,1 ->  **/
	return BOARD_SIZE-j-1;
}

int getBoardI(int i) {
	return i;
}

int isIJPressed(SDL_Event event, Matrix* matrix, int i, int j) {
	if ( i> matrix->n || j> matrix -> m)
		return 0;
	return matrix->buttonsMatrix[0][0]->isButtonPressed(matrix->buttonsMatrix[BOARD_SIZE-1-j][i], event);
}

Buttons* createButtons(Button** buttonsArray, SDL_Surface* image,
		int numOfButtons, SDL_Rect* clip) {
	Buttons* buttons = NULL;

	buttons = (Buttons*) malloc(sizeof(Buttons));
	if (buttons == NULL) {
		//TODO standardFunctionFailure("malloc"); /* exit unavoidable */
		return NULL;
	}
	buttons->widgetType = BUTTONS;
	buttons->buttonArray = buttonsArray;
	buttons->buttonsImages = image;
	buttons->numOfButtons = numOfButtons;
	buttons->clipArray = clip;

	return buttons;
}

int isButtonPressed(Button *button, SDL_Event sdlEvent) {
	int xOfEvent, yOfEvent;

	if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
		/* If the left mouse button was pressed */
		if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
			/* Get the mouse offsets */
			xOfEvent = sdlEvent.button.x;
			yOfEvent = sdlEvent.button.y;
			/* If the mouse is over the button */
			if (isXYInRelevantArea(button, xOfEvent, yOfEvent)) {
				return 1;
			}
		}
	}

	return 0;
}

int isXYInRelevantArea(Button *button, int x, int y) {
	return (x > button->relevantArea.x)
			&& (x < button->relevantArea.x + button->relevantArea.w)
			&& (y > button->relevantArea.y)
			&& (y < button->relevantArea.y + button->relevantArea.h);
}

// draw functions
void drawGUI(Window* window) {
	SDL_Surface* screen = window->screen;
	int dfsRes = treeDFS(window->UITreeHead, NULL, drawNode, screen);
	if (dfsRes == -1)
		return;

	if (SDL_Flip(window->screen) != 0) {
		// todo print error
		return;
	}
}

int drawNode(UITreeNode* UITreeNode, SDL_Surface* screen) {
	void* widget = UITreeNode->widget;
	switch (UITreeNode->widgetType) {
	case (PANEL):
		applySurface(((Panel*) widget)->relevantArea.x,
				((Panel*) widget)->relevantArea.y,
				((Panel*) widget)->panelBackground, screen, NULL);
		break;
//		case(MATRIX):
//			drawMatrix();
	case (BACKGROUND):
		applySurface(0, 0, ((Background*) widget)->image, screen, NULL);
		break;
	}
	return 1;
}

// Tree utilities

UITreeNode* createNode(void* widget, TreeWidgetType widgetType) {
	UITreeNode* newNode = (UITreeNode*) malloc(sizeof(UITreeNode));
	if (newNode == NULL) {
//		perrorPrint("malloc"); TODO
		return NULL;
	}

	newNode->widget = widget;
	newNode->widgetType = widgetType;

	newNode->next = NULL;
	newNode->child = NULL;
	newNode->parent = NULL;

	return newNode;
}

UITreeNode* appendChild(UITreeNode* list, void* widget, TreeWidgetType widgetType) {
	if (widget == NULL) {
		return list;
	}

	UITreeNode* appendedNode = createNode(widget, widgetType); /* create a new list node */
	if (appendedNode == NULL) {
		return NULL;
	}

	while (list->child != NULL) { /* while last node not reached */
		list = list->child; /* advance to the next node */
	}
	list->child = appendedNode; /* append the node at the end of the list */
	appendedNode->parent =list;
	return appendedNode; /* return the node appended */
}


/*
 * adds a new child to a listNode, at the end of the child list, and return it
 */
UITreeNode* addChildNode(UITreeNode* parent, void * widget,
		TreeWidgetType widgetType) {
	UITreeNode* childNode = createNode(widget, widgetType); /* create a new child node */
	if (childNode == NULL) { /* failed to create the list node */
		return NULL;
	}
//	if (isEmpty(parent)) {
//		printf("Do not use this function for an empty list!\n");
//		exit(0); //TODO delete this condition
//	}
	if (parent->child == NULL) { /* parent has no children */
		parent->child = childNode;
	} else {
		UITreeNode* currChild = parent->child;
		/* Loop until reached the last node of the children list. */
		while (currChild->next != NULL) { /* while last node not reached */
			currChild = currChild->next; /* advance to the next node */
		}
		currChild->next = childNode; /* append the node at the end of the list */
	}
	childNode->parent = parent;
	return childNode; /* return the node added */
}

/* A recursive function that makes a DFS traversal over a tree,
 * using treeNodePreFunction as a function that will run in a pre-order manner
 * (parent before child , and using treeNodePostFunction as a function that will run in a post-order manner
 * (child before parent). return -1 if there was an error running one of the functions.
 */
int treeDFS(UITreeNode* root, int (*treeNodePreFunction)(UITreeNode* node),
		int (*treeNodePostFunction)(UITreeNode* node, SDL_Surface* screen),
		SDL_Surface* screen) {
	if (root == NULL)
		return 0;
	int preState = treeNodePreFunction(root); /* run pre function on current root */
	if (preState == -1) { /* if there was an error, return -1 */
		return -1;
	}
	if (root->child != NULL) {
		UITreeNode* curr = root->child;
		while (curr != NULL) { /* go over each child of the root */
			if (treeDFS(curr, treeNodePreFunction, treeNodePostFunction, screen)
					== -1) /* make a recursive call */
				return -1; /* if there was an error, return -1 */
			curr = curr->next;
		}
	}
	int postState = treeNodePostFunction(root, screen); /* run post function */
	if (postState == -1) /* if there was an error, return -1 */
		return -1;
	return 0;
}

UITreeNode* getMinmaxPanelNodeGameWindow(UITreeNode* UITreeHead) {
	return UITreeHead->child->child->child->child->child;
}

// free functions

/* freeTree frees the tree nodes and frees their data using a free data function */
void freeTree(UITreeNode* root) {
	if (root != NULL) {
		UITreeNode* currChild = root->child;
		while (currChild != NULL) { /* go over each child of the root */
			UITreeNode* temp = currChild->next;
			freeTree(currChild); /* make a recursive call on the root child */
			currChild = temp;
		}
		if (root->widget != NULL) /* free the data  if it is not null */
			freeWidget(root->widget, root->widgetType);
		free(root); /* free the listRef itself */
	}
}

void freeWidget(void* widget, TreeWidgetType widgetType) {
	switch (widgetType) {
	case (BUTTONS):
		freeButtons((Buttons*) widget);
		break;
	case (BACKGROUND):
		freeBackground((Background*) widget);
		break;
	case (PANEL):
		freePanel((Panel*) widget);
		break;
	case (MATRIX):
		freeMatrix((Matrix*) widget);
		break;
	}
}

void freeButtons(Buttons* buttons) {
	/* frees all buttons fields, and background widget itself */
	int i;
	for (i = 0; i < buttons->numOfButtons; i++)
		if (buttons->buttonArray[i] != NULL) {
			free(buttons->buttonArray[i]);
		}
	free(buttons->buttonArray);
	free(buttons->clipArray);
	SDL_FreeSurface(buttons->buttonsImages);
	free(buttons);
}

void freeBackground(Background* background) {
	/* frees all background fields, and background widget itself */
	if (background->image != NULL) {
		SDL_FreeSurface(background->image);
	}
	free(background);
}

void freePanel(Panel* panel) {
	/* frees all panel fields, and panel widget itself */
	if (panel->panelBackground != NULL)
		SDL_FreeSurface(panel->panelBackground);
	free(panel);
}

void freeMatrix(Matrix* matrix) {
	// free matrix buttons
	int i, j;
	for (i = 0; i < matrix->n; i++) {
		for (j = 0; j < matrix->n; j++) {
			free(matrix->buttonsMatrix[i][j]);
		}
		free(matrix->buttonsMatrix[i]);
	}
	free(matrix->buttonsMatrix);

	free(matrix->piecesClipArray);

	SDL_FreeSurface(matrix->highlightImage);
	SDL_FreeSurface(matrix->piecesImages);
	free(matrix);
}

void initMemory(GUIMemory* memory) {
	memory->newI = -1;
	memory->newJ = -1;
	memory->oldI = -1;
	memory->oldJ = -1;
	memory->pressedSquarsNum = 0;
	memory->commandType = NO_COMMAND;
	memory->pieceChosen = 'a';
	memory->minmaxDepthChosen = 0;

	memory->pathOfBubbleToShow = NULL;
}
