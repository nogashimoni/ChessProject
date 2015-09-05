#include "WindowFactory.h"

Window initWindow(WindowId id, SDL_Surface* screen) {
	Window window; //TODO how is it not released outside?! = malloc(sizeof(window));
	window.windowId = id;
	window.UITreeHead = NULL;
	window.screen = screen;

	switch (id) {
	case WELCOME:
		window.start = startGeneralSetup;
		window.translateEvent = translateEventGeneralSetup;
		window.handleEvent = handleEventWelcomeWindow;
		window.stop = stopGeneralSetup;
		break;
	case PLAYER_SELECTION:
		window.start = startGeneralSetup;
		window.translateEvent = translateEventGeneralSetup;
		window.handleEvent = handleEventSelectionWindow;
		window.stop = stopGeneralSetup;
		break;
	case WHO_STARTS:
		window.start = startGeneralSetup;
		window.translateEvent = translateEventGeneralSetup;
		window.handleEvent = handleEventWhoStarts;
		window.stop = stopGeneralSetup;
		break;

	case SET_BOARD:

	default:
		break;
	}

	return window;
}








