#include "WindowFactory.h"

Window initWindow(WindowId id) {
	Window window; //TODO how is it not released outside?! = malloc(sizeof(window));
	window.windowId = id;

	switch (id) {
	case WELCOME:
		window.start = startWelcomeOrPlayerSelection;
		window.translateEvent = welcomeOrSelectionTranslateEvent;
		window.handleEvent = welcomeWindowHandleEvent;
		break;
	case PLAYER_SELECTION:
		window.start = startWelcomeOrPlayerSelection;
		window.translateEvent = welcomeOrSelectionTranslateEvent;
		window.handleEvent = playerSelectionWindowHandleEvent;
		break;

	default:
		break;
	}

	return window;
}








