#include "WindowFactory.h"

Window initWindow(WindowId id, SDL_Surface* screen) {
	Window window; //TODO how is it not released outside?! = malloc(sizeof(window));
	window.windowId = id;
	window.UITreeHead = NULL;
	window.screen = screen;

	switch (id) {
	case WELCOME:
		window.start = startWelcomeOrSelection;
		window.translateEvent = translateEventWelcomeOrSelection;
		window.handleEvent = handleEventWelcomeWindow;
		window.stop = stopWelcomeOrSelection;
		break;
	case PLAYER_SELECTION:
		window.start = startWelcomeOrSelection;
		window.translateEvent = translateEventWelcomeOrSelection;
		window.handleEvent = handleEventSelectionWindow;
		window.stop = stopWelcomeOrSelection;
		break;

	default:
		break;
	}

	return window;
}








