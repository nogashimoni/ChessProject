#include "GUI.h"

int isError = 0;

int GUIMain(Game* game) {

		//init gui
		if (SDL_Init(SDL_INIT_VIDEO) == -1) {
			notifyFunctionFailure("GUIMain");
			return 0;
		}
		atexit(SDL_Quit);

		SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
				SDL_SWSURFACE);
		if (screen == NULL) {
			notifyFunctionFailure("GUIMain");
			quit();
			return 0;
		}
		SDL_WM_SetCaption("Noa and Noga's World Of Fun!", NULL);


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
		if (memory == NULL) {
			notifyFunctionFailure("GUIMain");
			quit();
			return 0;
		}
		initMemory(memory);

		int isError = !activeWindow.start(&activeWindow, game, memory);

		if (isError) {
			activeWindow.stop(&activeWindow);
			quit();
		}


		while (!isError && nextWindowId != QUIT_WINDOW) {

			SDL_Event event;
			while (SDL_PollEvent(&event)) {

				if (activeWindow.windowId == GAME_WINDOW ) {
					updateComputerTurnIfNeeded(&activeWindow, game, memory);
				}
				/* translating the SDL event to a logical event */
				EventID eventID = activeWindow.translateEvent(&activeWindow, event, memory);
				if (isError)
					break;

				/* Handling the event and updating the game */
				nextWindowId = activeWindow.handleEvent(&activeWindow, eventID, game, memory);
				if (isError)
					break;

				/* Update the screen with changes */
				updateWindow(&activeWindow, game, memory);

				/* if we need to change window, stop the active window and move to the next one */
				if (activeWindow.windowId != nextWindowId) {
					if ( !( (nextWindowId == GAME_WINDOW && memory->isTie) || (nextWindowId == GAME_WINDOW && memory->isMate)) )
						initMemory(memory);
					if (nextWindowId == QUIT_WINDOW) {
						break;
					}
					else {
						activeWindow.stop(&activeWindow);
						if (isError) /* stop function may result in an error */
							break;
						activeWindow = windows[nextWindowId];
						isError = !activeWindow.start(&activeWindow, game, memory);
					}
				}
			}
			SDL_Delay(POLLING_DELAY);
		}

		activeWindow.stop(&activeWindow);
		free(memory);

		return 1;

}











