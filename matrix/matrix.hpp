#pragma once

#include <iostream>
using namespace std;

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
