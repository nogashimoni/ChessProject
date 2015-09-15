
#ifndef XMLFILEHANDLER_H_
#define XMLFILEHANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main/ChessDefinitions.h"

//#define XML_DECLARETION '<?xml version="1.0" encoding="UTF-8"?>'
#define TAG_GAME_S "<game>"
#define TAG_GAME_E "</game>"
#define TAG_NEXT_TURN_S "<next_turn>"
#define TAG_NEXT_TURN_E "</next_turn>"
#define TAG_GAME_MODE_S "<game_mode>"
#define TAG_GAME_MODE_E "</game_mode>"
#define TAG_DIFFICULTY_S "<difficulty>"
#define TAG_DIFFICULTY_E "</difficulty>"
#define EMPTY_DIFFICULTY_TAG "<difficulty/>"
#define TAG_USER_COLOR_S "<user_color>"
#define TAG_USER_COLOE_E "</user_color>"
#define EMPTY_USER_COLOR_TAG "<user_color/>"
#define TAG_BOARD_S "<board>"
#define TAG_BOARD_E "</board>"
#define TAG_ROW_TEMPLATE_S "<row_%d>"
#define TAG_ROW_TEMPLATE_E "<row_%d>"

#define NEXT_IS_WHITE "White"
#define NEXT_IS_BLACK "Black"
#define GAME_MODE_USER_COMPUTER "2"
#define GAME_MODE_USER_USER "1"
#define USER_COLOR_WHITE "White"
#define USER_COLOR_BLACK "Black"

#define SLOT_SEED "Slot_"


int saveGameToFile(Game* game, char* path);
int loadGameFromFile(Game* game, char* path);

/* For GUI usage */
int doesSlotContainFile(int i);
int saveToSlot(Game* game, int i);
int loadFromAFullSlot(Game* game, int slotNumber);

#endif /* XMLFILEHANDLER_H_ */
