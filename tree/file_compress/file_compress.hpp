#pragma once

#include <iostream>
#include <string>
#include "huffman_tree.hpp"

typedef long long_type;

//1.描述单个8比特位的字符
struct uchar_info{
	unsigned char ch;         //对应的char
	long_type appear_count;   //在对应文件中出现的次数，权重
	std::string huffman_code; //该char对应的huffman编码
	uchar_info(int _appear_count = 0)
		:ch(0)
		,appear_count(_appear_count)
	{}
	bool operator > (const uchar_info &_uchar) const
	{
		return this->appear_count > _uchar.appear_count;
	}
	bool operator != (const uchar_info &_uchar)const
	{
		return this->appear_count > _uchar.appear_count;
	}
	uchar_info operator + (const uchar_info &_uchar)
	{
		return uchar_info(this->appear_count + _uchar.appear_count);
	}
};

//2. 文件压缩类
class file_compress{
	private:
		void show_code(int ch, const std::string &code)
		{
			std::cout<<ch<<" : ";
			std::string::const_iterator _iter = code.begin();
			for(; _iter != code.end(); _iter++){
				std::cout<<*_iter<<' ';
			}
			std::cout<<std::endl;
		}

		void generate_huffman_code(huffman_node<uchar_info> *_root)
		{
			if(_root){
				//采用后序遍历的方式
				generate_huffman_code( _root->left );
				generate_huffman_code( _root->right );
				//只有叶子节点才是真真正正需要huffman编码
				if(_root->left == NULL && _root->right == NULL){
					std::string &code = file_infos[_root->weight.ch].huffman_code; //huffman编码的引用
					huffman_node<uchar_info> *curr = _root;
					huffman_node<uchar_info> *parent = _root->parent;
					while(parent){
						if(parent->left == curr){
							code += '0';
						}else{
							code += '1';
						}
						curr = parent;
						parent = curr->parent;
					}
				    //寻找编码是从叶子节点到根节点，所以要对编码进行逆置
				    reverse(code.begin(), code.end());
					show_code(_root->weight.ch, code);
				}
			}
		}
	public:
		file_compress()
		{
			for( int i = 0; i < 256; ++i ){
				file_infos[i].ch = i;
			}
		}

		bool compress(const std::string &file_name)
		{
			long long uchar_count = 0;
			//1. 读取文件统计字符出现的次数
			FILE *fin = fopen(file_name.c_str(), "rb");//按照读二进制方式打开文件
			if( NULL == fin ){
				perror("fopen");
				return false;
			}
			//2. 循环读取文件
			while(!feof(fin)){
				unsigned char ch = fgetc(fin);
				if( !feof(fin) ){
			    	file_infos[ch].appear_count++;   //在对应文件中出现的次数，权重
			    	++uchar_count;
				}
			}

			//3. 根据字符出现的次数，构建huffman树, 并生成huffman code
			huffman_tree<uchar_info> _tree;
			uchar_info invalid(0); //huffman中不需要出现次数为0的字符
			_tree.create_huffman_tree(file_infos, 256, invalid); //构建huffman
			generate_huffman_code(_tree.get_root());

			//4. 开始进行压缩
			std::string compress_file = file_name;
			compress_file += ".compress";
			FILE *fout = fopen(compress_file.c_str(), "wb");
			if( NULL == fout ){
				perror("fopen");
				fclose(fin);
				return false;
			}
			
			fseek(fin, 0, SEEK_SET);
			int pos = 0;
			unsigned char value = 0;

			while( !feof(fin) ){
				unsigned char ch = fgetc(fin);
				if( !feof(fin) ){//检测文件结尾，搜索一下feof的问题
					std::string &code = file_infos[ch].huffman_code;
					std::string::iterator _iter = code.begin();
					for( ; _iter != code.end(); ++_iter ){
						value <<= 1;
						if( *_iter == '1' ){
							value |= 1;
						}
						if( ++pos == 8 ){//按照8比特为单位进行写入
							fputc(value, fout);
							pos = 0;
							value = 0;
						}
					}
				}
			}
			//对于非文本类文件，他的比特位置不一定按照8为基本单位, 可能就是二进制流
			if(pos){
				value <<= (8-pos);
				fputc(value, fout);
			}
			fflush(fout);//刷新数据到文件

			//5. 便于恢复，写入配置文件
			std::string conf_file = file_name;
			conf_file += ".config";
			FILE *fconf = fopen(conf_file.c_str(), "wb");
			if( NULL == fconf ){
				perror("fopen");
				fclose(fin);
				fclose(fout);
				return false;
			}
			fclose(fin);
			fclose(fout);
			fclose(fconf);
			return true;
		}
		~file_compress()
		{}
	private:
		uchar_info file_infos[256]; //对于我们的压缩，是按照8比特来进行处理的,所以最多有256种
};



















