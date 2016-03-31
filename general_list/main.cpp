#include "general_list.hpp"

using namespace std;
int main()
{
	//一层
	general_list g1("(a, b)");
	g1.print();
	cout<<"level 1 depth : "<<g1.depth()<<endl;
	cout<<"level 1 size : "<<g1.size()<<endl;

	//两层
	general_list g2("(a, b, (c, d))");
	g2.print();
	cout<<"level 2 depth : "<<g2.depth()<<endl;
	cout<<"level 2 size : "<<g2.size()<<endl;

	//三层 ＋ 有空格
	//general_list g3("(a, b, (c, d, (), (), (e,f,g), (f)))");
	general_list g3("(a, b, (c, d, (e,f,g), (f)))");
	g3.print();
	cout<<"level 3 depth : "<<g3.depth()<<endl;
	cout<<"level 3 size : "<<g3.size()<<endl;

	//多层空格嵌套
	general_list g4("((),(),((),(),((),(,()))))");
	g4.print();
	cout<<"level 4 depth : "<<g4.depth()<<endl;
	cout<<"level 4 size : "<<g4.size()<<endl;

	//复制或拷贝
	general_list g5(g3);
	g5.print();

	general_list g6 = g3;
	g3.print();

	//other
	general_list g7("(1, 2,(3,4),(5,(6),7))");
	g7.print();

	return 0;
}
