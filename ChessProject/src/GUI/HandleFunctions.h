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

int welcomeWindowHandleEvent(Window* window, EventID eventID);
int playerSelectionWindowHandleEvent(Window* window, EventID eventID);


#endif /* HANDLEFUNCTIONS_H_ */
