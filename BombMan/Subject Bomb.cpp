#include"Subject Bomb.h"


#ifdef PHONE_TEST
unsigned long long int Subject::counter = 0;
#endif

#ifdef COMPUTER_TEST
unsigned long  int Subject::counter = 0;
#endif

Feature transfer(const string& f)
{
	if (f.size() > 9)
	return monster_maker;
	
	switch (f[0])
	{
		case 'n': return none;
		case 'f': return fire;
		case 't': return treasure;
		case 'w': return wall;
		case 'b': return bomb;
		case 'h':
						switch (f[1])
						{
							case 'i': return hit;
							case 'u': return human;
						}
		case 's':
						switch (f[1])
						{
							case 'p': return space;
							case 'u': return supply;
						}
		case 'm':
						return monster;
		default: return none;
	}
}


Subject::Subject()
:next(NULL), life(0), display_feature(none)
{}

Subject::Subject(Feature new_display_feature, int new_life, Point p)
:next(NULL), display_feature(new_display_feature), life(new_life),position(p)
{}
Subject::Subject(Feature new_display_feature, int new_life, int new_x, int new_y, Layer new_l)
:next(NULL), display_feature(new_display_feature), life(new_life),position(new_x, new_y, new_l)
{}

Subject::Subject(const Subject& s)
:next(NULL), display_feature(s.display_feature), life(s.life),position(s.position)
{}

Subject::~Subject()
{
	
}

		
void Subject::show()
{
	switch(display_feature)
	{
		case none: break;
		case fire: cout << "fire "; break;
		case hit: cout << "hit "; break;
		case space: cout << "space "; break;
		case wall: cout << "wall "; break;
		case monster: cout << "monster "; break;
		case human: cout << "human "; break;
	}
	
	cout << "life = " << life << "   ";
	position.show();
}

void Subject::attack()
{
	cout << "subject attack" << endl;
}




void Subject::cause_damage()
{}

Feature Subject::getfeature()
{
	return display_feature;
}

void Subject::setlife(int new_life)
{
	if (new_life < 0)
	{
		life += new_life;
	}
	else
		life = new_life;
}

bool Subject::getvisible()
{
	return true;
}

void Subject::act()
{
	
}

char Subject::name_head()
{
	return 's';
}

#ifdef PHONE_TEST
unsigned long long int Subject::get_copy_counter()
{
	return 0;
}
		
#endif

#ifdef COMPUTER_TEST
unsigned long int Subject::get_copy_counter()
{
	return 0;
}
#endif

string& Subject::get_name()
{
	return *(new string);
}



//#endif