#include "GUIUtils.h"

SDL_Surface* loadImage(char* imagePath) {
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage= NULL;
	//The optimized image that will be used
	SDL_Surface* optimizedImage=NULL;
	loadedImage = IMG_Load(imagePath);//IMG_Load( imagePath );
	 //If nothing went wrong in loading the image
	if( loadedImage != NULL ) {
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );
		//Free the old image
		SDL_FreeSurface( loadedImage );
	}
	else {
		return loadedImage; // returns NULL
	}
	//TODO make image transparent
	 //Return the optimized image
	return optimizedImage;
}

void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, clip, destination, &offset );
 	//Update Screen? outside..

}

