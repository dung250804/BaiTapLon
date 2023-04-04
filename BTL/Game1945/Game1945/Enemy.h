#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObj.h"

#define SWORD_ENEMY_FRAME 6
#define ENEMY_FRAME 11
#define GRAVITY_FALLS 0.8
#define MAX_GRAVITY 10
#define ENEMY_SPEED 3

class Enemy : public BaseObject
{
public:
	Enemy();
	~Enemy();

	enum Typemove 
	{
		STATIC_ENEMY = 0,
		MOVE_AREA = 1,
	};

	void set_x_val(const int& xVal) { x_val = xVal; }
	void set_y_val(const int& yVal) { y_val = yVal; }

	void set_x_pos(const int& xPos) { x_pos = xPos; }
	void set_y_pos(const int& yPos) { y_pos = yPos; }
	float get_x_pos() const { return x_pos; }
	float get_y_pos() const { return y_pos; }
	void SetMapXY(const int& mapX, const int& mapY) { map_x = mapX; map_y = mapY; }
	SDL_Rect GetRectFrame();

	void set_clips();

	bool LoadImg(std::string path, SDL_Renderer* screen);

	void show(SDL_Renderer* des);
	int get_width_frame() const { return width_frame; }
	int get_height_frame() const { return height_frame; }
	void EnemyMovement(Map& gMap);
	void CheckMapCollision(Map& gMap);
	void InitEnemy();

	void set_type_move(const int& typeMove) { type_move = typeMove; }
	void set_animation_pos(const int& pos_a, const int& pos_b) { animation_a = pos_a; animation_b = pos_b; }
	void set_input_left(const int& inputLeft) { input_type.left = inputLeft; }
	void ImpMoveType(SDL_Renderer* screen);


	std::vector<BulletObj*> get_bullet_list() const { return bullet_list; }
	void set_bullet_list(const std::vector<BulletObj*>& bl_list) { bullet_list = bl_list; }

	void InitBullet(BulletObj* p_bullet, SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
	void RemoveBullet(const int& index);

private:
	int map_x;
	int map_y;

	float x_pos;
	float y_pos;

	float x_val;
	float y_val;

	bool on_ground;
	int spawn_time;
	SDL_Rect frame_clip[ENEMY_FRAME];
	int width_frame;
	int height_frame;
	int frame;

	int type_move;
	int animation_a;
	int animation_b;
	Input input_type;

	std::vector <BulletObj*> bullet_list;
};


#endif // !ENEMY_H
