#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include "CommonFunction.h"
#include "BaseObject.h"

class Button : public BaseObject
{
public:
	ButtonSprite currentSprite;

	Button();

	Button(int x, int y);

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	SDL_Rect GetRectFrame();
	void set_clips();
	void ShowButton(SDL_Renderer* des, SDL_Event* e);

	void SetPosition(int x, int y);
	bool IsInside(SDL_Event* e, int size);
	void RenderMenu(SDL_Rect* currentClip, SDL_Renderer* gRenderer, BaseObject gButtonTexture);

	

private:
	SDL_Point position;

	int width_frame;
	int height_frame;

	SDL_Rect Button_clip[BUTTON_TOTAL];

};

#endif // !BUTTON_H_