#include <iostream>
#include "mystack.h"

using namespace std;

void data_conversion(int data, int base)
{
	mystack _s;
	_s.init_stack();
	while(data){
		_s.push(data%base);
		data /= base;
	}
	cout<<"(";
	while(!_s.is_stack_empty()){
		_s.pop(data);
		cout<<data;
	}
	cout<<")"<<base;
	cout<<endl;
}

int main()
{
	int data = 0;
	int base = 0;
	cout<<"Plase Enter your data: ";
	fflush(stdout);
	cin>>data;

	cout<<"Please Enter your base: ";
	fflush(stdout);
	cin>>base;
	data_conversion(data, base);
	return 0;
}







