#pragma once
#include "stdio.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768

#define MAX_UNIT 7
#define MAX_SEAT 5

enum { MAIN_MENU, PLAY, RESULT , PAUSE_MENU , HELPER }; //state
enum { START, QUIT, REPLAY, GOTO_MENU, HELP, PAUSE, RESUME, MUTE }; // button type

enum { WIN, OVER }; // game result
enum { LEFT, RIGHT, ONBOAT }; //unit and boat pos

typedef struct
{
	int x, y, w, h, side, type, pos, seat, weight;
	SDL_Texture *unitTexture; 

}Unit;

typedef struct
{
	int x, y, w, h, side, moving , seat[MAX_SEAT][3]; //0 = x, 1 = y, 2 = free_seat_flag
	int max_weight, current_weight;

}Boat;

typedef struct
{
	int r_unit, l_unit; //number of unit at left side
	int r_pos[MAX_UNIT][2], //0 = x
		l_pos[MAX_UNIT][2]; //1 = y

}Land;

typedef struct
{
	int x, y, w, h, state, type;
	SDL_Rect rect[2]; // 0 = stanby, 1 = hover
	SDL_Texture *texture;

}Button;

typedef struct
{
	int alpha;
	Button btn[3];
	SDL_Texture *bgResult, *gamePassTexture, *gameOverTexture;

}Result;

typedef struct
{
	int alpha;
	Button btn[4];
	SDL_Texture *bgPause, *helper;

}PauseMenu;

typedef struct
{
	Button btn[2];
	SDL_Texture *bg;

}Menu;

typedef struct
{
	int mx, my, state, time, quit;

	short pressed, keydown, bgm_mute;
	short level, level_unit, level_seat, game_result;

	int move, moveLabelW, moveLabelH, unit_move;
	
	Menu menu;
	PauseMenu pause;
	Result result;

	Button btn[3]; // pause, help, sound

	Unit unit[MAX_UNIT];
	Boat boat;
	Land land;

	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Texture *unitTexture[MAX_UNIT];
	SDL_Texture *bgTexture, *boatTexture;
	SDL_Texture *moveLabel, *helper;
	
	TTF_Font *font;
	SDL_Color *fontColor;

	Mix_Music *bgm;
	Mix_Chunk *win_effect;

}GameState;
