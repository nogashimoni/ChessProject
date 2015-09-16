

#include "GameFlow.h"

int main(int argc, char **argv) {
	Game game;
	int isGUIMode = ((argc == 2) && (!strcmp(argv[1], "gui")) ? 1 : 0);
	initGameFields(&game, isGUIMode);

	if (game.isGUIMode) {
		GUIMain(&game);
		quit(); //releases all chess logic variables
	}
	else {
		setupGameByConsole(&game);
		playByConsole(&game);
		quit();
	}
	return EXIT_SUCCESS;
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

void setupGameByConsole(Game* game) {
	print_board(game->board);

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
			loadGame(game, cmd + 4);
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
		}else if (!strcmp(cmd, "start")) {
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
		printf(ENTER_SETTINGS);
	}
	setIsComputerTurn(game);

	return;
}



void playByConsole(Game* game) {

	//Check if game is initialized in losing/tie situation.
	if (initializedMate(game) == 1){
		print_message("Mate! White player wins the game\n");
		return;
	}
	if (initializedMate(game) == 2){
		print_message("Mate! Black player wins the game\n");
		return;
	}

	if (game->isTwoPlayersMode) { //user-user game.

		while ( game->isRunning ) {

			if (isCurrentPlayerStuck(game)){
				game->isRunning = 0;
				if (isCurrentPlayersKingInDanger(game)){
					if (game->isWhiteTurn){
						print_message("Mate! Black player wins the game\n");
					}
					else{
						print_message("Mate! White player wins the game\n");
					}
					break;
				}
				else {
					print_message("The game ends in a tie\n");
				}
				break;
			}
			if (isCurrentPlayersKingInDanger(game)){
				print_message("Check!\n");
			}
			userTurn(game);
			switchTurns(game);
		}
	}

	else { //computer-user game.

		while ( game->isRunning ) {

			if (isCurrentPlayerStuck(game)){
				if (isCurrentPlayersKingInDanger(game)){
					game->isRunning = 0;
					if (game->isWhiteTurn){
						print_message("Mate! Black player wins the game\n");
					}
					else{
						print_message("Mate! White player wins the game\n");
					}
					break;
				}
				else {
					print_message("The game ends in a tie\n");
				}
			}
			if (isCurrentPlayersKingInDanger(game)){
				print_message("Check!\n");
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




void computerTurn(Game* game){
/* Perform computer turn. Note: we enter this function only if
 * computer isn't stuck, meaning there's at least 1 move. */

	printf("Computer: move ");
	minmax(game,game->minmaxDepth, INT_MIN, INT_MAX, 1, game->isWhiteTurn); //updates game->move
	doMove(game, game->minmaxMove, 1, EMPTY);
	freeMinmaxMove(game->minmaxMove);
	game->minmaxMove = NULL;

	print_board(game->board);
//	freeNullAndRemove(game->minmaxMove); // all other moves on tree will be freed only when quit
	game->minmaxScore = INT_MIN;
	game->minmaxMove = NULL; //just in case

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
			if (!isCurrentPlayerPeice(game, i, j)){
				if (!isValidIJ(i ,j)){
					print_message(WRONG_POSITION);
					continue;
				}
				print_message("The specified position does not contain your piece\n");
				continue;
			}
			Moves* moves = getMoves(game, i, j, 1);
			Move* currMove = moves->first;
			while ( currMove != NULL ) {
				printMove(currMove);
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

			int i1 = move->first->x;
			int j1 = move->first->y;
			int i2 = move->first->next->x;
			int j2 = move->first->next->y;

			if (!isValidIJ(i1 ,j1) || !isValidIJ(i2 ,j2)){
				print_message(WRONG_POSITION);
				freeMove(move);
				continue;
			}
			else if (!isCurrentPlayerPeice(game, i1, j1)){
				print_message("The specified position does not contain your piece\n");
				freeMove(move);
				continue;
			}

			int isValid = isValidMove(game, move); //validMove also prints if invalid
			if (isValid) {
				char peice = EMPTY;
				if (*(cmd+16) != '\0'){
					char* type = cmd+16;
					if (*type == 'k' && *(type + 1) == 'i') {
						print_message(ILLEGAL_COMMAND);
						break;
					} else if (*type == 'k' && *(type + 1) == 'n') {
						peice = (game->isWhiteTurn == 1 ? WHITE_N : BLACK_N);
					} else if (*type == 'q') {
						peice = (game->isWhiteTurn == 1 ? WHITE_Q : BLACK_Q);
					} else if (*type == 'r') {
						peice = (game->isWhiteTurn == 1 ? WHITE_R : BLACK_R);
					} else if (*type == 'b' && *(type + 1) == 'i') {
						peice = (game->isWhiteTurn == 1 ? WHITE_B : BLACK_B);
					}
				}
				doMove(game, move, 0, peice);
				isStillCurrentUserTurn = 0;
			}
			freeMove(move);
		}
		else if (!strncmp(cmd,"get_best_moves",14)){

			int d;
			if (*(cmd+14) == 'b'){
				d = 4;
				game->isBest = 1;
			}
			else{
				d = (int)strtol(cmd+14,(char**)NULL,10);
			}


			game->minmaxDepth = d;
			if (d == 0){
				print_message(ILLEGAL_COMMAND);
				continue;
			}
			Move* tempMove = getBestMoveForUser(game);
			freeMove(tempMove);
		}
		else if (!strncmp(cmd,"get_score",9)){

			int d;
			Move* move;
			char peice = EMPTY;

			if (*(cmd+9) == 'b') {
				d = 4;
				game->isBest = 1;
				move = createMoveFromString(cmd+13);
				if (*(cmd+29) != '\0'){//promotion move.
					char* type = cmd+29;
					if (*type == 'k' && *(type + 1) == 'i') {
						print_message(ILLEGAL_COMMAND);
						break;
					} else if (*type == 'k' && *(type + 1) == 'n') {
						peice = (game->isWhiteTurn == 1 ? WHITE_N : BLACK_N);
					} else if (*type == 'q') {
						peice = (game->isWhiteTurn == 1 ? WHITE_Q : BLACK_Q);
					} else if (*type == 'r') {
						peice = (game->isWhiteTurn == 1 ? WHITE_R : BLACK_R);
					} else if (*type == 'b' && *(type + 1) == 'i') {
						peice = (game->isWhiteTurn == 1 ? WHITE_B : BLACK_B);
					}
				}
			}
			else {
				d = (int)strtol(cmd+9,(char**)NULL,10);
				move = createMoveFromString(cmd+10);
				if (*(cmd+26) != '\0'){ //promotion move.
					char* type = cmd+26;
					if (*type == 'k' && *(type + 1) == 'i') {
						print_message(ILLEGAL_COMMAND);
						break;
					} else if (*type == 'k' && *(type + 1) == 'n') {
						peice = (game->isWhiteTurn == 1 ? WHITE_N : BLACK_N);
					} else if (*type == 'q') {
						peice = (game->isWhiteTurn == 1 ? WHITE_Q : BLACK_Q);
					} else if (*type == 'r') {
						peice = (game->isWhiteTurn == 1 ? WHITE_R : BLACK_R);
					} else if (*type == 'b' && *(type + 1) == 'i') {
						peice = (game->isWhiteTurn == 1 ? WHITE_B : BLACK_B);
					}
				}
			}
			if (d == 0){
				print_message(ILLEGAL_COMMAND);
				freeMove(move);
				continue;
			}

			if (!isValidMove(game, move)){ //isValidMove prints error if move is invalid.
				freeMove(move);
				continue;
			}

			game->minmaxDepth = d;
			int moveScore = getScore(game, move, d, peice);
			printf("%d\n",moveScore);
			freeMove(move);
		}

		else if (!strncmp(cmd,"save",4)){
			saveGame(game, cmd+4);
		}

		else {
			print_message(ILLEGAL_COMMAND);
		}

	}
	print_board(game->board);

//	game->whosTurn = 'c';

}



int getScore(Game* game, Move* move, int d, char piece){

	Game* gameCopy = cloneGame(game);
	gameCopy->minmaxDepth = d;
	doMove(gameCopy, move, 0, piece);
	//switchTurns(gameCopy);
	int minmaxScore = minmax(gameCopy, d-1, INT_MIN, INT_MAX, 1, gameCopy->isWhiteTurn);
	freeMinmaxMove(gameCopy->minmaxMove);
	game->minmaxScore = INT_MIN;
	game->minmaxMove = NULL; //just in case
	free(gameCopy);
	gameCopy = NULL;
	return minmaxScore;


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

