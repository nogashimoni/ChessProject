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
	case PLAYER_SELECTION:
		window.start = playerSelectionWindowStart;
		window.translateEvent = playerSelectionWindowTranslateEvent;
		window.handleEvent = playerSelectionWindowHandleEvent;
		break;

	default:
		break;
	}

	return window;
}








