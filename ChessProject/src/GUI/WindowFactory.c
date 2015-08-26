#include "WindowFactory.h"

Window initWindow(WindowId id) {
	Window window; //TODO how is it not released outside?! = malloc(sizeof(window));
	window.windowId = id;

	switch (id) {
	case MAIN_MENU:
		window.start = welcomeWindowStart;
		window.translateEvent = welcomeWindowTranslateEvent;
		window.handleEvent = welcomeWindowHandleEvent;
		break;
	case SETUP:
		window.start = setupWindowStart;
		window.translateEvent = setupWindowTranslateEvent;
		window.handleEvent = setupWindowHandleEvent;
		break;

	default:
		break;
	}

	return window;
}


int welcomeWindowStart(Window* window, void* initData) {
	SDL_Surface *screen = NULL;
	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	//If there was an error in setting up the screen
	if( screen == NULL )
	     return 0;
	SDL_WM_SetCaption( "Noa and Noga's World Of Fun!", NULL );

	SDL_Surface *image = NULL;
	SDL_Surface *menuImages = NULL;
	image  = loadImage(BACKGROUND);
	menuImages = loadImage("images/main_menu_sprite.png");
	if( image == NULL )
		return 0;

	SDL_Rect clip[ 4 ];
	welcomeWindowClip(clip);

	Button button;
	(button.box).x = 640/2-110;
	(button.box).y = 480/2-75;
	(button.box).w = 220;
	(button.box).h = 50;



	applySurface( 0, 0, image, screen, NULL );
	applySurface( 640/2-110, 480/2-75, menuImages, screen, &clip[0] );
	applySurface( 640/2-110 , 480/2-75+50, menuImages, screen, &clip[1] );
	applySurface( 640/2-110, 480/2-75+100, menuImages, screen, &clip[2] );

	if ( SDL_Flip(screen) ==  -1 ) {
	 	return 0;
	 }
	return 1;
}

void welcomeWindowClip( SDL_Rect* clip ){
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

int setupWindowStart(Window* window, void* initData) {
	SDL_Surface *screen = NULL;
	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	//If there was an error in setting up the screen
	if( screen == NULL )
	     return 0;
	SDL_WM_SetCaption( "Noa and Noga's World Of Fun!", NULL );

	SDL_Surface *image = NULL;
	SDL_Surface *menuImages = NULL;
	image  = loadImage(BACKGROUND);
	menuImages = loadImage("images/player_selection_sprite.png");
	if( image == NULL )
		return 0;

	SDL_Rect clip[ 4 ];
	welcomeWindowClip(clip);

	Button button;
	(button.box).x = 640/2-110;
	(button.box).y = 480/2-75;
	(button.box).w = 220;
	(button.box).h = 50;


	applySurface( 0, 0, image, screen, NULL );
	applySurface( 640/2-110, 480/2-75, menuImages, screen, &clip[0] );
	applySurface( 640/2-110 , 480/2-75+50, menuImages, screen, &clip[1] );
	applySurface( 640/2-110, 480/2-75+100, menuImages, screen, &clip[2] );

	if ( SDL_Flip(screen) ==  -1 ) {
	 	return 0;
	 }
	return 1;
}

void setupWindowClip( SDL_Rect* clip ){
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

EventID welcomeWindowTranslateEvent(Window* window, SDL_Event* event) {

}

EventID setupWindowTranslateEvent(Window* window, SDL_Event* event) {

}

int welcomeWindowHandleEvent(Window* window, EventID eventID) {

}
int setupWindowHandleEvent(Window* window, EventID eventID) {

}



