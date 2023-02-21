#include "RenderWindow.h"
#include<iostream>
using namespace std;

RenderWindow::RenderWindow(const char* p_title, int p_width, int p_height)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            p_width, p_height, SDL_WINDOW_SHOWN);

    if(window == NULL){
        cout << "Window failed to init. Error: " << SDL_GetError() << endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::CleanUp()
{
    SDL_DestroyWindow(window);
}

SDL_Texture* RenderWindow::LoadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if(texture == NULL)
        cout << "Faiiled to load texture. Error: " << SDL_GetError() << endl;

    return texture;
}

void RenderWindow::Clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::Render(Entity& p_entity)
{
    SDL_Rect O;                                     //goc toa do(tren cung` ben trai')
    O.x = p_entity.GetCurrentFrame().x;
    O.y = p_entity.GetCurrentFrame().y;
    O.w = p_entity.GetCurrentFrame().w;
    O.h = p_entity.GetCurrentFrame().h;

    SDL_Rect Destination;
    Destination.x = p_entity.GetPos().x;
    Destination.y = p_entity.GetPos().y;
    Destination.w = p_entity.GetCurrentFrame().w ;
    Destination.h = p_entity.GetCurrentFrame().h ;


    SDL_RenderCopy(renderer, p_entity.GetTex(), &O, &Destination);
}

void RenderWindow::Display()
{
    SDL_RenderPresent(renderer);
}


int RenderWindow::GetRefreshRate()
{
    int DisplayIndex = SDL_GetWindowDisplayIndex (window);

    SDL_DisplayMode mode;

    SDL_GetDisplayMode (DisplayIndex, 0, &mode);

    return mode.refresh_rate;
}
