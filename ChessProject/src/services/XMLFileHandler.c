#include "./XMLFileHandler.h"

int saveGameToFile(Game* game, char* path) {
	FILE* fp;
	if ( (fp = fopen(path, "w")) == NULL ) {
		return 0;
	}


	/* XML file - TODO
	void saveGameGUI(Game* game, FILE* f){
		int i, j;
		fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		fprintf(f, "<game>\n");
		fprintf(f, "\t<type>%d</type>\n", game->isComputerTurn + 1);
		if (game->isComputerTurn == 1){
			if (game->minmaxDepth == BEST_DEPTH)
				fprintf(f, "\t<difficulty>Best</difficulty>\n");
			else
				fprintf(f, "\t<difficulty>%d</difficulty>\n", game->minmaxDepth);
			fprintf(f, "\t<user_color>%s</user_color>\n", game->isUserWhite == 1 ? "White" : "Black");
		}
		fprintf(f, "\t<next_turn>%s</next_turn>\n", game->isWhiteTurn == 1 ? "White" : "Black");
		fprintf(f, "\t<board>\n");
		for (i = 0; i < BOARD_SIZE; i++){
			fprintf(f, "\t\t<row_%d>", 8 - i);
			for (j = 0; j < BOARD_SIZE; j++){
				switch (game->board[j][7 - i]){
				case WHITE_P:
					fprintf(f, "m");
					break;
				case WHITE_K:
					fprintf(f, "k");
					break;
				case BLACK_P:
					fprintf(f, "M");
					break;
				case BLACK_K:
					fprintf(f, "K");
					break;
				case WHITE_B:
					fprintf(f, "b");
					break;
				case BLACK_B:
					fprintf(f, "B");
					break;
				case WHITE_R:
					fprintf(f, "r");
					break;
				case BLACK_R:
					fprintf(f, "R");
					break;
				case WHITE_N:
					fprintf(f, "n");
					break;
				case BLACK_N:
					fprintf(f, "N");
					break;
				case WHITE_Q:
					fprintf(f, "q");
					break;
				case BLACK_Q:
					fprintf(f, "Q");
					break;
				case EMPTY:
					fprintf(f, "_");
					break;
				}
			}
			fprintf(f, "</row_%d>\n", 8 - i);
		}
		fprintf(f, "\t</board>\n");
		fprintf(f, "</game>\n");
	}
	*/

	return 1;
}
