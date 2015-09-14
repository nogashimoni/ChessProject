
#ifndef XMLFILEHANDLER_H_
#define XMLFILEHANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XML_DECLARETION '<?xml version="1.0" encoding="UTF-8"?>'
#define TAG_GAME_S "<game>"
#define TAG_GAME_E "</game>"
#define TAG_NEXT_TURN_S "<next_turn>"
#define TAG_NEXT_TURN_E "</next_turn>"
#define TAG_GAME_MODE_S "<game_mode>"
#define TAG_GAME_MODE_E "</game_mode>"
#define TAG_DIFFICULTY_S "<difficulty>"
#define TAG_DIFFICULTY_E "</difficulty>"
#define TAG_USER_COLOE_S "<user_color>"
#define TAG_USER_COLOE_E "</user_color>"
#define TAG_BOARD_S "<board>"
#define TAG_BOARD_E "</board>"
#define TAG_ROE_TEMPLATE_S "<row_%d>"

int saveGameToFile(Game* game, char* path);

#endif /* XMLFILEHANDLER_H_ */
