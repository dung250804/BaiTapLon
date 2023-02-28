#include "Player.h"
#include <iostream>

	Player::Player()
{
	frame = 0;
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	x_val = 0;
	width_frame = 0;
	height_frame = 0;
	status = -1;			//chua biet
	input_type.left = 0;
	input_type.right = 0;
	input_type.up = 0;
	input_type.down = 0;
	input_type.jump = 0;
	on_ground = false;
}

Player::~Player()
{
	
}


//scan frame
bool Player::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		width_frame = rect.w / 7;
		height_frame = rect.h;

		return ret;
	}
}
//set frame animation
void Player::set_clips()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < 7; i++) 
		{
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}
}

void Player::Show(SDL_Renderer* des)
{
	if (status == WALK_LEFT)
	{
		LoadImg("Gfx//moveL.png", des);
	}

	else
	{
		LoadImg("Gfx//moveR.png", des);
	}

	if (input_type.left == 1 || input_type.right == 1)
	{
		frame++;
	}
	else
	{
		frame = 0;
	}

	if (frame >= 7)
		frame = 0;

	rect.x = x_pos;
	rect.y = y_pos;

	SDL_Rect* current_clip = &frame_clip[frame];

	SDL_Rect renderQuad = { rect.x, rect.y, width_frame, height_frame };
	SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
}

void Player::HandleInput(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
			{
				status = WALK_RIGHT;
				input_type.right = 1;
				input_type.left = 0;
			}
			break;
		case SDLK_LEFT:
			{
				status = WALK_LEFT;
				input_type.left = 1;
				input_type.right = 0;
			}
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			input_type.right = 0;
		}
		break;
		case SDLK_LEFT:
		{
			input_type.left = 0;
		}
		break;
		}
	}
}

void Player::PlayerMovement(Map& map_data)
{
	x_val = 0;
	y_val += GRAVITY_FALL;

	if (y_val >= MAX_FALL_SPEED)
	{
		y_val = MAX_FALL_SPEED;
	}

	if (input_type.left == 1)
	{
		x_val -= PLAYER_SPEED;
	}
	else if (input_type.right == 1)
	{
		x_val += PLAYER_SPEED;
	}

	CheckMapCollision(map_data);
}

void Player::CheckMapCollision(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//Check theo truc Ox
	int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;			//1 la sai so' de co the? check va cham.

	y1 = y_pos / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val > 0)//player moving to right
		{
			if (map_data.tile[y1][x2] != BLANK_TILE
				|| map_data.tile[y2][x2] != BLANK_TILE)
			{
				x_pos = x2 * TILE_SIZE;
				x_pos -= width_frame + 1;						//+1 sai so khi nay~
				x_val = 0;
			}
		}
		else if (x_val < 0)//player moving to left
		{
			if (map_data.tile[y1][x1] != BLANK_TILE
				|| map_data.tile[y2][x1] != BLANK_TILE)
			{
				x_pos = (x1 + 1) * TILE_SIZE;					//+1 sai so khi nay~
				x_val = 0;
			}
		}
	}


	//Check theo truc Oy

	int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
	x1 = x_pos / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + height_frame - 1) / TILE_SIZE;		//1 la sai so' de co the? check va cham.

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val > 0)
		{
			if (map_data.tile[y2][x1] != BLANK_TILE
				|| map_data.tile[y2][x2] != BLANK_TILE)
			{
				y_pos = y2 * TILE_SIZE;
				y_pos -= (height_frame + 1);
				y_val = 0;
				on_ground = true;
			}
		}
		else if (y_val < 0)
		{
			if (map_data.tile[y1][x1] != BLANK_TILE
				|| map_data.tile[y1][x2] != BLANK_TILE)
			{
				y_pos* (y1 + 1)* TILE_SIZE;
				y_val = 0;
			}
		}
	};

	x_pos += x_val;
	y_pos += y_val;

	if (x_pos < 0)
	{
		x_pos = 0;
	}
	else if (x_pos + width_frame > map_data.max_x)
	{
		x_pos = map_data.max_x - width_frame - 1;
	}
}
