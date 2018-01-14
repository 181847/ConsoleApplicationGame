#pragma once
#include<iostream>
#include <string>
#include<stdlib.h>
#include<cmath>

using namespace std;

//#define PHONE_TEST
#define COMPUTER_TEST 1

#ifndef POINT_BOMB_H
#define POINT_BOMB_H
enum Direction{UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4};

Direction rand_direction();

Direction& operator += (Direction& d, int i);

enum Layer{atk = 1, cha = 2, obj = 3, gro = 4};
class Subject_List;

class Point
{
	protected:
		int x, y;
		Layer l;
	public:
		Point();
		Point(int , int , Layer );
		Point(const Point& p);
		
		void show();
		Layer getlayer();
		Point& operator += (Direction move_direction);
		Point operator + (Layer new_layer);
		
		Point operator + (Direction move_directionr);
		Point operator = (const Point& p);
		int operator - (const Point & p);
		friend Direction operator >> (Point & p1, const Point & p);
		
		friend Direction operator >> (Point p1, const Subject_List& cl);
		friend class Map;
};



#endif