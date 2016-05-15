#include <iostream>
#include <stack>
using namespace std;

template<class T>
class queue_by_2stack{
	public:
		queue_by_2stack()
		{}
		void push(const T &_val)
		{
			_s_in.push(_val);
		}
		//1.优先_s_out
		void pop()
		{
			if(_s_out.empty()){ //将_s_in栈中数据全部出栈，进入_s_out, 实现数据逆置，当时优先进入_s_in的数据，此时再_s_out的top！
				while( !_s_in.empty() ){
					_s_out.push(_s_in.top());
					_s_in.pop();
				}
			}
			_s_out.pop();
		}

		bool empty()
		{
			if( _s_in.empty() && _s_out.empty() ){
				return true;
			}
		}

		const T &front()
		{
		}

		const T &back()
		{
		}

		~queue_by_2stack()
		{}
	private:
		std::stack<T> _s_in; //数据统一push到该栈结构
		std::stack<T> _s_out;//pop
}

int main()
{
	queue_by_2stack<int> _q;
	_q.push(1);
	_q.push(2);
	_q.push(3);
	_q.push(4);
	_q.push(5);
	_q.push(6);
	_q.push(7);
	_q.push(8);

	while( !_q.empty() ){
		std::cout<<_q.front()<<" ";
		_q.pop();
	}
}




