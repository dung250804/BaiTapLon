#include <iostream>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "MapGame.h"
#include "Player.h"
#include "FPSnTicks.h"

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
	FPSnTicks fps_time;

	if (InitData() == false)
		return -1;

	if (loadBackGround() == false)
		return -1;

	char dat[100] = "map/map01.dat";

	GameMap game_map;
	game_map.LoadMap(dat);
	game_map.LoadTiles(g_screen);

	Player p_player;
	p_player.LoadImg("Gfx//moveR+.png", g_screen);
	p_player.set_clips();


	bool gameRunning = true;
	while (gameRunning)
	{
		fps_time.start();
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				gameRunning = false;
			}

			p_player.HandleInput(g_event, g_screen);
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);
		
		Map map_data = game_map.GetMap();

		p_player.HandleBullet(g_screen);
		p_player.SetMapXY(map_data.start_x, map_data.start_y);
		p_player.PlayerMovement(map_data);
		p_player.Show(g_screen);

		game_map.SetMap(map_data);
		game_map.DrawMap(g_screen);

		SDL_RenderPresent(g_screen);

		int real_time_passed = fps_time.GetTicks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;	//ms

		if (real_time_passed < time_one_frame)
		{
			int delay_time = time_one_frame - real_time_passed;
			if(delay_time >= 0)
				SDL_Delay(delay_time);
		}

	}

	close();
	return 0;
}