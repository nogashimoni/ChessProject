/*
 * GameFlow.c
 *
 *  Created on: Sep 5, 2015
 *      Author: noaleibo1
 */

#include "GameFlow.h"

int main(int argc, char **argv) {
	Game game;
	setupGame(&game, argc, argv);
	play(&game);
	quit();
	return EXIT_SUCCESS;
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

