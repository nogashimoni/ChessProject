
#include "ChessDefinitions.h"

void print_line() {
	int i;
	printf(" |");
	for (i = 1; i < BOARD_SIZE * 4; i++) {
		printf("-");
	}
	printf("|\n");
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

extern Moves* moves = NULL;
extern Moves* movesTemp = NULL;
