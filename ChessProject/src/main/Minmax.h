
#ifndef MINMAX_H_
#define MINMAX_H_

#include <stdio.h>
#include <stdlib.h>

#include <limits.h>
#include "ChessDefinitions.h"
#include "ChessLogic.h"

extern Moves* moves;
extern Moves* movesTemp;

//Function declarations
int minmax(Game* game,int depth, int alpha, int beta, int isMaximizing);
int min(int x, int y);
int max (int x, int y);
Moves* getAllMoves(Game* game);
int scoringFunction(Game* game);
void addMovesToAllMoves(Moves* allMoves);

#endif /* MINMAX_H_ */
