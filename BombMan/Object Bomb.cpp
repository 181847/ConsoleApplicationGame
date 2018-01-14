#include"Object Bomb.h"

Subject_List* Object::ol = new Object_List;

Object::Object()
:next(NULL), copy_counter(0), capacity(0), visible(true)
{
	map[position] = this;
	*ol + this;
}

Object::Object(int new_capacity, bool new_visible, Feature new_display_feature, int new_life, int new_x, int new_y, Layer new_l)
:next(NULL), copy_counter(0), capacity(new_capacity), visible(new_visible), Subject(new_display_feature, new_life, new_x, new_y, new_l)
{
	switch (display_feature)
	{
		case bomb: if (visible) copy_counter = counter + new_life + 1;break;
	}
	map[position] = this;
	*ol + this;
}

Object::Object(int new_capacity, bool new_visible, Feature new_display_feature, int new_life, Point p)
:next(NULL), copy_counter(0), capacity(new_capacity), visible(new_visible), Subject(new_display_feature, new_life, p)
{
	switch (display_feature)
	{
		case bomb: if (visible) copy_counter = counter + new_life + 1;break;
	}
	map[position] = this;
	*ol + this;
}

Object::Object(const Object& o)
:next(o.next), copy_counter(o.copy_counter), capacity(o.capacity), visible(o.visible), Subject(o)
{
	map[position] = this;
	*ol + this;
}

Object::~Object()
{
	if (visible && display_feature == bomb)//if 1
	{
		Point moving_point(position + atk);
		
		new Attack(20, fire, capacity + 1, moving_point);
		
		for (Direction moving_direction = UP; ; moving_direction += 1)//for 1
		{
			moving_point = position + moving_direction + atk;
			
			
			for ( int i = 0; i < capacity; i++, moving_point += moving_direction)//for 2
			{
				if (map[moving_point + gro] -> display_feature == space )//&& (map[moving_point + obj] == NULL || map[moving_point + obj] -> getvisible()))
				{
					new Attack(8, fire, capacity - i, moving_point);
				}
				else
				{
					break;
				}
			}//endfor 2
			
			if (moving_direction == RIGHT)
				break;
		}//endfor 1
	}//endif 1
	map[position] = NULL;
	
	
}

void Object::show()
{
	switch(display_feature)
	{
		case bomb:
		{
			cout << "bomb:" << life << " left to boom!!" << endl;
		}break;
		
		case supply:
		{
			cout << "there are " << capacity << " bombs to supply." << endl;
		}break;
		
		case treasure:
		{
			cout << "there is a treasure." << endl;
		}break;
		
		case monster_maker:
		{
			cout << capacity << " monsters left in here." << endl;
		}break;
	}
}

bool Object::getvisible()
{
	return visible;
}

void Object::setlife(int new_life)
{
	if (visible)
	{
		if (display_feature == bomb)
		{
			copy_counter = counter + 1;
		}
	}
	else
	{
		visible = true;
		
		if (display_feature == none)
		{
			life = 0;
		}
	}
}


void creat_new_object(int new_capacity, int new_life, Point p)
{
	new Object(new_capacity, true, bomb, new_life, p);
}

#ifdef PHONE_TEST
unsigned long long int Object::get_copy_counter()
{
	return copy_counter;
}
		
#endif

#ifdef COMPUTER_TEST
unsigned long int Object::get_copy_counter()
{
	return copy_counter;
}
#endif



/************link list************/

Object_List::Object_List()
{}

void Object_List::clear()
{
	pre = cur = head;
	int test_counter = 0;
	if (head != NULL)
	do
	{
		cur -> act();
		
		if (cur -> get_copy_counter() == Subject::counter && cur -> display_feature == bomb || cur -> life == 0)
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
			pre = cur;
			cur = cur -> next;
		}
	} while (cur != NULL);
}