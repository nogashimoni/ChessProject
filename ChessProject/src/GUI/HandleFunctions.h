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

int handleEventWelcomeWindow(Window* window, EventID eventID, Game* game);
int handleEventSelectionWindow(Window* window, EventID eventID, Game* game);
int handleEventToSetWhoStarts(Window* window, EventID eventID, Game* game);
int handleEventSetWhoStarts(Window* window, EventID eventID, Game* game);
int handleEventToSetBoard(Window* window, EventID eventID, Game* game);
int handleEventSetBoard(Window* window, EventID eventID, Game* game);

#endif /* HANDLEFUNCTIONS_H_ */
