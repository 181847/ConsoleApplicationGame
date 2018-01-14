#include"Map Bomb.h"
const int Width = 30;
const int Height = 15;

Map::Map()
{
	height = 30;
	width = 30;

#ifdef COMPUTER_TEST
	Atk = new Subject* [height * width];
	Cha = new Subject* [height * width];
	Obj = new Subject* [height * width];
	Gro = new Subject* [height * width];
#endif

#ifdef PHONE_TEST
	Atk = new Subject* [Width * Height];
	Cha = new Subject* [Width * Height];
	Obj = new Subject* [Width * Height];
	Gro = new Subject* [Width * Height];
#endif
	
	for (int i = 0; i < height * width; i++)
	{
		Atk[i] = Cha[i] = Obj[i] = Gro[i] = NULL;
	}
}

Map::Map(int new_width, int new_height)
{
	cout << "creat map" << endl;

#ifdef COMPUTER_TEST
	height = new_height;
	width = new_width;
	
	Atk = new Subject* [height * width];
	Cha = new Subject* [height * width];
	Obj = new Subject* [height * width];
	Gro = new Subject* [height * width];
#endif


#ifdef PHONE_TEST
	height = Height;
	width = Width;
	
	Atk = new Subject* [Width * Height];
	Cha = new Subject* [Width * Height];
	Obj = new Subject* [Width * Height];
	Gro = new Subject* [Width * Height];
#endif
	
	for (int i = 0; i < height * width; i++)
	{
		Atk[i] = Cha[i] = Obj[i] = Gro[i] = NULL;
	}
}


Map::Map(const Map& m)
{
#ifdef COMPUTER_TEST
	height = m.height;
	width = m.width;
	
	Atk = new Subject* [height * width];
	Cha = new Subject* [height * width];
	Obj = new Subject* [height * width];
	Gro = new Subject* [height * width];
	

	for (int i = 0; i < height * width; i++)
		Atk[i] = m.Atk[i];
	for (int i = 0; i < height * width; i++)
		Cha[i] = m.Cha[i];
	for (int i = 0; i < height * width; i++)
		Obj[i] = m.Obj[i];
	for (int i = 0; i < height * width; i++)
		Gro[i] = m.Gro[i];
#endif

#ifdef PHONE_TEST
	height = Height;
	width = Width;
	
	Atk = new Subject* [Width * Height];
	Cha = new Subject* [Width * Height];
	Obj = new Subject* [Width * Height];
	Gro = new Subject* [Width * Height];

	for (int i = 0; i < height * width; i++)
		Atk[i] = m.Atk[i];
	for (int i = 0; i < height * width; i++)
		Cha[i] = m.Cha[i];
	for (int i = 0; i < height * width; i++)
		Obj[i] = m.Obj[i];
	for (int i = 0; i < height * width; i++)
		Gro[i] = m.Gro[i];

#endif
}

Map:: ~Map()
{
	delete [] Atk;
	delete [] Cha;
	delete [] Obj;	
	delete [] Gro;
}

void Map::reset_size(int new_width, int new_height)
{
	if (new_width * new_height != width * height)// if 1
	{
		delete [] Atk;
		delete [] Cha;
		delete [] Obj;
		delete [] Gro;
		
		
		#ifdef COMPUTER_TEST
		height = new_height;
		width = new_width;
		
		Atk = new Subject* [height * width];
		Cha = new Subject* [height * width];
		Obj = new Subject* [height * width];
		Gro = new Subject* [height * width];
		#endif


		#ifdef PHONE_TEST
		height = Height;
		width = Width;
		
		Atk = new Subject* [Width * Height];
		Cha = new Subject* [Width * Height];
		Obj = new Subject* [Width * Height];
		Gro = new Subject* [Width * Height];
		#endif
	
		for (int i = 0; i < height * width; i++)
		{
			Atk[i] = Cha[i] = Obj[i] = Gro[i] = NULL;
		}
	}//end if 1
	else
	{
		width = new_width;
		height = new_height;
	}
}


Subject*& Map::operator [](const Point p)
{
	if (p.x < width && p.y <   height)
	switch(p.l)
	{
		case atk:return Atk[p.y * width + p.x];
		case obj:return Obj[p.y * width + p.x];
		case cha:return Cha[p.y * width + p.x];
		case gro:return Gro[p.y * width + p.x];
	}
	
	cout << "error!! point out of map" << endl;
	//getchar();
	return Gro[0];
}

ostream& operator << (ostream& out, Map& map)
{
	int w = map.width, h = map.height;
	
	Subject *temp_subject_pointer;
	
	out << "start output" << endl;
#ifdef PHONE_TEST
	
	
	for (int i = 0; i < w * h; i++)
	{
		//out << i;
		if (( temp_subject_pointer = map.Atk[i] ) != NULL)
		{
			switch (temp_subject_pointer -> display_feature)
			{
				case fire: //out << "f ";
								 out << "▲ ";
								break;
				case hit: //out << "h ";
								out << "★ ";
								break;
				default: out << "11"; break;
			}
		}
		else if (( temp_subject_pointer = map.Cha[i] ) != NULL)
		{
			
				switch (temp_subject_pointer -> display_feature)
				{
					case human: 
											out << "▼" << temp_subject_pointer -> name_head();
											break;
					case monster: //out << "o ";
											out << "◆ ";
											break;
					default: out << "22"; break;
				}
			
		}
		else if (( temp_subject_pointer = map.Obj[i] ) != NULL)
		{
			if (temp_subject_pointer -> getvisible())
			{
				switch (temp_subject_pointer -> display_feature)
				{
					case bomb: //out << "b ";
										out << "● ";
										break;
					case supply: //out << "s ";
										out << "◇ ";
										break;
					case treasure: //out << "t ";
										out << "☆ ";
										break;
					case monster_maker: //out << "m ";
										out << "○ ";
										break;
					default: out << "33"; break;
				}
			}
			else
			{
				//out << "w ";
				out << "■ ";
			}
		}
		else if(( temp_subject_pointer = map.Gro[i] ) != NULL)
		{
			
			switch ((temp_subject_pointer -> display_feature))
			{
				case wall: 	//out << "w ";
										out << "■ ";
										 break;
				default: out << "□ "; break;
			}
		}
		else
		{
			out << "4";
		}
		
		if (( i + 1 ) % w == 0)
		{
			putchar('\n');
		}
	}
	
#endif
	
#ifdef COMPUTER_TEST
	
	for (int i = 0; i < w * h; i++)
	{
		//out << i;
		if (( temp_subject_pointer = map.Atk[i] ) != NULL)
		{
			switch (temp_subject_pointer -> display_feature)
			{
				case fire: //out << "f ";
								 out << "** ";
								break;
				case hit: //out << "h ";
								out << "** ";
								break;
				default: out << "11"; break;
			}
		}
		else if (( temp_subject_pointer = map.Cha[i] ) != NULL)
		{
			
				switch (temp_subject_pointer -> display_feature)
				{
					case human: //out << "a ";
											out << "▼" << temp_subject_pointer -> name_head();
											break;
					case monster: //out << "o ";
											out << "● ";
											break;
					default: out << "22"; break;
				}
			
		}
		else if (( temp_subject_pointer = map.Obj[i] ) != NULL)
		{
			if (temp_subject_pointer -> getvisible())
			{
				switch (temp_subject_pointer -> display_feature)
				{
					case bomb:			out << "◆ ";
										break;
					case supply:		out << "◇ ";
										break;
					case treasure:		out << "★ ";
										break;
					case monster_maker: out << "¤ ";
										break;
					default:			out << "33 "; break;
				}
			}
			else
			{
				out << "■ ";
			}
		}
		else if(( temp_subject_pointer = map.Gro[i] ) != NULL)
		{
			
			switch ((temp_subject_pointer -> display_feature))
			{
				case wall:	out << "■ ";
										 break;
				default:	out << "   "; break;
			}
		}
		else
		{
			out << "4";
		}
		
		if (( i + 1 ) % w == 0)
		{
			putchar('\n');
		}
	}
	
#endif
	
	out << "end output" << endl;
	
	return out;
}