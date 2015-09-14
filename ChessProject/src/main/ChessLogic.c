
#include "ChessLogic.h"

void setDisk(Game* game, char x, int y, char color, char* type) {
	/* sets a piece in a specified legal position */
	if (isInvalidXY(x, y)) {
		print_message(WRONG_POSITION);
		return;
	}
	int i = xToI(x);
	int j = yToJ(y);
	char peice = ' ';
	if (*type == 'k' && *(type + 1) == 'i') {
		peice = (color == 'w' ? WHITE_K : BLACK_K);
	} else if (*type == 'k' && *(type + 1) == 'n') {
		peice = (color == 'w' ? WHITE_N : BLACK_N);
	} else if (*type == 'q') {
		peice = (color == 'w' ? WHITE_Q : BLACK_Q);
	} else if (*type == 'r') {
		peice = (color == 'w' ? WHITE_R : BLACK_R);
	} else if (*type == 'b') {
		peice = (color == 'w' ? WHITE_B : BLACK_B);
	} else if (*type == 'p') {
		peice = (color == 'w' ? WHITE_P : BLACK_P);
	}

	if (isLegalPeiceAddition(game, peice)) {
		game->board[i][j] = peice;
	} else {
		print_message(NO_PIECE);
	}
}

int isLegalPeiceAddition(Game* game, char peice) {
	int n = countPeices(game, peice);
	int isLegalKingAdd = (peice == WHITE_K || peice == BLACK_K) && (n == 0);
	int isLegalQweenAdd = (peice == WHITE_Q || peice == BLACK_Q) && (n == 0);
	int isLegalRookAdd = (peice == WHITE_R || peice == BLACK_R) && (n < 2);
	int isLegalKnightAdd = (peice == WHITE_N || peice == BLACK_N) && (n < 2);
	int isLegalBishopAdd = (peice == WHITE_B || peice == BLACK_B) && (n < 2);
	int isLegalPawnAdd = (peice == WHITE_P || peice == BLACK_P) && (n < 8);

	int result = isLegalKingAdd || isLegalQweenAdd || isLegalRookAdd
			|| isLegalKnightAdd || isLegalBishopAdd || isLegalPawnAdd;
	return result;
}

int countPeices(Game* game, char peice) {
	int peiceTypeCount = 0;
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if (game->board[i][j] == peice) {
				peiceTypeCount++;
			}
		}
	}
	return peiceTypeCount;
}

void removeDisk(Game* game, char x, int y) {
	/* checks if the specified location is valid and sets to empty*/
	if (isInvalidXY(x, y)) {
		print_message(WRONG_POSITION);
		return;
	}
	int i = xToI(x);
	int j = yToJ(y);

	game->board[i][j] = EMPTY;
}

void setGameMode(Game* game, char input) {
	if (input == '1') {
		game->isTwoPlayersMode = 1;
		print_message(TWO_PLAYERS_GAME_MODE);
	} else if (input == '2') {
		game->isTwoPlayersMode = 0;
		print_message(PLAYER_VS_AI_GAME_MODE);
	} else {
		print_message(WRONG_GAME_MODE);
	}
}

void setDifficulty(Game* game, char* pointer) {
	if (game->isTwoPlayersMode) {
		print_message(ILLEGAL_COMMAND);
		return;
	}
	if (*pointer == 'd') {
		int num = (int) strtol(pointer + 5, (char**) NULL, 10);
		int numIsGreaterThan10 = (*(pointer + 6) == '\0' ? 0 : 1);
		if (numIsGreaterThan10 || num == 0 || num > 4) {
			print_message(WRONG_MINIMAX_DEPTH);
		} else {
			game->minmaxDepth = num;
		}
	} else if (*pointer == 'b') {
		game->minmaxDepth = 4;
		game->isBest = 1;
	} else {
		print_message(ILLEGAL_COMMAND);
	}
}

void setUserColor(Game* game, char color) {
	if (game->isTwoPlayersMode) {
		print_message(ILLEGAL_COMMAND);
		return;
	}
	if (color == 'b') {
		game->isUserWhite = 0;
		game->isComputerTurn=1;
	} else if (color == 'w') {
		game->isUserWhite = 1;
		game->isComputerTurn=0;
	} else {
		print_message(ILLEGAL_COMMAND);
	}
}

void loadGame(Game* game, char* path) {
	if (loadGameFromFile(game, path) == 0){
		print_message(WRONG_FILE_NAME);
		return;
	}
	print_board(game->board);
}

void saveGame(Game* game, char* path){

	if (saveGameToFile(game, path) == 0){
		print_message(WRONG_FILE_NAME);
	}

}

void clearBoard(Game* game) {
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++)
			game->board[i][j] = EMPTY;
}

void initGameFields(Game* game, int isGUIMode) {
	game->isGUIMode = isGUIMode;
	game->minmaxDepth = 1;
	game->minmaxMove = NULL;
	game->isWhiteTurn = 1;
	game->isTwoPlayersMode = 1;
	game->isUserWhite = 1; // relevant only in player vs. ai mode
	game->isRunning=1;
	game->isComputerTurn=!game->isUserWhite;
	init_board(game->board);
	game->isBest = 0;
}

void init_board(char board[BOARD_SIZE][BOARD_SIZE]) {
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if (j == 0 || j == 7) {
				if (i == 0 || i == 7) {
					board[i][j] = (j == 0 ? WHITE_R : BLACK_R);
				} else if (i == 1 || i == 6) {
					board[i][j] = (j == 0 ? WHITE_N : BLACK_N);
				} else if (i == 2 || i == 5) {
					board[i][j] = (j == 0 ? WHITE_B : BLACK_B);
				} else if (i == 3) {
					board[i][j] = (j == 0 ? WHITE_Q : BLACK_Q);
				} else if (i == 4) {
					board[i][j] = (j == 0 ? WHITE_K : BLACK_K);
				}
			} else if (j == 1 || j == 6) {
				board[i][j] = (j == 1 ? WHITE_P : BLACK_P);
			} else {
				board[i][j] = EMPTY;
			}
		}
	}
}


void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
	int i, j;
	print_line();
	for (j = BOARD_SIZE - 1; j >= 0; j--) {
		printf((j < 9 ? " %d" : "%d"), j + 1);
		for (i = 0; i < BOARD_SIZE; i++) {
			printf("| %c ", board[i][j]);
		}
		printf("|\n");
		print_line();
	}
	printf("   ");
	for (j = 0; j < BOARD_SIZE; j++) {
		printf(" %c  ", (char) ('a' + j));
	}
	printf("\n");
}

void printMove(Move* move){
	printf("<%c,%u> to ",iToX((move->first)->x),jToY((move->first)->y));
	Position* currPosition = (move->first)->next;
	while ( currPosition != NULL ) {
		printf("<%c,%u>", iToX(currPosition->x) ,jToY(currPosition->y));
		currPosition = currPosition->next;
	}
	printf("\n");
}


int isInvalidIJ(unsigned int i, unsigned int j) {
	if (i < 0 || i > BOARD_SIZE - 1 || j < 0 || j > BOARD_SIZE - 1)
		return 1;
	return 0;
}

int isInvalidXY(char x, unsigned int y) {
	unsigned int i, j;
	i = xToI(x);
	j = yToJ(y);
	return !isValidIJ(i,j);
}

int isCheck(Game* game){
	if (isCurrentPlayersKingInDanger(game) && !isCurrentPlayerLose(game)){
		return 1;
	}
	return 0;
}

int isTie(Game* game){
	if (!isCurrentPlayersKingInDanger(game) && isCurrentPlayerStuck(game)){
		return 1;
	}
	return 0;
}

int isCurrentPlayerLose(Game* game){
	if (isCurrentPlayersKingInDanger(game) && isCurrentPlayerStuck(game)){
		return 1;
	}
	return 0;
}

int isCurrentPlayerStuck(Game* game){

	for (int i=0; i<BOARD_SIZE; i++){
		for (int j=0; j<BOARD_SIZE; j++){
			getMoves(game, i, j, 1);
			if (moves->first != NULL){
				freeMoves(0);
				return 0;
			}
			freeMoves(0);
		}
	}
	return 1;
}

int isCurrentPlayersKingInDanger(Game* game){
/*Checks if current player's king is in danger - 'Check' for current player*/

	Game* gameCopy = cloneGame(game);
	switchTurns(gameCopy);

	for (int i=0; i<BOARD_SIZE; i++){
		for (int j=0; j<BOARD_SIZE; j++){
			getMoves(gameCopy, i, j, 0);
			Move* moveCurr = movesTemp->first;
			while (moveCurr != NULL){
				if (isEatingOpponentKing(gameCopy, moveCurr)){
					if (gameCopy != NULL){
						free(gameCopy);
						gameCopy = NULL;
					}
					freeMoves(1);
					return 1;
				}
				moveCurr = moveCurr->next;
			}
			freeMoves(1);
		}
	}

	if (gameCopy != NULL){
		free(gameCopy);
		gameCopy = NULL;
	}

	return 0;
}

int isValidMove(Game* game, Move* move) {

	getMoves(game, move->first->x, move->first->y, 1);
	Move* first = moves->first;
	while (first != NULL){
		if (compareMoves(first,move)){
			freeMoves(0);
			return 1;
		}
		first = first->next;
	}
	if (moves != NULL){
		freeMoves(0);
	}
	if (!game->isGUIMode){
		print_message(ILLEGAL_MOVE);
	}
	return 0;
}

int isValidMoveIJ(Game* game, int i1, int j1, int i2, int j2){

	Move* move = creatNewMove(i1, j1, i2, j2);
	int result = isValidMove(game, move);
	freeMove(move);
	return result;

}

void doMoveIJ(Game* game, int i1, int j1, int i2, int j2, char specialPawn){

	Move* move = creatNewMove(i1, j1, i2, j2);
	doMove(game, move, 0, specialPawn);
	freeMove(move);

}

int compareMoves(Move* m1, Move* m2){
	int i = comparePositions(m1->first,m2->first);
	int j =comparePositions(m1->first->next,m2->first->next);
	return (i && j);
}

int comparePositions(Position* p1, Position* p2){
	if ((p1->x != p2->x) || (p1->y != p2->y)){
		return 0;
	}
	return 1;
}

void doMove(Game* game, Move* move, int isPrintMove, char specialPawn) {
/*Performs move on the game board. */
	if (isPrintMove){
		printMove(move);
	}

	Position* first = move->first;
	Position* last = first->next;
	if (isSpecialPawnMove(game, first, last)){
		if (specialPawn == EMPTY){ //default for special pawn move is queen.
			if (game->isWhiteTurn){
				game->board[last->x][last->y] = WHITE_Q;
				game->board[first->x][first->y] = EMPTY;
			}
			else {
				game->board[last->x][last->y] = BLACK_Q;
				game->board[first->x][first->y] = EMPTY;
			}
			return;
		}
		game->board[last->x][last->y] = specialPawn;
		game->board[first->x][first->y] = EMPTY;
		return;
	}
	game->board[last->x][last->y] = game->board[first->x][first->y];
	game->board[first->x][first->y] = EMPTY;

}

int isSpecialPawnMove(Game* game, Position* first, Position* last){

	if (game->board[first->x][first->y] == BLACK_P || game->board[first->x][first->y] == WHITE_P){
			if (last->y == BOARD_SIZE-1 && game->isWhiteTurn){
				return 1;
			}
			if (last->y == 0 && !game->isWhiteTurn){
				return 1;
			}
	}
	return 0;
}


void switchTurns(Game* game) {
	if (game->isWhiteTurn){
		game->isWhiteTurn = 0;
	}
	else{
		game->isWhiteTurn = 1;
	}

	if (!(game->isTwoPlayersMode) ) {
		game->isComputerTurn=!game->isComputerTurn;
	}
}

/* Returns all legal moves for a certian piece */

Moves* getMoves(Game* game, int x, int y, int isCheckRelevence ){

	if (isCheckRelevence){
		moves = calloc(sizeof(Moves),1);
		if ( moves == NULL ) {
			notifyFunctionFailure("getMoves");
			quit();
		}

		moves->maxEats = 0;

		moves->first = NULL;

		getMovesForPiece(game, x, y, moves);

		removeUnreleventMoves(game, moves);

		return moves;
	}

	else{
		movesTemp = calloc(sizeof(Moves),1);
		if ( movesTemp == NULL ) {
			notifyFunctionFailure("getMoves");
			quit();
		}

		movesTemp->maxEats = 0;

		movesTemp->first = NULL;

		getMovesForPiece(game, x, y, movesTemp);

		return movesTemp;
	}

}

void getMovesForPiece(Game* game, int x, int y, Moves* movesCopy){

	if (isCurrentPlayerPeice(game, x, y)){
		//Piece is a Pawn
		if (game->board[x][y] == WHITE_P || game->board[x][y] == BLACK_P){
			getPawnMoves(game, movesCopy, x, y);
		}
		//Piece is a Knight.
		else if (game->board[x][y] == WHITE_N || game->board[x][y] == BLACK_N){
			getKnightMoves(game, movesCopy, x, y);
		}
		//Piece is a King.
		else if (game->board[x][y] == WHITE_K || game->board[x][y] == BLACK_K){
			getKingMoves(game, movesCopy, x, y);
		}
		//Piece is a Bishop.
		else if (game->board[x][y] == WHITE_B || game->board[x][y] == BLACK_B){
			getBishopMoves(game, movesCopy, x, y);
		}
		//Piece is a Queen.
		else if (game->board[x][y] == WHITE_Q || game->board[x][y] == BLACK_Q){
			getQueenMoves(game, movesCopy, x, y);
		}
		//Piece is a Rook.
		else if (game->board[x][y] == WHITE_R || game->board[x][y] == BLACK_R){
			getRookMoves(game, movesCopy, x, y);
		}
	}

}


void removeUnreleventMoves(Game* game, Moves* moves){
	/* Out of all possible move, removes moves with not enough eats and frees them */

	Move* prevMove = moves->first;

	if (prevMove == NULL){
		return;
	}

	int isNotLegalMove = isEndangeringKingMove(game,prevMove);

	while (isNotLegalMove){
		moves->first = prevMove->next;
		Move* tmpPrev = prevMove;
		prevMove = prevMove->next;
		freeMove(tmpPrev);
		if (prevMove == NULL){
			moves->first = NULL;
			moves->maxEats = 0;
			return;
		}
		isNotLegalMove = isEndangeringKingMove(game,prevMove);
	}

	Move* currMove = prevMove->next;

	while (currMove != NULL){

		if (isEndangeringKingMove(game, currMove)){
			prevMove->next = currMove->next;
			Move* tmpCurr = currMove;
			currMove = currMove->next;
			freeMove(tmpCurr);
			continue;
		}
		prevMove = currMove;
		currMove = currMove->next;

	}
}


int isEndangeringKingMove (Game* game, Move* move){
	/*Checks if the move puts the player's king in a danger (check) */

	Game* gameCopy = cloneGame(game);

	doMove(gameCopy, move, 0, EMPTY);
	switchTurns(gameCopy);

	for (int i=0; i<BOARD_SIZE;i++){
		for (int j=0; j<BOARD_SIZE; j++){
			getMoves(gameCopy, i, j, 0);
			Move* moveCurr = movesTemp->first;
			while (moveCurr != NULL){
				if (isEatingOpponentKing(gameCopy, moveCurr)){
					if (gameCopy != NULL){
						free(gameCopy);
						gameCopy = NULL;
					}
					freeMoves(1);
					return 1;
				}
				moveCurr = moveCurr->next;
			}
			freeMoves(1);
		}
	}
	if (gameCopy != NULL){
		free(gameCopy);
		gameCopy = NULL;
	}
	return 0;
}

int isEatingOpponentKing(Game* game, Move* move){
	/*Checks if the 'move' is eating the opponent's king */
	if (isOpponentKingPosition(game, move->first->next->x, move->first->next->y)){
		return 1;
	}
	return 0;
}

int isOpponentKingPosition(Game* game, int x, int y){
	/*Checks if the Opponent's king is in position x,y */
	if (game->isWhiteTurn && game->board[x][y] == BLACK_K){
		return 1;
	}
	if (!game->isWhiteTurn && game->board[x][y] == WHITE_K){
		return 1;
	}
	return 0;
}


void getPawnMoves(Game* game, Moves* movesCopy, int x, int y){
	//Pawn is white - standard move.
	if (isValidIJ(x,y+1)){
		if (game->isWhiteTurn && (game->board[x][y+1] == EMPTY)){
			Move* move = creatNewMove(x, y, x, y+1);
			move->eats=0;
			addToMoves(movesCopy,move);
		}
	}
	//Pawn is white - check for eats.
	if (game->isWhiteTurn){
		for (int i=-1 ; i<=1; i+=2){
			if (!isValidIJ(x+i,y+1)){
				continue;
			}
			if ( (!game->isWhiteTurn)==getPieceColor(game, x+i,y+1) ){
				Move* move = creatNewMove(x, y, x+i, y+1);
				move->eats=1;
				addToMoves(movesCopy,move);
			}
		}
	}

	//Pawn is black - standard move.
	if (isValidIJ(x,y-1)){
		if ((!game->isWhiteTurn) && game->board[x][y-1] == EMPTY){
			Move* move = creatNewMove(x, y, x, y-1);
			move->eats=0;
			addToMoves(movesCopy,move);
		}
	}
	//Pawn is black - check for eats
	if (!game->isWhiteTurn){
		for (int i=-1 ; i<=1; i+=2){
			if (!isValidIJ(x+i,y-1)){
				continue;
			}
			int pieceColor = getPieceColor(game, x+i,y-1);
			if (pieceColor == 1){
				Move* move = creatNewMove(x, y, x+i, y-1);
				move->eats=1;
				addToMoves(movesCopy,move);
			}
		}
	}
}

void getKnightMoves(Game* game, Moves* movesCopy, int x, int y){

	for (int i=-1;i<=1;i+=2){
		for (int j=-1; j<=1; j+=2){
			if (isValidIJ(x+1*i,y+2*j)){
				if (!isCurrentPlayerPeice(game, x+1*i,y+2*j)){
					Move* move = creatNewMove(x, y, x+1*i,y+2*j);
					if (getPieceColor(game, x+1*i,y+2*j) != -1){
						move->eats=1;
					}
					addToMoves(movesCopy,move);
				}
			}
			if (isValidIJ(x+2*i,y+1*j)){
				if (!isCurrentPlayerPeice(game, x+2*i,y+1*j)){
					Move* move = creatNewMove(x, y, x+2*i,y+1*j);
					if (getPieceColor(game, x+2*i,y+1*j) != -1){
						move->eats=1;
					}
					addToMoves(movesCopy,move);
				}
			}
		}
	}
}

void getKingMoves(Game* game, Moves* movesCopy, int x, int y){
	for (int i=-1 ; i<=1;i++){
		for (int j=-1; j<=1;j++){
			if (i==j && j==0){
				continue;
			}
			if (!isValidIJ(x+i,y+j)){
				continue;
			}
			if (!isCurrentPlayerPeice(game, x+i,y+j)){
				Move* move = creatNewMove(x, y, x+i,y+j);
				if (getPieceColor(game, x+i,y+j) != -1){
					move->eats=1;
				}
				addToMoves(movesCopy,move);
			}
		}

	}
}

void getBishopMoves(Game* game, Moves* movesCopy, int x, int y){

	for (int r=-1; r<=1;r+=2){
		for (int j=-1; j<=1;j+=2){
			for (int i=1; i<=BOARD_SIZE;i++){
				if (!isValidIJ(x+i*j,y+i*r)){
					break;
				}
				if (isCurrentPlayerPeice(game, x+i*j,y+i*r)){
					break;
				}
				if (!isCurrentPlayerPeice(game, x+i*j,y+i*r) && isValidIJ(x+i*j,y+i*r)){
					Move* move = creatNewMove(x, y, x+i*j,y+i*r);
					if (getPieceColor(game, x+i*j,y+i*r) != -1){
						move->eats=1;
						addToMoves(movesCopy,move);
						break;
					}
					addToMoves(movesCopy,move);
				}
			}
		}
	}
}

void getRookMoves(Game* game, Moves* movesCopy, int x, int y){

	for (int j=-1; j<=1;j+=2){
		for (int i=1; i<=BOARD_SIZE;i++){
			if (!isValidIJ(x+i*j,y)){
				break;
			}
			if (isCurrentPlayerPeice(game, x+i*j,y)){
				break;
			}
			else if (!isCurrentPlayerPeice(game, x+i*j,y)){
				Move* move = creatNewMove(x, y, x+i*j,y);
				if (getPieceColor(game, x+i*j,y) != -1){
					move->eats=1;
					addToMoves(movesCopy,move);
					break;
				}
				addToMoves(movesCopy,move);
			}
		}
	}

	for (int j=-1; j<=1;j+=2){
		for (int i=1; i<=BOARD_SIZE;i++){
			if (!isValidIJ(x,y+i*j)){
				break;
			}
			if (isCurrentPlayerPeice(game, x,y+i*j)){
				break;
			}
			if (!isCurrentPlayerPeice(game, x,y+i*j)){
				Move* move = creatNewMove(x, y, x,y+i*j);
				if (getPieceColor(game, x,y+i*j) != -1){
					move->eats=1;
					addToMoves(movesCopy,move);
					break;
				}
				addToMoves(movesCopy,move);
			}
		}
	}
}

void getQueenMoves(Game* game, Moves* movesCopy, int x, int y){

	getRookMoves(game, movesCopy, x, y);
	getBishopMoves(game, movesCopy, x, y);

}


Move* creatNewMove(int startX, int startY, int endX, int endY){
	Position* position = NULL;
	position = calloc(sizeof(Position), 1);
	if (position == NULL){
		quit();
	}
	position->x = startX;
	position->y = startY;
	position->next = NULL;
	Move* move = NULL;
	move = calloc(sizeof(Move), 1);
	if (move == NULL){
		quit();
	}
	move->first = position;
	Position* newPosition = NULL;
	newPosition = calloc(sizeof(Position), 1);
	if (newPosition == NULL){
		freeMove(move);
		quit();
	}
	newPosition->x = endX;
	newPosition->y = endY;
	move->first->next = newPosition;
	move->eats = 0;
	move->next = NULL;
	return move;
}


//what if newMove == NULL??
int isCurrentPlayerPeice(Game* game, int i, int j) {
	/* receives a legal i,j and returns 1 if it's the current player's piece */
	if (!isValidIJ(i,j)){
		return 0;
	}
	if (game->board[i][j] == EMPTY){
		return 0;
	}
	if ( game->isWhiteTurn && (getPieceColor(game,i,j)==1)) {
		return 1;
	}
	if ( (!game->isWhiteTurn) && ((0 == getPieceColor(game,i,j))) ) {
		return 1;
	}
	return 0;

}

int getPieceColor(Game* game, int i, int j){
	/*Returns 1 is white, 0 if black, -1 if empty */
	//The piece is white - returns 1.
	if (game->board[i][j] == WHITE_P ||
	                   game->board[i][j] == WHITE_B ||
	                                  game->board[i][j] == WHITE_N
	                                		  ||game->board[i][j] == WHITE_R ||
	                                		                   game->board[i][j] == WHITE_Q ||
	                                		                                  game->board[i][j] == WHITE_K){
		return 1;
	}
	//The piece is black - returns 0.
	if (game->board[i][j] == BLACK_P ||
	                   game->board[i][j] == BLACK_B ||
	                                  game->board[i][j] == BLACK_N
	                                		  ||game->board[i][j] == BLACK_R ||
	                                		                   game->board[i][j] == BLACK_Q ||
	                                		                                  game->board[i][j] == BLACK_K){
		return 0;
	}
	return -1; //The square is empty.

}

int isValidIJ(int i, int j) {
	if ( i < 0 || i > BOARD_SIZE-1 || j < 0 || j > BOARD_SIZE-1 )
		return 0;
	return 1;
}

void addToMoves(Moves* movesCopy, Move* newMove){
	/* Add a move to the linked list moves */
	if (movesCopy->first == NULL){
		movesCopy->first = newMove;
		return;
	}
	Move* temp = movesCopy->first;
	movesCopy->first = newMove;
	newMove->next = temp;

	if (newMove->eats > movesCopy->maxEats){
		movesCopy->maxEats = newMove->eats;
	}
}

Game* cloneGame(Game* game){
	Game* gameCopy = NULL;
	gameCopy = calloc(sizeof(Game), 1);
	if (gameCopy == NULL){
		quit();
	}

	for (int i=0; i<BOARD_SIZE; i++){
		for (int j=0; j<BOARD_SIZE; j++){
			gameCopy->board[i][j]=game->board[i][j];
		}
	}

	gameCopy->isComputerTurn = game->isComputerTurn;
	gameCopy->isGUIMode = game->isGUIMode;
	gameCopy->isRunning = game->isRunning;
	gameCopy->isTwoPlayersMode = game->isRunning;
	gameCopy->isUserWhite = game->isUserWhite;
	gameCopy->isWhiteTurn = game->isWhiteTurn;
	gameCopy->minmaxDepth = game->minmaxDepth;
	gameCopy->isBest = game->isBest;
	gameCopy->minmaxMove = NULL;
	gameCopy->minmaxScore = game->minmaxScore;
	return gameCopy;
}

Move* cloneMove(Move* move){

	if (move == NULL){
		return NULL;
	}

	Move* moveCopy = NULL;
	moveCopy = calloc(sizeof(Move),1);
	if (moveCopy == NULL){
		quit();
	}
	moveCopy->eats = move->eats;
	moveCopy->next = NULL;
	moveCopy->first = clonePosition(move->first);
	moveCopy->first->next = clonePosition(move->first->next);

	return moveCopy;
}

Position* clonePosition(Position* position){

	Position* positionCopy = NULL;
	positionCopy = calloc(sizeof(Position), 1);
	if (positionCopy == NULL){
		quit();
	}
	positionCopy->x = position->x;
	positionCopy->y = position->y;
	positionCopy->next = NULL;
	return positionCopy;
}

void freeAndNull(void* obj) {
	if ( obj != NULL ) {
		free(obj);
	}
	obj = NULL;
}

void quit() {
	if (moves != NULL){
		freeMoves(0);
	}
	if (movesTemp != NULL){
		freeMoves(1);
	}
	exit(0);
}

void freeMove(Move* move){
	if (move != NULL){
		Position* curr = move->first;
		while ( curr != NULL ) {
			Position* next = curr->next;
			free(curr);
			curr = NULL;
			curr = next;
		}
		free(move);
	}
	move = NULL;
}

void freeMoves(int isTmpMoves){

	if (isTmpMoves){
		if (movesTemp != NULL){
			Move* currMove = movesTemp->first;
			while ( currMove != NULL ) {
				Move* prevMove=currMove;
				currMove = currMove->next;
				freeMove(prevMove);
			}
			free(movesTemp);
		}
		movesTemp = NULL;
	}

	else {
		if (moves != NULL){
			Move* currMove = moves->first;
			while ( currMove != NULL ) {
				Move* prevMove=currMove;
				currMove = currMove->next;
				freeMove(prevMove);
			}
			free(moves);
		}
		moves = NULL;
	}
}

int getBestMoveI1(Move* move){

	return move->first->x;

}

int getBestMoveI2(Move* move){

	return move->first->next->x;

}

int getBestMoveJ1(Move* move){

	return move->first->y;

}

int getBestMoveJ2(Move* move){

	return move->first->next->y;

}

