#include <iostream>
#include <stack>
using namespace std;

bool is_operator(int exp)
{
	char *op_set = "+-*/()#";
	while(*op_set != '\0'){
		if( *op_set == exp ){
			return true;
		}
	}
	return false;
}

static int priority_val(int pri)
{
	switch(pri){
		case '+':
		case '-':
			return 0;
		case '*':
		case '/':
			return 1;
		case '(':
		case ')':
			return 2;
		case '#':
			return 3;
	}
}


//量化优先级
char precede(int top, int exp)
{

}

//保证输入表达式准确无误
int evauate_expression(char *exp)
{
	if(exp){
    	stack<int> _optr;//运算符栈
    	stack<int> _opnd;//运算数栈
    	_optr.push('#');
		while( exp != '#' ||  _opnd.top() != '#' ){
			if( !is_operator(*exp) ){ //如果不是运算符(运算数)
				_opnd.push(*exp);
				exp++;
			}else{//运算符
				switch(precede(_optr.top(), *exp)){
					case '<': //栈顶优先级低, 直接将高优先级运算符入栈
						_optr.push(*exp);
						exp++;
						break;
					case '=': //脱括号，'(' = ')' , '#' = '#'
						_optr.pop();
						exp++;
						break;
					case '>': //栈顶优先级高，进行运算，将结果入栈
						{
							int x = _opnd.top();
							_opnd.pop();
							int y = _opnd.top();
							_opnd.pop();
							char op = _optr.top();
							_optr.pop();
							_opnd.push(operator_data(x, op, y));
						}
						break;
				}//switch
			}//else
		}//while
		return _opnd.top();
	}
}

int main()
{
	return 0;
}
