#include "Chess.h"

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
	return isInvalidIJ(i, j);
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
		GUIMain();
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
	/* sets a peice in a specified legal position */
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
	if (game->isTwoPlayersMode) {
		while ( game->isRunning ) {
			userTurn(game);
			switchTurns(game);
		}
	}
	else { //computer-user

		while ( game->isRunning ) {
			if ( game->isComputerTurn ) {
				computerTurn(game);
				switchTurns(game);
			}
			userTurn(game);
			switchTurns(game);
		}
	}
}

void computerTurn(Game* game){
//	printf("computer\n");
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
			Moves* moves = getMoves(game, i, j);
			Move* currMove = moves->first;
			while ( currMove != NULL ) {
				printMove(currMove);
				Move* prevMove=currMove;
				currMove = currMove->next;
				freeMove(prevMove);
			}
			freeAndNull(moves);
		} else if ( !strcmp(cmd,"quit") ) {
			quit();
		} else if ( !strncmp(cmd,"move",4) ) {
			Move* move = createMoveFromString(cmd);
			int isValid = isValidMove(game, move); //validMove also prints if invalid
			if (isValid) {
				doMove(game, move);
				isStillCurrentUserTurn = 0;
			}
			freeMove(move);

		} else {
			print_message(ILLEGAL_COMMAND);
		}

	}
	print_board(game->board);
//	int didSomeoneWin = checkIfNextWinsAndPrint(game,manager);
//	if ( didSomeoneWin )
//		game->isRunning = 0;
//	game->whosTurn = 'c';

}

int isValidMove(Game* game, Move* move) {
	return 1;
}

void doMove(Game* game, Move* move) {
	printMove(move);
}

Move* createMoveFromString(char* cmd) {
	Move* move = malloc(sizeof(move));
	if ( move == NULL ) {
		notifyFunctionFailure("createMoveFromString");
		quit();
	}

	Position* first = malloc(sizeof(Position));
	if ( first == NULL ) {
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
			curr = malloc(sizeof(Position));
			if ( curr == NULL ) {
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
	game->isWhiteTurn=!game->isWhiteTurn;

	if (!(game->isTwoPlayersMode) ) {
		game->isComputerTurn=!game->isComputerTurn;
	}
}

/* Returns all legal moves for a certian piece */

Moves* getMoves(Game* game, int x, int y){

	printf("%d %d\n", x,y);

	Moves* moves = calloc(sizeof(Moves),1);
	if ( moves == NULL ) {
		quit("getMoves");
	}

//	addToAllAllocs(moves);

	moves->maxEats = 0;

	moves->first = NULL;

	if (isCurrentPlayerPeice(game, x, y)){
		//Piece is a Pawn
		if (game->board[x][y] == WHITE_P || game->board[x][y] == BLACK_P){
			getPawnMoves(game, moves, x, y);
		}
		//Piece is a Knight.
		if (game->board[x][y] == WHITE_N || game->board[x][y] == BLACK_N){
			getKnightMoves(game, moves, x, y);
		}
		if (game->board[x][y] == WHITE_K || game->board[x][y] == BLACK_K){
			getKingMoves(game, moves, x, y);
		}
		if (game->board[x][y] == WHITE_B || game->board[x][y] == BLACK_B){
			getBishpMoves(game, moves, x, y);
		}
		if (game->board[x][y] == WHITE_Q || game->board[x][y] == BLACK_Q){
			getQueenMoves(game, moves, x, y);
		}
		if (game->board[x][y] == WHITE_R || game->board[x][y] == BLACK_R){
			getRookMoves(game, moves, x, y);
		}
	}

	return moves;
}


//TODO add special pawn move.
Moves* getPawnMoves(Game* game, Moves* moves, int x, int y){
	//Pawn is white - standard move.
	if (game->isWhiteTurn && (game->board[x][y+1] == EMPTY) && isValidIJ(x,y+1)){
		Move* move = creatNewMove(x, y, x, y+1);
		move->eats=0;
		addToMoves(moves,move);
	}
	//Pawn is white - check for eats.
	for (int i=-1 ; i<=1;i+=2){
		if (game->isWhiteTurn && (!game->isWhiteTurn==getPieceColor(game, x+i,y+1)) && isValidIJ(x+i,y+1)){
			Move* move = creatNewMove(x, y, x+i, y+1);
			move->eats=1;
			addToMoves(moves,move);
		}
	}

	//Pawn is black - standard move.
	if ((!game->isWhiteTurn) && game->board[x][y-1] == EMPTY && isValidIJ(x,y-1)){
		Move* move = creatNewMove(x, y, x, y-1);
		move->eats=0;
		addToMoves(moves,move);
	}
	//Pawn is black - check for eats
	for (int i=-1 ; i<=1;i+=2){
		if ((!game->isWhiteTurn) && (!game->isWhiteTurn==getPieceColor(game, x+i,y+1)) && isValidIJ(x+i,y-1)){
			Move* move = creatNewMove(x, y, x+i, y-1);
			move->eats=1;
			addToMoves(moves,move);
		}
	}
	return moves;
}

Moves* getKnightMoves(Game* game, Moves* moves, int x, int y){

	for (int i=-1;i<=1;i+=2){
		for (int j=-1; j<=1; j+=2){
			if (!isCurrentPlayerPeice(game, x+1*i,y+2*j)
					&& isValidIJ(x+1*i,y+2*j)){
				Move* move = creatNewMove(x, y, x+1*i,y+2*j);
				if (getPieceColor(game, x+2*i,y+1*j) != -1){
					move->eats=1;
				}
				addToMoves(moves,move);
			}
			if (!isCurrentPlayerPeice(game, x+2*i,y+1*j)
					&& isValidIJ(x+2*i,y+1*j)){
				Move* move = creatNewMove(x, y, x+2*i,y+1*j);
				if (getPieceColor(game, x+2*i,y+1*j) != -1){
					move->eats=1;
				}
				addToMoves(moves,move);
			}
		}
	}
	return moves;
}

Moves* getKingMoves(Game* game, Moves* moves, int x, int y){
	for (int i=-1 ; i<=1;i++){
		for (int j=-1; j<=1;j++){
			if (i==j && j==0){
				continue;
			}
			if (!isCurrentPlayerPeice(game, x+i,y+j)
					&& isValidIJ(x+i,y+j)){
				Move* move = creatNewMove(x, y, x+i,y+j);
				if (getPieceColor(game, x+i,y+j) != -1){
					move->eats=1;
				}
				addToMoves(moves,move);
			}
		}

	}
	return moves;
}

Moves* getBishpMoves(Game* game, Moves* moves, int x, int y){

	for (int r=-1; r<=1;r+=2){
		for (int j=-1; j<=1;j+=2){
			for (int i=1; i<=BOARD_SIZE;i++){
				if (!isCurrentPlayerPeice(game, x+i*j,y+i*r) && isValidIJ(x+i*j,y+i*r)){
					Move* move = creatNewMove(x, y, x+i*j,y+i*r);
					if (getPieceColor(game, x+i*j,y+i*r) != -1){
						move->eats=1;
						addToMoves(moves,move);
						break;
					}
					addToMoves(moves,move);
				}
			}
		}
	}
	return moves;
}

Moves* getRookMoves(Game* game, Moves* moves, int x, int y){

	for (int j=-1; j<=1;j+=2){
		for (int i=1; i<=BOARD_SIZE;i++){

			if (!isCurrentPlayerPeice(game, x+i*j,y) && isValidIJ(x+i*j,y)){
				Move* move = creatNewMove(x, y, x+i*j,y);
				if (getPieceColor(game, x+i*j,y) != -1){
					move->eats=1;
					addToMoves(moves,move);
					break;
				}
				addToMoves(moves,move);
			}
			if (!isCurrentPlayerPeice(game, x,y+i*j) && isValidIJ(x,y+i*j)){
				Move* move = creatNewMove(x, y, x,y+i*j);
				if (getPieceColor(game, x,y+i*j) != -1){
					move->eats=1;
					addToMoves(moves,move);
					break;
				}
				addToMoves(moves,move);
			}
		}
	}

	return moves;
}

Moves* getQueenMoves(Game* game, Moves* moves, int x, int y){
	for (int j=-1; j<=1;j+=2){
		for (int i=1; i<=BOARD_SIZE;i++){

			if (!isCurrentPlayerPeice(game, x+i*j,y) && isValidIJ(x+i*j,y)){
				Move* move = creatNewMove(x, y, x+i*j,y);
				if (getPieceColor(game, x+i*j,y) != -1){
					move->eats=1;
					addToMoves(moves,move);
					break;
				}
				addToMoves(moves,move);
			}
			if (!isCurrentPlayerPeice(game, x,y+i*j) && isValidIJ(x,y+i*j)){
				Move* move = creatNewMove(x, y, x,y+i*j);
				if (getPieceColor(game, x,y+i*j) != -1){
					move->eats=1;
					addToMoves(moves,move);
					break;
				}
				addToMoves(moves,move);
			}
		}
	}

	for (int r=-1; r<=1;r+=2){
		for (int j=-1; j<=1;j+=2){
			for (int i=1; i<=BOARD_SIZE;i++){
				if (!isCurrentPlayerPeice(game, x+i*j,y+i*r) && isValidIJ(x+i*j,y+i*r)){
					Move* move = creatNewMove(x, y, x+i*j,y+i*r);
					if (getPieceColor(game, x+i*j,y+i*r) != -1){
						move->eats=1;
						addToMoves(moves,move);
						break;
					}
					addToMoves(moves,move);
				}
			}
		}
	}

	return moves;
}


Move* creatNewMove(int startX, int startY, int endX, int endY){
	Position* position = calloc(sizeof(Position), 1);
	position->x = startX;
	position->y = startY;
	Move* move = calloc(sizeof(Move), 1);
	move->first = position;
	Position* newPosition = calloc(sizeof(Position), 1);
	newPosition->x = endX;
	newPosition->y = endY;
	move->first->next = newPosition;
	return move;
}

void addToMoves(Moves* moves, Move* newMove){
	/* Add a move to the linked list moves */
	Move* temp = moves->first;
	moves->first = newMove;
	newMove->next = temp;

	if (newMove->eats > moves->maxEats){
		moves->maxEats = newMove->eats;
	}
}

void removeUnreleventMoves(Moves* moves){
	/* Out of all possible move, removes moves with not enough eats and frees them */
	Move* prev = moves->first;

	if ( prev == NULL ) {
		return;
	}

	while (prev->eats < moves->maxEats){
			moves->first = prev->next;
			Move* tmpPrev = prev;
			prev = prev->next;
//			freeNullAndRemove(tmpPrev);
		}

	Move* curr = prev->next;

	while (curr != NULL){
		if (curr->eats < moves->maxEats){
			prev->next = curr->next;
			Move* tmpCurr = curr;
			curr = curr->next;
//			freeNullAndRemove(tmpCurr);
			continue;
		}
		prev = curr;
		curr = curr->next;

	}
}


int isCurrentPlayerPeice(Game* game, int i, int j) {
	/* receives a legal i,j and returns 1 if it's the current player's piece */
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

int isValidIJ(unsigned int i, unsigned int j) {
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
void freeMove(Move* move) {
	Position* curr = move->first;
	while ( curr != NULL ) {
		Position* next = curr->next;
		freeAndNull(curr);
		curr = next;
	}
	freeAndNull(move);
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
//	free all
//TODO
	exit(0);
}


