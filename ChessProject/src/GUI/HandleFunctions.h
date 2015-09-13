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

// update window functions
int updateWindow(Window* activeWindow,Game* game, GUIMemory* memory);
int updateSetBoard(Window* activeWindow,Game* game, GUIMemory* memory);
int updateGameBoard(Window* activeWindow,Game* game,GUIMemory* memory);

// helper functions
void displayAllPossibleMoves(Matrix* matrix,GUIMemory* memory, Game* game, SDL_Surface* screen);
void displayBestMove(Matrix* matrix,GUIMemory* memory, Game* game, SDL_Surface* screen);

#endif /* HANDLEFUNCTIONS_H_ */
