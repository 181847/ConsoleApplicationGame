#include"File Bomb.h"
#include<fstream>


int creat_object(const char * file_name, Layer l, int num)
{
	int sum_treasure = 0;
	
	int capacity, visible, life, x, y;
	char control[7];
	string display_feature, name;
	
	ifstream save(file_name);
	if (! save)
	{
		while (1)
		{
			cout << "open file error!" << endl;
			getchar();
		}
	}
	
	if (num == 0)
	{
		save >> num;
	}
	else
	{
		save >> x;
	}
	
	switch (l)
	{
		case obj:
						while (num -- > 0)
						{
							save >> capacity >> visible >> display_feature >> life >> x >> y;
							new Object(capacity, visible == 1 ? true : false, transfer(display_feature),  life, x, y, l);
							if (display_feature[0] == 't')
							{
								sum_treasure ++;
							}
						}
						break;
						
		case cha:
						while (num -- > 0)
						{
							save >> name >> capacity >> display_feature;
							save.get();
							save.get(control, 6);
							save >> life >> x >> y;
							new Character(UP, name, capacity, transfer(display_feature), control, life, x, y, l);
						}
	}//end switch
	
	
	save.close();
	
	return sum_treasure;
}





#ifdef COMPUTER_TEST
#include<windows.h>


void goto_xy(int x, int y)
{
	HANDLE hout;
	COORD coord;

	coord.X = x;
	coord.Y = y;

	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout,coord);
}


#endif