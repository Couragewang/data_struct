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
	trituple(int _row, int _col, const T &_val)
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

		~sparse_matrix()
		{}
	private:
		vector<trituple<T> > matrix;//保存三元组的数组
		size_t row_size;  //原始矩阵的行号
		size_t col_size;  //原始矩阵的列号
		T invalid;        //稀疏矩阵的无效值，大部分是0
};

#endif


