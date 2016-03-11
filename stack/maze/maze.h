#pragma once
#include <iostream>
#include <stack>

#define LINE_SIZE 10
#define COL_SIZE 10

typedef enum{ N=0, E, S, W, O}dir_t;
typedef struct{
	int line;
	int col;
}pos_t;

class man{
	public:
		man();
		~man();
		int next_dir();
		int next_pos();
		pos_t pos;
		dir_t dir;
};

class maze{
	public:
		maze();
		~maze();
		void show();
		bool maze_run(man &m, const pos_t &end);
		bool is_pos_pass(const pos_t &_pos);
		bool is_over(const pos_t &_pos, const pos_t &end);
		bool die_pos(const pos_t &_pos);
		bool foot(const pos_t &_pos);
	private:
		static int maze_map[LINE_SIZE][COL_SIZE];
};





