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
