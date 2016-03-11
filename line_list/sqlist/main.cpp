#include <unistd.h>
#include "my_sqlist.h"

using namespace std;
int main()
{
	my_sqlist mylist;

	int count = 20;
	while(count){
		mylist.push_back(count--);
		mylist.show();
	}
//	my_sqlist sq = mylist;

	count = 10;
	while(count){
		mylist.erase(4);
		mylist.show();
		sleep(1);
		count--;
	}

//	sq = mylist;
//	sq.show();
//	while(count < 5){
//		sleep(1);
//		elem_type _val = 0;
//		mylist.pop_back(_val);
//		cout<<"val is :"<<_val<<endl;
//		mylist.show();
//		count++;
//	}
//
//	count = 1;
//	while(count < 20){
//		//elem_type pos = rand()%100;
//		mylist.insert(count, count);
//		mylist.show();
//		sleep(1);
//		count++;
//	}
	return 0;
}
