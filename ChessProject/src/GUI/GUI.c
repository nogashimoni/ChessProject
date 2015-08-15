#include "GUI.h"


int GUIMain(){
	SDL_Surface* screen = NULL;
	screen = initGUI();
	createWelcomePage(screen);
	quitSDL();
	return 1;
}

int createWelcomePage(SDL_Surface* screen) {
	SDL_Surface* image = NULL;
	SDL_Surface *message = NULL;
	SDL_Surface *background = NULL;

	image = openImage(WELCOME_WINDOW);
	applyImageOnScreen(screen, image);
	closeImage(image);
	return 0;
}

SDL_Surface* initGUI() {
	SDL_Surface* screen = NULL;
	//Start SDL
	SDL_Init( SDL_INIT_VIDEO );
	//Set up screen
	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
	return screen;
}

SDL_Surface* openImage(char* imagePath) {
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage= NULL;
	//The optimized image that will be used
	SDL_Surface* optimizedImage=NULL;
	//Load image
	loadedImage = SDL_LoadBMP( WELCOME_WINDOW );
	 //If nothing went wrong in loading the image
	if( loadedImage != NULL ) {
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );
		//Free the old image
		SDL_FreeSurface( loadedImage );
	}
	else {
		return loadedImage;
	}
	 //Return the optimized image
	return optimizedImage;
}


int applyImageOnScreen(SDL_Surface* screen, SDL_Surface* image) {
	 //Apply image to screen
	SDL_BlitSurface( image, NULL, screen, NULL );
	//Update Screen
	SDL_Flip( screen );
	//Pause
	SDL_Delay( 20000 );
	return 1;
}

int closeImage(SDL_Surface* image) {
	 //Free the loaded image
	SDL_FreeSurface( image );
	return 1;
}

int quitSDL() {
	//Quit SDL
	SDL_Quit();
	return 1;
}
