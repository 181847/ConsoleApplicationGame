#include"File Bomb.cpp"

#define PHONE_TEST

//#define COMPUTER_TEST

#ifdef PHONE_TEST

#elif COMPUTER_TEST

#include<windows.h>

#endif

using namespace std;
/*
class MyString;

int find_char(MyString& s,const char& search_char);
void control_result(MyString& c,MyString& s);

class MyString
{
	private:
		char *buffer;
		int capacity;
		int size;
		
	public:
		MyString(int new_c = 30);
		MyString(const char* s);
		~MyString();
		
		void show();

		char& operator [] (int index);
		int size_of(){return size;}
		int get_control_input();
};






*/



int main()
{
	ControlString control_input;


	
	ControlString s2("uhjkn");
	ControlString s3("wsad ");
	ControlString s4("28465");
	ControlString s5(s4);
	
	int counter = 0;
	
	s3.show();
	s4.show();
	
	swap(s3, s4);
	
	s3.show();
	s4.show();
	
	
	/*
	
	while (counter ++ <= 1000)
	{
		control_input.get_control_input();
		
		
		cout << s2[control_input];
		cout << s3[control_input];
		cout << s4[control_input];
		
	
		
		
		putchar('\n');
		
		#ifdef PHONE_TEST
		usleep(289999);
		#elif COMPUTER_TEST
		Sleep(1);
		#endif
	}
	*/

	return 0;
}











/*

MyString::MyString(int new_c)
{
	capacity = new_c;
	buffer = new char[capacity + 1];
	size = 0;
	buffer[0] = '\0';
}

MyString::MyString(const char* s)
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

MyString::~MyString()
{
	delete [] buffer;
}

void MyString::show()
{
	for (int i=0;i < size ; i ++)
		putchar(buffer[i]);

	putchar('\n');
}

char& MyString::operator [] (int index)
{
	if (index >= 0 && index <= size)
		return buffer[index];
	else
	{
		cout << "out of the range" << endl;
		return buffer[0];
	}
		
}

int MyString::get_control_input()
{
	clock_t start_time=clock();
	
	size = 0;
	
	while(clock() - start_time < 0.1 * CLOCKS_PER_SEC && size < capacity)
	{
		if (kbhit())
		{
			buffer[size++] = getch();
		}
	}
	fflush(stdin);
	return size;
}

void control_result(MyString& c,MyString& s)
{
	int l = s.size_of();
	
	int action;
	
	for (l -= 1; l >= 0; l --)
	{
		if ((action = find_char(c,s[l]) ) >= 0)
		{
			switch (action)
			{
				case 0:cout << "up" << endl;goto control_result;
				
				case 1:cout << "down" << endl;goto control_result;
				
				case 2:cout << "left" << endl;goto control_result;
				
				case 3:cout << "right" << endl;goto control_result;
				
				case 4:cout << "boom" << endl;goto control_result;
			}
		}
		
	}

	control_result:;

}


int find_char(MyString& s,const char& search_char)
{
	for (int i = 0; s[i] != '\0'; i ++)
	{
		if (s[i] == search_char)
			return i;
	}
	return -1;
}
*/