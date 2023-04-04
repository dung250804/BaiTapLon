#include "DeathAnimation.h"

DeathAnimation::DeathAnimation()
{
	frame_width_ = 0;
	frame_height_ = 0;
	frame_ = 0;
}

DeathAnimation::~DeathAnimation()
{

}

bool DeathAnimation::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret)
	{
		frame_width_ = rect.w / NUM_FRAME_DEATH;
		frame_height_ = rect.h;
	}

	return ret;
}

void DeathAnimation::set_clip()
{
	if (frame_width_ > 0 && frame_height_ > 0)
	{
		for (int i = 0; i < NUM_FRAME_DEATH; i++)
		{
			frame_clip_[i].x = i * frame_width_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = frame_width_;
			frame_clip_[i].h = frame_height_;
		}
	}
}

void DeathAnimation::Show(SDL_Renderer* screen)
{
	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect render_quad = { rect.x, rect.y, frame_width_, frame_height_ };
	if (current_clip != NULL)
	{
		render_quad.w = current_clip->w;
		render_quad.h = current_clip->h;
	}

	SDL_RenderCopy(screen, p_object, current_clip, &render_quad);
}