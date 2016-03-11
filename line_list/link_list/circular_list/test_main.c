#include "my_circular_list.h"
#include <unistd.h>

int main()
{
	node_ptr head = NULL;
	init_list(&head);
	
	int count = 10;
	while(count){
		push_back(head, count);
		show_list(head);
		sleep(1);
		count--;
	}
	while(count < 10){
		pop_front(head);
		show_list(head);
		sleep(1);
		count++;
	}
	return 0;
}
