#include <iostream>
#include "maze.h"
using namespace std;

int main()
{
	man boy;
	boy.pos.line = 1;
	boy.pos.col = 1;
	boy.dir = N;
	pos_t end = {8, 8};

	maze m;
	m.show();
	m.maze_run(boy, end);
	cout<<endl;
	m.show();
	return 0;
}





