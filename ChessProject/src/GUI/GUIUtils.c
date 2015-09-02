#include "GUIUtils.h"

SDL_Surface* createScreen() {
	SDL_Surface* screen = malloc(sizeof(SDL_Surface));
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
			SDL_SWSURFACE);
	//If there was an error in setting up the screen
	if (screen == NULL)
		return 0;
	SDL_WM_SetCaption("Noa and Noga's World Of Fun!", NULL);
	return screen;
}

Button** createVerticalButtonsArray(int numOfButtons, int xForButtons,
		int yFirstButton, SDL_Surface* buttonsImages, SDL_Rect* relevantFirstClip, SDL_Surface* screen) {

	Button** buttons = (Button**) malloc(sizeof(Button*) * numOfButtons);
	int i;
	for (i = 0; i < numOfButtons; i++) {
		Button* button = NULL;
		SDL_Rect box = { xForButtons, yFirstButton + i * BUTTON_HEIGHT,
				BUTTON_WIDTH, BUTTON_HEIGHT };
		button = createButton(box); //should the relevantArea also be alloced?
		applySurface( xForButtons, yFirstButton+ i * BUTTON_HEIGHT, buttonsImages, screen, relevantFirstClip );
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

Button* createButton(SDL_Rect relevantArea) {

	Button* button = NULL;

	button = (Button*) malloc(sizeof(Button));
	if (button == NULL) {
		//TODO standardFunctionFailure("malloc"); /* exit unavoidable */
		return NULL;
	}

	button->relevantArea = relevantArea;
	button->isButtonPressed = isButtonPressed;
	return button;
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

// Tree utilities

UITreeNode* createNode(void* headData) {
	UITreeNode* newTree = (UITreeNode*) malloc(sizeof(UITreeNode));
	if (newTree == NULL) {
//		perrorPrint("malloc"); TODO
		return NULL;
	}
	/* data and next will point to NULL: */
	newTree->data = NULL;
	newTree->next = NULL;
	newTree->child = NULL;
	newTree->parent = NULL;

	/* if headData is not NULL, put it in the list data field */
	if (headData != NULL) {
		newTree->data = headData;
	}
	return newTree;
}

UITreeNode* append(UITreeNode* list, void* data) {
	if (data == NULL) {
		return list;
	}
	if (isEmpty(list)) {
		/* an empty list is a one node list
		 * that has its data pointer points to NULL. Thus adding the
		 * data to an empty list will be done by changing the data
		 * pointer to the new data. */
		list->data = data;
		return list;
	} else { /* list is not empty */
		UITreeNode* appendList = createNode(data); /* create a new list node */
		if (appendList == NULL) { /* failed to create the list node */
			return NULL;
		}
		/* Loop until reached the last node of the list.
		 * If the list passed to the function is the last node
		 * of the list, then this loop will take O(1) time.
		 */
		while (list->next != NULL) { /* while last node not reached */
			list = list->next; /* advance to the next node */
		}
		list->next = appendList; /* append the node at the end of the list */
		return appendList; /* return the node appended */
	}
}

int isEmpty(UITreeNode* list) {
	if (list->data == NULL) { /* if the data pointer is NULL.*/
		return 1;
	}
	return 0;
}

/*
 * adds a new child to a listNode, at the end of the child list, and return it
 */
UITreeNode* addChildNode(UITreeNode* parent, void * data) {
	UITreeNode* childNode = createNode(data); /* create a new child node */
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
