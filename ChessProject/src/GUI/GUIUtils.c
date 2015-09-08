#include "GUIUtils.h"

//SDL_Surface* openScreen() {
//	SDL_Surface* screen = malloc(sizeof(SDL_Surface));
//	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
//			SDL_SWSURFACE);
//	//If there was an error in setting up the screen
//	if (screen == NULL)
//		return 0;
//	SDL_WM_SetCaption("Noa and Noga's World Of Fun!", NULL);
//	return screen;
//}

Button** createVerticalButtonsArrayAndApplayToScreen(int numOfButtons,
		int xForButtons, int yFirstButton, SDL_Surface* buttonsImages,
		SDL_Rect* clipArray, int relevantFirstClipIndex, SDL_Surface* screen) {
	/** assuming clips are serially organized as needed **/

	Button** buttons = (Button**) malloc(sizeof(Button*) * numOfButtons);
	int i;
	for (i = 0; i < numOfButtons; i++) {
		Button* button = NULL;
		SDL_Rect box = { xForButtons, yFirstButton + i * BUTTON_HEIGHT,
				BUTTON_WIDTH, BUTTON_HEIGHT };
		button = createButton(box); //should the relevantArea also be alloced?
		applySurface(xForButtons, yFirstButton + i * BUTTON_HEIGHT,
				buttonsImages, screen, &clipArray[i]);
		if (button == NULL) {
			//quitGUI(); TODO
		}
		buttons[i] = button;
	}
	return buttons;
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
	case (QUIT_WINDOW):
		break;
	}

	background->image = loadImage(imagePath);
	if (background->image == NULL) {
		//TODO
	}
	return background;
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
	matrix->peicesClipArray = clip;
	matrix->piecesImages = loadImage(PEICES_SPRITE);
	matrix->m = BOARD_SIZE;
	matrix->n = BOARD_SIZE;
//	matrix->drawIJ
	matrix->isIJPressed = isIJPressed;

	updateMatrixByGame(matrix, game);

//	matrix->fatherPanel
//	int (*drawIJ)(Panel* panel, Matrix* matrix, PieceID peiceType, int i, int j);
	return matrix;
}

void updateMatrixByGame(Matrix* matrix, Game* game) {
	for (int i=0; i<BOARD_SIZE; i++ ) {
		for (int j=0; j<BOARD_SIZE; j++ ) {
			((matrix->buttonsMatrix)[i][j])->peiceToDraw = game->board[j][i];
		}
	}
}

void drawMatrix(Matrix* matrix, SDL_Surface* screen) {
	for (int i=0; i<BOARD_SIZE; i++ ) {
		for (int j=0; j<BOARD_SIZE; j++ ) {
			char peiceChar = (matrix->buttonsMatrix[i][j])->peiceToDraw;
			SDL_Rect* relevantClip;
			switch (peiceChar){
				case ('m'):
					relevantClip = &matrix->peicesClipArray[11];
					break;
				case ('b'):
					relevantClip = &matrix->peicesClipArray[7];
					break;
				case ('n'):
					relevantClip = &matrix->peicesClipArray[10];
					break;
				case ('r'):
					relevantClip = &matrix->peicesClipArray[6];
					break;
				case ('q'):
					relevantClip = &matrix->peicesClipArray[8];
					break;
				case ('k'):
					relevantClip = &matrix->peicesClipArray[9];
					break;
				case ('M'):
					relevantClip = &matrix->peicesClipArray[5];
					break;
				case ('B'):
					relevantClip = &matrix->peicesClipArray[1];
					break;
				case ('N'):
					relevantClip = &matrix->peicesClipArray[4];
					break;
				case ('R'):
					relevantClip = &matrix->peicesClipArray[0];
					break;
				case ('Q'):
					relevantClip = &matrix->peicesClipArray[2];
					break;
				case ('K'):
					relevantClip = &matrix->peicesClipArray[3];
					break;
				case (' '):
					relevantClip = NULL;
					break;
			}
			if ( relevantClip != NULL )
				applySurface(matrix->buttonsMatrix[i][j]->relevantArea.x,matrix->buttonsMatrix[i][j]->relevantArea.y,matrix->piecesImages,screen,relevantClip);
		}
	}
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

UITreeNode* append(UITreeNode* list, void* widget, TreeWidgetType widgetType) {
	if (widget == NULL) {
		return list;
	}
//	if (isEmpty(list)) {
//		/* an empty list is a one node list
//		 * that has its data pointer points to NULL. Thus adding the
//		 * data to an empty list will be done by changing the data
//		 * pointer to the new data. */
//		list->widget = data;
//		return list;
//	} else { /* list is not empty */
	UITreeNode* appendedNode = createNode(widget, widgetType); /* create a new list node */
	if (appendedNode == NULL) { /* failed to create the list node */
		return NULL;
//		}
		/* Loop until reached the last node of the list.
		 * If the list passed to the function is the last node
		 * of the list, then this loop will take O(1) time.
		 */
		while (list->next != NULL) { /* while last node not reached */
			list = list->next; /* advance to the next node */
		}
		list->next = appendedNode; /* append the node at the end of the list */
		return appendedNode; /* return the node appended */
	}
}

//int isEmpty(UITreeNode* list) {
//	if (list->widget == NULL) { /* if the data pointer is NULL.*/
//		return 1;
//	}
//	return 0;
//}

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

	free(buttons);
}

void freeBackground(Background* background) {
	/* frees all background fields, and background widget itself */
	if (background->image != NULL) {
		SDL_FreeSurface(background->image);
	}
	free(background);
}
