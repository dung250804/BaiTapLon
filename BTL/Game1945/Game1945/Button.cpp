#include "Button.h"

Button::Button()
{
	position.x = 0;
	position.y = 0;

	width_frame = 0;
	height_frame = 0;

	currentSprite = BUTTON_MOUSE_OUT;
}

Button::Button(int x, int y)
{
	position.x = x;
	position.y = y;

	currentSprite = BUTTON_MOUSE_OUT;
}

bool Button::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		width_frame = rect.w / BUTTON_TOTAL;
		height_frame = rect.h;

		return ret;
	}
}

SDL_Rect Button::GetRectFrame()
{
	SDL_Rect rect_;
	rect_.x = rect.x;
	rect_.y = rect.y;
	rect_.w = width_frame;
	rect_.h = height_frame;

	return rect_;
}

void Button::set_clips()
{
	if (width_frame > 0 && height_frame > 0)
	{
		for (int i = 0; i < BUTTON_TOTAL; i++)
		{
			Button_clip[i].x = i * width_frame;
			Button_clip[i].y = 0;
			Button_clip[i].w = width_frame;
			Button_clip[i].h = height_frame;
		}
	}
}


void Button::ShowButton(SDL_Renderer* des, SDL_Event* e)
{
	if (IsInside(e, COMMON_BUTTON))
	{
		currentSprite = BUTTON_MOUSE_OVER;
	}
	else
	{
		currentSprite = BUTTON_MOUSE_OUT;
	}

	rect.x = position.x;
	rect.y = position.y;

	SDL_Rect* current_clip = &Button_clip[currentSprite];

	SDL_Rect renderQuad = { rect.x, rect.y, width_frame, height_frame };
	SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
}

void Button::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

bool Button::IsInside(SDL_Event* e, int size)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		int button_width, button_height;
		if (size == SMALL_BUTTON)
		{
			button_width = SMALL_BUTTON_WIDTH;
			button_height = SMALL_BUTTON_HEIGHT;
		}
		else
		{
			button_width = COMMON_BUTTON_WIDTH;
			button_height = COMMON_BUTTON_HEIGHT;
		}

		SDL_GetMouseState(&x, &y);

		bool inside = true;
		if (x < position.x)
		{
			inside = false;
		}
		else if (x > position.x + button_width)
		{
			inside = false;
		}
		else if (y < position.y)
		{
			inside = false;
		}
		else if (y > position.y + button_height)
		{
			inside = false;
		}
		return inside;
	}
	return false;
}

void Button::RenderMenu(SDL_Rect* currentClip, SDL_Renderer* gRenderer, BaseObject gButtonTexture)
{
	gButtonTexture.RenderMenu(position.x, position.y, gRenderer, currentClip);
}

