#include "mystack.h"
using namespace std;

#ifndef _DEL_MAIN_
int main()
{
	mystack s;
	s.init_stack();
	int i = 1;
	int val = 0;
	scanf("%d", &val);
	while(val){
		int x = val%2;
		s.push(x);
		val = val/2;
	}

	while( !s.is_stack_empty() ){
		int e;
		s.pop(e);
		cout<<e;
	}
	cout<<endl;
//	while( i< 34 ){
//		s.push(i);
//		std::cout<<"length : "<<s.stack_length()<<::std::endl;
//		i++;
//		s.stack_traverse(mystack::stack_visit);//call visit function for all elem
//		sleep(1);
//	}
//
//	int tmp = 0;
//	while(i>23){
//		s.pop(tmp);
//		std::cout<<"top val is : "<<tmp<<std::endl;
//		s.stack_traverse(mystack::stack_visit);//call visit function for all elem
//		sleep(1);
//		i--;
//	}
//	s.get_top(tmp);
//	std::cout<<"top val is : "<<tmp<<std::endl;
//
//	std::cout<<"stack len is : "<<s.stack_length()<<std::endl;
//	s.clear_stack();
//	std::cout<<"stack len is : "<<s.stack_length()<<std::endl;
	
	return 0;
}
#endif
