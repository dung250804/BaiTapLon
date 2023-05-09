#include "PlayerLP.h"

PlayerLP::PlayerLP()
{
	number_ = 0;

}

PlayerLP::~PlayerLP()
{

}
void PlayerLP::AddPos(const int& xPos)
{
	pos_list_.push_back(xPos);
}

void PlayerLP::Init(SDL_Renderer* screen)
{
    LoadImg("Gfx//LifePoint.png", screen); 
    number_ = MAX_LIFE_POINT;
    if (pos_list_.size() > 0)
    {
        pos_list_.clear();

    }
    AddPos(140);
    AddPos(190);
    AddPos(240);
}

void PlayerLP::Show(SDL_Renderer* screen)
{
    for (int i = 0; i < pos_list_.size(); i++)
    {
        rect.x = pos_list_.at(i); 
        rect.y = 15; 
        Render(screen);  
    }
}

void PlayerLP::Decrease()
{
    number_--;
    pos_list_.pop_back();
}

//void PlayerLP::Increase()
