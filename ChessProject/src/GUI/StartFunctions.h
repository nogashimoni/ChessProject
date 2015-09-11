/*
 * StartFunctions.h
 *
 *  Created on: Aug 29, 2015
 *      Author: nogalavi1
 */

#ifndef STARTFUNCTIONS_H_
#define STARTFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL/SDL_image.h>
#include "GUIUtils.h"
#include "GUIDefinitions.h"

int startGeneralSetup (Window* window, Game* game);
int startSetDifficultyAndColor(Window* window, Game* game);
int startSetBoard(Window* window, Game* initData);
int startGameWindow(Window* window, Game* game);

void clipGeneralSetup( SDL_Rect* clip );
void clipDifficulty(SDL_Rect* clip);
void clipUserColor(SDL_Rect* clip);
void clipPeices(SDL_Rect* clip);
void clipCancelContinue(SDL_Rect* clip);
void clipSetBoard(SDL_Rect* clip);

char* getSpriteByWindowID(WindowId windowID);

int updateWindow(Window* activeWindow,Game* game, GUIMemory* memory);
int updateSetBoard(Window* activeWindow,Game* game, GUIMemory* memory);

#endif /* STARTFUNCTIONS_H_ */
