#include <iostream>
#include <unistd.h>
#include "mylist.h"

using namespace std;

int main()
{
	mylist _list;
	int i = 0;
	while(i<10){
		_list.push_front(i++);
	}
	_list.show_list();
	sleep(1);
	_list.pop_front();
	_list.show_list();
	return 0;
}
