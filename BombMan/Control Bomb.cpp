#include"Control Bomb.h"

using namespace std; 


ControlString::ControlString(int new_c)
{
	capacity = new_c;
	buffer = new char[capacity + 1];
	size = 0;
	buffer[0] = '\0';
}

ControlString::ControlString(const char* s)
{
	capacity = size = strlen(s);
	
	buffer = new char[capacity + 1];
	
	int i;
	for (i = 0; i < size;i ++)
	{
		buffer[i] = s[i];
	}
	buffer[i] = '\0';
}

ControlString::ControlString(const ControlString& c)
{
	capacity = c.capacity;
	size = c.size;
	
	buffer = new char[capacity + 1];
	int i;
	for (i = 0; i < size;i ++)
	{
		buffer[i] = c.buffer[i];
	}
	buffer[i] = '\0';
}

/*
ControlString::ControlString(const string& c)
{
	capacity = c.size() + 1;
	size = c.size();
	
	buffer = new char[capacity + 1];
	int i;
	for (i = 0; i < size;i ++)
	{
		buffer[i] = c.[i];
	}
	buffer[i] = '\0';
}
*/

ControlString::~ControlString()
{
	delete [] buffer;
}

void ControlString::show()
{
	for (int i=0;i < size ; i ++)
		putchar(buffer[i]);

	putchar('\n');
}

char& ControlString::operator [] (int index)
{
	if (index >= 0 && index <= size)
		return buffer[index];
	else
	{
		cout << "out of the range" << endl;
		return buffer[0];
	}
		
}

/*
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
*/
/*
int control_result(ControlString& c,ControlString& s)
{
	int l = s.size_of();
	
	int action;
	
	for (l -= 1; l >= 0; l --)
	{
		if ((action = c.find_char(s[l]) ) >= 0)   //if ((action = find_char(c,s[l]) ) >= 0)
		{
			switch (action)
			{
				case 0:cout << "up" << endl;return 0;
				
				case 1:cout << "down" << endl;return 1;
				
				case 2:cout << "left" << endl;return 2;
				
				case 3:cout << "right" << endl;return 3;
				
				case 4:cout << "boom" << endl;return 4;
			}
		}
	}
	
	return -1;
}
*/

int ControlString::operator [](ControlString& s)
{
    int l = s.size_of();
	
	int action;
	
	for (l -= 1; l >= 0; l --)
	{
		if ((action = find_char(s[l]) ) >= 0)   //if ((action = find_char(c,s[l]) ) >= 0)
		{
			switch (action)
			{
				case 0:return 0;
				
				case 1:return 1;
				
				case 2:return 2;
				
				case 3:return 3;
				
				case 4:return 4;
				
				/*
				
				case 0:cout << "up" << endl;return 0;
				
				case 1:cout << "down" << endl;return 1;
				
				case 2:cout << "left" << endl;return 2;
				
				case 3:cout << "right" << endl;return 3;
				
				case 4:cout << "boom" << endl;return 4;
				*/
			}
		}
	}
	
	return -1;
}

/*
int find_char(ControlString& s,const char& search_char)
{
	for (int i = 0; s[i] != '\0'; i ++)
	{
		if (s[i] == search_char)
			return i;
	}
	return -1;
}
*/
int ControlString::find_char(const char& search_char)
{
	for (int i = 0; buffer[i] != '\0'; i ++)
	{
		if (buffer[i] == search_char)
			return i;
	}
	return -1;
}

ControlString& ControlString::operator = (const ControlString& cs)
{
	capacity = cs.capacity;
	size = cs.size;
	
	buffer = new char[capacity + 1];
	int i;
	for (i = 0; i < size;i ++)
	{
		buffer[i] = cs.buffer[i];
	}
	buffer[i] = '\0';

	return *this;
}

void swap(ControlString& c1, ControlString& c2)
{
	ControlString temp;

	temp = c1;
	c1 = c2;
	c2 = temp;
}