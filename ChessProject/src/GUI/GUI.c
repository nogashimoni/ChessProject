#include "GUI.h"

int isError = 0;

int GUIMain(Game* game) {
		//init gui
		if (SDL_Init(SDL_INIT_VIDEO) == -1) {
			notifyFunctionFailure("GUIMain"); //TODO sdlErrorPrint("unable to init SDL");
			return 0;
		}
		SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
				SDL_SWSURFACE);
		if (screen == NULL)
			//TODO error
		SDL_WM_SetCaption("Noa and Noga's World Of Fun!", NULL);
		atexit(SDL_Quit);

		// init windows
		Window windows[WINDOWS_COUNT];
		/* initialize GUI structs mapping by state ids: */

		windows[WELCOME] = initWindow(WELCOME, screen);
		windows[PLAYER_SELECTION] = initWindow(PLAYER_SELECTION, screen);
		windows[TO_SET_WHO_STARTS] = initWindow(TO_SET_WHO_STARTS, screen);
		windows[SET_WHO_STARTS] = initWindow(SET_WHO_STARTS, screen);
		windows[TO_SET_BOARD] = initWindow(TO_SET_BOARD, screen);
		windows[SET_BOARD] = initWindow(SET_BOARD, screen);


		/* Starting the default/initial GUI: */

		Window activeWindow = windows[WELCOME];
		WindowId nextWindowId = WELCOME;

		activeWindow.start(&activeWindow, NULL);

		while (!isError && nextWindowId != QUIT_WINDOW) {
//			if (activeGUI.stateId == PLAY_GAME){ /* if we are currently playing the game */
//				updateMachineMoveIfNeeded(activeGUI); /* make machine move if it is machibe turn */
//				if (isError)
//					break;
//			}
			SDL_Event event;
			while (SDL_PollEvent(&event)) {

				/* translating the SDL event to a logical event using the view: */
				EventID eventID = activeWindow.translateEvent(&activeWindow, event);
				if (isError) /* PHE function may result in an error */
					break;

				/* Handling the event */
				nextWindowId = activeWindow.handleEvent(&activeWindow, eventID, game);
				if (isError) /* PHE function may result in an error */
					break;

				/* if state has changed, stop the active GUI and move to the next one: */
				if (activeWindow.windowId != nextWindowId) {
					if (nextWindowId == QUIT_WINDOW) {
						break;
					}
					else {
						void* nextWindowInitData = activeWindow.stop(&activeWindow);
						if (isError) /* stop function may result in an error */
							break;
						activeWindow = windows[nextWindowId];
						activeWindow.start(&activeWindow, nextWindowInitData);
					}
				}
			}
			SDL_Delay(POLLING_DELAY);
		}

		/* stop the active GUI (stop function will return NULL stop if called from here) */
		activeWindow.stop(&activeWindow);
return 1;
}

















//
//
////The surfaces
//SDL_Surface *image = NULL;
//SDL_Surface *screen = NULL;
//SDL_Surface *dots = NULL;
////The portions of the sprite map to be blitted
//SDL_Rect clip[ 4 ];
//
//SDL_Event event;
//
//int GUIMain(){
//	int toQuit = 0;
//    if( initGUI() == 0 ) {
//        return 0;
//    }
//
//    //Load the files
//    if( loadFiles() == 0 ) {
//        return 0;
//    }
//    setClip();
//
//     Button button;
//     (button.box).x = 640/2-110;
//     (button.box).y = 480/2-75;
//     (button.box).w = 220;
//     (button.box).h = 50;
//
//
//	applySurface( 0, 0, image, screen, NULL );
//	applySurface( 640/2-110, 480/2-75, dots, screen, &clip[0] );
//	applySurface( 640/2-110 , 480/2-75+50, dots, screen, &clip[1] );
//	applySurface( 640/2-110, 480/2-75+100, dots, screen, &clip[2] );
//
// 	if ( SDL_Flip(screen) ==  -1 ) {
// 		return 0;
// 	}
//
// 	//While the user hasn't quit
// 	while ( toQuit == 0 ) {
//        //While there's an event to handle
//        while( SDL_PollEvent( &event ) ) {
//            //If the user has Xed out the window
//            if( event.type == SDL_QUIT ){
//                //Quit the program
//                toQuit = 1;
//                break;
//            }
//            //button->handle_events
//            handleEvents(&button,0,0,NULL);
////            //If a mouse was pressed
////            if( event.type == SDL_KEYDOWN ) {
////            	printf("down was pressed\n");
////            }
//        }
//    }
//
//
//	quitSDL();
//	return 1;
//}
//
//void handleEvents(Button *button, int x_offset, int y_offset,
//		char board[BOARD_SIZE][BOARD_SIZE]) {
//    //The mouse offsets
//    int x = 0, y = 0;
//
//    //If the mouse moved
//    if( event.type == SDL_MOUSEMOTION ){
//        //Get the mouse offsets
//        x = event.motion.x;
//        y = event.motion.y;
//
//        //If the mouse is over the button
//        if( ( x > button->box.x ) && ( x < button->box.x + button->box.w ) && ( y > button->box.y ) && ( y < button->box.y + button->box.h ) ){
//            //Set the button sprite
//            printf("a click event!! \n");
//        }
//        //If not
//        else
//        {
//            //Set the button sprite
//            return;
//        }
//    }
//}
//
//void setClip() {
//    //Clip range for the top left
//    clip[ 0 ].x = 0;
//    clip[ 0 ].y = 0;
//    clip[ 0 ].w = 220;
//    clip[ 0 ].h = 50;
//
//    //Clip range for the top right
//    clip[ 1 ].x = 0;
//    clip[ 1 ].y = 50;
//    clip[ 1 ].w = 220;
//    clip[ 1 ].h = 50;
//
//    //Clip range for the bottom left
//    clip[ 2 ].x = 0;
//    clip[ 2 ].y = 100;
//    clip[ 2 ].w = 220;
//    clip[ 2 ].h = 50;
//}
//
//int loadFiles(){
//    //Load the image
//    image = loadImage( BACKGROUND );
//    dots = loadImage("images/main_menu_sprite.png");
//    //If there was an error in loading the image
//    if( image == NULL || dots == NULL) {
//        return 0;
//    }
//
//    //If everything loaded fine
//    return 1;
//}
//
//int createWelcomePage() {
//	return 0;
//}
//
//int initGUI() {
//
//	//Start SDL
//	if ( SDL_Init( SDL_INIT_VIDEO ) == -1 ) {
//		return 0;
//	}
//	//Set up screen
//	screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
//    //If there was an error in setting up the screen
//    if( screen == NULL ) {
//        return 0;
//    }
//
//    //Set the window caption
//    SDL_WM_SetCaption( "Noa and Noga's World Of Fun!", NULL );
//
//    //If everything initialized fine
//    return 1;
//}
//
//SDL_Surface* loadImage(char* imagePath) {
//	//Temporary storage for the image that's loaded
//	SDL_Surface* loadedImage= NULL;
//	//The optimized image that will be used
//	SDL_Surface* optimizedImage=NULL;
//	//Load image
//	loadedImage = IMG_Load(imagePath);//IMG_Load( imagePath );
//	 //If nothing went wrong in loading the image
//	if( loadedImage != NULL ) {
//		//Create an optimized image
//		optimizedImage = SDL_DisplayFormat( loadedImage );
//		//Free the old image
//		SDL_FreeSurface( loadedImage );
//	}
//	else {
//		return loadedImage; // returns NULL
//	}
//	 //Return the optimized image
//	return optimizedImage;
//}
//
//
////int applyImageOnScreen(SDL_Surface* screen, SDL_Surface* image) {
////	 //Apply image to screen
////	SDL_BlitSurface( image, NULL, screen, NULL );
////	//Update Screen
////	SDL_Flip( screen );
////	//Pause
////	SDL_Delay( 100 );
////	return 1;
////}
//
//void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
//    //Make a temporary rectangle to hold the offsets
//    SDL_Rect offset;
//
//    //Give the offsets to the rectangle
//    offset.x = x;
//    offset.y = y;
//
//    //Blit the surface
//    SDL_BlitSurface( source, clip, destination, &offset );
// 	//Update Screen? outside..
//
//}
//
//int closeImage(SDL_Surface* image) {
//	 //Free the loaded image
//	SDL_FreeSurface( image );
//	return 1;
//}
//
//int quitSDL() {
//	//cleanup - close all open images
//	closeImage(image);
//	closeImage(dots);
//	//Quit SDL - closes the screen
//	SDL_Quit();
//	return 1;
//}
