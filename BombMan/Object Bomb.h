#pragma once
#include"Attack Bomb.h"
#ifndef OBJECT_BOMB_H
#define OBJECT_BOMB_H


class Object:public Subject
{
	protected:
		Object *next;
		int capacity;
#ifdef PHONE_TEST
		unsigned long long int copy_counter;
#endif

#ifdef COMPUTER_TEST
		unsigned long int copy_counter;
#endif
	public:
		bool visible;
		static Subject_List* ol;
		
		Object();
		Object(int new_capacity, bool new_visible, Feature new_display_feature, int new_life, int new_x, int new_y, Layer new_l);
		Object(int new_capacity, bool new_visible, Feature new_display_feature, int new_life, Point p);
		Object(const Object& o);
		virtual ~Object();
		
		virtual void show();
		virtual bool getvisible();
		virtual void setlife(int new_life);
		virtual void act();
#ifdef PHONE_TEST
		virtual unsigned long long int get_copy_counter();
#endif

#ifdef COMPUTER_TEST
		virtual unsigned long int get_copy_counter();
#endif
		
		friend ostream& operator << (ostream& out, Map& map);
		friend class Character;
		friend class Object_List;
};

void creat_new_object(int new_capacity, int new_life, Point p);


class Object_List:public Subject_List
{

	public:
		Object_List();
		virtual void clear();
		
		//void operator +(Subject* new_head);
		//void operator << (ControlString& command);
		
		//void clear_death();
		
		//friend ostream& operator << (ostream& out, Character_List& cl);
};




#endif