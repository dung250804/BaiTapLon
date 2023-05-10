
#include "CommonFunction.h"
#include "BaseObject.h"
#include "MapGame.h"
#include "Player.h"
#include "FPSnTicks.h"
#include "Enemy.h"
#include "DeathAnimation.h"
#include "TextObj.h"
#include "Menu.h"
#include "PlayerLP.h"
#include "Background.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------
BaseObject gLoseTexture;
BaseObject gWinTexture;
//-----------------------------------------------------------------------------------------------------------------------------------------------------
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gDeath = nullptr;
Mix_Chunk* gLose = nullptr;
Mix_Chunk* gWin = nullptr;
//-----------------------------------------------------------------------------------------------------------------------------------------------------
BaseObject g_background;
TTF_Font* font_time = NULL;
//-----------------------------------------------------------------------------------------------------------------------------------------------------


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
		if (TTF_Init() == -1)
		{
			success = false;
		}

		font_time = TTF_OpenFont("font//Font.ttf", 20);
		if (font_time == NULL)
		{
			success = false;
		}
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			return false;

		gClick = Mix_LoadWAV("sound//click2.wav");
		if (gClick == nullptr)
		{
			success = false;
		}

		gLose = Mix_LoadWAV("sound//Failed.mp3");
		if (gClick == nullptr)
		{
			success = false;
		}

		gMusic = Mix_LoadMUS("sound/GameMusic.mp3");
		if (gMusic == nullptr)
		{
			success = false;
		}

		gDeath = Mix_LoadWAV("sound/death.mp3");
		if (gMusic == nullptr)
		{
			success = false;
		}
		if (!gLoseTexture.LoadImg("Menu/GameOver1.png", g_screen))
		{
			success = false;
		}

		/*if (!gWinTexture.LoadImg("imgs/background/win.png", g_screen))
		{
			cout << "Failed to load win image.\n";
			success = false;
		}*/
	}
	return success;
}


void close()
{
	//Sound
	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenuMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gLose);
	Mix_FreeChunk(gWin);
	gMusic = nullptr;
	gMenuMusic = nullptr;
	gClick = nullptr;
	gLose = nullptr;
	gWin = nullptr;
	//window

	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}


std::vector<Enemy*> MakeEnemyList()
{
	std::vector<Enemy*> enemy_list;


	//chuyen dong.
	Enemy* dynamic_enemies = new Enemy[30];
	for (int i = 0; i < 30; i++)
	{
		Enemy* p_enemy = (dynamic_enemies + i);
		if (p_enemy != NULL)
		{
			p_enemy->LoadImg("Gfx//SwordEnemyL.png", g_screen);
			p_enemy->set_clips();
			p_enemy->set_type_move(Enemy::MOVE_AREA);
			p_enemy->set_x_pos(500 + i * 500);
			p_enemy->set_y_pos(200);

			int pos1 = p_enemy->get_x_pos() - 60;
			int pos2 = p_enemy->get_x_pos() + 60;
			p_enemy->set_animation_pos(pos1, pos2);
			p_enemy->set_input_left(1);

			enemy_list.push_back(p_enemy);
		}
	}

	//dung' yen
	Enemy* Enemies = new Enemy[20];

	for (int i = 0; i < 20; i++)
	{
		Enemy* p_enemy = (Enemies + i);
		if (p_enemy != NULL)
		{
			p_enemy->LoadImg("Gfx//EliteEnemyL.png", g_screen);
			p_enemy->set_clips();
			p_enemy->set_x_pos(700 + i * 1500);
			p_enemy->set_y_pos(0);
			p_enemy->set_type_move(Enemy::STATIC_ENEMY);

			BulletObj* p_bullet = new BulletObj();
			p_enemy->InitBullet(p_bullet, g_screen);
			enemy_list.push_back(p_enemy);
		}
	}
	return enemy_list;
}

int main(int argc, char* argv[])
{
	FPSnTicks fps_time;

	if (InitData() == false)
		return -1;


	bool gameRunning = false;
	if (!gameRunning) {

		Menu menuScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
		menuScreen.loadMenuIMG(g_screen);

		while (menuScreen.menuIsRunning) {
			SDL_Delay(10);
			while (SDL_PollEvent(&g_event))
			{
				if (g_event.type == SDL_QUIT)
				{
					menuScreen.menuIsRunning = false;
					return 0;
				}
				menuScreen.handleEvent(g_event);
				if (g_event.type == SDL_KEYDOWN)
					Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			}
			menuScreen.render(g_screen);
		}
		Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
		gameRunning = true;
	}

	Background background;
	background.loadBG(g_screen);

	Mix_PauseMusic();
	Mix_PlayMusic(gMusic, IS_REPEATITIVE);

	char dat[100] = "map/map02.dat";

	//map
	GameMap game_map;
	game_map.LoadMap(dat);
	game_map.LoadTiles(g_screen);

	//character
	Player p_player;
	p_player.LoadImg("Gfx//moveR+.png", g_screen);
	p_player.set_clips();

	//life point
	PlayerLP player_life;
	player_life.Init(g_screen);

	std::vector<Enemy*> enemy_list = MakeEnemyList();

	//death
	DeathAnimation death_enemy;
	bool eRet = death_enemy.LoadImg("Gfx//Blood.png", g_screen);
	if (!eRet) return -1;
	int LP = 0;
	death_enemy.set_clip();

	//Text (time)
	TextObj time_game;
	time_game.SetColor(TextObj::WHITE_TEXT);

	Mix_PlayMusic(gMusic, IS_REPEATITIVE);



	while (gameRunning)
	{
		
		fps_time.start();

		//SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR); 
		SDL_RenderClear(g_screen);

		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				gameRunning = false;

			}
			background.HandleInput(g_event, g_screen); 
			p_player.HandleInput(g_event, g_screen);
		}

		background.render(g_screen);

		Map map_data = game_map.GetMap();

		p_player.HandleBullet(g_screen);
		p_player.SetMapXY(map_data.start_x, map_data.start_y);
		p_player.PlayerMovement(map_data);
		p_player.Show(g_screen);

		game_map.SetMap(map_data);
		game_map.DrawMap(g_screen);

		player_life.Show(g_screen);

		for (int i = 0; i < enemy_list.size(); i++)
		{
			Enemy* p_enemy = enemy_list.at(i);
			if (p_enemy != NULL)
			{
				p_enemy->SetMapXY(map_data.start_x, map_data.start_y);
				p_enemy->ImpMoveType(g_screen);
				p_enemy->EnemyMovement(map_data);
				p_enemy->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				p_enemy->show(g_screen);

				SDL_Rect rect_player = p_player.GetRectFrame();
				bool bCol1 = false;
				std::vector<BulletObj*> eBullet_list = p_enemy->get_bullet_list();
				for (int eb = 0; eb < eBullet_list.size(); eb++)
				{
					BulletObj* enemy_bullet = eBullet_list.at(eb);
					if (enemy_bullet)
					{
						bCol1 = SDLCommonfunc::CheckCollision(enemy_bullet->GetRect(), rect_player);
						if (bCol1)
						{
							p_enemy->RemoveBullet(eb);
							break;
						}
					}
				}

				SDL_Rect rect_enemy = p_enemy->GetRectFrame();
				bool bCol2 = SDLCommonfunc::CheckCollision(rect_player, rect_enemy);
				if (bCol1 || bCol2)
				{
					
					Mix_PlayChannel(MIX_CHANNEL, gDeath, NOT_REPEATITIVE);
					LP++;
					if (LP <= 3)
					{
						p_player.SetRect(0, 0);
						p_player.set_spawn_time(1);
						SDL_Delay(1000);
						player_life.Decrease();
						player_life.Render(g_screen);
						continue;
					}
					else
					{
						//Mix_PauseMusic();
						Mix_HaltChannel(-1);
						Mix_PlayChannel(-1, gLose, NOT_REPEATITIVE); 
						DrawEndGameSelection(gLoseTexture, &g_event, g_screen, gameRunning);
						p_enemy->Free();
						close();
						SDL_Quit();
						return 0;
						
					}
				}
			}
		}

		bool winner = p_player.WinStatus(map_data);
		if (winner) {
			if (MessageBox(NULL, L"YOU ARE THE WINNER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
			{
				enemy_list.clear();
				close();
				SDL_Quit();
				return 0;
			}
		}

		if (Mix_PlayingMusic() == 1 && p_player.spawn_time > 0)
		{ 
			Mix_PauseMusic(); 
		}
		else if (Mix_PausedMusic() == 1 && p_player.spawn_time == 0)
		{
			Mix_ResumeMusic(); 
		} 

		int frame_death_width = death_enemy.get_frame_width();
		int frame_death_height = death_enemy.get_frame_height();
		std::vector<BulletObj*> bullet_arr = p_player.get_bullet_list();
		for (int r = 0; r < bullet_arr.size(); r++)
		{
			BulletObj* p_bullet = bullet_arr.at(r);
			if (p_bullet != NULL)
			{
				for (int t = 0; t < enemy_list.size(); t++)
				{
					Enemy* obj_enemy = enemy_list.at(t);
					if (obj_enemy != NULL)
					{
						SDL_Rect eRect;//enemy
						eRect.x = obj_enemy->GetRect().x;
						eRect.y = obj_enemy->GetRect().y;
						eRect.w = obj_enemy->get_width_frame();
						eRect.h = obj_enemy->get_height_frame();

						SDL_Rect bRect = p_bullet->GetRect();

						bool bCol = SDLCommonfunc::CheckCollision(bRect, eRect);

						if (bCol)
						{
							Mix_PlayChannel(MIX_CHANNEL, gDeath, NOT_REPEATITIVE);
							for (int d = 0; d < NUM_FRAME_DEATH; d++)
							{
								int x_pos = p_bullet->GetRect().x - frame_death_width * 0.5;
								int y_pos = p_bullet->GetRect().y - frame_death_height * 0.5;

								death_enemy.set_frame(d);
								death_enemy.SetRect(x_pos, y_pos);
								death_enemy.Show(g_screen);

							}
							p_player.RemoveBullet(r);
							obj_enemy->Free();
							enemy_list.erase(enemy_list.begin() + t);
						}
					}
				}
			}
		}

		//show game time
		std::string str_time = "Time: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		Uint32 val_time = 300 - time_val;
		if (val_time <= 0)
		{
			if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
			{
				gameRunning = false;
				break;
			}
		}
		else
		{
			std::string str_val = std::to_string(val_time);
			str_time += str_val;

			time_game.SetText(str_time);
			time_game.LoadFromRenderText(font_time, g_screen);
			time_game.RenderText(g_screen, SCREEN_WIDTH - 250, 20);
		}

		SDL_RenderPresent(g_screen);

		int real_time_passed = fps_time.GetTicks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;	//ms

		if (real_time_passed < time_one_frame)
		{
			int delay_time = time_one_frame - real_time_passed;
			if (delay_time >= 0)
				SDL_Delay(delay_time);
		}

	}

	for (int i = 0; i < enemy_list.size(); i++)
	{
		Enemy* p_enemy = enemy_list.at(i);
		if (p_enemy)
		{
			p_enemy->Free();
			p_enemy = NULL;
		}
	}

	enemy_list.clear();

	close();
	return 0;
}