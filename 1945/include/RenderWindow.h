#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#pragma once;
#include<SDL.h>
#include<SDL_image.h>

class RenderWindow
{
    public:
        RenderWindow(const char* p_title, int p_width, int p_height);       //p_ : tham so', thong so' (parameter)
        void CleanUp();
        SDL_Texture* LoadTexture(const char* p_filePath);

    protected:

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};

#endif // RENDERWINDOW_H
