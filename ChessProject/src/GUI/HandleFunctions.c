/*
 * StartFunctions.c
 *
 *  Created on: Aug 29, 2015
 *      Author: nogalavi1
 */

#include "HandleFunctions.h"

int welcomeWindowHandleEvent(Window* window, EventID eventID) {
	switch (eventID) {
		case (FIRST_PRESSED): //new game
			return PLAYER_SELECTION;
	}
	return WELCOME;
}
int playerSelectionWindowHandleEvent(Window* window, EventID eventID) {

}
