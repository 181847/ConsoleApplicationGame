#include"Ground Bomb.h"

Subject_List* Ground::gl = new Ground_List;

Ground::Ground()
:next(NULL)
{
	map[position] = this;
	*gl + this;
}

Ground::Ground(Feature new_display_feature, int new_life, int new_x, int new_y, Layer new_l)
:next(NULL), display_feature(new_display_feature), Subject(new_display_feature, new_life, new_x, new_y, new_l)
{
	map[position] = this;
	*gl + this;
}

Ground::Ground(Feature new_display_feature, int new_life, Point p)
:next(NULL), display_feature(new_display_feature), Subject(new_display_feature, new_life, p)
{
	map[position] = this;
	*gl + this;
}

Ground::Ground(const Ground& g)
:next(g.next), Subject(g)
{
	map[position] = this;
	*gl + this;
}

Ground::~Ground()
{
	map[position] = NULL;
}

void Ground::show()
{
	switch (display_feature)
	{
		case space: cout << "space" << endl;break;
		case wall: cout << "wall" << endl;break;
	}
}

/************link list************/

Ground_List::Ground_List()
{}