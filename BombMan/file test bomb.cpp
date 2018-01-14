#include"File Bomb.h"


#ifdef PHONE_TEST
#define CLR clrscr()
#endif

#ifdef COMPUTER_TEST
//#define CLR system("cls")
#define CLR goto_xy(0, 0)
#endif

const int gNumEmptyLine = 9;

void printEmptyLines(int numEmpty)
{
	while (numEmpty-- > 0)
	{
		cout <<  "                               " << endl;
	}
}



using namespace std;

int main()
{
	//(Subject::map).reset_size(30, 50);

	int level = 1, sum_treasure = 0, player = 0;
	ControlString control_input;
	
	cout << "Intput the number of players: ";
	cin >> player;

	
	for (int i = 0; i < Subject::map.height; i ++)
		for (int j = 0; j < Subject::map.width; j ++)
			if (i == 0 || i == Subject::map.height -1 || j == 0 || j == Subject::map.width - 1)
				new Ground(wall, 99, j, i, gro);
			else if (i % 2 == 0 && j % 2 == 0)
				new Ground(wall, 99, j, i, gro);
			else
				new Ground(space, 99, j, i, gro);
				
				
	game_start:
	
	//cout << "********" << "creat object" << "*********" << endl;
	creat_object("character data.txt", cha, player);
	
	//cout << "********" << "1" << "*********" << endl;
	
	switch (level)
	{
		case 1:sum_treasure = creat_object("object data.txt", obj);break;
		case 2:sum_treasure = creat_object("object data 2.txt", obj);break;
	}
	
	//cout << "********" << "2" << "*********" << endl;
	
	
	
	while (Subject::counter ++ <= 11000)
	{
		
		//cout << "********" << "3" << "*********" << endl;
		
		control_input.get_control_input();
		
		//cout << "********" << "4" << "*********" << endl;
		
		*(Character::cl) << control_input;
		
		//cout << "********" << "5" << "*********" << endl;
		
		Character::cl -> clear();
		
		//cout << "********" << "6" << "*********" << endl;
		
		Object::ol -> clear();
		
		//cout << "********" << "7" << "*********" << endl;
		
		Attack::al -> clear();
		
		//cout << "********" << "8" << "*********" << endl;
		
		CLR;
		
		//cout << "********" << "9" << "*********" << endl;
		
		cout << Subject::map;
		
		//cout << "********" << "10" << "*********" << endl;
		
		cout << *(Character_List*)(Character::cl);
		
		//cout << "********" << "11" << "*********" << endl;
		
		//cout << Subject::counter << endl;
		
		//cout << "********" << "12" << "*********" << endl;

		printEmptyLines(gNumEmptyLine);
		
		if (Character::human_count == 0)
		{
			Object::ol -> clear_all();
			
			Attack::al -> clear_all();
		
			Character::cl -> clear_all();
			
			level = 1;
			
			goto game_start;
		}
		else if (Character:: pocket == sum_treasure && Character::monster_count == 0)
		{
			level ++;
			
			if (level > 2)
			{
				level = 1;
			}
			
			Object::ol -> clear_all();
		
			Character::cl -> clear_all();
			
			//cout << "********" << "clear complete" << "*********" << endl;

			goto game_start;
		}
	}

	return 0;
}