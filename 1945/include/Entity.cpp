#include "Entity.h"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_texture)
:pos(p_pos), Texture(p_texture)
{
    CurrentFrame.x = 0;
    CurrentFrame.y = 0;
    CurrentFrame.w = 13834;
    CurrentFrame.h = 720;
}


SDL_Texture* Entity::GetTex()
{
    return Texture;
}

SDL_Rect Entity::GetCurrentFrame()
{
    return CurrentFrame;
}


