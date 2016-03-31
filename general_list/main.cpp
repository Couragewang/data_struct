#include "general_list.hpp"

using namespace std;
int main()
{
	general_list LS("(1,3,5,(a, b,(c, d), e)");
	LS.print();
	cout<<"depth : "<<LS.depth()<<endl;
	cout<<"size : "<<LS.size()<<endl;
	return 0;
}
