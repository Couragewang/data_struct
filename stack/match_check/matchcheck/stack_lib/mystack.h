#ifndef _STACK_
#define _STACK_

#include <iostream>
#include <string.h>
#include <unistd.h>

//typedef int data_type;
typedef char data_type;
const int INI_SIZE = 32;
const int INC_SIZE = 32;

class mystack{
	public:
		mystack();
		~mystack();
		bool init_stack();// init stack
		bool destroy_stack();// destroy stack, stack don't exist
		bool clear_stack();// clear stack, stack is exist
		bool is_stack_empty();//
		bool is_stack_full();
		int  stack_length();// get stack length current

		bool get_top(data_type &_data);//  get top val
		bool push(const data_type &_data);// push data
		bool pop(data_type &_data);//  pop data

		bool stack_traverse(bool (*visit)(const data_type &_data));//call visit function for all elem
		//static bool stack_visit(const data_type &_data);
        static bool stack_visit(const data_type &_data)
        {
//        	std::cout<<_data<<" "<<std::endl;
        	std::cout<<_data<<" ";
        	return true;
        }
	private:
		bool stack_realloc();

	private:
		data_type *base;
		data_type *top;
		int stack_size;
};

#endif

