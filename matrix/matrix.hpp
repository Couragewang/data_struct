#pragma once

#include <iostream>
#include <vector>
using namespace std;

#ifdef _SYM_
//对称矩阵存储，存储下三角
template<class T>
class symmetric_matrix{
	public:
		symmetric_matrix(unsigned int n = N)//n*n矩阵
			:n(_n), size(_n*(_n+1)/2)    //计算压缩存贮的节点个数
		{
			matrix = new T[size];
		}
		bool restore(T arr[][N], int line = N)
		{
			for(int i = 0; i <= line, i++){
				for(int j = 0;){
				}
			}
		}
		~symmetric_matrix()
		{
			if(matrix){
				delete []matrix;
			}
		}
	private:
		size_t n;   //矩阵阶数
		size_t size;//存储数组的大小
		T* matrix;
};

#else

//稀疏矩阵
template<class T>
struct trituple{
	int row;
	int col;
	T val;
	trituple(int _row = 0, int _col = 0, const T &_val = 0)
		:row(_row),
		col(_col),
		val(_val)
	{}
};

//使用数组方式来进行稀疏矩阵的压缩存储
template<class T>
class sparse_matrix{
	public:
		//使用一维数组传递二维参数
		sparse_matrix(T *_arr, size_t _row_size, size_t _col_size, T _invalid)
			:row_size(_row_size),
			col_size(_col_size),
			invalid(_invalid)
		{
			//读取初始数组，行优先.注意二维数组的存储方式
			for( int i = 0; i < _row_size; i++ ){
				for( int j = 0; j < _col_size; j++ ){
					//映射到二维数组中的下标，找到对应的val,判断是否合法
					if(_arr[i*_col_size+j] != _invalid){//有效数据，行优先保存到vector中
						//matrix.push_back(struct trituple<T>(i, j, _arr[i*_col_size+j]));
						matrix.push_back(trituple<T>(i, j, _arr[i*_col_size+j])); //C++可以去掉struct
					}
				}
			}
		}
		//拷贝构造 
		sparse_matrix(const sparse_matrix<T> &obj)
		{
			matrix = obj.matrix;
			row_size = obj.row_size;
			col_size = obj.col_size;
			invalid  = obj.invalid;
		}

		void display()
		{
			//当初插入的时候，是行优先的，所以，显示也是按照行优先来
			//所以，显示的时候，vector中的值肯定按照行优先，有序的方式按次访问
			//并且无需多次遍历
//			for(int i = 0; i < matrix.size(); i++){
//				cout<<"{ "<<matrix[i].row<<" "<<matrix[i].col<<" "<<matrix[i].val<<" }"<<"\t";
//			}
			cout<<endl;
			int index = 0;
			for( int i = 0; i < row_size; i++ ){
				for( int j = 0; j < col_size; j++ ){
					int k = 0;
					int total_elems = matrix.size();
					if(index < total_elems && matrix[index].row == i && matrix[index].col == j){
						cout<<"\t\033[32m"<<matrix[index].val<<"\033[0m";
						++index;
					}else{
						cout<<"\t"<<invalid;
					}
				//	while( k < total_elems ){
				//		int _row = matrix[k].row;
				//		int _col = matrix[k].col;
				//		if( i == _row && j == _col ){
				//			cout<<matrix[k].val;
				//		}else{
				//			cout<<"\t"<<invalid;
				//		}
				//	}
				}
				cout<<endl;
			}
		}


		//关于行优先的思考：转置到并压缩存储，行相同的elems，肯定连续存储，并且行数越小，存储位置整体越靠前
		//vector的存储数据的方式就好像甘蔗，每节存储的都是行相同元素，相邻节表示列相邻，并且节内部有序(同行不同列)，
		//节与节整体有序(一节表示一行，行行之间有序)

		//矩阵的转置,普通方式
		int transpose(sparse_matrix<T> &_target)
		{
			//存储的时候是行优先存储，转置后，行变列，列变行。
			//因此，变化之后的矩阵，再次压缩存储，对比于目前，就是列优先存储
			_target.row_size = col_size; //行号为目前的列
			_target.col_size = row_size; //列号为目前的行
			_target.invalid = invalid;   //无效元素相同

			//找出vactor中所有列相同的元素，插入新的vactor中，模拟转置之后的行优先存储
			for(int i = 0; i < col_size; i++){
				int total_size  = matrix.size();
				for(int j = 0; j < total_size; j++){
					if(matrix[j].col == i){ //找到第i行，i由小到达，并且表示转置之后的行，所以肯定是行优先
						_target.matrix.push_back(trituple<T>(matrix[j].col, matrix[j].row, matrix[j].val));
					}
				}
			}
			return 0;
		}

		//1. 类内部元素直接赋值
		//2. 统计原始矩阵中，每一列有效数据的个数(转置后，为每行元素的个数)
		//3. 根据2，可以统计出，转置后每行在vector中的起始下标
	    //4. 根据3，直接按照列优先遍历vactor，赋值给新vector	
		int fast_transport(sparse_matrix<T> &_target)
		{
			//1.
			//存储的时候是行优先存储，转置后，行变列，列变行。
			//因此，变化之后的矩阵，再次压缩存储，对比于目前，就是列优先存储
			_target.row_size = col_size; //行号为目前的列
			_target.col_size = row_size; //列号为目前的行
			_target.invalid = invalid;   //无效元素相同
			int i = 0;
			for( ; i < matrix.size(); i++ ){
				_target.matrix.push_back(trituple<T>());//扩容至目标大小
			}
			//2.
		    int *col_counts = new int[col_size];
			memset(col_counts, 0, sizeof(int)*col_size);
			for(int i = 0; i < matrix.size(); i++){ //遍历有效数据
				col_counts[matrix[i].col]++; //列号从0开始 col_counts下标对应列号, 内容对应该列元素的个数
			}

			//3.
			int *row_start = new int[col_size];
			memset(row_start, 0, sizeof(int)*col_size);
			row_start[0] = 0;//row_start按照列数来申请空间，其实就是转置后的行数,第一行的起始位置肯定为0
			for(int i = 1; i < col_size; i++){
				//row_start 下标对应转置后的行号（原始矩阵的列号，同上）, 内容对应该行在vector中的起始下标
				row_start[i] = row_start[i-1] + col_counts[i-1]; //新一行的起始位置 ＝ 上一行的起始位置 ＋ 上一行元素个数
			}

			//4.
			for(int i = 0; i < matrix.size(); i++){
				int row_index = row_start[matrix[i].col]; //col => 目标vector 中的起始下标
				_target.matrix[row_index].row = matrix[i].col;
				_target.matrix[row_index].col = matrix[i].row;
				_target.matrix[row_index].val = matrix[i].val;
				++(row_start[matrix[i].col]); //对应列中元素已经插入taget， 更新同列中后续在vector中的下标
			}

			delete []col_counts;
			delete []row_start;

			return 0;
		}

		~sparse_matrix()
		{}
	private:
		vector<trituple<T> > matrix;//保存三元组的数组
		size_t row_size;  //原始矩阵的行号
		size_t col_size;  //原始矩阵的列号
		T invalid;        //稀疏矩阵的无效值，大部分是0
};

#endif






