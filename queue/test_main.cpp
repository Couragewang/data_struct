#include <iostream>
#include "myqueue.hpp"

using namespace std;

int main()
{
	myqueue<int> q;
	q.push(1);
	q.print();
	q.push(2);
	q.print();
	q.push(3);
	q.print();
	q.push(4);
	q.print();
	q.push(5);
	q.print();
	q.push(6);
	q.print();
	q.push(7);
	q.print();
	q.push(8);
	q.print();

	q.pop();
	q.print();
	q.pop();
	q.print();
	q.pop();
	q.print();
	q.pop();
	q.print();
	q.pop();
	q.print();
	q.pop();
	q.print();
	q.pop();
	q.print();
	q.pop();
	q.print();
	return 0;
}
