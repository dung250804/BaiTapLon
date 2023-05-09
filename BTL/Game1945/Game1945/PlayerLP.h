#pragma once

#ifndef PLAYER_LP_H_
#define PLAYER_LP_H_

#include "CommonFunction.h"
#include "BaseObject.h"

class PlayerLP : public BaseObject
{
public:
	PlayerLP();
	~PlayerLP();

	void SetNum(const int& num) { number_ = num; }
	void AddPos(const int& xPos);
	void Show(SDL_Renderer* screen);
	void Init(SDL_Renderer* screen);

	void Increase();
	void Decrease();

private:
	int number_;
	std::vector<int> pos_list_;

};



#endif // !PLAYER_LP_H
