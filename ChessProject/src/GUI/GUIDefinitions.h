/*
 * GUIdefinitions.h
 *
 *  Created on: Aug 26, 2015
 *      Author: nogalavi1
 */

#ifndef GUIDEFINITIONS_H_
#define GUIDEFINITIONS_H_

#define BOARD_SIZE 8

typedef enum {
	MAIN_MENU,
	SETUP,
	QUIT
} WindowId;

typedef enum {
	PRESS_FIRST,
	PRESS_SECOND,
	PRESS_THIRD,
} EventID;
typedef struct Node Node;

struct Node {
	Node** next;
};

typedef struct Button Button;

struct Button {
	/* data members */
	//The attributes of the button
	SDL_Rect box; //The part of the button sprite sheet that will be shown
	SDL_Rect *clip;//*sprite_map;

	/* methods */
	char (*handle_events)(Button *control, int x_offset, int y_offset,
			char board[BOARD_SIZE][BOARD_SIZE]);
	void (*show)(Button *control, SDL_Surface *parent,
			char board[BOARD_SIZE][BOARD_SIZE]);
};


typedef struct Window Window;

struct Window {
	/* data members */
//	Game* game;
	Node* UITreeHead; //ui tree
	WindowId windowId;
	/* methods */
	EventID (*translateEvent)(Window* window, SDL_Event* event);
	int (*handleEvent)(Window* window, EventID event);
	int (*start) (Window* window, void* initData);
	void* (*stop) (Window* window);
};


#endif /* GUIDEFINITIONS_H_ */
