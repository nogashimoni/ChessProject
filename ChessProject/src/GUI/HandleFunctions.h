/*
 * StartFunctions.h
 *
 *  Created on: Aug 29, 2015
 *      Author: nogalavi1
 */

#ifndef HANDLEFUNCTIONS_H_
#define HANDLEFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL/SDL_image.h>
#include "GUIUtils.h"
#include "GUIDefinitions.h"
#include "../main/ChessLogic.h"

int handleEventWelcomeWindow(Window* window, EventID eventID, Game* game, GUIMemory* memory);
int handleEventSelectionWindow(Window* window, EventID eventID, Game* game, GUIMemory* memory);
int handleEventSetDiffAndColor(Window* window, EventID eventID, Game* game, GUIMemory* memory);
int handleEventToSetWhoStarts(Window* window, EventID eventID, Game* game, GUIMemory* memory);
int handleEventSetWhoStarts(Window* window, EventID eventID, Game* game, GUIMemory* memory);
int handleEventToSetBoard(Window* window, EventID eventID, Game* game, GUIMemory* memory);
int handleEventSetBoard(Window* window, EventID eventID, Game* game, GUIMemory* memory);
int handleEventGameWindow(Window* window, EventID eventID, Game* game, GUIMemory* memory);

#endif /* HANDLEFUNCTIONS_H_ */
