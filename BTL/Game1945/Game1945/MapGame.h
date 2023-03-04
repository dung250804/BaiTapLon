#pragma once

#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunction.h"
#include "BaseObject.h"

#define MAX_TILES 20 

class TileMap : public BaseObject
{
public:
	TileMap() { ; }
	~TileMap() { ; }
};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }
	void LoadMap(char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map GetMap() const { return game_map; };
	void SetMap(Map& map_data) { game_map = map_data; };

private:
	Map game_map;
	TileMap tile_map[MAX_TILES];
};


#endif