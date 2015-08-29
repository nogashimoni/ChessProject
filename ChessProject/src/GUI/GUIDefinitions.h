/*
 * GUIdefinitions.h
 *
 *  Created on: Aug 26, 2015
 *      Author: nogalavi1
 */

#ifndef GUIDEFINITIONS_H_
#define GUIDEFINITIONS_H_

#define BOARD_SIZE 8

//macros for files
#define WELCOME_BACKGROUND "images/800_600.png"
#define PLAYER_SELECTION_BACKGROUND "images/player_selection_panel_background.png"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32
#define WINDOWS_COUNT 2
#define POLLING_DELAY 10

#define BUTTON_WIDTH 220
#define BUTTON_HEIGHT 50

typedef enum {
	MAIN_MENU,
	PLAYER_SELECTION,
	QUIT
} WindowId;

typedef enum {
	PRESS_FIRST,
	PRESS_SECOND,
	PRESS_THIRD,
} EventID;


struct UITreeNode {
    void *data;
    struct UITreeNode* next;
    struct UITreeNode* child;
    struct UITreeNode* parent;
};

typedef struct UITreeNode UITreeNode;

typedef struct Button Button;

struct Button {
	/* data members */
	//The attributes of the button
	SDL_Rect relevantArea; //The part of the screen the button works in
	SDL_Rect *clip;//*sprite_map;

	/* methods */
	int (*isButtonPressed)(Button *button, SDL_Event sdlEvent);
};


typedef struct Window Window;

struct Window {
	/* data members */
//	Game* game;
	UITreeNode* UITreeHead; //ui tree
	WindowId windowId;
	/* methods */
	int (*start) (Window* window, void* initData);
	EventID (*translateEvent)(Window* window, SDL_Event* event);
	int (*handleEvent)(Window* window, EventID event);
	void* (*stop) (Window* window);
};


#endif /* GUIDEFINITIONS_H_ */
