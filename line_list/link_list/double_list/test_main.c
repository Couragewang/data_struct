#include <unistd.h>
#include "double_list.h"

int main()
{
	dlist_t dlist;
	init_dlist(&dlist);

	int count = 0;
	while(count < 10){
		push_front(&dlist, count++); 
		show_dlist(&dlist);
		sleep(1);
	}

	while(count > 5){
		pop_front(&dlist);
		show_dlist(&dlist);
		sleep(1);
		count--;
	}

	node_ptr tmp = find(&dlist , 4);
	if(tmp){
		erase(&dlist, tmp);
	}
	show_dlist(&dlist);
	return 0;
}
