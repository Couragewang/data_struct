#include "maze.h"
using namespace std;

int maze::maze_map[LINE_SIZE][COL_SIZE]={
	1,1,1,1,1,1,1,1,1,1,
	1,0,0,1,0,0,0,1,0,1,
	1,0,0,1,0,0,0,1,0,1,
	1,0,0,0,0,1,1,1,0,1,
	1,0,1,1,1,1,1,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,1,0,1,1,1,1,0,1,
	1,0,1,0,0,0,0,0,0,1,
	1,1,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,
};

man::man()
{
	//pos = {0, 0};
	dir = N;
}
man::~man()
{
	//do nothing
}

int man::next_dir()
{
	switch(dir){
		case N:
			dir = E;
			break;
		case E:
			dir = S;
			break;
		case S:
			dir = W;
			break;
		case W:
			dir = O;//over
			break;
		case O:
			return 1;
		defaule:
			return 1;
	}
	return 0;
}

int man::next_pos()
{
	switch(dir){
		case N:
			pos.line--;
			break;
		case E:
			pos.col++;
			break;
		case S:
			pos.line++;
			break;
		case W:
			pos.col--;
			break;
		default:
			return -1;
	}
	return 0;
}


maze::maze()
{
	//do nothing
}

void maze::show()
{
	int i = 0;
	int j = 0;
	for(;i < LINE_SIZE; i++){
		cout<<"\t\t\t\t";
		for(j = 0; j<COL_SIZE; j++){
			cout<<maze_map[i][j]<<' ';
		}
		cout<<endl;
	}
}

bool maze::is_pos_pass(const pos_t &_pos)
{
	int i = _pos.line;
	int j = _pos.col;
	if( i >= 0 && i < LINE_SIZE &&  j>=0 && j < COL_SIZE ){
		if( maze_map[i][j] == 0 ){ //为0表示没有走过，并且可通
			return true;
		}
	}
	return false;
}

bool maze::is_over(const pos_t &_pos, const pos_t &end)
{
	if( _pos.line == end.line && _pos.col == end.col ){
		return true;
	}else{
		return false;
	}
}

bool maze::die_pos(const pos_t &_pos)
{
	int i = _pos.line;
	int j = _pos.col;
	if( i >= 0 && i < LINE_SIZE &&  j >= 0 && j < COL_SIZE ){
		maze_map[i][j] = 4;
		return true;
	}else{
		return false;
	}
}

bool maze::foot(const pos_t &_pos)
{
	int i = _pos.line;
	int j = _pos.col;
	if( i >= 0 && i < LINE_SIZE &&  j >= 0 && j < COL_SIZE ){
		maze_map[i][j] = 8;
		return true;
	}else{
		return false;
	}
}

bool maze::maze_run(man &m, const pos_t &end)
{
	//m.pos = start;
	std::stack<man> s;
	do{
		if(is_pos_pass(m.pos)){
			foot(m.pos);//留下脚印
			m.dir = N; //设定一个新的探索方向
			s.push(m); //当前位置方向入栈区
			if(is_over(m.pos, end)){ //当前是否已经到达了出口
				return true;
			}
			m.next_pos();//在新的探索方向上，迈向下一步
		}else{
			if( !s.empty() ){
				m = s.top();
				s.pop();
				while(m.dir == O && !s.empty()){//四个方向都已经探索过了
					die_pos(m.pos);//标记该位置是一条死路
					m = s.top();//回退到上一个位置
					s.pop();
				}
				if( m.dir != O ){
					m.next_dir();
					s.push(m);
					m.next_pos();
				}
			}
		}
	}while( !s.empty() );
	return false;
}

maze::~maze()
{
	//do nothing
}

