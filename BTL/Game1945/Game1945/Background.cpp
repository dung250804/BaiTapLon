#include "background.h"

using namespace std;

Background::Background()
{
    layerTime = SDL_GetTicks();
    input_type.left = 0;
    input_type.right = 0;
}

Background :: ~Background()
{
}

void Background::loadBG(SDL_Renderer* renderer)
{
    background = loadTexture("background/bg.png", renderer);
    Layer1 = loadTexture("background/bg1.png", renderer);
    Layer2 = loadTexture("background/bg2.png", renderer);
    Layer3 = loadTexture("background/bg3.png", renderer);
    Layer4 = loadTexture("background/bg4.png", renderer);
    Layer5 = loadTexture("background/bg5.png", renderer);

    SDL_QueryTexture(Layer1, NULL, NULL, &Layer1Pos.w, NULL);
    Layer1Pos.h = 640;
    Layer1Pos.x = 0;
    Layer1Pos.y = 0;

    SDL_QueryTexture(Layer2, NULL, NULL, &Layer2Pos.w, NULL);
    Layer2Pos.h = 640;
    Layer2Pos.x = 0;
    Layer2Pos.y = 0;

    SDL_QueryTexture(Layer3, NULL, NULL, &Layer3Pos.w, NULL);
    Layer3Pos.h = 640;
    Layer3Pos.x = 0;
    Layer3Pos.y = 0;

    SDL_QueryTexture(Layer4, NULL, NULL, &Layer4Pos.w, NULL);
    Layer4Pos.h = 640;
    Layer4Pos.x = 0;
    Layer4Pos.y = 0;

    SDL_QueryTexture(Layer5, NULL, NULL, &Layer5Pos.w, NULL);
    Layer5Pos.h = 640;
    Layer5Pos.x = 0;
    Layer5Pos.y = 0;

}

void Background::HandleInput(SDL_Event events, SDL_Renderer* screen)
{
    if (events.type == SDL_KEYDOWN)
    {
        if (events.key.keysym.sym == SDLK_d)
        {
            input_type.right = 1;
            input_type.left = 0;
        }
        else if (events.key.keysym.sym == SDLK_a)
        {
            input_type.right = 0;
            input_type.left = 1;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        if (events.key.keysym.sym == SDLK_d)
        {
            input_type.right = 0;
        }
        else if (events.key.keysym.sym == SDLK_a)
        {
            input_type.left = 0;
        }
    }
}

void Background::renderLayer1(SDL_Renderer* renderer)
{
    SDL_Rect Layer1Pos1, Layer1Pos2;

    Layer1Pos1.w = Layer1Pos2.w = screenW;
    Layer1Pos1.h = Layer1Pos2.h = Layer1Pos.h;
    Layer1Pos2.x = Layer1Pos.x;
    Layer1Pos1.x = Layer1Pos2.x - screenW;
    Layer1Pos1.y = Layer1Pos2.y = Layer1Pos.y;

    SDL_RenderCopy(renderer, Layer1, NULL, &Layer1Pos1);
    SDL_RenderCopy(renderer, Layer1, NULL, &Layer1Pos2);

    if (input_type.left == 1)
    {
        Layer1Pos.x += LAYER_1_SPEED;
    }
    else if (input_type.right == 1)
    {
        Layer1Pos.x -= LAYER_1_SPEED;
    }

    if (Layer1Pos.x > screenW)
    {
        Layer1Pos.x = 0;
    }
    if (Layer1Pos.x < 0)
    {
        Layer1Pos.x = screenW;
    }
}

void Background::renderLayer2(SDL_Renderer* renderer)
{
    SDL_Rect Layer2Pos1, Layer2Pos2;

    Layer2Pos1.w = Layer2Pos2.w = screenW;
    Layer2Pos1.h = Layer2Pos2.h = Layer2Pos.h;
    Layer2Pos2.x = Layer2Pos.x;
    Layer2Pos1.x = Layer2Pos2.x - screenW;
    Layer2Pos1.y = Layer2Pos2.y = Layer2Pos.y;

    SDL_RenderCopy(renderer, Layer2, NULL, &Layer2Pos1);
    SDL_RenderCopy(renderer, Layer2, NULL, &Layer2Pos2);

    if (input_type.left == 1)
    {
        Layer2Pos.x += LAYER_2_SPEED;
    }
    else if (input_type.right == 1)
    {
        Layer2Pos.x -= LAYER_2_SPEED;
    }

    if (Layer2Pos.x > screenW)
    {
        Layer2Pos.x = 0;
    }
    if (Layer2Pos.x < 0)
    {
        Layer2Pos.x = screenW;
    }
}

void Background::renderLayer3(SDL_Renderer* renderer)
{
    SDL_Rect Layer3Pos1, Layer3Pos2;

    Layer3Pos1.w = Layer3Pos2.w = screenW;
    Layer3Pos1.h = Layer3Pos2.h = Layer3Pos.h;
    Layer3Pos2.x = Layer3Pos.x;
    Layer3Pos1.x = Layer3Pos2.x - screenW;
    Layer3Pos1.y = Layer3Pos2.y = Layer3Pos.y;

    SDL_RenderCopy(renderer, Layer3, NULL, &Layer3Pos1);
    SDL_RenderCopy(renderer, Layer3, NULL, &Layer3Pos2);

    if (input_type.left == 1)
    {
        Layer3Pos.x += LAYER_3_SPEED;
    }
    else if (input_type.right == 1)
    {
        Layer3Pos.x -= LAYER_3_SPEED;
    }

    if (Layer3Pos.x > screenW)
    {
        Layer3Pos.x = 0;
    }
    if (Layer3Pos.x < 0)
    {
        Layer3Pos.x = screenW;
    }
}

void Background::renderLayer4(SDL_Renderer* renderer)
{
    SDL_Rect Layer4Pos1, Layer4Pos2;

    Layer4Pos1.w = Layer4Pos2.w = screenW;
    Layer4Pos1.h = Layer4Pos2.h = Layer4Pos.h;
    Layer4Pos2.x = Layer4Pos.x;
    Layer4Pos1.x = Layer4Pos2.x - screenW;
    Layer4Pos1.y = Layer4Pos2.y = Layer4Pos.y;

    SDL_RenderCopy(renderer, Layer4, NULL, &Layer4Pos1);
    SDL_RenderCopy(renderer, Layer4, NULL, &Layer4Pos2);

    if (input_type.left == 1)
    {
        Layer4Pos.x += LAYER_4_SPEED;
    }
    else if (input_type.right == 1)
    {
        Layer4Pos.x -= LAYER_4_SPEED;
    }

    if (Layer4Pos.x > screenW)
    {
        Layer4Pos.x = 0;
    }
    if (Layer4Pos.x < 0)
    {
        Layer4Pos.x = screenW;
    }
}

void Background::renderLayer5(SDL_Renderer* renderer)
{
    SDL_Rect Layer5Pos1, Layer5Pos2;

    Layer5Pos1.w = Layer5Pos2.w = screenW;
    Layer5Pos1.h = Layer5Pos2.h = Layer5Pos.h;
    Layer5Pos2.x = Layer5Pos.x;
    Layer5Pos1.x = Layer5Pos2.x - screenW;
    Layer5Pos1.y = Layer5Pos2.y = Layer5Pos.y;

    SDL_RenderCopy(renderer, Layer5, NULL, &Layer5Pos1);
    SDL_RenderCopy(renderer, Layer5, NULL, &Layer5Pos2);

    if (input_type.left == 1)
    {
        Layer5Pos.x += LAYER_5_SPEED;
    }
    else if (input_type.right == 1)
    {
        Layer5Pos.x -= LAYER_5_SPEED;
    }
    
    if (Layer5Pos.x > screenW)
    {
        Layer5Pos.x = 0;
    }
    if (Layer5Pos.x < 0)
    {
        Layer5Pos.x = screenW;
    }
}


void Background::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, background, NULL, NULL);
    renderLayer5(renderer);
    renderLayer4(renderer);
    renderLayer3(renderer);
    renderLayer2(renderer);
    renderLayer1(renderer);
    //SDL_RenderCopy(renderer, stage, NULL, &Layer2Pos);
    //SDL_RenderCopy(renderer, ground, NULL, &Layer1Pos);
}