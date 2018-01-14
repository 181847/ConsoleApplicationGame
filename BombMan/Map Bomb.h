#pragma once
#include"Subject Bomb.h"

#ifndef MAP_BOMB_H
#define MAP_BOMB_H

class Map
{
	protected:
		Subject **Atk;
		Subject **Cha;
		Subject **Obj;
		Subject **Gro;
		
	public:
		int height, width;
		Map();
		Map(int new_height, int new_width);
		Map(const Map& m);
		~Map();
		
		void reset_size(int new_width, int new_height);
		Subject*& operator [](const Point p);
		
		friend ostream& operator << (ostream& out, Map& map);
};




#endif