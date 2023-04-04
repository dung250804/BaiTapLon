#pragma once

#ifndef DEATH_ANIMATION_H
#define DEATH_ANIMATION_H

#include "CommonFunction.h"
#include "BaseObject.h"

#define NUM_FRAME_DEATH 40

class DeathAnimation : public BaseObject
{
public:
	DeathAnimation();
	~DeathAnimation();
public:
	void set_clip();
	void set_frame(const int& fr) { frame_ = fr; }
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	int get_frame_width() const { return frame_width_; }
	int get_frame_height() const { return frame_height_; }


private:
	int frame_width_;
	int frame_height_;

	unsigned int frame_;
	SDL_Rect frame_clip_[40];
};


#endif // !DEATH_ANIMATION_H
