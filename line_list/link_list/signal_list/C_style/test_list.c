#include <stdio.h>
#include <unistd.h>
#include "mylist.h"

#define _INIT_VAL_ 10
//测试链表
node_ptr head = NULL;

//测试用例
void test_push()
{
	int count = _INIT_VAL_;
	while(count){
		push_front(head, count--);
		printf("test push_front : ");
		show_list(head);
		sleep(1);
	}

	count = _INIT_VAL_;
	while(count){
		push_back(head, count--);
		printf("test push_back : ");
		show_list(head);
		sleep(1);
	}

	count = _INIT_VAL_;
	while(count){
		push_back(head, count);
		push_front(head, count);
		printf("test push_back_front : ");
		show_list(head);
		count--;
		sleep(1);
	}
}

void test_pop()
{
	while( !is_empty(head) ){
		printf("test pop_front_back : ");
		pop_front(head);
		pop_back(head);
		show_list(head);
		sleep(1);
	}
}

void test_insert()
{
	int count = _INIT_VAL_;
	node_ptr _node = NULL;
	while(count){
		printf("test insert : pos : %d\n", count);
		if(find(head, 0, &_node)){
			insert(head, _node, -1);//节点之后插入
		}
		show_list(head);
		sleep(1);
		count--;
	}
}

void test_find()
{
	int count = _INIT_VAL_;
	elem_type _val = 0;
	while(count){
		get_elem(head, count, &_val);
		printf("test get_elem : %d, pos : %d\n" , _val, count--);
		show_list(head);
		sleep(1);
	}
}

void test_erase()
{
	int count = _INIT_VAL_;
	node_ptr _node = NULL;
	while(count){
		printf("test erase :  pos : %d\n", count);
		if(find(head, 0, &_node)){
			erase(head, _node);
		}
		show_list(head);
		sleep(1);
		count--;
	}
}

void test_other()
{
	printf("size : %d\n", size(head));
}

void begin_test()
{
	clear(head);
	int count = _INIT_VAL_;
	while(count){
		push_front(head, 0);
		count--;
	}
	show_list(head);
}

int main()
{
#ifdef	_DEBUG_
	printf("#################################### BEGIN AUTO TEST #################################\n");
	list_init(&head);
	test_push();
	test_pop();
	begin_test();//统一链表元素
	test_insert();
	begin_test();//统一链表元素
	test_find();
	begin_test();//统一链表元素
	test_erase();
	begin_test();//统一链表元素
	test_other();
	printf("#################################### AUTO TEST DONE ###################################\n");
#endif
	return 0;
}



