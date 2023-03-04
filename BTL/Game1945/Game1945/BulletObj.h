#pragma once

#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H

#include "BaseObject.h"
#include "CommonFunction.h"


class BulletObj : public BaseObject
{
public:
	BulletObj();
	~BulletObj();

	enum BulletDir
	{
		DIR_RIGHT = 10,
		DIR_LEFT = 11,
		DIR_UP = 12,
		DIR_UP_LEFT = 13,
		DIR_UP_RIGHT = 14,
		DIR_DOWN = 15,
		DIR_DOWN_RIGHT = 16,
		DIR_DOWN_LEFT = 17,
	};

	void set_x_val(const int& xVal) { x_val = xVal; }
	void set_y_val(const int& yVal) { y_val = yVal; }
	int get_x_val() const { return x_val; }
	int get_y_val() const { return y_val; }

	void set_is_move(const bool& isMove) { is_move = isMove; }
	bool get_is_move() const { return is_move; }

	void HandleBulletMove(const int& x_border, const int& y_border);
	void set_bullet_dir(const unsigned int& bulletDir) { bullet_dir = bulletDir; }
	int get_bullet_dir() const { return bullet_dir; }

private:
	int x_val;
	int y_val;
	bool is_move;
	unsigned int bullet_dir;
};


#endif // ! BULLET_OBJECT_H

