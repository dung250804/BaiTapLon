#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "CommonFunction.h"
#include "BaseObject.h"


class Player : public BaseObject
{
public:
	Player();
	~Player();

	enum WalkType
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
	};

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInput(SDL_Event events, SDL_Renderer* screen);
	void set_clips();

private:
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
};



#endif
