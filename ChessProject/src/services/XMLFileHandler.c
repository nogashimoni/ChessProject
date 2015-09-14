#include "./XMLFileHandler.h"

int saveGameToFile(Game* game, char* path) {
	FILE* fp;
	if ( (fp = fopen(path, "w")) == NULL )
		return 0;

	char* nextTurn = (game->isWhiteTurn ? NEXT_IS_BLACK: NEXT_IS_WHITE);
	char* gameMode = (game->isTwoPlayersMode ? GAME_MODE_USER_USER : GAME_MODE_USER_COMPUTER);
	char* userColor = (game->isUserWhite ? "White" : "Black");
	char* minmaxDepth;
	if ( game->minmaxDepth == 1 ) minmaxDepth = "1";
	if ( game->minmaxDepth == 2 ) minmaxDepth = "2";
	if ( game->minmaxDepth == 3 ) minmaxDepth = "3";
	if ( game->minmaxDepth == 4 ) minmaxDepth = "4";
	char* difficulty = (game->isBest ? "Best" :  minmaxDepth );

	fprintf(fp,"%s\n", "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	fprintf(fp, "%s\n", TAG_GAME_S);
	fprintf(fp, "\t%s %s %s \n", TAG_NEXT_TURN_S, nextTurn, TAG_NEXT_TURN_E);
	fprintf(fp, "\t%s %s %s \n", TAG_GAME_MODE_S, gameMode, TAG_GAME_MODE_E);
	if ( !game->isTwoPlayersMode ) {
		fprintf(fp, "\t%s %d %s \n", TAG_DIFFICULTY_S,  , TAG_DIFFICULTY_E);
		fprintf(fp, "\t%s %s %s \n", TAG_USER_COLOE_S, userColor , TAG_USER_COLOE_E);
	}
	else {
		fprintf(fp, "\t%s \n", EMPTY_DIFFICULTY_TAG);
		fprintf(fp, "\t%s \n", EMPTY_USER_COLOR_TAG);;
	}
	fprintf(fp, "\t%s\n", TAG_BOARD_S);

	for (int i = 0; i < BOARD_SIZE; i++){
		fprintf(fp, "\t\t<row_%d>", BOARD_SIZE - i);
			for (int j = 0; j < BOARD_SIZE; j++){
				switch (game->board[j][BOARD_SIZE -1 - i]){
				case WHITE_P:
					fprintf(fp, "m");
					break;
				case WHITE_K:
					fprintf(fp, "k");
					break;
				case BLACK_P:
					fprintf(fp, "M");
					break;
				case BLACK_K:
					fprintf(fp, "K");
					break;
				case WHITE_B:
					fprintf(fp, "b");
					break;
				case BLACK_B:
					fprintf(fp, "B");
					break;
				case WHITE_R:
					fprintf(fp, "r");
					break;
				case BLACK_R:
					fprintf(fp, "R");
					break;
				case WHITE_N:
					fprintf(fp, "n");
					break;
				case BLACK_N:
					fprintf(fp, "N");
					break;
				case WHITE_Q:
					fprintf(fp, "q");
					break;
				case BLACK_Q:
					fprintf(fp, "Q");
					break;
				case EMPTY:
					fprintf(fp, "_");
					break;
				}
			}
			fprintf(fp, "</row_%d>\n", BOARD_SIZE - i);
		}
		fprintf(fp, "\t%s\n", TAG_BOARD_E);
		fprintf(fp, "%s/n", TAG_GAME_E);

		fclose(fp);

	return 1;
}

int loadFileFromFile(Game* game, char* path) {
	FILE* fp;
	if ((fp = fopen(path, "r")) == NULL) {
		return 0;
	}

}
