#include"Subject_List Bomb.h"

/************link list************/

Map Subject::map(30, 15);

Subject_List::Subject_List()
:head(NULL), cur(NULL), tail(NULL), num(0)
{}

void Subject_List::operator +(Subject* new_head)
{
	if (head == NULL)
	{
		head = tail = new_head;
	}
	else
	{
		new_head -> next = head;
	
		head = new_head;
	}
	
	num ++;
}

void Subject_List::clear()
{
	pre = cur = head;
	int test_counter = 0;
	if (head != NULL)
	do
	{
		//cout << "*************start  " << test_counter ++ << endl;
		
		if (cur -> life <= 0)
		{
			if (cur == head)
			{
				head = cur -> next;
				
				//Subject::map[cur -> position] = NULL;
				
				delete cur;
				
				num --;
			
				pre = cur = head;
			}
			else 
			{
				pre -> next = cur -> next;
				
				//Subject::map[cur -> position] = NULL;
				
				delete cur;
				num --;
				
				cur = pre -> next;
			}
		}
		else
		{
			pre = cur;
			cur = cur -> next;
		}
	} while (cur != NULL);
	
	//cout << "*******Test******" << endl;
	//usleep(300000);
}

void Subject_List::operator << (ControlString& command)
{}

void Subject_List::clear_all()
{
	cur = head;
	
	//cout << "*********start clear all********" << endl;
	
	while (cur != NULL)
	{
		//cout << "******* 1 ******" << endl;
		
		pre = cur;
		
		//cout << "******* 2 ******" << endl;
		
		cur = cur -> next;
		
		//cout << "******* 3 ******" << endl;
		
		delete pre;
		
		//cout << "******* 4 ******" << endl;
		
		num --;
		
		//cout << "******* num = " << num << " ******" << endl;
	}
	
	head = pre = cur = tail = NULL;
	
	//cout << "*********end clear all*********" << endl;
}

void Subject_List::exchange_control_panel()
{
	
}