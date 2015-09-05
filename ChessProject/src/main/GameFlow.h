
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
void init_board(char board[BOARD_SIZE][BOARD_SIZE]);
void getCmdFromUser(char* output);
void removeSpaces(char* string);
int setupGame(Game* game, int argc, char** argv);
void setDisk(Game* game, char x, int y, char color, char* type);
int isLegalPeiceAddition(Game* game, char peice);
int countPeices(Game* game, char peice);
void removeDisk(Game* game, char x, int y);
void setGameMode(Game* game, char input);
void setDifficulty(Game* game, char* pointer);
void setUserColor(Game* game, char color);
void loadGameFromXML(Game* game, char* path);
void clearBoard(Game* game);
void play(Game* game);
void computerTurn(Game* game);
void userTurn(Game* game);
Move* createMoveFromString(char* cmd);
void setDisk(Game* game, char x, int y, char color, char* type);




#endif /* GAMEFLOW_H_ */
