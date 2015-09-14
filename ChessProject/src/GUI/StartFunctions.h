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

int startGeneralSetup (Window* window, Game* game, GUIMemory* memory);
int startSetDifficultyAndColor(Window* window, Game* game, GUIMemory* memory);
int startSetBoard(Window* window, Game* game, GUIMemory* memory);
int startGameWindow(Window* window, Game* game, GUIMemory* memory);

void clipBestMove(SDL_Rect* clip);
void clipGeneralSetup( SDL_Rect* clip );
void clipDifficulty(SDL_Rect* clip);
void clipUserColor(SDL_Rect* clip);
void clipPeices(SDL_Rect* clip);
void clipCancelContinue(SDL_Rect* clip);
void clipSetBoard(SDL_Rect* clip);
void clipSixPeices(SDL_Rect* clip, int isWhitePieces);
void clipPromotionPeices(SDL_Rect* clip, int isWhitePieces);
void clipIContinue(SDL_Rect* clip);
void clipISlots(SDL_Rect* clip, int numOfSlots);

char* getSpriteByWindowID(WindowId windowID);



#endif /* STARTFUNCTIONS_H_ */
