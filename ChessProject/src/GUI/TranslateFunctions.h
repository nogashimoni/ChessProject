/*
 * StartFunctions.h
 *
 *  Created on: Aug 29, 2015
 *      Author: nogalavi1
 */

#ifndef TRANSLATEFUNCTIONS_H_
#define TRANSLATEFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
//#include <SDL/SDL_image.h>
#include </usr/local/lib/SDL_image-1.2.12/include/SDL/SDL_image.h>
#include "GUIUtils.h"
#include "GUIDefinitions.h"

EventID translateEventGeneralSetup(Window* window, SDL_Event event, GUIMemory* memory);
EventID translateEventSetDiffAndColor(Window* window, SDL_Event event, GUIMemory* memory);
EventID translateEventSetBoard(Window* window, SDL_Event event, GUIMemory* memory);
EventID translateEventGameWindow(Window* window, SDL_Event event, GUIMemory* memory);

#endif /* TRANSLATEFUNCTIONS_H_ */
