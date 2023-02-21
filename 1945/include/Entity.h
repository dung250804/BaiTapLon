#ifndef ENTITY_H
#define ENTITY_H

#pragma once;
#include<SDL.h>
#include<SDL_image.h>

#include "math_algorithm.h"
class Entity
{
    public:
        Entity(Vector2f pos, SDL_Texture* p_texture);
        Vector2f& GetPos()
        {
            return pos;
        }

        SDL_Texture* GetTex();
        SDL_Rect GetCurrentFrame();



    protected:

    private:
        Vector2f pos;
        SDL_Rect CurrentFrame;
        SDL_Texture* Texture;
};

#endif // ENTITY_H
