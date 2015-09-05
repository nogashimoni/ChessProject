
#ifndef CHESSLOGIC_H_
#define CHESSLOGIC_H_

#include <stdio.h>
#include <stdlib.h>

#include "../services/ErrorHandling.h"
#include "ChessDefinitions.h"
//#include "Minmax.h"
//#include "../GUI/GUI.h"

extern Moves* moves;
extern Moves* movesTemp;

//**** functions declarations *******//
////main flow
//int setupGame(Game* game, int argc, char** argv);
//void play(Game*);
//void quit();
//// board init and print
//void print_line();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
//void init_board(char board[BOARD_SIZE][BOARD_SIZE]);
//int countPeices(Game* game, char peice);
//unsigned int yToJ(unsigned int y);
//unsigned int xToI(char x);
//int jToY(int j);
//char iToX(int i);
int isInvalidXY(char x, unsigned int y);
void printMove(Move* move);
//// cmd parsing
//void getCmdFromUser(char* output);
//void removeSpaces(char* string);
//// setup
//void setGameMode(Game* game, char input);
//void setDifficulty(Game* game, char* input);
//void setUserColor(Game* game, char color);
//void loadGameFromXML(Game* game, char* path);
//void clearBoard(Game* game);
//void removeDisk(Game* game, char x, int y);
//void setDisk(Game* game, char x, int y, char color, char* type);
//int isLegalPeiceAddition(Game* game, char peice);
//game
Moves* getMoves(Game* game, int x, int y, int isCheckRelevence);
void getMovesForPiece(Game* game, int x, int y, Moves* movesCopy);
void getPawnMoves(Game* game, Moves* moves, int x, int y);
void getKnightMoves(Game* game, Moves* moves, int x, int y);
void getKingMoves(Game* game, Moves* moves, int x, int y);
void getBishopMoves(Game* game, Moves* moves, int x, int y);
void getRookMoves(Game* game, Moves* moves, int x, int y);
void getQueenMoves(Game* game, Moves* moves, int x, int y);
Move* creatNewMove(int startX, int startY, int endX, int endY);
void addToMoves(Moves* moves, Move* newMove);
void removeUnreleventMoves(Game* game, Moves* moves);
Game* cloneGame(Game* game);
int isEndangeringKingMove (Game* game, Move* move);
int isEatingOpponentKing(Game* game, Move* move);
int isOpponentKingPosition(Game* game, int x, int y);
int isCurrentPlayerPeice(Game* game, int i, int j);
int isValidIJ(int i, int j);
void switchTurns(Game* game);
void computerTurn(Game* game);
int getPieceColor(Game* game, int i, int j);
void userTurn(Game* game);
Move* createMoveFromString(char* cmd);
int isValidMove(Game* game, Move* move);
int compareMoves(Move* m1, Move* m2);
int comparePositions(Position* p1, Position* p2);
//void addMovesToAllMoves(Moves* allMoves);
Move* cloneMove(Move* move);
Position* clonePosition(Position* position);


void doMove(Game* game, Move* move, int printMove);
int isCurrentPlayerLose(Game* game);
int isCurrentPlayersKingInDanger(Game* game);
//free
void freeAndNull(void* obj);
void freeMove(Move* move);
void freeMoves();
void quit();

#endif
