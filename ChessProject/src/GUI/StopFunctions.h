
#ifndef STOPFUNCTIONS_H_
#define STOPFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
//#include <SDL/SDL_image.h>
#include </usr/local/lib/SDL_image-1.2.12/include/SDL/SDL_image.h>
#include "GUIUtils.h"
#include "GUIDefinitions.h"


#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL/SDL_image.h>
#include "GUIUtils.h"

void* stopGeneralSetup (Window* window);
void* stopSetDiffAndColor(Window* window);
void* stopSetBoard (Window* window);

#endif /* STOPFUNCTIONS_H_ */
