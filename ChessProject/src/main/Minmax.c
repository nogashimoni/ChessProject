
//
#include "ChessLogic.h"
#include "Minmax.h"


int minmax(Game* game,int depth, int alpha, int beta, int isMaximizing) {

	//halting condition.
	if ( depth == 0 || isCurrentPlayerLose(game) ) {
		return scoringFunction(game);
	}

	//Current player is maximizing.
	if ( isMaximizing ) {
		Moves* allMoves = getAllMoves(game);
		Move* move = allMoves->first;

		int val;
		int bestValue = INT_MIN;

		while ( move != NULL ) {
			Game* gameCopy = cloneGame(game); //doesn't clone move field
			doMove(gameCopy, move,0);

			// switch turns before recursive call
			switchTurns(gameCopy);

			//find score by rec call
			val = minmax(gameCopy,depth-1,alpha,beta,0);

			Move* tmpMove = move;
			move = move->next;
			if ( val > bestValue ) {
				bestValue = val;
				game->minmaxScore = bestValue;
				if ( game->minmaxMove != NULL ) {
					freeMove(game->minmaxMove); //frees only when not null
				}
				game->minmaxMove = tmpMove;
			}
			alpha = max(alpha, bestValue); //check where this needs to be put.
			if (alpha >= beta){
				break;
			}
		}
		//free moves
		//freeNullAndRemove(allMoves); //to be modified.
		return bestValue;
	}

	//Current player is minimizing
	else {
		Moves* moves = getAllMoves(game);
		Move* move = moves->first;

		int val;
		int bestValue = INT_MAX;

		while ( move != NULL ) {
			Game* gameCopy = cloneGame(game); //doesn't clone minmax fields
			gameCopy->minmaxScore = INT_MAX;
			doMove(gameCopy, move,0);
			// switch turns before recursive call

			switchTurns(gameCopy);

			//find score by rec call
			val = minmax(gameCopy,depth-1,alpha,beta,1);

			Move* tmpMove = move;
			move = move->next;
			if ( val < bestValue ) {
				bestValue = val;
				game->minmaxScore = bestValue;
				if ( game->minmaxMove != NULL ) {
					freeMove(game->minmaxMove); //frees only when not null
				}
				game->minmaxMove = tmpMove;
			}
			beta = min(beta, bestValue);//check where this needs to be put.
			if (alpha >= beta){
				break;
			}
		}
		//free moves
		//freeNullAndRemove(moves); // to be modified.
		return bestValue;
	}
}

int min(int x, int y){
	if (x>y){
		return y;
	}
	return x;
}

int max (int x, int y){
	if (x>y){
		return x;
	}
	return y;
}

Moves* getAllMoves(Game* game){

	Moves* allMoves = NULL;
	allMoves = calloc(sizeof(Moves), 1);
	if (allMoves != NULL){
		quit();
	}
	allMoves->first = NULL;
	allMoves->maxEats = 0;

	for (int i=0; i<BOARD_SIZE;i++){
		for (int j=0; j<BOARD_SIZE; j++){
			getMoves(game, i, j, 1);
			addMovesToAllMoves(allMoves);
			freeMoves(0);
		}
	}

	return allMoves;
}

int scoringFunction(Game* game) {
	/* Scoring function for the minimax. */
	int result;

	//someone lost
	if ( isCurrentPlayerLose(game) ) {
		int sign;
		if  (game->isComputerTurn) {
			sign = -1;
		}
		else {
			sign = 1;
		}
		return sign * 100;
	}

	// no one lost- we got to depth 0
	int numOfWhitePawns = 0;
	int numOfWhiteKnights = 0;
	int numOfWhiteBishops = 0;
	int numOfWhiteRooks = 0;
	int numOfWhiteQueens = 0;
	int numOfWhiteKings = 0;

	int numOfBlackPawns = 0;
	int numOfBlackKnights = 0;
	int numOfBlackBishops = 0;
	int numOfBlackRooks = 0;
	int numOfBlackQueens = 0;
	int numOfBlackKings = 0;
	int i,j;
	for ( i=0; i<BOARD_SIZE; i ++) {
		for ( j=0; j<BOARD_SIZE; j++ ) {
			 if ( game->board[i][j] == WHITE_P ) {
				 numOfWhitePawns ++;
			 }
			 if ( game->board[i][j] == WHITE_N ) {
				 numOfWhiteKnights ++;
			 }
			 if ( game->board[i][j] == WHITE_B ) {
				 numOfWhiteBishops ++;
			 }
			 if ( game->board[i][j] == WHITE_R ) {
				 numOfWhiteRooks ++;
			 }
			 if ( game->board[i][j] == WHITE_Q ) {
				 numOfWhiteQueens ++;
			 }
			 if ( game->board[i][j] == WHITE_K ) {
				 numOfWhiteKings ++;
			 }

			 if ( game->board[i][j] == BLACK_P ) {
				 numOfBlackPawns ++;
			 }
			 if ( game->board[i][j] == BLACK_N ) {
				 numOfBlackKnights ++;
			 }
			 if ( game->board[i][j] == BLACK_B ) {
				 numOfBlackBishops ++;
			 }
			 if ( game->board[i][j] == BLACK_R ) {
				 numOfBlackRooks ++;
			 }
			 if ( game->board[i][j] == BLACK_Q ) {
				 numOfBlackQueens ++;
			 }
			 if ( game->board[i][j] == BLACK_K ) {
				 numOfBlackKings ++;
			 }
		}
	}
	int whitePlayerScore = numOfWhitePawns + 3*(numOfWhiteKnights+numOfWhiteBishops) + 5*numOfWhiteRooks + 9*numOfWhiteQueens + 400*numOfWhiteKings;
	int blackPlayerScore = numOfBlackPawns + 3*(numOfBlackKnights+numOfBlackBishops) + 5*numOfBlackRooks + 9*numOfBlackQueens + 400*numOfBlackKings;

	if (!game->isWhiteTurn) {
		result = whitePlayerScore - blackPlayerScore;
	}
	else {
		result = blackPlayerScore - whitePlayerScore;
	}
	return result;
}

void addMovesToAllMoves(Moves* allMoves){

	if(moves->first == NULL){ // There are no moves in moves.
		return;
	}

	if (allMoves->first == NULL){
		Move* movesCurrMove = moves->first;
		Move* allMovesCurrMove = allMoves->first;
		allMovesCurrMove = cloneMove(movesCurrMove); //doesn't clone 'next'.
		while (movesCurrMove != NULL){
			allMovesCurrMove->next = cloneMove(movesCurrMove->next);
			movesCurrMove = movesCurrMove->next;
			allMovesCurrMove = allMovesCurrMove->next;
		}
	}

	else{
		Move* movesCurrMove = moves->first;
		while (movesCurrMove != NULL){
			Move* temp = allMoves->first;
			allMoves->first = cloneMove(movesCurrMove);
			movesCurrMove->next = temp;
		}
	}
}
