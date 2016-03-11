#include <iostream>
#include <unistd.h>
#include "mystack.h"
using namespace std;

bool equal_symbol(char x, char y)
{
	switch(x){
		case '(':
			return y==')'?true:false;
		case '[':
			return y==']'?true:false;
		case '{':
			return y=='}'?true:false;
		case '<':
			return y=='>'?true:false;
		default:
			return false;
	}
}

//学生此时处于数据结构学习阶段，
//stl并未讲解，所以此处直接使用原生数据类型
bool match_check(char *str)
{
	mystack _s;
	_s.init_stack();
	char _val;
	char *start = str;
	while(*start != '\0'){
	//	sleep(1);
	//	cout<<*start<<endl;
		switch(*start){
			case '(':
			case '[':
			case '{':
			case '<':
				_s.push(*start);
				break;
			case ')':
			case ']':
			case '}':
			case '>':
				{
					if(_s.get_top(_val)){
//	     				cout<<"get top is : "<<_val<<endl;
//						if(_val == *start){
						if(equal_symbol(_val, *start)){
//							cout<<"equal : "<<_val <<" == "<<*start<<endl;
							_s.pop(_val);
						}else{
							_s.push(*start);
							//return false;
						}
					}else{
						_s.push(*start);
					}
				}
				break;
			default:
				break;
		}
		start++;
	}
	if( _s.is_stack_empty() ){
		return true;
	}else{
		return false;
	}
}

int main()
{
	cout<<"Please Enter String: ";
	fflush(stdout);
	char buf[128];
	memset(buf, '\0', sizeof(buf));
	cin>>buf;
	if(match_check(buf)){
		cout<<buf<<" -> "<<"ok";
	}else{
		cout<<buf<<" -> "<<"false";
	}
	cout<<endl;
	return 0;
}

