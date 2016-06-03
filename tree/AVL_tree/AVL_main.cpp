#include "AVL_tree.hpp"

using namespace std;

//using namespace non_recursion;
using namespace recursion;
int main()
{
	//non_recursion
	/*
    AVL_tree<int, int> t1;
	//int a1[] = {3, 1, 2};
    int a1[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    
    for (int  i = 0; i < sizeof(a1)/sizeof(int); ++i)
    {
		t1.insert(a1[i], a1[i]);
    }
    
    t1.in_order();

    AVL_tree<int, int> t2;
    int a2[] = {164, 34, 7, 112, 92, 26, 18, 143, 152, 9, 21, 3, 123};

    for (int  i = 0; i < sizeof(a2)/sizeof(int); ++i)
    {
		t2.insert(a2[i], a2[i]);
    }
    
    t2.in_order();
    
    AVL_tree<int, int> t3;
	int a3[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
    for (int  i = 0; i < sizeof(a3)/sizeof(int); ++i)
    {
		t3.insert(a3[i], a3[i]);
    }
    
    t3.in_order();
    
    cout<<"t1是否平衡?:"<<t1.is_blance()<<endl;
    cout<<"t2是否平衡?:"<<t2.is_blance()<<endl;
    cout<<"t3是否平衡?:"<<t3.is_blance()<<endl;
	*/

	//recursion
	test_avl();

    return 0;
}





