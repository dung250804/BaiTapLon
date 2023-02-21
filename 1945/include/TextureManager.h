#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include "SDL.h"
#include <map>
using namespace std;

class TextureManager
{
    public:
        static TextureManager* GameLoop(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();}

        bool Load(string id, string filename);
        void CleanUp(string id);
        void Clean();

        void Draw(string id, int x, int y, int width, int heigt, SDL_RendererFlip flip=SDL_FLIP_NONE);
        void DrawFrame(string id, int x, int y, int width, int heigt, int row, int frame, SDL_RendererFlip flip=SDL_FLIP_NONE);

    private:
        TextureManager(){}
        map < string, SDL_Texture* > m_TextureMap;
        static TextureManager* s_Instance;
};

#endif // TEXTUREMANAGER_H
