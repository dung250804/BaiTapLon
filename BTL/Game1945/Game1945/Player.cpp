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
	status = WALK_NONE;			//chua biet
	input_type.left = 0;
	input_type.right = 0;
	input_type.up = 0;
	input_type.down = 0;
	input_type.jump = 0;
	on_ground = false;
	map_x_ = 0;
	map_y_ = 0;
	spawn_time = 0;

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
		width_frame = rect.w / PLAYER_FRAME;
		height_frame = rect.h;

		return ret;
	}
}

SDL_Rect Player::GetRectFrame()
{
	SDL_Rect rect_;
	rect_.x = rect.x;
	rect_.y = rect.y;
	rect_.w = width_frame;
	rect_.h = height_frame;

	return rect_;
}

//set frame animation
void Player::set_clips()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < PLAYER_FRAME; i++)
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
	UpdateAnimation(des);

	if (input_type.left == 1 || input_type.right == 1)
	{
		frame++;
	}
	else
	{
		frame = 0;
	}

	if (frame >= PLAYER_FRAME * 4)
		frame = 0;

	if (spawn_time == 0) 
	{
		rect.x = x_pos - map_x_;
		rect.y = y_pos - map_y_;

		SDL_Rect* current_clip = &frame_clip[frame/4];
	
		SDL_Rect renderQuad = { rect.x, rect.y, width_frame, height_frame };
		SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
	}
	
}

void Player::HandleInput(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		if (events.key.keysym.sym == SDLK_d)
		{
				status = WALK_RIGHT;
				input_type.right = 1;
				input_type.left = 0;
				UpdateAnimation(screen);
		}
		else if (events.key.keysym.sym == SDLK_a)
		{
			status = WALK_LEFT;
			input_type.left = 1;
			input_type.right = 0;
			UpdateAnimation(screen);
		}
		if (events.key.keysym.sym == SDLK_w)
		{
			if (status == WALK_RIGHT)
			{
				status = SEE_UP_RIGHT;
			}
			else if(status == WALK_LEFT)
			{
				status = SEE_UP_LEFT;
			}
		}
		if (events.key.keysym.sym == SDLK_s)
		{
			if (status == WALK_RIGHT)
			{
				status = SEE_DOWN_RIGHT;
			}  
			else if (status == WALK_LEFT)
			{
				status = SEE_DOWN_LEFT;
			}
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		if (events.key.keysym.sym == SDLK_w)
		{
			if (status == SEE_UP_RIGHT)
			{
				status = WALK_RIGHT;
			}
			else if (status == SEE_UP_LEFT)
			{
				status = WALK_LEFT;
			}
		}
		if (events.key.keysym.sym == SDLK_s) 
		{
			if (status == SEE_DOWN_RIGHT) 
			{  
				status = WALK_RIGHT; 
			}
			else if (status == SEE_DOWN_LEFT)
			{
				status = WALK_LEFT;  
			} 
		}
		if (events.key.keysym.sym == SDLK_d)
		{
			input_type.right = 0;
		}
		else if (events.key.keysym.sym == SDLK_a)
		{
			input_type.left = 0;
		}
			
	}

	if (events.type == SDL_KEYDOWN)
	{
		if (events.key.keysym.sym == SDLK_k /* || events.key.keysym.sym == SDLK_w */)
		{
			input_type.jump = 1;
		}
		if (events.key.keysym.sym == SDLK_j)
		{
			BulletObj* p_bullet = new BulletObj();
			p_bullet->set_bullet_type(BulletObj::DEFAULT_BULLET);
			p_bullet->LoadBulletIMG(screen);

			if (status == WALK_LEFT)
			{
				p_bullet->set_bullet_dir(BulletObj::DIR_LEFT);
				p_bullet->SetRect(this->rect.x + 20, rect.y + height_frame * BULLET_POS_Y);
			}
			else if (status == WALK_RIGHT)
			{
				p_bullet->set_bullet_dir(BulletObj::DIR_RIGHT);
				p_bullet->SetRect(this->rect.x + width_frame - 30, rect.y + height_frame * BULLET_POS_Y);
			}
			else if (status == SEE_UP_RIGHT)
			{
				p_bullet->set_bullet_dir(BulletObj::DIR_UP);
				p_bullet->SetRect(this->rect.x + width_frame - 22, rect.y + height_frame * BULLET_POS_Y);
			}
			else if (status == SEE_UP_LEFT)
			{
				p_bullet->set_bullet_dir(BulletObj::DIR_UP);
				p_bullet->SetRect(this->rect.x + 12, rect.y + height_frame * BULLET_POS_Y);
			}
			else if (status == SEE_DOWN_LEFT)
			{
				p_bullet->set_bullet_dir(BulletObj::DIR_DOWN);
				p_bullet->SetRect(this->rect.x + 20, rect.y + height_frame * BULLET_POS_Y);
			}
			else if (status == SEE_DOWN_RIGHT)
			{
				p_bullet->set_bullet_dir(BulletObj::DIR_DOWN);
				p_bullet->SetRect(this->rect.x + width_frame - 30, rect.y + height_frame * BULLET_POS_Y);
			}

			p_bullet->set_x_val(20);
			p_bullet->set_y_val(20);
			p_bullet->set_is_move(true);

			p_bullet_list.push_back(p_bullet);
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		if (events.key.keysym.sym == SDLK_k /* || events.key.keysym.sym == SDLK_w */)
		{
			input_type.jump = 0;
		}
		else if (events.key.keysym.sym == SDLK_j);
	}
}

void Player::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < p_bullet_list.size(); i++)
	{
		BulletObj* p_bullet = p_bullet_list.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->HandleBulletMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des);
			}
			else
			{
				p_bullet_list.erase(p_bullet_list.begin() + i);
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}
}

void Player::PlayerMovement(Map& map_data)
{
	if (spawn_time == 0)
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

		if (input_type.jump == 1)
		{
			if (on_ground == true)
			{
				y_val = -PLAYER_JUMP_VAL;
			}
			on_ground = false;
			input_type.jump == 0;
		}

		CheckMapCollision(map_data);
		CenterMapCamera(map_data);
	}
	if (spawn_time > 0)
	{
		spawn_time--;
		if (spawn_time == 0)
		{
			on_ground = false;
			x_pos = 0;		
			y_pos = 0;
			x_val = 0;
			y_val = 0;
		}
	}
}

void Player::CenterMapCamera(Map& map_data)
{
	map_data.start_x = x_pos - (SCREEN_WIDTH / 3);							// 1/3 chieu` ngang thi` di chuyen man` hinh`
	if (map_data.start_x < 0)
	{
		map_data.start_x = 0;
	}
	else if (map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
	{
		map_data.start_x = map_data.max_x - SCREEN_WIDTH;
	}

	map_data.start_y = y_pos - (SCREEN_HEIGHT / 2);
	if (map_data.start_y < 0)
	{
		map_data.start_y = 0;
	}
	else if (map_data.start_y + SCREEN_HEIGHT >= map_data.max_y)
	{
		map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
	}
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
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if (val1 == DANGER_ZONE || val2 == DANGER_ZONE)
			{
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
			}
			else
			{
				if ((val1 > 0 && val1 < 10 ) || (val2 > 0 && val2 < 10))
				{
					x_pos = x2 * TILE_SIZE;
					x_pos -= width_frame + 1;						//+1 sai so khi nay~
					x_val = 0;
				}
			}
			
		}
		else if (x_val < 0)//player moving to left
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if (val1 == DANGER_ZONE || val2 == DANGER_ZONE)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
			}
			else 
			{
				if ((val1 > 0 && val1 < 10) || (val2 > 0 && val2 < 10))
				{
					x_pos = (x1 + 1) * TILE_SIZE;					//+1 sai so khi nay~
					x_val = 0;
				}
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
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if (val1 == DANGER_ZONE || val2 == DANGER_ZONE)
			{
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
			}
			else
			{
				if ((val1 > 0 && val1 < 10) || (val2 > 0 && val2 < 10))
				{
					y_pos = y2 * TILE_SIZE;
					y_pos -= (height_frame + 1);
					y_val = 0;
					on_ground = true;
					if (status == WALK_NONE)
					{
						status == WALK_RIGHT;
					}

				}
			}
			
		}
		else if (y_val < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];

			if (val1 == DANGER_ZONE || val2 == DANGER_ZONE)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
			}
			else
			{
				if ((val1 > 0 && val1 < 10) || (val2 > 0 && val2 < 10))
				{
					y_pos* (y1 + 1)* TILE_SIZE;
					y_val = 0;	
				}
			}
			
		}
	}

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

	if (y_pos > map_data.max_y)
	{
		spawn_time = 60;
	}
}

void Player::UpdateAnimation(SDL_Renderer* des)
{
	if (on_ground == true)
	{
		if (status == WALK_LEFT)
		{
			LoadImg("Gfx//moveL+.png", des);
		}
		else if(status == WALK_RIGHT)
		{
			LoadImg("Gfx//moveR+.png", des);
		}
		else if (status == SEE_UP_RIGHT)
		{
			LoadImg("Gfx//SeeUpR.png", des);
		}
		else if (status == SEE_UP_LEFT)
		{
			LoadImg("Gfx//SeeUpL.png", des);
		}
		else if (status == SEE_DOWN_LEFT) 
		{
			LoadImg("Gfx//SeeDownL.png", des);
		}
		else if (status == SEE_DOWN_RIGHT) 
		{
			LoadImg("Gfx//SeeDownR.png", des);
		}
	}
	else 
	{
		if (status == WALK_LEFT)
		{
			LoadImg("Gfx//jumpL.png", des);
		}
		else if(status == WALK_RIGHT)
		{
			LoadImg("Gfx//jumpR.png", des);
		}
		else if (status == SEE_UP_RIGHT)
		{
			LoadImg("Gfx//SeeUpR.png", des);
		}
		else if (status == SEE_UP_LEFT)
		{
			LoadImg("Gfx//SeeUpL.png", des);
		}
		else if (status == SEE_DOWN_LEFT)
		{
			LoadImg("Gfx//SeeDownL.png", des);
		}
		else if (status == SEE_DOWN_RIGHT)
		{
			LoadImg("Gfx//SeeDownR.png", des);
		}
	}
}

void Player::RemoveBullet(const int& index)
{
	int size = p_bullet_list.size();
	if (size > 0 && index < size)
	{
		BulletObj* p_bullet = p_bullet_list.at(index);
		p_bullet_list.erase(p_bullet_list.begin() + index);
		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

bool Player::WinStatus(Map& map_data)
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
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			if (val1 == WIN_AREA1 || val2 == WIN_AREA2)
				return true;
		}
		else if (x_val < 0)//player moving to left
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if (val1 == WIN_AREA1 || val2 == WIN_AREA2)
				return true;
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
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if (val1 == WIN_AREA1 || val2 == WIN_AREA2)
				return true;
		}
		else if (y_val < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if (val1 == WIN_AREA1 || val2 == WIN_AREA2)
				return true;
		}
	}
	return false;
}