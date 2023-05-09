#include "BaseObject.h"

BaseObject::BaseObject()
{
	p_object = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

BaseObject::~BaseObject()
{
	Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{

	Free();												//ngan tran` du lieu khi khoi tao lien tuc ham loadIMG;
	SDL_Texture* new_texture = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL)
		{
			rect.w = load_surface->w;
			rect.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface);
	}

	p_object = new_texture;

	return p_object != NULL;

}

void BaseObject::RenderMenu(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
	SDL_Rect renderSpace = { x, y, rect.w, rect.h };

	if (clip != nullptr)
	{
		renderSpace.w = clip->w;
		renderSpace.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, p_object, clip, &renderSpace);
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };

	SDL_RenderCopy(des, p_object, clip, &renderquad);
}

SDL_Texture* BaseObject::loadTexture(std::string path, SDL_Renderer* renderer)
{
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		std::cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == nullptr)
		{
			std::cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << std::endl;
		}
		SDL_FreeSurface(loadedSurface);
		p_object = newTexture;
	}
	return p_object;
}

Mix_Chunk* BaseObject::loadSound(std::string path)
{
	Mix_Chunk* newSound = nullptr;
	newSound = Mix_LoadWAV(path.c_str());
	if (newSound == nullptr)
	{
		std::cout << "Unable to load sound " << path << "Mix_Chunk Error: " << Mix_GetError() << std::endl;
	}
	return newSound;
}

Mix_Music* BaseObject::loadSong(std::string path)
{
	Mix_Music* newSong = nullptr;
	newSong = Mix_LoadMUS(path.c_str());
	if (newSong == nullptr)
	{
		std::cout << "Unable to load song " << path << "Mix_Music Error: " << Mix_GetError() << std::endl;
	}
	return newSong;
}

void BaseObject::Free()
{
	if (p_object != NULL)
	{
		SDL_DestroyTexture(p_object);
		p_object = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}