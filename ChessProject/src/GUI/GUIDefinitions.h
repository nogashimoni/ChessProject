

#ifndef GUIDEFINITIONS_H_
#define GUIDEFINITIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep
#include "../main/ChessDefinitions.h"

#define BOARD_SIZE 8

//macros for files
#define WELCOME_BACKGROUND "images/welcome_background.png"
#define PLAYER_SELECTION_BACKGROUND "images/player_selection_background.png"
#define SET_DIFFICULTY_AND_COLOR_BACKGROUND "images/welcome_background.png"
#define TO_SET_WHO_STARTS_BACKGROUND "images/to_set_who_starts_background.png"
#define TO_SET_BOARD_BACKGROUND "images/to_set_the_board_background.png"
#define SET_WHO_STARTS_BACKGROUND "images/set_who_starts_background.png"
#define SET_BOARD_BACKGROUND "images/board_background.png"

#define BOARD_PANEL_BACKGROUND "images/board.png"
#define CHOOSE_PIECE_PANEL_BACKGROUND "images/choose_piece_panel_background.png"

#define WRONG_INIT_BUBBLE "images/wrong_board_init_bubble.png" // TODO change

#define WELCOME_SPRITE "images/main_menu_sprite.png"
#define PLAYER_SELECTION_SPRITE "images/player_selection_sprite.png"
#define DIFFICULTY_SPRITE "images/difficulty_sprite.png"
#define USER_COLOR_SPRITE "images/user_color_sprite.png"
#define CANCEL_CONTINUE_SPRITE "images/cancel_continue_sprite.png"
#define TO_SET_WHO_STARTS_SPRITE "images/to_set_who_starts_sprite.png"
#define TO_SET_BOARD_SPRITE "images/to_set_board_sprite.png"
#define SET_WHO_STARTS_SPRITE "images/set_who_starts_sprite.png"
#define PIECES_SPRITE "images/chess_symbols.png"
#define SET_BOARD_BUTTONS_SPRITE "images/set_board_sprite.png"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32

#define POLLING_DELAY 10

#define BUTTON_WIDTH 220
#define BUTTON_HEIGHT 50

#define SIZE_OF_DIFFICULTY_SQUARE 45
#define WIDTH_OF_COLOR_BUTTON 90
#define HEIGHT_OF_COLOR_BUTTON 45
#define AI_SETTINGS_BUTTONS_X 400
#define AI_SETTINGS_BUTTONS_FIRST_Y 200

#define X_FOR_PANEL 30
#define Y_FOR_PANEL 55
#define PANEL_WIDTH 461
#define PANEL_HEIGHT 463

#define X_FOR_ADD_PANEL 75
#define Y_FOR_ADD_PANEL 75
#define ADD_PANEL_WIDTH 421
#define ADD_PANEL_HEIGHT 423
#define FIRST_X_FOR_PEICES_ON_PANEL 90
#define FIRST_Y_FOR_PEICES_ON_PANEL 200

#define BUBBLE_X 550
#define BUBBLE_Y 360
#define BUBBLE_TIME 1500

#define BOARD_MATRIX_TOP_LEFT_X 49
#define BOARD_MATRIX_TOP_LEFT_Y 55
#define BOARD_MATRIX_SQUARE_SIZE 55
#define SET_BOARD_MENU_X 550
#define SET_BOARD_MENU_Y 55

#define WINDOWS_COUNT 8

typedef enum {
	WELCOME,
	PLAYER_SELECTION,
	SET_DIFFICULTY_AND_COLOR,
	TO_SET_WHO_STARTS,
	TO_SET_BOARD,
	SET_WHO_STARTS,
	SET_BOARD,
	GAME_WINDOW,
	QUIT_WINDOW
} WindowId;


typedef enum {
	NOTHING_HAPPANED,
	QUIT_EVENT,

	FIRST_PRESSED,
	SECOND_PRESSED,
	THIRD_PRESSED,
	FOURTH_PRESSED, // relevant only in difficulty and color window
	FIFTH_PRESSED,
	SIXTH_PRESSED,
	SEVENTH_PRESSED,
	EIGHTH_PRESSED,

	SOME_SQUARE_PRESSED, // relevant in windows with matrix widget
	CHOSE_PIECE // relevant in setup's add piece
} EventID;

typedef enum {
	BACKGROUND,
	BUTTONS,
	PANEL,
	MATRIX
} TreeWidgetType;

typedef enum {
	MOVE,
	ADD,
	REMOVE,
	NO_COMMAND
} CommandType;

struct UITreeNode {
    void *widget;
    TreeWidgetType widgetType;
    struct UITreeNode* next;
    struct UITreeNode* child;
    struct UITreeNode* parent;
};
typedef struct UITreeNode UITreeNode;

// GUI Structures


typedef struct GUIMemory GUIMemory;
struct GUIMemory {
	int newI;
	int newJ;
	int oldI;
	int oldJ;
	int pressedSquarsNum;
	CommandType commandType;
	int isScreenUpdated;

	char* pathOfBubbleToShow;

	char pieceChosen; //relevant in setup's add
};

typedef struct Window Window;
struct Window {
	/* data members */
	UITreeNode* UITreeHead; //ui tree
	WindowId windowId;
	SDL_Surface* screen;
	/* methods */
	int (*start) (Window* window, Game* initData);
	EventID (*translateEvent)(Window* window, SDL_Event event, GUIMemory* memory);
	int (*handleEvent)(Window* window, EventID event, Game* game, GUIMemory* memory);
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
	char pieceToDraw;

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
	SDL_Rect* piecesClipArray; // white queen , black queen...

	SDL_Surface* fatherPanel;

	int n;
	int m;

	int (*isIJPressed)(SDL_Event event, Matrix* matrix, int i, int j);
	int (*drawIJ)(Panel* panel, Matrix* matrix, char pieceType, int i, int j);
};

typedef struct GameBoard GameBoard;
struct GameBoard {
	SDL_Surface* boardImage;
	Buttons* ButtonsMatrix;
};




#endif /* GUIDEFINITIONS_H_ */
