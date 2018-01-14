#include"Point Bomb.h"

//#ifndef POINT_BOMB_CPP
//#define SUBJECT_BOMB_CPP

using namespace std;

Direction& operator += (Direction& d, int i)
{
	switch (d)
	{
	case UP: d = DOWN; break;
	case DOWN: d = LEFT; break;
	case LEFT: d = RIGHT; break;
	case RIGHT: d = UP; break;
	}

	return d;
}

Direction rand_direction()
{
	switch (rand() % 4 + 1)
	{
		case 1: return UP;
		case 2: return DOWN;
		case 3: return LEFT;
		case 4: return RIGHT;
		default: return UP;
	}
}



Point::Point()
:x(0), y(0), l(atk)
{}


Point::Point(int new_x, int new_y, Layer new_l)
:x(new_x), y(new_y), l(new_l)
{}

Point::Point(const Point& p)
:x(p.x), y(p.y), l(p.l)
{}

		
void Point::show()
{
	cout << '(' << x << ',' << y << ',';
	switch(l)
	{
		case atk: cout << "atk)" << endl;break;
		case obj: cout << "obj)" << endl;break;
		case cha: cout << "cha)" << endl;break;
		case gro: cout << "gro)" << endl;break;
	}
}

Layer Point::getlayer()
{
	return l;
}

Point& Point::operator += (Direction move_direction)
{
	switch (move_direction)
	{
		case UP: if (y > 0) y--;break;
		case DOWN: y++;break;
		case LEFT: if (x > 0) x--;break;
		case RIGHT: x++;break;
	}
	
	return *this;
}

Point Point::operator + (Layer new_layer)
{
	return Point(x, y, new_layer);
}

Point Point::operator + (Direction move_direction)
{
	switch (move_direction)
	{
		case UP: return Point(x, (y > 0 ? y - 1 : y), l);break;
		case DOWN: return Point(x, y + 1, l);break;
		case LEFT: return Point((x > 0 ? x - 1 : x), y, l);break;
		case RIGHT: return Point(x + 1, y, l);break;
	}
	
	return *this;
}

Point Point::operator = (const Point& p)
{
	x = p.x;
	y = p.y;
	l = p.l;

	return *this;
}

int Point::operator - (const Point & p)
{
	return fabs(x - p.x) + fabs(y - p.y);
}



//#endif