#pragma once
#include"Ground Bomb.h"

#ifndef ATTACK_BOMB_H
#define ATTACK_BOMB_H


class Attack:public Subject
{
	protected:
		Attack *next;
		int damage;

#ifdef PHONE_TEST
		unsigned long long int copy_counter;
#endif

#ifdef COMPUTER_TEST
		unsigned long int copy_counter;
#endif
		

	public:
		static Subject_List* al;
	
		Attack();
		Attack(int new_damage, Feature new_display_feature, int new_life, int new_x, int new_y, Layer new_l);
		Attack(int new_damage, Feature new_display_feature, int new_life, Point p);
		Attack(const Attack& a);
		virtual ~Attack();
		
		virtual void cause_damage();
		
		virtual void attack();
		virtual int getdamage();
#ifdef PHONE_TEST
		virtual unsigned long long int get_copy_counter();
#endif

#ifdef COMPUTER_TEST
		virtual unsigned long int get_copy_counter();
#endif

		
		friend ostream& operator << (ostream& out, Map& map);
		friend class Attack_List;
};

class Attack_List:public Subject_List
{

	public:
		Attack_List();
		
		virtual void clear();
		
		//void operator +(Subject* new_head);
		//void operator << (ControlString& command);
		
		//void clear_death();
		
		//friend ostream& operator << (ostream& out, Character_List& cl);
};

#endif