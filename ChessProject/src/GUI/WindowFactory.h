#ifndef WINDOWFACTORY_H_
#define WINDOWFACTORY_H_

#include "../main/Chess.h"
#include "GUI.h"
#include "GUIUtils.h"
#include "../services/ErrorHandling.h"
#include "GUIDefinitions.h"

Window initWindow(WindowId id);

int welcomeWindowStart (Window* window, void* initData);
void welcomeWindowClip( SDL_Rect* clip );
int setupWindowStart (Window* window, void* initData);

EventID welcomeWindowTranslateEvent(Window* window, SDL_Event* event);
EventID setupWindowTranslateEvent(Window* window, SDL_Event* event);

int welcomeWindowHandleEvent(Window* window, EventID eventID);
int setupWindowHandleEvent(Window* window, EventID eventID);



#endif /* WINDOWFACTORY_H_ */
