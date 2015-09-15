#include "WindowFactory.h"

Window initWindow(WindowId id, SDL_Surface* screen) {
	Window window;
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
	case SET_DIFFICULTY_AND_COLOR:
		window.start = startSetDifficultyAndColor;
		window.translateEvent = translateEventSetDiffAndColor;
		window.handleEvent = handleEventSetDiffAndColor;
		window.stop = stopSetDiffAndColor;
		break;
	case TO_SET_WHO_STARTS:
		window.start = startGeneralSetup;
		window.translateEvent = translateEventGeneralSetup;
		window.handleEvent = handleEventToSetWhoStarts;
		window.stop = stopGeneralSetup;
		break;
	case SET_WHO_STARTS:
		window.start = startGeneralSetup;
		window.translateEvent = translateEventGeneralSetup;
		window.handleEvent = handleEventSetWhoStarts;
		window.stop = stopGeneralSetup;
		break;
	case TO_SET_BOARD:
		window.start = startGeneralSetup;
		window.translateEvent = translateEventGeneralSetup;
		window.handleEvent = handleEventToSetBoard;
		window.stop = stopGeneralSetup;
		break;
	case SET_BOARD:
		window.start = startSetBoard;
		window.translateEvent = translateEventSetBoard;
		window.handleEvent = handleEventSetBoard;
		window.stop = stopSetBoard;
		break;
	case GAME_WINDOW:
		window.start = startGameWindow;
		window.translateEvent = translateEventGameWindow;
		window.handleEvent = handleEventGameWindow;
		window.stop = stopSetBoard;
		break;
	default:
		break;
	}

	return window;
}








