#pragma once
#include"Object Bomb.h"


#ifndef CHARACTER_BOMB_H
#define CHARACTER_BOMB_H

using namespace std;

class Character_List;

class Character:public Subject
{
	protected:
		Direction direction;
		string name;
		ControlString control_panel;
	public:
		static Subject_List* cl;
		static int pocket;
		static int human_count;
		static int monster_count;
		int bomb;		
		
		Character();
		Character(Direction new_direction, const string& new_name, int new_bomb, Feature new_display_feature, const char* new_control_panel, int new_life, int new_x, int new_y, Layer new_l);
		Character(Direction new_direction, const string& new_name, int new_bomb, Feature new_display_feature, const char* new_control_panel, int new_life, Point p);
		Character(const Character& c);
		virtual ~Character();
		
		virtual void show();
		virtual void attack();
		void operator << (ControlString& command);
		void move(Direction move_direction);
		void setbomb();
		void auto_move();
		virtual char name_head();
		virtual string& get_name();
		
		friend ostream& operator << (ostream& out, Map& map);
		friend ostream& operator << (ostream& out, Character_List& cl);
		friend Direction operator >> (Point p1, const Subject_List& cl);
		friend Direction operator >> (Point & p1, const Point & p);
		friend class Character_List;
		friend class Object;
};


class Character_List:public Subject_List
{

	public:
		Character_List();
		
		//void operator +(Subject* new_head);
		virtual void operator << (ControlString& command);
		virtual void clear_all();
		virtual void exchange_control_panel();

		friend ostream& operator << (ostream& out, Character_List& cl);
		
};

//ostream& operator << (ostream& out, Character_List& cl);

#endif