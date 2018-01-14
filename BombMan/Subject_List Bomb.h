#pragma once
#include"Map Bomb.h"


class Subject_List
{
	protected:
		Subject *head;
		Subject *pre;
		Subject *cur;
		Subject *tail;
		int num;
	public:
		Subject_List();
		
		void operator +(Subject* new_head);
		virtual void clear();
		virtual void clear_all();
		virtual void operator << (ControlString& command);
		virtual void exchange_control_panel();
		//void clear_death();
		
		friend Direction operator >> (Point p1, const Subject_List& cl);
};