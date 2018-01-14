#pragma once
#include"Subject_List Bomb.h"


#ifndef GROUND_BOMB_H
#define GROUND_BOMB_H

class Ground:public Subject
{
	protected:
		Ground *next;
		Feature display_feature;
	public:
		static Subject_List* gl;
	
		Ground();
		Ground(Feature new_display_feature, int new_life, int new_x, int new_y, Layer new_l);
		Ground(Feature new_display_feature, int new_life, Point p);
		Ground(const Ground& g);
		virtual ~Ground();
		
		virtual void show();
		
		friend ostream& operator << (ostream& out, Map& map);
};

class Ground_List:public Subject_List
{

	public:
		Ground_List();
		
		//void operator +(Subject* new_head);
		//void operator << (ControlString& command);
		
		//void clear_death();
		
		//friend ostream& operator << (ostream& out, Character_List& cl);
};


#endif