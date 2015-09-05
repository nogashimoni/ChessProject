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
#define PLAYER_SELECTION_BACKGROUND "images/800_600.png"
#define TO_SET_WHO_STARTS_BACKGROUND "images/800_600.png"
#define TO_SET_BOARD_BACKGROUND "images/800_600.png"
#define SET_WHO_STARTS_BACKGROUND "images/800_600.png"
#define SET_BOARD_BACKGROUND "images/800_600.png"

#define WELCOME_SPRITE "images/main_menu_sprite.png"
#define PLAYER_SELECTION_SPRITE "images/player_selection_sprite.png"
#define TO_SET_WHO_STARTS_SPRITE "images/to_set_who_starts_sprite.png"
#define TO_SET_BOARD_SPRITE "images/to_set_board_sprite.png"
#define SET_WHO_STARTS_SPRITE "images/set_who_starts_sprite.png"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32
#define WINDOWS_COUNT 7
#define POLLING_DELAY 10

#define BUTTON_WIDTH 220
#define BUTTON_HEIGHT 50

typedef enum {
	WELCOME,
	PLAYER_SELECTION,
	TO_SET_WHO_STARTS,
	TO_SET_BOARD,
	SET_WHO_STARTS,
	SET_BOARD,
	QUIT_WINDOW
} WindowId;

typedef enum {
	NOTHING_HAPPANED,
	QUIT_EVENT,

	FIRST_PRESSED,
	SECOND_PRESSED,
	THIRD_PRESSED,
} EventID;

typedef enum {
	BACKGROUND,
	BUTTONS,
} TreeWidgetType;


struct UITreeNode {
    void *widget;
    TreeWidgetType widgetType;
    struct UITreeNode* next;
    struct UITreeNode* child;
    struct UITreeNode* parent;
};
typedef struct UITreeNode UITreeNode;

// GUI Structures

typedef struct Window Window;
struct Window {
	/* data members */
	UITreeNode* UITreeHead; //ui tree
	WindowId windowId;
	SDL_Surface* screen;
	/* methods */
	int (*start) (Window* window, void* initData);
	EventID (*translateEvent)(Window* window, SDL_Event event);
	int (*handleEvent)(Window* window, EventID event);
	void* (*stop) (Window* window);
};

// Tree members

typedef struct Button Button;
struct Button {
	/* data members */
	int widgetType; // Every GUI struct will have this field that will help us know in runtime what's it's type
	//The attributes of the button
	SDL_Rect relevantArea; //The part of the screen the button works in
	SDL_Rect *clip;//*sprite_map;

	/* methods */
	int (*isButtonPressed)(Button *button, SDL_Event sdlEvent);
};

typedef struct Buttons Buttons;
struct Buttons {
	SDL_Surface* buttonsImages;
	Button** buttonArray;
	int numOfButtons;
};

typedef struct Background Background;
struct Background {
	SDL_Surface* image;
};

#endif /* GUIDEFINITIONS_H_ */
