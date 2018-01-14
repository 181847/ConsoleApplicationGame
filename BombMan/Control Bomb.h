#pragma once
#include<time.h>
#include<conio.h>
//#include<windows.h>
#include<iostream>
#include<string>


#ifndef CONTROL_STRING_H
#define CONTROL_STRING_H


class ControlString
{
	private:
		char *buffer;
		int capacity;		int size;
		
	public:
		ControlString(int new_c = 30);
		ControlString(const char* s);
		ControlString(const ControlString& c);
		~ControlString();
		
		void show();

		char& operator [] (int index);
		int size_of(){return size;}
		int get_control_input();		int find_char(const char& search_char);
		int operator [](ControlString& s);
		ControlString& operator =(const ControlString& cs);
};

void swap(ControlString& c1, ControlString& c2);

//int find_char(ControlString& s,const char& search_char);
//int control_result(ControlString& c, ControlString& s);


#endif