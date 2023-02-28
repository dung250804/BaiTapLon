#include <iostream>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "MapGame.h"
#include "Player.h"

BaseObject g_background;

bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("GameTest CPP 1945",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (g_window == NULL)
	{
		success = false;
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
			success = false;
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = false;
		}
	}
	return success;
}

bool loadBackGround()
{
	bool ret = g_background.LoadImg("Gfx/city.jpg", g_screen);
	if (ret == false)
		return false;

	return true;
}

void close()
{
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) 
{
	if (InitData() == false)
		return -1;

	if (loadBackGround() == false)
		return -1;

	char dat[100] = "map/map01.dat";

	GameMap game_map;
	game_map.LoadMap(dat);
	game_map.LoadTiles(g_screen);

	Player p_player;
	p_player.LoadImg("Gfx//moveR.png", g_screen);
	p_player.set_clips();


	bool gameRunning = true;
	while (gameRunning)
	{
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				gameRunning = false;
			}

			p_player.HandleInput(g_event, g_screen);
		}

		//SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);
		game_map.DrawMap(g_screen);
		Map map_data = game_map.GetMap();

		p_player.PlayerMovement(map_data);
		p_player.Show(g_screen);

		SDL_RenderPresent(g_screen);

	}

	close();
	return 0;
}