/*
 * StartFunctions.c
 *
 *  Created on: Aug 29, 2015
 *      Author: nogalavi1
 */

#include "StopFunctions.h"

void* stopGeneralSetup (Window* window) {
	freeTree(window->UITreeHead);
	return NULL;
}
