#include "GUI.h"


int GUIMain(){
	SDL_Surface* screen = NULL;
	screen = initGUI();
	if ( screen == NULL ) {
		return 1;
	}
    //Set the window caption
    SDL_WM_SetCaption( "Noa and Noga's World Of Fun!", NULL );
	createWelcomePage(screen);
 	//Pause
 	SDL_Delay( 10000 );
	quitSDL();
	return 0;
}

int createWelcomePage(SDL_Surface* screen) {
	SDL_Surface* image = NULL;
	SDL_Surface *message = NULL;
	SDL_Surface *background = NULL;

	message = openImage("images/test.bmp");
	background = openImage(WELCOME_WINDOW);
	applySurface( 0, 0, background, screen );
	applySurface( 180, 140, message, screen );
	closeImage(image);
	return 0;
}

SDL_Surface* initGUI() {
	SDL_Surface* screen = NULL;
	//Start SDL
	if ( SDL_Init( SDL_INIT_VIDEO ) == -1 ) {
		return NULL;
	}
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
	loadedImage = IMG_Load( imagePath );
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


//int applyImageOnScreen(SDL_Surface* screen, SDL_Surface* image) {
//	 //Apply image to screen
//	SDL_BlitSurface( image, NULL, screen, NULL );
//	//Update Screen
//	SDL_Flip( screen );
//	//Pause
//	SDL_Delay( 100 );
//	return 1;
//}

void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination) {
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    //Blit the surface
     SDL_BlitSurface( source, NULL, destination, &offset );
 	//Update Screen
 	SDL_Flip( destination );

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
