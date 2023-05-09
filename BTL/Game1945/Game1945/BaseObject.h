#pragma once

#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "CommonFunction.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x, const int& y) { rect.x = x, rect.y = y; }
	SDL_Rect GetRect() const { return rect; }
	SDL_Texture* GetObject() const { return p_object; }

	void RenderMenu(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
	void Free();

protected:
	SDL_Texture* p_object;
	SDL_Rect rect;
};

#endif

