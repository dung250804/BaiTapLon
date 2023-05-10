#pragma once
#include "CommonFunction.h"
#include "BaseObject.h"

#define LAYER_1_SPEED 10
#define LAYER_2_SPEED 8
#define LAYER_3_SPEED 6
#define LAYER_4_SPEED 4
#define LAYER_5_SPEED 2

using namespace std;

#pragma once
class Background : public BaseObject
{
public:
    static const int screenW = 1280;
    static const int screenH = 640;

    Background();
    ~Background();

    void loadBG(SDL_Renderer* renderer);

    void HandleInput(SDL_Event events, SDL_Renderer* screen);

    void renderLayer1(SDL_Renderer* renderer);
    void renderLayer2(SDL_Renderer* renderer);
    void renderLayer3(SDL_Renderer* renderer);
    void renderLayer4(SDL_Renderer* renderer);
    void renderLayer5(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);

    SDL_Rect Layer1Pos, Layer2Pos, Layer3Pos, Layer4Pos, Layer5Pos;

    SDL_Texture* background, * Layer1, * Layer2, * Layer3, * Layer4, * Layer5;

private:
    Uint32 layerTime;

    Input input_type;

};