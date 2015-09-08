
#ifndef CHESSLOGIC_H_
#define CHESSLOGIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../services/ErrorHandling.h"
#include "ChessDefinitions.h"
//#include "Minmax.h"
//#include "../GUI/GUI.h"

extern Moves* moves;
extern Moves* movesTemp;

//**** functions declarations *******//
////Setup functions
void initGameFields(Game* game, int isGUIMode);
void setDisk(Game* game, char x, int y, char color, char* type);
int isLegalPeiceAddition(Game* game, char peice);
int countPeices(Game* game, char peice);
void removeDisk(Game* game, char x, int y);
void setGameMode(Game* game, char input);
void init_board(char board[BOARD_SIZE][BOARD_SIZE]);
void setDifficulty(Game* game, char* pointer);
void setUserColor(Game* game, char color);
void loadGameFromXML(Game* game, char* path);
void clearBoard(Game* game);
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int isInvalidXY(char x, unsigned int y);
void printMove(Move* move);
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
Move* cloneMove(Move* move);
Position* clonePosition(Position* position);


void doMove(Game* game, Move* move, int isPrintMove, char specialPawn);
int isSpecialPawnMove(Game* game, Position* first, Position* last);
int isCurrentPlayerStuck(Game* game);
int isCurrentPlayersKingInDanger(Game* game);
//free
void freeAndNull(void* obj);
void freeMove(Move* move);
void freeMoves();
void quit();

#endif
