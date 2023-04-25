#include "FPSnTicks.h"

FPSnTicks::FPSnTicks()
{
	start_tick = 0;
	paused_tick = 0;
	is_paused_ = false;
	is_started_ = false;

}

FPSnTicks::~FPSnTicks()
{

}

void FPSnTicks::start()
{
	is_started_ = true;
	is_paused_ = false;
	start_tick = SDL_GetTicks();
}

void FPSnTicks::stop()
{
	is_paused_ = false;
	is_started_ = false;
}

void FPSnTicks::paused()
{
	if (is_started_ == true && is_paused_ == false)
	{
		is_paused_ = true;
		paused_tick = SDL_GetTicks() - start_tick;
	}
}

void FPSnTicks::unpaused()
{
	if (is_paused_ == true)
	{
		is_paused_ = false;
		start_tick = SDL_GetTicks() - paused_tick;
		paused_tick = 0;
	}
}

int FPSnTicks::GetTicks()
{
	if (is_started_ == true)
	{
		if (is_paused_ == true)
		{
			return paused_tick;
		}
		else
		{
			return SDL_GetTicks() - start_tick;
		}
	}

	return 0;
}

bool FPSnTicks::is_started()
{
	return is_started_;
}

bool FPSnTicks::is_paused()
{
	return is_paused_;
}