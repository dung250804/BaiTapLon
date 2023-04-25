
#include "CommonFunction.h"
#include "BaseObject.h"
#include "MapGame.h"
#include "Player.h"
#include "FPSnTicks.h"
#include "Enemy.h"
#include "DeathAnimation.h"
#include "TextObj.h"
#include "Button.h"
#include "GameUtils.h"

BaseObject gMenuTexture;
BaseObject gInstructionTexture;
BaseObject gPlayButtonTexture;
BaseObject gHelpButtonTexture;
BaseObject gExitButtonTexture;
BaseObject gBackButtonTexture;
BaseObject gPauseButtonTexture;
BaseObject gContinueButtonTexture;
BaseObject gLoseTexture;
//-----------------------------------------------------------------------------------------------------------------------------------------------------
SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];
//-----------------------------------------------------------------------------------------------------------------------------------------------------
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gLose = nullptr;
//-----------------------------------------------------------------------------------------------------------------------------------------------------
Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
//-----------------------------------------------------------------------------------------------------------------------------------------------------
BaseObject g_background;
TTF_Font* font_time = NULL;

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
		if (!gMenuTexture.LoadImg("Menu/StartMenu.png", g_screen))				//Menu/StartMenu.png			
		{
			std::cout << "Failed to load menu image" << std::endl;
			success = false;
		}

		if (!gInstructionTexture.LoadImg("Menu/instruction.png", g_screen))
		{
			std::cout << "Failed to load instruction image" << std::endl;
			success = false;
		}

		if (!gPlayButtonTexture.LoadImg("button/play_button.png", g_screen))
		{
			std::cout << "Failed to load play_button image" << std::endl;
			success = false;
		}
		else
		{
			for (int i = 0; i < BUTTON_TOTAL; ++i)
			{
				gPlayButton[i].x = 150 * i;
				gPlayButton[i].y = 0;
				gPlayButton[i].w = 150;
				gPlayButton[i].h = 98;
			}
		}

		if (!gHelpButtonTexture.LoadImg("button/help_button.png", g_screen))
		{
			std::cout << "Failed to load help_button image" << std::endl;
			success = false;
		}
		else
		{
			for (int i = 0; i < BUTTON_TOTAL; ++i)
			{
				gHelpButton[i].x = 150 * i;
				gHelpButton[i].y = 0;
				gHelpButton[i].w = 150;
				gHelpButton[i].h = 98;
			}
		}

		if (!gBackButtonTexture.LoadImg("button/back_button.png", g_screen))
		{
			std::cout << "Failed to load back_button image" << std::endl;
			success = false;
		}
		else
		{
			for (int i = 0; i < BUTTON_TOTAL; ++i)
			{
				gBackButton[i].x = 100 * i;
				gBackButton[i].y = 0;
				gBackButton[i].w = 100;
				gBackButton[i].h = 78;
			}
		}

		if (!gExitButtonTexture.LoadImg("button/exit_button.png", g_screen))
		{
			std::cout << "Failed to load exit_button image" << std::endl;
			success = false;
		}
		else
		{
			for (int i = 0; i < BUTTON_TOTAL; ++i)
			{
				gExitButton[i].x = 150 * i;
				gExitButton[i].y = 0;
				gExitButton[i].w = 150;
				gExitButton[i].h = 98;
			}
		}

		if (!gPauseButtonTexture.LoadImg("button/pause_button.png", g_screen))
		{
			std::cout << "Failed to load pause_button image " << std::endl;
			success = false;
		}
		else
		{
			for (int i = 0; i < BUTTON_TOTAL; ++i)
			{
				gPauseButton[i].x = 22 * i;
				gPauseButton[i].y = 0;
				gPauseButton[i].w = 22;
				gPauseButton[i].h = 34;
			}
		}

		if (!gContinueButtonTexture.LoadImg("button/continue_button.png", g_screen))
		{
			std::cout << "Failed to load continue_button image " << std::endl;
			success = false;
		}
		else
		{
			for (int i = 0; i < BUTTON_TOTAL; ++i)
			{
				gContinueButton[i].x = 22 * i;
				gContinueButton[i].y = 0;
				gContinueButton[i].w = 22;
				gContinueButton[i].h = 34;
			}
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
	//Sound
	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenuMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gLose);
	Mix_FreeChunk(gJump);
	gMusic = nullptr;
	gMenuMusic = nullptr;
	gClick = nullptr;
	gLose = nullptr;
	gJump = nullptr;
	//window
	gMenuTexture.Free();
	gInstructionTexture.Free();
	gPlayButtonTexture.Free();
	gHelpButtonTexture.Free();
	gExitButtonTexture.Free();
	gBackButtonTexture.Free();
	gPauseButtonTexture.Free();
	gContinueButtonTexture.Free();
	gLoseTexture.Free();

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
	Enemy* dynamic_enemies = new Enemy[20];
	for (int i = 0; i < 20; i++)
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
			p_enemy->set_x_pos(700 + i*1500);
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

	if (loadBackGround() == false)
		return -1;

	char dat[100] = "map/map01.dat";

	GameMap game_map;
	game_map.LoadMap(dat);
	game_map.LoadTiles(g_screen);

	Player p_player;
	p_player.LoadImg("Gfx//moveR+.png", g_screen);
	p_player.set_clips();

	std::vector<Enemy*> enemy_list = MakeEnemyList();

	DeathAnimation death_enemy;
	bool eRet = death_enemy.LoadImg("Gfx//Blood.png", g_screen);
	if (!eRet) return -1;
	int LP = 0;
	death_enemy.set_clip();

	//Text (time)
	TextObj time_game;
	time_game.SetColor(TextObj::WHITE_TEXT);

	bool Quit_Menu = false;
	bool gameRunning = false;

	Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);
	while (!Quit_Menu)
	{
		SDL_Event e_mouse;
		while (SDL_PollEvent(&e_mouse) != 0)
		{
			if (e_mouse.type == SDL_QUIT)
			{
				Quit_Menu = true;
				gameRunning = false;
			}

			bool Quit_Game = false;

			HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, gameRunning, gClick);

			/*HandleHelpButton(&e_mouse, gBackButton,
				HelpButton, BackButton,
				gInstructionTexture, gBackButtonTexture,
				g_screen, Quit_Game, gClick);*/
			if (HelpButton.IsInside(&e_mouse, COMMON_BUTTON))
			{
				switch (e_mouse.type)
				{
				case SDL_MOUSEMOTION:
					HelpButton.currentSprite = BUTTON_MOUSE_OVER;
					break;
				case SDL_MOUSEBUTTONDOWN:
					HelpButton.currentSprite = BUTTON_MOUSE_OVER;
					Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

					bool ReadDone = false;
					while (!ReadDone)
					{
						do
						{
							if (e_mouse.type == SDL_QUIT)
							{
								ReadDone = true;
								Quit_Game = true;
								//Close();
							}

							else if (BackButton.IsInside(&e_mouse, COMMON_BUTTON))
							{
								switch (e_mouse.type)
								{
								case SDL_MOUSEMOTION:
									BackButton.currentSprite = BUTTON_MOUSE_OVER;
									break;
								case SDL_MOUSEBUTTONDOWN:
									BackButton.currentSprite = BUTTON_MOUSE_OVER;
									Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
									ReadDone = true;
									break;
								}
							}
							else
							{
								BackButton.currentSprite = BUTTON_MOUSE_OUT;
							}

							gInstructionTexture.RenderMenu(0, 0, g_screen);

							SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
							BackButton.RenderMenu(currentClip_Back, g_screen, gBackButtonTexture);

							SDL_RenderPresent(g_screen);
						} while (SDL_PollEvent(&e_mouse) != 0 && e_mouse.type == SDL_MOUSEBUTTONDOWN || e_mouse.type == SDL_MOUSEMOTION);
					}
					break;
				}
			}

			HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);

			if (Quit_Game == true)
			{
				return 0;
			}
		}

		

		SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
		PlayButton.RenderMenu(currentClip_Play, g_screen, gPlayButtonTexture);

		SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
		HelpButton.RenderMenu(currentClip_Help, g_screen, gHelpButtonTexture);

		SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
		ExitButton.RenderMenu(currentClip_Exit, g_screen, gExitButtonTexture);

		gMenuTexture.RenderMenu(0, 0, g_screen);

		SDL_RenderPresent(g_screen);
		
	}

	
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
					LP++;
					if (LP <= 3)
					{
						p_player.SetRect(0, 0);
						p_player.set_spawn_time(60);
						SDL_Delay(1000);
						continue;
					}
					else
					{
						if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
						{
							p_enemy->Free();
							close();
							SDL_Quit();
							return 0;
						}
					}
				}
			}
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