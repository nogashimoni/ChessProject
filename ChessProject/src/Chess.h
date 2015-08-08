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

#define ILLEGAL_COMMAND "Illegal command, please try again\n"
#define ILLEGAL_MOVE "Illegal move\n"
 
#define WRONG_ROOK_POSITION "Wrong position for a rook\n" 
#define ILLEGAL_CALTLING_MOVE "Illegal castling move\n"  

#define TIE "The game ends in a tie\n"
 
#define print_message(message) (printf("%s", message));



//ours
#include <stdio.h>
#include <stdlib.h>


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
	int minmaxDepth;
	int isUserWhite;
	char isWhiteTurn;
	int isConsoleMode;
	int isTwoPlayersMode;
	int minmaxScore;
	Move* minmaxMove;
} Game;

#endif
