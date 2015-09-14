#include "GUI.h"

int isError = 0;

int GUIMain(Game* game) {

		//init gui
		if (SDL_Init(SDL_INIT_VIDEO) == -1) {
			notifyFunctionFailure("GUIMain");
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

		windows[WELCOME] = initWindow(WELCOME, screen);
		windows[PLAYER_SELECTION] = initWindow(PLAYER_SELECTION, screen);
		windows[SET_DIFFICULTY_AND_COLOR] = initWindow(SET_DIFFICULTY_AND_COLOR, screen);
		windows[TO_SET_WHO_STARTS] = initWindow(TO_SET_WHO_STARTS, screen);
		windows[SET_WHO_STARTS] = initWindow(SET_WHO_STARTS, screen);
		windows[TO_SET_BOARD] = initWindow(TO_SET_BOARD, screen);
		windows[SET_BOARD] = initWindow(SET_BOARD, screen);
		windows[GAME_WINDOW] = initWindow(GAME_WINDOW, screen);

		/* Starting the initial window: */

		Window activeWindow = windows[WELCOME];
		WindowId nextWindowId = WELCOME;

		GUIMemory* memory = (GUIMemory*)malloc(sizeof(GUIMemory));
		initMemory(memory);

		activeWindow.start(&activeWindow, game, memory);



		while (!isError && nextWindowId != QUIT_WINDOW) {

			SDL_Event event;
			while (SDL_PollEvent(&event)) {

				if (activeWindow.windowId == GAME_WINDOW ) {
					updateComputerTurnIfNeeded(&activeWindow, game, memory);
				}
				/* translating the SDL event to a logical event using the view: */
				EventID eventID = activeWindow.translateEvent(&activeWindow, event, memory);
				if (isError)
					break;

				/* Handling the event */
				nextWindowId = activeWindow.handleEvent(&activeWindow, eventID, game, memory);
				if (isError)
					break;

				updateWindow(&activeWindow, game, memory);

				/* if state has changed, stop the active GUI and move to the next one: */
				if (activeWindow.windowId != nextWindowId) {
					initMemory(memory);
					if (nextWindowId == QUIT_WINDOW) {
						break;
					}
					else {
						void* nextWindowInitData = activeWindow.stop(&activeWindow);
						if (isError) /* stop function may result in an error */
							break;
						activeWindow = windows[nextWindowId];
						activeWindow.start(&activeWindow, game, memory);
					}
				}
			}
			SDL_Delay(POLLING_DELAY);
		}

		activeWindow.stop(&activeWindow);
		free(memory);
return 1;

}











