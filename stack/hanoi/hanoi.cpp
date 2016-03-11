//算法：
//   当只有一个盘子的时候，只需要从将A塔上的一个盘子移到C塔上。
//过程：
//1. 当A塔上有2个盘子时，先将A塔上的1号盘子（编号从上到下）移动到B塔上，再将A塔上的2号盘子移动的C塔上，最后将B塔上的小盘子移动到C塔上。
//2. 当A塔上有3个盘子时，先将A塔上编号1至2的盘子（共2个）移动到B塔上（需借助C塔），然后
//   将A塔上的3号最大的盘子移动到C塔，最后将B塔上的两个盘子借助A塔移动到C塔上。
//3. 当A塔上有n个盘子时，先将A塔上编号1至n-1的盘子（共n-1个）移动到B塔上（借助C塔），然后将
//   A塔上最大的n号盘子移动到C塔上，最后将B塔上的n-1个盘子借助A塔a动到C塔上。
//综上:
//   除了只有一个盘子时不需要借助其他塔外，其余情况均一样（只是事件的复杂程度不一样）。
#include <iostream>
using namespace std;

static int step_count = 0;//统计求解总步数
void move(char A, char C, int n)
{
	cout<<"step "<<++step_count<<": move disk ["<<n<<"] "<<A<<"->"<<C<<endl;
}

void hanoi(char A, char B, char C, int n)
{
	//当只有一个盘子的情况, 直接把1号盘子由 A－>C 即可
	if( 1 == n ){
		move(A, C, 1); //只有一张盘子, 把1号盘子，由A->C
	}else{//盘子个数大于1个
	   	hanoi(A, C, B, n-1);//step1. 把上面的n-1个盘子，借助C, 由A->B
		move(A, C, n);      //step2. 把A上面最大的n盘，直接由A->C
	   	hanoi(B, A, C, n-1);//step3. 问题和上面的类似, 此时， B（n-1）个盘子，A上没有盘子，
		                    //       C上有最大的盘子(可以看作空)。此时问题和前面的问题类似，只是规模变小了。
		                    //       此时，B等于以前的A, A等于以前的C， C等于以前的B, 递归，解决较小的规模的问题
	}
}

int main()
{
	char tower_a = 'A';
	char tower_b = 'B';
	char tower_c = 'C';
	int count = 0;
	cout<<"Please Enter you disk count : ";
	fflush(stdout);
	cin>>count;
	hanoi(tower_a, tower_b, tower_c, count);
	return 0;
}

