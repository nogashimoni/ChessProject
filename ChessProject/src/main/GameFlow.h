
#ifndef GAMEFLOW_H_
#define GAMEFLOW_H_

#include <stdio.h>
#include <stdlib.h>

#include "ChessDefinitions.h"
#include "ChessLogic.h"
#include "Minmax.h"
#include "../GUI/GUI.h"

extern Moves* moves;
extern Moves* movesTemp;

//Functions declarations
int main(int argc, char **argv);
void setupGameByConsole(Game* game);
void getCmdFromUser(char* output);
void removeSpaces(char* string);
void playByConsole(Game* game);
void computerTurn(Game* game);
void userTurn(Game* game);
Move* createMoveFromString(char* cmd);
void setDisk(Game* game, char x, int y, char color, char* type);
void getBestMoveForUser(Game* game);
int getScore(Game* game, Move* move, int d);




#endif /* GAMEFLOW_H_ */
