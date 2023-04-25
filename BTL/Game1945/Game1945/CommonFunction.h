#pragma once

#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

//Button
#define SMALL_BUTTON 1
#define COMMON_BUTTON 2

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};
const int COMMON_BUTTON_WIDTH = 150;
const int COMMON_BUTTON_HEIGHT = 98;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;

const int PLAY_BUTON_POSX = 1280/2 - COMMON_BUTTON_WIDTH/2;
const int PLAY_BUTTON_POSY = 640/2 - COMMON_BUTTON_HEIGHT/2;
const int HELP_BUTTON_POSX = PLAY_BUTON_POSX;
const int HELP_BUTTON_POSY = PLAY_BUTTON_POSY + COMMON_BUTTON_HEIGHT;
const int EXIT_BUTTON_POSX = PLAY_BUTON_POSX;
const int EXIT_BUTTON_POSY = HELP_BUTTON_POSY + COMMON_BUTTON_HEIGHT;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 31;
const int CONTINUE_BUTTON_POSY = 29;

//Sound
#define MIX_CHANNEL -1
#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

//Base
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Screen
const int FRAME_PER_SECOND = 55;	//(fps)

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_PIXEL = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0Xff;

#define BLANK_TILE 0
#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define DANGER_ZONE 4

typedef struct Input
{
	int left;
	int right;
	int up;
	int down;
	int jump;
};

typedef struct Map
{
	int start_x;
	int start_y;

	int max_x;
	int max_y;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name;
};

namespace SDLCommonfunc
{
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}

#endif // !COMMON_FUNCTION_H

