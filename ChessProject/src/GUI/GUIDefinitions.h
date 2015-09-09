

#ifndef GUIDEFINITIONS_H_
#define GUIDEFINITIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include "../main/ChessDefinitions.h"

#define BOARD_SIZE 8

//macros for files
#define WELCOME_BACKGROUND "images/800_600.png"
#define PLAYER_SELECTION_BACKGROUND "images/800_600.png"
#define TO_SET_WHO_STARTS_BACKGROUND "images/800_600.png"
#define TO_SET_BOARD_BACKGROUND "images/800_600.png"
#define SET_WHO_STARTS_BACKGROUND "images/800_600.png"
#define SET_BOARD_BACKGROUND "images/800_600.png"

#define BOARD_PANEL_BACKGROUND "images/board_with_characters.png"


#define WELCOME_SPRITE "images/main_menu_sprite.png"
#define PLAYER_SELECTION_SPRITE "images/player_selection_sprite.png"
#define TO_SET_WHO_STARTS_SPRITE "images/to_set_who_starts_sprite.png"
#define TO_SET_BOARD_SPRITE "images/to_set_board_sprite.png"
#define SET_WHO_STARTS_SPRITE "images/set_who_starts_sprite.png"
#define PEICES_SPRITE "images/chess_symbols.png"
#define SET_BOARD_BUTTONS_SPRITE "images/set_board_sprite.png"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32

#define POLLING_DELAY 10

#define BUTTON_WIDTH 220
#define BUTTON_HEIGHT 50

#define X_FOR_PANEL 30
#define Y_FOR_PANEL 55
#define PANEL_WIDTH 461
#define PANEL_HEIGHT 463

#define BOARD_MATRIX_TOP_LEFT_X 49// not regarding it's father panel!
#define BOARD_MATRIX_TOP_LEFT_Y 55 // not regarding it's father panel!
#define BOARD_MATRIX_SQUARE_SIZE 55
#define SET_BOARD_MENU_X 520
#define SET_BOARD_MENU_Y 55

#define WINDOWS_COUNT 6

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
	PANEL,
	MATRIX
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
	int (*start) (Window* window, Game* initData);
	EventID (*translateEvent)(Window* window, SDL_Event event);
	int (*handleEvent)(Window* window, EventID event, Game* game);
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

	// for Game use
	char peiceToDraw;

	/* methods */
	int (*isButtonPressed)(Button *button, SDL_Event sdlEvent);
};


typedef struct Buttons Buttons;
struct Buttons {
	TreeWidgetType widgetType;
	SDL_Surface* buttonsImages;
	Button** buttonArray;
	int numOfButtons;
	SDL_Rect* clipArray;
};

typedef struct Background Background;
struct Background {
	SDL_Surface* image;
};

typedef struct Panel Panel;
struct Panel {
	//fields
	TreeWidgetType widgetType;
	SDL_Rect relevantArea;
	SDL_Surface* panelBackground;
	//functions
	void (*applyOnPanel)(SDL_Surface* screen, Panel* panel, SDL_Surface* surface, int relativeX, int relativeY);
};

typedef struct Matrix Matrix;
struct Matrix {
	Button*** buttonsMatrix;
	SDL_Surface* piecesImages;
	SDL_Rect* peicesClipArray; // white queen , black queen...

	SDL_Surface* fatherPanel;

	int n;
	int m;

	int (*isIJPressed)(SDL_Event event, Matrix* matrix, int i, int j);
	int (*drawIJ)(Panel* panel, Matrix* matrix, char peiceType, int i, int j);
};

typedef struct GameBoard GameBoard;
struct GameBoard {
	SDL_Surface* boardImage;
	Buttons* ButtonsMatrix;
};


#endif /* GUIDEFINITIONS_H_ */
