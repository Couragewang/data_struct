#include <iostream>
using namespace std;
#define mut(a, b) (a)*(b)

int main()
{
	cout<<mut(10, 10)<<endl;
}
//class test{
//	private:
//		int a;
//	public:
//		test(int _a)
//		{
//			cout<<"construct"<<endl;
//		}
//		~test()
//		{
//		}
//	    const test& operator()(int _a)
//	    {
//	    	cout<<"operator : "<<_a<<endl;
//	    }
//};
//int main()
//{
//	test(3)(3);
////	char *p = "hello world";
////	while(*p){
////		cout<<(*++p)<<" "<<endl;
////	}
//}
//
////template<typename T>
////const T& sum(const T &x, const T &y, const T &z)
////{
////	cout<<"fun1"<<endl;
////	return x + y + z;
////}
////
////template<typename T1, typename T2>
////const T1& sum(const T1 &x, const T2 &y)
////{
////	cout<<"fun2"<<endl;
////	return x + y;
////}
////
////int main()
////{
////	int a = 10;
////	int b = 10;
////	int c = 10;
////	cout<<sum(a, b,c)<<endl;
////	double d = 3.14;
////	cout<<sum(d, a)<<endl;
////	return 0;
////}
////
////const T& add(const T &_val1, const T &_val2)
////{
////	return _val1+_val2;
////}
////
////int main()
////{
////	int a = 10;
////	int b = 10;
////	cout<<add(a, b)<<endl;
////
////	double x = 3.14;
////	double y = 2.18;
////	cout<<add(x, y)<<endl;
////
////	return 0;
////}
////
////
//////int main()
//////{
//////	int *p = new(std::nothrow) int[10000000000000000];
//////	if( p == NULL ){
//////		printf("new failed\n");
//////	}
//////	//else
//////		//delete []p;
//////	return 0;
//////}
////////  
////////  void operator sizeof(int a)
////////  {
////////  	cout<<"hello world"<<endl;
////////  }
////////  
////////  int main()
////////  {
////////  	sizeof(int);
////////  	return 0;
////////  }
////////  
////////typedef int* int_ptr;
////////
////////int main()
////////{
////////	int a = 10;
////////	int_ptr p = &a;
////////
////////	printf("%d\n", *p);
////////	char a[100];
////////	scanf("%s", a);
////////	printf("%s\n", a);
////////	if( isdigit(a) ){
////////		printf("this is a int\n");
////////	}else{
////////		printf("this is not a int\n");
////////	}
////////}
////////int fun(int sum)
////////{
////////	if(sum == 1)
////////	{
////////		return 1;
////////	}
////////	return sum+fun(--sum);
////////}
////////
////////int main()
////////{
////////	int sum = 0;
////////	scanf("%d", &sum);
////////	int ret = fun(sum);
////////	printf("%d\n", ret);
//////////	int *p = new(std::nothrow) int[1024*1024*1024*1024];
//////////	if(NULL == p){
//////////		std::cerr<<"alloc mem error"<<std::endl;
//////////	}
//////////	std::cout<<*p<<std::endl;
//////////
//////////	delete []p;
////////	return 0;
////////i}
