#include "stdafx.h"
#include"Character Bomb.h"
#include "File Bomb.h"

#ifdef PHONE_TEST
#define CLR clrscr()
#elif COMPUTER_TEST
#define CLR goto_xy(0, 0)
//#define CLR system("cls")
#endif
using namespace std;



int main()
{
	cout << "start game" << endl;
	
	ControlString control_input;
	
	Point p1(1, 2, cha),
	p2(5, 6, gro),
	p3(7, 8, atk),
	p4(9, 10, obj),
	p5(11, 12, obj),
	p6(13, 14, obj),
	p7(15, 6, obj),
	p8(17, 8, gro),
	p9(19, 10, cha);
	
	
	cout << "start creat object" << endl;
	
	
	new Character(UP,  "Tomclancy", 90, human, "wsad ", 17, p1);
	new Character(UP,  "Tom", 54, human, "omjlk", 70, p9);
	new Character(UP,  "Sam", 54, human, "28465", 70, 3, 3, cha);
	new Character(UP, "MONSTER", 5, monster, "tvfhg", 21, 3, 4, cha);
	new Character(UP, "MONSTER", 5, monster, "tvfhg", 21, 13, 5, cha);
	new Character(UP, "MONSTER", 5, monster, "tvfhg", 21, 3, 6, cha);
	
	new Object(5, true, transfer("bomb"), 40, 9, 10, obj);
	new Object(5, true, bomb, 40, 8, 11, obj);
	new Object(5, true, bomb, 40, 9, 12, obj);
	
	new Object(4, false, supply, 99, p5);
	new Object(1, false, treasure, 99, p6);
	new Object(20, false, monster_maker, 10, p7);
	new Object(20, false, none, 10, 17, 6, obj);
	
	

	
	for (int i = 0; i < Subject::map.height; i ++)
		for (int j = 0; j < Subject::map.width; j ++)
			if (i == 0 || i == Subject::map.height -1 || j == 0 || j == Subject::map.width - 1)
				new Ground(wall, 99, j, i, gro);
			else if (i % 2 == 0 && j % 2 == 0)
				new Ground(wall, 99, j, i, gro);
			else
				new Ground(space, 99, j, i, gro);
				
		cout << "end creat object" << endl;
	
	
	
	
	
	while (Subject::counter ++ <= 11000)
	{
		
		control_input.get_control_input();
		
		
		
		*(Character::cl) << control_input;
		
		Character::cl -> clear();
		
		Object::ol -> clear();
		
		Attack::al -> clear();
		
		CLR;
		
		
		cout << "output" << Subject::map;
		
		cout << *(Character_List*)(Character::cl);
		
		cout << Subject::counter << endl;
		
		/*
		#ifdef PHONE_TEST
		usleep(289999);
		#elif COMPUTER_TEST
		Sleep(1);
		#endif
		*/
	}
	
	
}