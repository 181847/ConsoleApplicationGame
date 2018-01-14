#pragma once
#include"Character Bomb.h"
#include<fstream>

int creat_object(const char * file_name, Layer l, int num = 0);

#ifdef COMPUTER_TEST
void goto_xy(int x, int y);
#endif
