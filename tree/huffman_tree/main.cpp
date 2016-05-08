#include "huffman_tree.hpp"

#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int a, int b)
{
	return a>b;
}

static void show_vec(const vector<int> &_v)
{
	std::vector<int>::const_iterator _iter = _v.begin();
	for(; _iter != _v.end(); _iter++ ){
		cout<<*_iter<<" ";
	}
	cout<<endl;
}

int main()
{
	int a[]={1,2,3,4,5,6,8,9,0,23,4};
	int len = sizeof(a)/sizeof(a[0])-1;
	std::vector<int> _vec(a, a+len);
	//std::cout<<_vec.size()<<std::endl;
	//std::vector<int>::iterator _iter = _vec.begin();
	//for(; _iter != _vec.end(); _iter++ ){
	//	cout<<*_iter<<" "<<endl;
	//}
	//堆的使用
	//默认最大堆
	make_heap(_vec.begin(), _vec.end());
	std::vector<int>::iterator _iter = _vec.begin();

	//添加比较函数，让他变成最小堆
	make_heap(_vec.begin(), _vec.end(), cmp);
	show_vec(_vec);

	//添加元素
	_vec.push_back(-1);
	show_vec(_vec);
	make_heap(_vec.begin(), _vec.end(), cmp);
	show_vec(_vec);

	//删除元素
	pop_heap(_vec.begin(), _vec.end(), cmp);
	show_vec(_vec);
	int val = _vec[_vec.size()-1];
	_vec.pop_back();
	cout<<val<<endl;
	show_vec(_vec);
	sort_heap(_vec.begin(), _vec.end(), cmp);
	//sort_heap(_vec.begin(), _vec.end());
	show_vec(_vec);
	return 0;
}






