#pragma once

#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;

enum TYPE{
	HEAD_TYPE = 0,   //附加头节点
	VALUE_TYPE = 1,  //存储值节点
	SUB_TYPE = 2,    //指向子表
};

//广义表节点类型
class general_list_node{
	friend class general_list;
	public:
		general_list_node(TYPE _type = VALUE_TYPE, const int _value = 0)
			:type(_type),
			next(NULL),
			value(0)
		{
			if( type == VALUE_TYPE ){
				value = _value;
			}
			if( type == SUB_TYPE ){
				sub_link = NULL;
			}
		}

	private:
		TYPE type;                 //节点类型
		general_list_node *next;   //指向同一层下一个节点的指针
		union{
			char value;           //如果是存储值节点，则该域保存数值
			general_list_node *sub_link;  //如果是指向子表节点，则指向新节点
		};
};

//广义表
class general_list{
	private:
		bool is_value(char ch)
		{
			if( isdigit(ch)  || isalpha(ch) ){ //是数字或者是字母
				return true;
			}else{
				return false;
			}
		}

		void _print(general_list_node *&_head)
		{
			general_list_node *_begin = _head;
			while(_begin){
				//1. 头节点，打印'('
				//2. 值节点，打印数值
				//3. 子表节点，递归打印子表
				if(_begin->type == HEAD_TYPE){
					cout<<'(';
				}else if(_begin->type == VALUE_TYPE){
					cout<<(char)_begin->value;
					if(_begin->next){ //还有后续节点
						cout<<',';
					}
				}else{//子表节点
					_print(_begin->sub_link);//递归打印后续子表，和当前表结构一致，只是规模变小
					if(_begin->next){
						cout<<','; //当前后续还有节点
					}
				}
				_begin = _begin->next;
			}
			cout<<')';
		}
	public:
		general_list(const std::string &_str="")
			:head(NULL)
		{
			const char *str = _str.c_str();
			create_list(head, str);
		}

		void create_list(general_list_node *&_head, const char *&_str) //注意这里的引用类型！
		{
			if( *_str++ != '(' ){ //注意，判断完成之后，指向下一个字符
				cerr<<"invalid string"<<endl;
				return;
			}
			//创建该层头节点
			_head = new general_list_node(HEAD_TYPE); //进入该函数，首先建立本层表头
			general_list_node *_begin = _head;
			while(*_str != '\0'){ //注意这里的_str类型
				if( *_str == '(' ){ //此处是子表,递归建立后续子表 
					_begin->next = new general_list_node(SUB_TYPE);
					_begin = _begin->next;//指向新sub_link节点
					create_list(_begin->sub_link, _str); //递归建立子表结构 
				}else if( *_str == ')'){ //该层表结束
					return;
				}else if( is_value(*_str) ){
					_begin->next = new general_list_node(VALUE_TYPE, *_str++); //数值节点
					_begin = _begin->next;
				}else{
					++_str; //否则，跳过其他与表无关的字符
				}
			}
		}
		void print()
		{
			_print(this->head);
			cout<<endl;
		}
	private:
		general_list_node *head; //初始头指针
};





