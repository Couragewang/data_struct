#include "matrix.hpp"

#define N 10

int main()
{
#ifdef _SYM_
	int arr[N][N]={
		{0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0},
	};
	symmetric_matrix<int> _matrix(10);
#else
	int arr[N][N]={
		{4,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0},
		{6,0,0,0,0,0,0,0,0,0},
		{0,4,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,6,0,0,0,8,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,9,0,0},
		{1,0,0,0,0,0,0,0,0,1},
	};
	sparse_matrix<int> _matrix((int *)arr, N, N, 0);
	_matrix.display();

	cout<<" 转置 ＝ 》 ";
	sparse_matrix<int> _target_matrix(NULL, 0, 0, 0);
	//_matrix.transpose(_target_matrix);
	_matrix.fast_transport(_target_matrix);
	_target_matrix.display();


#endif
	return 0;
}
