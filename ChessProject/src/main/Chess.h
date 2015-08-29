#ifndef CHESS_
#define CHESS_

#define WHITE_P 'm'
#define WHITE_B 'b'
#define WHITE_N 'n'
#define WHITE_R 'r'
#define WHITE_Q 'q'
#define WHITE_K 'k'

#define BLACK_P 'M'
#define BLACK_B 'B'
#define BLACK_N 'N'
#define BLACK_R 'R'
#define BLACK_Q 'Q'
#define BLACK_K 'K'


#define EMPTY ' '

#define BOARD_SIZE 8

// board initialization
#define ENTER_SETTINGS "Enter game settings:\n" 
#define WRONG_GAME_MODE "Wrong game mode\n"
#define TWO_PLAYERS_GAME_MODE "Running game in 2 players mode\n"
#define PLAYER_VS_AI_GAME_MODE "Running game in player vs. AI mode\n"
#define WRONG_MINIMAX_DEPTH "Wrong value for minimax depth. The value should be between 1 to 4\n"
#define WRONG_FILE_NAME "Wrong file name\n"
#define WRONG_POSITION "Invalid position on the board\n"
#define NO_PIECE "Setting this piece creates an invalid board\n"  
#define WROND_BOARD_INITIALIZATION "Wrong board initialization\n"

#define ENTER_MOVE " player - enter your move:\n"
#define ILLEGAL_COMMAND "Illegal command, please try again\n"
#define ILLEGAL_MOVE "Illegal move\n"
 
#define WRONG_ROOK_POSITION "Wrong position for a rook\n" 
#define ILLEGAL_CALTLING_MOVE "Illegal castling move\n"  

#define TIE "The game ends in a tie\n"
 
#define print_message(message) (printf("%s", message));



//ours
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
#include "../GUI/GUI.h"
#include "../services/ErrorHandling.h"


struct Position{
	int x;
	int y;
	struct Position* next;
};
typedef struct Position Position;

struct Move{
	Position* first;
	int eats;
	struct Move* next;
};
typedef struct Move Move;

typedef struct Moves {
	Move* first;
	int maxEats;
} Moves;

typedef struct Game {
	char board[BOARD_SIZE][BOARD_SIZE];
	int isRunning;
	int isGUIMode;
	int isTwoPlayersMode;

	// user-user
	int isWhiteTurn;

	// computer-user
	int minmaxDepth;
	int isComputerTurn;
	int isUserWhite;
	int minmaxScore;
	Move* minmaxMove;
} Game;


//**** functions declarations *******//
//main flow
int setupGame(Game* game, int argc, char** argv);
void play(Game*);
void quit();
// board init and print
void print_line();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
void init_board(char board[BOARD_SIZE][BOARD_SIZE]);
int countPeices(Game* game, char peice);
unsigned int yToJ(unsigned int y);
unsigned int xToI(char x);
int jToY(int j);
char iToX(int i);
int isInvalidXY(char x, unsigned int y);
void printMove(Move* move);
// cmd parsing
void getCmdFromUser(char* output);
void removeSpaces(char* string);
// setup
void setGameMode(Game* game, char input);
void setDifficulty(Game* game, char* input);
void setUserColor(Game* game, char color);
void loadGameFromXML(Game* game, char* path);
void clearBoard(Game* game);
void removeDisk(Game* game, char x, int y);
void setDisk(Game* game, char x, int y, char color, char* type);
int isLegalPeiceAddition(Game* game, char peice);
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

void doMove(Game* game, Move* move, int printMove);
int currentPlayerLose(Game* game);
//free
void freeAndNull(void* obj);
void freeMove(Move* move);
void freeMoves();

#endif
