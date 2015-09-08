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

int startGeneralSetup (Window* window, Game* initData);
int startSetBoard(Window* window, Game* initData);

void clipGeneralSetup( SDL_Rect* clip );
void clipPeices(SDL_Rect* clip);
char* getSpriteByWindowID(WindowId windowID);

#endif /* STARTFUNCTIONS_H_ */
