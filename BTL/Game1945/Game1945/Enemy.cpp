
#include "Enemy.h"

Enemy::Enemy()
{
	x_pos = 0.0;
	y_pos = 0.0;
	x_val = 0.0;
	y_val = 0.0;
	on_ground = false;
	spawn_time = 0;
	width_frame = 0;
	height_frame = 0;
	frame = 0;

	animation_a = 0;
	animation_b = 0;

	input_type.left = 0;
	type_move = STATIC_ENEMY;
}

Enemy::~Enemy()
{

}

SDL_Rect Enemy::GetRectFrame()
{
	SDL_Rect rect_;
	rect_.x = rect.x;
	rect_.y = rect.y;
	rect_.w = width_frame;
	rect_.h = height_frame;

	return rect_;
}

void Enemy::show(SDL_Renderer* des)
{
	if (spawn_time == 0)
	{
		rect.x = x_pos - map_x;
		rect.y = y_pos - map_y;
		frame++;
		if (frame >= 24)
		{
			frame = 0;
		}

		SDL_Rect* Current_Clip = &frame_clip[frame / 4];
		SDL_Rect rendQuad = { rect.x, rect.y, width_frame, height_frame };
		SDL_RenderCopy(des, p_object, Current_Clip, &rendQuad);
	}
}

bool Enemy::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret)
	{
		width_frame = rect.w / SWORD_ENEMY_FRAME;
		height_frame = rect.h;
	}
	return ret;
}

void Enemy::set_clips()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < 6; i++)
		{
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}
}


void Enemy::EnemyMovement(Map& gMap)
{
	if (spawn_time == 0)
	{
		x_val = 0;
		y_val += GRAVITY_FALLS;
		if (y_val >= MAX_GRAVITY)
		{
			y_val = MAX_GRAVITY;
		}

		if (input_type.left == 1)
		{
			x_val -= ENEMY_SPEED;
		}
		else if (input_type.right == 1)
		{
			x_val += ENEMY_SPEED;
		}

		CheckMapCollision(gMap);
	}
	else if (spawn_time > 0)
	{
		spawn_time--;
		if (spawn_time == 0)
		{
			InitEnemy();
		}
	}
}

void Enemy::InitEnemy()
{
	x_val = 0;
	y_val = 0;
	if (x_pos > 256)
	{
		x_pos -= 256;
		animation_a -= 256;
		animation_b -= 256;
	}
	else
	{
		x_pos = 0;
	}
	y_pos = 0;
	spawn_time = 0;
	input_type.left = 1;
}

void Enemy::CheckMapCollision(Map& gMap)
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
			int val1 = gMap.tile[y1][x2];
			int val2 = gMap.tile[y2][x2];

			if (val1 != BLANK_TILE || val2 != BLANK_TILE)
			{
				x_pos = x2 * TILE_SIZE;
				x_pos -= width_frame + 1;						//+1 sai so khi nay~
				x_val = 0;
			}
		}
		else if (x_val < 0)//player moving to left
		{
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y2][x1];

			if (val1 != BLANK_TILE || val2 != BLANK_TILE)
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
			int val1 = gMap.tile[y2][x1];
			int val2 = gMap.tile[y2][x2];

			if (val1 != BLANK_TILE || val2 != BLANK_TILE)
			{
				y_pos = y2 * TILE_SIZE;
				y_pos -= (height_frame + 1);
				y_val = 0;
				on_ground = true;

			}

		}
		else if (y_val < 0)
		{
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y1][x2];

			if (val1 != BLANK_TILE || val2 != BLANK_TILE)
			{
				y_pos* (y1 + 1)* TILE_SIZE;
				y_val = 0;
			}

		}
	}

	x_pos += x_val;
	y_pos += y_val;

	if (x_pos < 0)
	{
		x_pos = 0;
	}
	else if (x_pos + width_frame > gMap.max_x)
	{
		x_pos = gMap.max_x - width_frame - 1;
	}

	if (y_pos > gMap.max_y)
	{
		spawn_time = 60;
	}
}

void Enemy::ImpMoveType(SDL_Renderer* screen)
{
	if (type_move == STATIC_ENEMY)
	{

	}
	else
	{
		if (on_ground == true)
		{
			if (x_pos > animation_b)
			{
				input_type.left = 1;
				input_type.right = 0;
				LoadImg("Gfx//SwordEnemyL.png", screen);
			}
			else if (x_pos < animation_a)
			{
				input_type.left = 0;
				input_type.right = 1;
				LoadImg("Gfx//SwordEnemyR.png", screen);
			}
		}
		else
		{
			if (input_type.left == 1)
			{
				LoadImg("Gfx//SwordEnemyL.png", screen);
			}
		}
	}
}

void Enemy::InitBullet(BulletObj* p_bullet, SDL_Renderer* screen)
{
	if (p_bullet != NULL)
	{
		p_bullet->set_bullet_type(BulletObj::GATLIN_BULLET);

		bool ret = p_bullet->LoadBulletIMG(screen);
		if (ret)
		{
			p_bullet->set_is_move(true);
			p_bullet->set_bullet_dir(BulletObj::DIR_LEFT);
			p_bullet->SetRect(rect.x - 130, y_pos + 30);
			p_bullet->set_x_val(15);
			bullet_list.push_back(p_bullet);
		}
	}
}

void Enemy::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < bullet_list.size(); i++)
	{
		BulletObj* p_bullet = bullet_list.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move())
			{
				int bullet_distance = rect.x + width_frame - p_bullet->GetRect().x;
				if (bullet_distance < 600 && bullet_distance > 0)
				{
					p_bullet->HandleBulletMove(x_limit, y_limit);
					p_bullet->Render(screen);
				}
				else
				{
					p_bullet->set_is_move(false);
				}
			}
			else
			{
				p_bullet->set_is_move(true);
				p_bullet->SetRect(rect.x - 130, y_pos + 30);
			}
		}
	}
}


void Enemy::RemoveBullet(const int& index)
{
	int size = bullet_list.size();
	if (size > 0 && index < size)
	{
		BulletObj* p_bullet = bullet_list.at(index);
		bullet_list.erase(bullet_list.begin() + index);
		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

