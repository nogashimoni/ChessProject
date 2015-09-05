#include "Chess.h"
Moves* moves = NULL;
Moves* movesTemp = NULL;

int main(int argc, char **argv) {
	Game game;
	setupGame(&game, argc, argv);
	play(&game);
	quit();
	return EXIT_SUCCESS;
}

void print_line() {
	int i;
	printf("  |");
	for (i = 1; i < BOARD_SIZE * 4; i++) {
		printf("-");
	}
	printf("|\n");
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

unsigned int yToJ(unsigned int y) {
	return y - 1;
}

unsigned int xToI(char x) {
	int i = x - '0';
	i -= 49;
	return i;
}

char iToX(int i) {
	char result = 'a' + i;
	return result;
}

int jToY(int j) {
	return j + 1;
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

void getCmdFromUser(char* output) {
	char current;
	while ((current = getchar()) != '\n' && current != EOF) {
		if (ferror(stdin))
			notifyFunctionFailure("gerchar");
		*output = current;
		output++;
	}
	*output = '\0';
}

void removeSpaces(char* string) {
	char* i = string;
	char* j = string;
	while (*j != '\0') {
		*i = *j++;
		if (*i != ' ')
			i++;
	}
	*i = '\0';
}

int setupGame(Game* game, int argc, char** argv) {
	game->isGUIMode = ((argc == 2) && (strcmp(argv[0], "gui")) ? 1 : 0);
	game->minmaxDepth = 1;
	game->isWhiteTurn = 1;
	game->isTwoPlayersMode = 1;
	game->isUserWhite = 1; // relevant only in player vs. ai mode
	game->isRunning=1;
	init_board(game->board);
	print_board(game->board);

	if (game->isGUIMode) {
//		GUIMain();
	}

	printf(ENTER_SETTINGS);
	char cmd[51];


	while (1) {
		getCmdFromUser(cmd);
		removeSpaces(cmd);
		if (!strncmp(cmd, "game_mode", 9)) {
			setGameMode(game, cmd[9]);
		} else if (!strncmp(cmd, "difficulty", 10)) {
			setDifficulty(game, cmd + 10);
		} else if (!strncmp(cmd, "user_color", 10)) {
			setUserColor(game, cmd[10]);
		} else if (!strncmp(cmd, "load", 4)) {
			loadGameFromXML(game, cmd + 4);
		} else if (!strncmp(cmd, "clear", 5)) {
			clearBoard(game);
		} else if (!strncmp(cmd, "next_player", 11)) {
			game->isWhiteTurn = (*(cmd + 11) == 'w' ? 1 : 0);
		} else if (!strncmp(cmd, "rm<", 3)) {
			char x = *(cmd + 3);
			int y = (int) strtol(cmd + 5, (char**) NULL, 10);
			removeDisk(game, x, y);
		} else if (!strncmp(cmd, "set<", 4)) {
			char x = *(cmd + 4);
			int y = (int) strtol(cmd + 6, (char**) NULL, 10);
			char color = *(cmd + 8);
			char* type = cmd + 13;
			setDisk(game, x, y, color, type);
		} else if (!strncmp(cmd, "print", 4)) {
			print_board(game->board);
		} else if (!strcmp(cmd, "quit")) {
			quit();
		} else if (!strcmp(cmd, "start")) {
			int numOfWhiteKIsOk = (countPeices(game, WHITE_K) == 1);
			int numOfBlackKisOk = (countPeices(game, BLACK_K) == 1);
			if (numOfWhiteKIsOk && numOfBlackKisOk) {
				break;
			} else {
				print_message(WROND_BOARD_INITIALIZATION);
			}
		} else {
			print_message(ILLEGAL_COMMAND);
		}
	}
	return 1;
}

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
		int num = (int) *(pointer + 5);
		int numIsGreaterThan10 = (*(pointer + 6) == '\0' ? 0 : 1);
		if (numIsGreaterThan10 || num == 0 || num > 4) {
			print_message(WRONG_MINIMAX_DEPTH);
		} else {
			game->minmaxDepth = num;
		}
	} else if (*pointer == 'b') {
		// TODO bonus
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

void loadGameFromXML(Game* game, char* path) {
	//TODO
}

void clearBoard(Game* game) {
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++)
			game->board[i][j] = EMPTY;
}

void play(Game* game) {
	if (game->isTwoPlayersMode) { //user-user game.
		while ( game->isRunning ) {
			if (isCurrentPlayerLose(game)){
				game->isRunning = 0;
				if (game->isWhiteTurn){
					printf("Check Mate! Black player wins! \n");
				}
				else{
					printf("Check Mate! White player wins! \n");
				}
				break;
			}
			if (isCurrentPlayersKingInDanger(game)){
				if (game->isWhiteTurn){
					printf("Check! White king threatened!\n");
				}
				else{
					printf("Check! Black king threatened! \n");
				}
			}
//			if (OpponentKingInDanger()){
//				printf("Check! \n");
//			}
			userTurn(game);
			switchTurns(game);
		}
	}
	else { //computer-user game.

		while ( game->isRunning ) {
			if ( isCurrentPlayerLose(game) ){
				game->isRunning = 0;
				if (game->isWhiteTurn){
					printf("Check Mate! Black player wins! \n");
				}
				else{
					printf("Check Mate! White player wins! \n");
				}
				break;
			}
			if ( game->isComputerTurn ) {
				computerTurn(game);
				switchTurns(game);
			}
			userTurn(game);
			switchTurns(game);
		}
	}
}


int isCurrentPlayerLose(Game* game){

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

void computerTurn(Game* game){
/* Perform computer turn. Note: we enter this function only if
 * computer isn't stuck, meaning there's at least 1 move. */

	minmax(game,game->minmaxDepth, INT_MIN, INT_MAX, 1); //updates game->move
	printf("Computer: move ");
	doMove(game, game->minmaxMove, 1);

	print_board(game->board);
//	freeNullAndRemove(game->minmaxMove); // all other moves on tree will be freed only when quit
//	game->minmaxScore = INT_MIN;
	game->minmaxMove = NULL; //just in case


//	int didSomeoneWin = checkIfNextWinsAndPrint(game);
//	if (didSomeoneWin){
//		game->isRunning = 0;
//	}
}

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

void userTurn(Game* game){
	/* Receives user commands, stops when user inputs a valid move - and performes it */
	char cmd[51];
	int isStillCurrentUserTurn = 1;
	while ( isStillCurrentUserTurn ) {
		char* userColor = ( (!game->isTwoPlayersMode && game->isUserWhite) || (game->isTwoPlayersMode && game->isWhiteTurn) ? "White" : "Black" );
		printf("%s%s",userColor,ENTER_MOVE);
		getCmdFromUser(cmd);
		removeSpaces(cmd);
		if ( !strncmp(cmd,"get_moves",9) ) {
			int i = xToI(*(cmd+10));
			int intY = (int)strtol(cmd+12,(char**)NULL,10);
			int j = yToJ(intY);
			Moves* moves = getMoves(game, i, j, 1);
			Move* currMove = moves->first;
			while ( currMove != NULL ) {
				printMove(currMove);
				Move* prevMove=currMove;
				currMove = currMove->next;
				//freeMove(prevMove);
			}
			if (moves != NULL){
				freeMoves(0);
			}
		}
		else if ( !strcmp(cmd,"quit") ) {
			quit();
		}
		else if ( !strncmp(cmd,"move",4) ) {
			Move* move = createMoveFromString(cmd);
			int isValid = isValidMove(game, move); //validMove also prints if invalid
			if (isValid) {
				doMove(game, move, 1);
				isStillCurrentUserTurn = 0;
			}
			freeMove(move);

		}
		else {
			print_message(ILLEGAL_COMMAND);
		}

	}
	print_board(game->board);

//	game->whosTurn = 'c';

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
	print_message(ILLEGAL_MOVE);
	return 0;
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

void doMove(Game* game, Move* move, int isPrintMove) {
	if (isPrintMove){
		printMove(move);
	}

	Position* first = move->first;
	Position* last = first->next;
	game->board[last->x][last->y] = game->board[first->x][first->y];
	game->board[first->x][first->y] = EMPTY;

}

Move* createMoveFromString(char* cmd) {
	Move* move = NULL;
	move = malloc(sizeof(move));
	if ( move == NULL ) {
		notifyFunctionFailure("creatrMoveFromString");
		quit();
	}

	Position* first = malloc(sizeof(Position));
	if ( first == NULL ) {
		free(move);
		move = NULL;
		notifyFunctionFailure("createMoveFromString");
		quit();
	}

	move->first = first;
	char* c = cmd;
	// first node
	while ( *c != '<' ) {
		c ++;
	}
	//c is now on first <
	c++;
	first->x = xToI(*c);
	c += 2;
	if ( *(c+1) != '>' ) {
		first->y = 9;
	}
	else {
		int intY = (int)strtol(c,(char**)NULL,10);
		first->y = yToJ(intY);
	}
	// all other positions
	Position* prev = first;
	Position* curr;
	while ( *c != '\0' ) {
		if ( *c == '<') {
			curr = NULL;
			curr = malloc(sizeof(Position));
			if ( curr == NULL ) {
				freeMove(move);
				notifyFunctionFailure("createMoveFromString");
				quit();
			}

			c ++;
			curr->x = xToI(*c);
			c += 2;
			if ( *(c+1) != '>' ) {
				curr->y = 9;
			}
			else {
				int intY = (int)strtol(c,(char**)NULL,10);
				curr->y = yToJ(intY);
			}
			prev->next = curr;
			prev = curr;
		}
		c++;
	}
	curr->next = NULL;
	return move;
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

	doMove(gameCopy, move, 0);
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


//TODO add special pawn move (what happens when pawn reaches end f board).
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
				break;
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
				break;
			}
			if ((!game->isWhiteTurn)==getPieceColor(game, x+i,y+1)){
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

//char currentUserColor(Game* game) {
//	if ( ( ( game->whosTurn == 'u') && ( game->userColor == 'w') )|| ( ( game->whosTurn != 'u') && (game->userColor == 'b')) ) {
//		return 'w';
//	}
//	return 'b';
//}

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
	gameCopy->minmaxMove = game->minmaxMove;
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

void printMove(Move* move){
	printf("<%c,%u> to ",iToX((move->first)->x),jToY((move->first)->y));
	Position* currPosition = (move->first)->next;
	while ( currPosition != NULL ) {
		printf("<%c,%u>", iToX(currPosition->x) ,jToY(currPosition->y));
		currPosition = currPosition->next;
	}
	printf("\n");
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

