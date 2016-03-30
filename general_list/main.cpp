#include "general_list.hpp"

using namespace std;
int main()
{
	general_list LS("(1,3,5,(a, b,(c, d), e)");
	LS.print();
	return 0;
}
