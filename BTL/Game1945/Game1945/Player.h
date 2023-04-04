#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObj.h"


#define GRAVITY_FALL 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VAL 15
#define BULLET_POS_Y 0.35
#define PLAYER_FRAME 7


class Player : public BaseObject
{
public:
	Player();
	~Player();

	enum WalkType
	{
		WALK_NONE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		JUMP_RIGHT = 3,
		JUMP_LEFT = 4,
		SEE_UP = 5,
		SEE_UP_RIGHT = 6,
		SEE_UP_LEFT = 7,
	};

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInput(SDL_Event events, SDL_Renderer* screen);
	void set_clips();

	void PlayerMovement(Map& map_data);
	void CheckMapCollision(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; };
	void CenterMapCamera(Map& map_data);
	void UpdateAnimation(SDL_Renderer* des);
	SDL_Rect GetRectFrame();

	void set_bullet_list(std::vector<BulletObj*> bullet_list)
	{
		p_bullet_list = bullet_list;
	}
	std::vector<BulletObj*> get_bullet_list() const { return p_bullet_list; }
	void HandleBullet(SDL_Renderer* des);
	void RemoveBullet(const int& index);
	void set_spawn_time(const int& spAwn_time) { spawn_time = spAwn_time; }

private:
	std::vector<BulletObj*> p_bullet_list;

	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int width_frame;
	int height_frame;

	SDL_Rect frame_clip[7];		//defaut 7 frames

	Input input_type;
	int frame;
	int status;					//lay' anh? khi bam' phim'
	bool on_ground;

	int map_x_;
	int map_y_;
	int spawn_time;
};



#endif
