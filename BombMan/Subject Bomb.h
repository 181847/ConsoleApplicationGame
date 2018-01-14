#pragma once
#include"Point Bomb.h"
#include"Control Bomb.h"

enum Feature{none = 0, fire = 1, hit = 2, space = 3, wall = 4, monster = 5, human = 6, bomb = 7, supply = 8, treasure = 9, monster_maker = 10};

Feature transfer(const string& f);

class Map;

class Subject
{
	public:
		Point position;
		int life;
		Feature display_feature;
		Subject* next;
	public:
		static Map map;
		
#ifdef PHONE_TEST
		static unsigned long long  int counter;
#endif

#ifdef COMPUTER_TEST
		static unsigned long int counter;
#endif
		Subject();
		Subject(Feature , int , Point );
		Subject(Feature , int , int , int , Layer );
		Subject(const Subject& s);
		virtual ~Subject();
		
		virtual Feature getfeature();
		
		virtual void show();
		virtual void attack();
		virtual void cause_damage();
		virtual void setlife(int new_life);
		virtual bool getvisible();
		virtual void act();
		virtual char name_head();
		virtual string& get_name();
#ifdef PHONE_TEST
		virtual unsigned long long int get_copy_counter();
#endif

#ifdef COMPUTER_TEST
		virtual unsigned long int get_copy_counter();
#endif
		
		
		friend class Subject_List;
		friend class Attack;
		friend class Object;
};
