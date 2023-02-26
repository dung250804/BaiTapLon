#include "Player.h"

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
			}
			break;
		case SDLK_LEFT:
			{
				status = WALK_LEFT;
				input_type.left = 1;
			}
			break;
		default:
			break;
		}
		
	}
	else if (events.type == SDL_KEYUP)
	{

	}
}