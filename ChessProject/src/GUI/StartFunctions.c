#include "StartFunctions.h"

int welcomeWindowStart(Window* window, void* initData) {
	window->UITreeHead = createNode(NULL); // TODO UI TREE!

	SDL_Surface *screen = NULL;
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	//If there was an error in setting up the screen
	if( screen == NULL )
	     return 0;
	SDL_WM_SetCaption( "Noa and Noga's World Of Fun!", NULL );

	SDL_Surface *image = NULL;
	SDL_Surface *menuImages = NULL;

	// Apply background
	image  = loadImage(WELCOME_BACKGROUND);
	if( image == NULL ) {
		printf("Error");
		return 0;
	}
	applySurface( 0, 0, image, screen, NULL );

	// Create buttons and apply on screen
	menuImages = loadImage("images/main_menu_sprite.png");
	if( menuImages == NULL )
		return 0;

	SDL_Rect clip[ 4 ];
	clipWelcomeOrPlayerSelection(clip);

	int xForButtons = 0.5*SCREEN_WIDTH-0.5*BUTTON_WIDTH;
	int yFirstButton = 0.5*SCREEN_HEIGHT-1.5*BUTTON_HEIGHT;

	// Create buttons
	Button* newGameButton = NULL;
	SDL_Rect box1 = { xForButtons, yFirstButton, BUTTON_WIDTH, BUTTON_HEIGHT };
	newGameButton = createButton(box1);  //should the relevantArea also be alloced?
	if ( newGameButton == NULL ) {
		//quitGUI(); TODO
	}
	window->UITreeHead->child = createNode(newGameButton);
	if (window->UITreeHead->child == NULL) {
		//quiteGUI(); // TODO
	}

	Button* loadGameButton = NULL;
	SDL_Rect box2 = { xForButtons, yFirstButton + BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT };
	loadGameButton = createButton(box2);
	if ( loadGameButton == NULL ) {
		//quiteGUI(); TODO
	}
	window->UITreeHead->child->next = createNode(loadGameButton);
	if (window->UITreeHead->child->next == NULL) {
		// quiteGUI(); TODO
	}

	Button* quitButton;
	SDL_Rect box3 = { xForButtons, yFirstButton + 2*BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT };
	quitButton = createButton(box3);
	if ( quitButton == NULL ) {
		//quiteGUI(); TODO
	}
	window->UITreeHead->child->next->next = createNode(quitButton);
	if (window->UITreeHead->child->next->next == NULL) {
		// quiteGUI(); TODO
	}

	// Apply button images on screen
	applySurface( xForButtons, yFirstButton, menuImages, screen, &clip[0] );
	applySurface( xForButtons , yFirstButton+BUTTON_HEIGHT, menuImages, screen, &clip[1] );
	applySurface( xForButtons, yFirstButton+2*BUTTON_HEIGHT, menuImages, screen, &clip[2] );

	// Update what we see on screen
	if ( SDL_Flip(screen) ==  -1 ) {
	 	printf("ERROR \n");
		return 0;
	}


	return 1;
}

void clipWelcomeOrPlayerSelection( SDL_Rect* clip ){
	//Clip range for the top left
	clip[ 0 ].x = 0;
	clip[ 0 ].y = 0;
	clip[ 0 ].w = 220;
	clip[ 0 ].h = 50;

	//Clip range for the top right
	clip[ 1 ].x = 0;
	clip[ 1 ].y = 50;
	clip[ 1 ].w = 220;
	clip[ 1 ].h = 50;

	//Clip range for the bottom left
	clip[ 2 ].x = 0;
	clip[ 2 ].y = 100;
	clip[ 2 ].w = 220;
	clip[ 2 ].h = 50;

}

int playerSelectionWindowStart(Window* window, void* initData) {
	window->UITreeHead = createNode(NULL); // TODO UI TREE!

	SDL_Surface *screen = NULL;
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	//If there was an error in setting up the screen
	if( screen == NULL )
	     return 0;
	SDL_WM_SetCaption( "Noa and Noga's World Of Fun!", NULL );

	SDL_Surface *image = NULL;
	SDL_Surface *menuImages = NULL;

	// Apply background
	image  = loadImage(PLAYER_SELECTION_BACKGROUND);
	applySurface( 0, 0, image, screen, NULL );

	// Create buttons and apply on screen
	menuImages = loadImage("images/player_selection_sprite.png");
	if( image == NULL )
		return 0;

	SDL_Rect clip[ 4 ];
	clipWelcomeOrPlayerSelection(clip);

	int xForButtons = 0.5*SCREEN_WIDTH-0.5*BUTTON_WIDTH;
	int yFirstButton = 0.5*SCREEN_HEIGHT-1.5*BUTTON_HEIGHT;

	// Create buttons
	Button NewGamebutton;
	SDL_Rect box1 = { xForButtons, yFirstButton, BUTTON_WIDTH, BUTTON_HEIGHT };
	NewGamebutton.relevantArea = box1;

	Button LoadGamebutton;
	SDL_Rect box2 = { xForButtons, yFirstButton + BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT };
	LoadGamebutton.relevantArea = box2;

	Button Quitbutton;
	SDL_Rect box3 = { xForButtons, yFirstButton + 2*BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT };
	Quitbutton.relevantArea = box3;

	// Apply button images on screen
	applySurface( xForButtons, yFirstButton, menuImages, screen, &clip[0] );
	applySurface( xForButtons , yFirstButton+BUTTON_HEIGHT, menuImages, screen, &clip[1] );
	applySurface( xForButtons, yFirstButton+2*BUTTON_HEIGHT, menuImages, screen, &clip[2] );

	// Update what we see on screen
	if ( SDL_Flip(screen) ==  -1 ) {
	 	return 0;
	}
	return 1;


}




