#include"Attack Bomb.h"

Subject_List* Attack::al = new Attack_List();

Attack::Attack()
:next(NULL), damage(0)
{
	copy_counter = counter + life;
	if (map[position] == NULL || map[position] -> get_copy_counter() < copy_counter)
		map[position]= this;
		
	*al + this;
}

Attack::Attack(int new_damage, Feature new_display_feature, int new_life, int new_x, int new_y, Layer new_l)
:damage(new_damage), Subject(new_display_feature, new_life, new_x, new_y, new_l)
{
	copy_counter = counter + new_life;
	if (map[position] == NULL || map[position] -> get_copy_counter() < copy_counter)
		map[position]= this;
	*al + this;
}

Attack::Attack(int new_damage, Feature new_display_feature,  int new_life, Point p)
:damage(new_damage), Subject(new_display_feature, counter, p)
{
	copy_counter = counter + new_life;
	map[position] = this;
	*al + this;
}

Attack::Attack(const Attack& a)
:next(a.next), copy_counter(a.copy_counter), damage(a.damage), Subject(a)
{
	map[position] = this;
}

Attack::~Attack()
{
	if (map[position] != NULL)
	if (map[position] -> get_copy_counter() == copy_counter)
	{
		map[position] = NULL;
	}
}

		
void Attack::attack()
{
	switch(display_feature)
	{
		
		case none: cout << "no damage" << endl;break;
		case fire: cout << "fire damage:" << damage << endl;break;
		case hit: cout << "hit damage:" << damage << endl;break;
	}
}

int Attack::getdamage()
{
	return damage;
}

void Attack::cause_damage()
{
	bool flag = false;
	
	Subject* attack_target = map[position + cha];
	
	if (attack_target != NULL && damage != 0)
	{
		attack_target -> setlife( -damage);
		
		damage = 1;
		
		flag = true;
	}
	
	attack_target = map[position + obj];
	
	if (attack_target != NULL && damage != 0)
	{
		attack_target -> setlife( -damage);
		
		flag = true;
	}
	
	if (flag)
	{
		damage = 0;
	}
}

#ifdef PHONE_TEST
unsigned long long int Attack::get_copy_counter()
{
	return copy_counter;
}
		
#endif

#ifdef COMPUTER_TEST
unsigned long int Attack::get_copy_counter()
{
	return copy_counter;
}
#endif


/************link list************/

Attack_List::Attack_List()
{}

void Attack_List::clear()
{
	pre = cur = head;
	int test_counter = 0;
	if (head != NULL)
	do
	{
		
		if (cur -> get_copy_counter()  == Subject::counter)
		{
			if (cur == head)
			{
				head = cur -> next;
				
				delete cur;
			
				pre = cur = head;
			}
			else 
			{
				pre -> next = cur -> next;
				
				delete cur;
				
				cur = pre -> next;
			}
		}
		else
		{
			cur -> cause_damage();
			
			pre = cur;
			cur = cur -> next;
		}
	} while (cur != NULL);
}