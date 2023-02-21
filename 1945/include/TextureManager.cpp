#include "TextureManager.h"
#include "Engine.h"

using namespace std;

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(string id, string filename){

    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr){
        SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GameLoop()->GetRenderer(), surface);
    if(texture == nullptr){
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::Draw(string id, int x, int y, int width, int heigt, SDL_RendererFlip flip){
    SDL_Rect srcRect = {0, 0, width, heigt};
    SDL_Rect dstRect = {x, y, width, heigt};
    SDL_RenderCopyEx(Engine::GameLoop()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(string id, int x, int y, int width, int heigt, int row, int frame, SDL_RendererFlip flip){
    SDL_Rect srcRect = {x, y, width, heigt};
    SDL_Rect dstRect = {width, y, width, heigt};
    SDL_RenderCopyEx(Engine::GameLoop()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}


void TextureManager::CleanUp(string id){
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean(){
    map<string, SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);

    m_TextureMap.clear();

    SDL_Log("texture map cleaned!");
}
