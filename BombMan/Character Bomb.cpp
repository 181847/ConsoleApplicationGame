#include"Character Bomb.h"

Direction operator >> (Point p1, const Subject_List& cl)
{
	int steps = 0;
	Point p2;
	steps = 999999;
	
	for (Subject* cur = cl.head; cur != NULL; cur = cur -> next)
	{
		if (cur -> get_name() != "MONSTER")
		{
			if (p1 - (cur -> position) < steps)
			{
				p2 = cur -> position;
				steps = p1 - p2;
			}
		}
	}
	
	/*
	p2.show();
	
	getchar();
	*/
	
	return p1 >> p2;
}

Subject_List* Character::cl = new Character_List();
int Character::pocket = 0;
int Character::monster_count = 0;
int Character::human_count= 0;

Character::Character()
:direction(UP), name("unknow"), bomb(0)
{
	map[position] = this;
	*cl + this;
}

Character::Character(Direction new_direction, const string& new_name, int new_bomb, Feature new_display_feature, const char* new_control_panel, int new_life, int new_x, int new_y, Layer new_l)
:direction(new_direction), name(new_name), bomb(new_bomb), control_panel(new_control_panel), Subject(new_display_feature, new_life, new_x, new_y, new_l)
{
	if ( name == "MONSTER" )
	{
		monster_count ++;
	}
	else
	{
		human_count ++;
	}
	map[position] = this;
	*cl + this;
}

Character::Character(Direction new_direction, const string& new_name, int new_bomb, Feature new_display_feature, const char* new_control_panel, int new_life, Point p)
:direction(new_direction), name(new_name), bomb(new_bomb), control_panel(new_control_panel), Subject(new_display_feature, new_life, p)
{
	if ( name == "MONSTER" )
	{
		monster_count ++;
	}
	else
	{
		human_count ++;
	}
	map[position] = this;
	*cl + this;
}

Character::Character(const Character& c)
:direction(c.direction), name(c.name), bomb(c.bomb), control_panel(c.control_panel),  Subject(c)
{
	if ( name == "MONSTER" )
	{
		monster_count ++;
	}
	else
	{
		human_count ++;
	}
	
	map[position] = this;
	*cl + this;
}

Character::~Character()
{
	if ( name == "MONSTER" )
	{
		monster_count --;
	}
	else
	{
		human_count --;
	}
	
	map[position] = NULL;
}
		
void Character::show()
{
	cout << "Name:" << name << '\t';
	cout << "Life:" << life << '\t';
	cout << "Bomb:" << bomb << '\t';
}
void Character::attack()
{
	switch (display_feature)
	{
		case human: cout << "human:" << name << " attack" << endl;break;
		case monster: cout << "monster:" << name << " attack" << endl;break;
	}
}

void Character::operator << (ControlString& command)
{
	switch (display_feature)
	{
		case human:
					switch (control_panel[command])
					{
						case 0:move(UP);break;
						case 1:move(DOWN);break;
						case 2:move(LEFT);break;
						case 3:move(RIGHT);break;
						case 4:setbomb();
						
										break;
					}//end human case
					break;
		case monster:
					auto_move();
					break;
	}
	
}

void Character::move(Direction move_direction)
{
	Point new_position(position + move_direction);
	direction = move_direction;
	
	if (name == "MONSTER")//if 1 monster's movement
	{
		if (map[new_position] != NULL)
		{
			if (map[new_position] -> get_name() != "MONSTER")
				new Attack(1, hit, 1, new_position + atk);
			goto move_end;
		}
		
		if (map[new_position + obj] != NULL)
		{
			goto move_end;
		}
	}//end if 1
	else//else human's movement
	{
		if (map[new_position] != NULL)
		{
			life = map[new_position] -> life = (life + map[new_position] -> life) / 2;
			
			goto move_end;
		}
		
		if (map[new_position + obj] != NULL)//if 2
		{
		
			Object* temp_object_pointer = (Object*)(map[new_position + obj]);
		
			if (temp_object_pointer -> visible)//if 3
			{
				switch(temp_object_pointer -> display_feature)//switch
				{
					case treasure:	pocket += temp_object_pointer -> capacity;
												temp_object_pointer -> life = 0;
												break;
					case supply:	bomb += temp_object_pointer -> capacity;
												temp_object_pointer -> life = 0;
												break;
				}//end switch
			}//end if 3
			goto move_end;
		}//end if 2
	}//end else
	
	
	if ((map[new_position + gro] -> getfeature()) == space)
	{
		map[position] = NULL;
		
		position = new_position;
		
		map[new_position] = this;
	}
	
	move_end:;
}

void Character::setbomb()
{
	if (bomb > 0 && map[position + obj] == NULL && name != "MONSTER")
	{
		creat_new_object(4, 40, position + obj);
		bomb --;
	}
}


void Character::auto_move()
{
	if (counter % bomb == 0)// if 1
	{
		//move(position >> *cl);
		
		
		if (counter % 12 == 0)
		{
			move(rand_direction());
		}
		else
		{
			move(position >> *cl);
		}
		
	}// end if 1
}

char Character::name_head()
{
	return name[0];
}

string& Character::get_name()
{
	return name;
}

/****************link list***********/


Character_List::Character_List()
{}

void Character_List::operator << (ControlString& command)
{
	cur = head;
	
	while (cur != NULL)
	{
		*(Character*)cur << command;
		
		cur = cur -> next;
	}
}

void Character_List::clear_all()
{
	Subject_List::clear_all();
	
	Character:: pocket = 0;
}

ostream& operator << (ostream& out, Character_List& cl)
{
	cl.cur = cl.head;
	
	while (cl.cur != NULL)
	{
		if (1)//cl.cur -> getfeature() == human)
		{
			cl.cur -> show();
			((Character*)cl.cur) -> control_panel.show();
		}
		
		cl.cur = cl.cur -> next;
	}
	
	cout << "Treasure:" << Character::pocket << " human:" << Character::human_count << " monster:" << Character::monster_count <<  endl;

	return out;
}

Direction operator >> (Point & p1, const Point & p)
{
	int x_steps = p1.x - p.x, y_steps = p1.y - p.y;
	Direction move_direction;
	
	if (fabs( x_steps ) > fabs( y_steps))
	{
		if (x_steps < 0)
		{
			move_direction = RIGHT;
		}
		else
		{
			move_direction = LEFT;
		}
	}
	else
	{
		if (y_steps < 0)
		{
			move_direction = DOWN;
		}
		else
		{
			move_direction = UP;
		}
	}
	
	if ((Subject::map[p1 + cha + move_direction] != NULL ) && ((Character*)Subject::map[p1 + cha + move_direction]) -> name == "MONSTER" || Subject::map[p1 + obj + move_direction] != NULL || Subject::map[p1 + gro + move_direction] -> getfeature() != space)
	{
		if (fabs( x_steps ) <= fabs( y_steps))
		{
			
			if (x_steps < 0)
			{
				move_direction = RIGHT;
			}
			else
			{
				move_direction = LEFT;
			}
			
		}
		else
		{
			if (y_steps < 0)
			{
				move_direction = DOWN;
			}
			else
			{
				move_direction = UP;
			}
		}
	}
	
	return move_direction;
}

void Object::act()
{
	switch (display_feature)
	{
		case bomb:
				if ( copy_counter == 0 && visible)
				{
					copy_counter = life + counter;
				}
				break;
		case monster_maker:
				if (visible && counter % life == 0)
				{
					
					if (map[position + cha] == NULL && life > 0)
					{
						new Character(UP, "MONSTER", 5, monster, "tvfhg", 21, position + cha);
						capacity --;
						if (capacity == 0)
						life = 0;
					}
				}
				break;
		case none:
						if (visible)
						life = 0;
						break;
	}
}


void Character_List::exchange_control_panel()
{
	pre = cur = head;

	while (cur -> next != NULL)
	{
		while (cur -> getfeature() != human)
		{
			cur  = cur -> next;
			
			if (cur == NULL)
			{
				goto end;
			}
		}
		
		pre = cur -> next;
		
		while (pre -> getfeature() != human)
		{
			pre  = pre -> next;
			
			if (pre == NULL)
			{
				goto end;
			}
		}
		
		swap(((Character*)pre) -> control_panel, ((Character*)cur) -> control_panel);
		
		cur = pre;
	}
	
	end:;
}

int ControlString::get_control_input()
{
	clock_t start_time=clock();
	
	size = 0;
	
	while(clock() - start_time < 0.1 * CLOCKS_PER_SEC && size < capacity)
	{
		if (_kbhit())
		{
			buffer[size++] = _getch();

			if (buffer[size - 1] == '?')
			{
				Character::cl -> exchange_control_panel();
			}
		}
	}
	fflush(stdin);
	return size;
}