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
#include <SDL/SDL_image.h>
#include "GUIUtils.h"
#include "GUIDefinitions.h"

EventID translateEventGeneralSetup(Window* window, SDL_Event event);
EventID translateEventSetBoard(Window* window, SDL_Event event);

#endif /* TRANSLATEFUNCTIONS_H_ */
