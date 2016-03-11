#include "mystack.h"

static void print_log(const char *str)
{
#ifdef _DEBUG_
	std::cout<<"log : "<<str<<std::endl;
#endif
}

mystack::mystack()
{
	base = top = NULL;
	stack_size = 0;
}

bool mystack::stack_realloc()
{
	print_log("stack is full, realloc!");
	int _len = stack_length();// get stack length current

	data_type *tmp = new(std::nothrow) data_type[stack_size+INC_SIZE+1];
	if( NULL == tmp ){
		return false;
	}
	memcpy(tmp, base, sizeof(data_type)*stack_size);
	delete []base;
	base = tmp;
	top  = base + _len;
	stack_size = stack_size + INC_SIZE;
	return true;
}

bool mystack::init_stack()// init stack
{
	base = new(std::nothrow) data_type[INI_SIZE+1];//1 is nouse;
	if( NULL == base ){
		std::cerr<<""<<std::endl;
		return false;
	}
	top = base;
	stack_size = INI_SIZE;
	return true;
}

bool mystack::destroy_stack()// destroy stack, stack don't exist
{
	delete []base;
	base = top = NULL;
	stack_size = 0;
	return true;
}

bool mystack::clear_stack()// clear stack, stack is exist
{
	top = base;
	stack_size = 0;
	return true;
}

bool mystack::is_stack_empty()
{
	if( base == top ){
		return true;
	}else{
		return false;
	}
}

bool mystack::is_stack_full()
{
	int len = stack_length();
	if( len >= stack_size ){
		return true;
	}else{
		return false;
	}
}

int  mystack::stack_length()// get stack length current
{
	//return (top - base)/sizeof(data_type);
	return (top - base);
}


bool mystack::get_top(data_type &_data)
{
	if( is_stack_empty() ){
		return false;
	}else{
		_data = *(top -1);
		return true;
	}
}

bool mystack::push(const data_type &_data)// push data
{
	if( !is_stack_full() || stack_realloc() ){
		*top = _data;
		top++;
		return true;
	}else{
		return false;
	}
}

bool mystack::pop(data_type &_data)//  pop data
{
	if( is_stack_empty() ){
		return false;
	}else{
		_data = *(--top);
		return true;
	}
}

bool mystack::stack_traverse(bool (*visit)(const data_type &_data))//call visit function for all elem
{
	data_type *start = base;
	bool flag = false;
	for(; start < top; start++ ){
		flag = true;
		if( !visit(*start) ){
			return false;
		}
	}
	std::cout<<std::endl;
	return flag;
}

mystack::~mystack()
{
	destroy_stack();// destroy stack, stack don't exist
}

