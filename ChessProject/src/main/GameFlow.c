

#include "GameFlow.h"

int main(int argc, char **argv) {
	Game game;
	int isGUIMode = ((argc == 2) && (strcmp(argv[0], "gui")) ? 1 : 0);
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
	return;
}



void playByConsole(Game* game) {
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

void computerTurn(Game* game){
/* Perform computer turn. Note: we enter this function only if
 * computer isn't stuck, meaning there's at least 1 move. */

	printf("Computer: move ");
	minmax(game,game->minmaxDepth, INT_MIN, INT_MAX, 1); //updates game->move
	doMove(game, game->minmaxMove, 1);
	freeMove(game->minmaxMove);

	print_board(game->board);
//	freeNullAndRemove(game->minmaxMove); // all other moves on tree will be freed only when quit
	game->minmaxScore = INT_MIN;
	game->minmaxMove = NULL; //just in case


//	int didSomeoneWin = checkIfNextWinsAndPrint(game);
//	if (didSomeoneWin){
//		game->isRunning = 0;
//	}
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
		else if (!strncmp(cmd,"get_best_move",13)){
			int d = (int)strtol(cmd+13,(char**)NULL,10);
			game->minmaxDepth = d;
			getBestMoveForUser(game);
		}

		else {
			print_message(ILLEGAL_COMMAND);
		}

	}
	print_board(game->board);

//	game->whosTurn = 'c';

}

void getBestMoveForUser(Game* game){

	minmax(game,game->minmaxDepth, INT_MIN, INT_MAX, 1); //updates game->move
	printMove(game->minmaxMove);

	freeMove(game->minmaxMove);
	game->minmaxScore = INT_MIN;
	game->minmaxMove = NULL; //just in case
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
