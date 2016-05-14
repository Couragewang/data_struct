#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include "huffman_tree.hpp"

template<class T>
void type_to_string(const T _val, std::string &_str_res)
{
	std::stringstream ss;
	ss<<_val;
	ss>>_str_res;
}

template<class T>
void string_to_type(const std::string _str, T &_val_res)
{
	std::stringstream ss;
	ss<<_str;
	ss>>_val_res;
}

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
		return this->appear_count != _uchar.appear_count;
	}
	uchar_info operator + (const uchar_info &_uchar)
	{
		return uchar_info(this->appear_count + _uchar.appear_count);
	}
};

std::ostream& operator<<(std::ostream &os, const uchar_info &_info)
{
	os<<"debug : "<<(int)_info.ch<<":"<<_info.appear_count<<std::endl;;
	return os;
}

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

		//读取配置文件，肯定是普通文本文件
		int read_line(FILE *fconf, std::string &line)
		{
			assert(fconf);
			char ch;
			
			line = "";
			int count = 0;
			do{
				ch = fgetc(fconf);
			//	if( ch == EOF ){
			//		break;
			//	}

				if( feof(fconf) ){ //到达文件结尾
					break;
				}

				line += ch;
				count++;
			}while( ch != '\n' );
			return count;
		}

		void init()
		{
			for( int i = 0; i < 256; ++i ){
				file_infos[i].ch = i;
				file_infos[i].appear_count = 0;
			}
		}

	public:
		file_compress()
		{
			init();
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

			std::cout<<"compress : +++++++++++++++++++++++++++"<<std::endl;
			_tree.level_order();
			std::cout<<"compress : +++++++++++++++++++++++++++"<<std::endl;

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
						if( ++pos >= 8 ){//按照8比特为单位进行写入
							fputc(value, fout);
							pos = 0;
							value = 0;
						}
					}
				}
			}
			//对于非文本类文件，他的比特位置不一定按照8为基本单位, 可能就是二进制流
			if(pos){
				std::cout<<"before write in compress : "<<(int)value<<std::endl;
				value <<= (8-pos);
				fputc(value, fout);
				std::cout<<"after write in compress : "<<(int)value<<std::endl;
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
			
			//uchar_count;
			std::string config_str;
			type_to_string(uchar_count, config_str); 
			fputs(config_str.c_str(), fconf);
			fputc('\n', fconf);
//			std::string config_str;
//			type_to_string(uchar_count>>32, config_str); //long long 型变量提取高32位
//			fputs(config_str.c_str(), fconf);
//			fputc('\n', fconf);
//
//			config_str="";
//			type_to_string(uchar_count&0xffffffff, config_str); //long long 型变量提取低32位
//			fputs(config_str.c_str(), fconf);
//			fputc('\n', fconf);

			config_str="";
			std::string _count;
			for(int i = 0; i < 256; ++i ){
				if(file_infos[i] != invalid){ //当前字符已经经过编码，为有效节点
					_count="";
					config_str = file_infos[i].ch;
					config_str += ',';
					type_to_string(file_infos[i].appear_count, _count);
					config_str += _count;
					config_str +='\n';
					fputs(config_str.c_str(), fconf);
				}
			}

			fclose(fin);
			fclose(fout);
			fclose(fconf);
			return true;
		}

		bool uncompress(const std::string &file_name)
		{
			init();
			std::string config_file = file_name;
			config_file += ".config";
			FILE *fconf = fopen(config_file.c_str(), "rb");
			if( NULL == fconf ){
				std::cerr<<strerror(errno)<<std::endl;
				return false;
			}

			long long uchar_count; //读取原文件中字符的个数
			std::string _line;
			unsigned char ch;
			//char ch;
			read_line(fconf, _line);
			string_to_type(_line, uchar_count);

			std::cout<<"debug: total size : "<<uchar_count<<std::endl;

			while( read_line(fconf, _line) ){
				if ( _line == "\n" ){
					std::string _next_line;
					read_line(fconf, _next_line);
					_line += _next_line;
				}
				ch = _line[0];
				string_to_type(_line.substr(2), file_infos[ch].appear_count);
				std::cout<<"======================="<<std::endl;
				std::cout<<(int)ch<<":"<<file_infos[ch].appear_count<<std::endl;
				std::cout<<"======================="<<std::endl;
			}
			fclose(fconf);

			//3. 根据字符出现的次数，构建huffman树
			huffman_tree<uchar_info> _tree;
			uchar_info invalid(0); //huffman中不需要出现次数为0的字符
			_tree.create_huffman_tree(file_infos, 256, invalid); //构建huffman

			std::cout<<"uncompress : +++++++++++++++++++++++++++"<<std::endl;
			_tree.level_order();
			std::cout<<"uncompress : +++++++++++++++++++++++++++"<<std::endl;

			//4. 打开目标解压文件和原始压缩文件
			std::string compress_file = file_name;
			compress_file += ".compress";
			FILE *fin = fopen(compress_file.c_str(), "rb");
			if( NULL == fin ){
				std::cerr<<strerror(errno)<<std::endl;
				return false;
			}
			std::string uncompress_file = file_name;
			uncompress_file += ".uncompress";
			FILE *fout = fopen(uncompress_file.c_str(), "wb");
			if( NULL == fout ){
				std::cerr<<strerror(errno)<<std::endl;
				fclose(fin);
				return false;
			}

			//5. 开始解压
			//根据压缩文件字符编码再Huffman树中寻找对应的字符
			huffman_node<uchar_info> *root = _tree.get_root();
			huffman_node<uchar_info> *curr = root;

			//fseek(fin, 0, SEEK_END);//定位文件结尾
			//int file_size = ftell(fin);
			//fseek(fin, 0, SEEK_SET);

			//if(file_size > 0){
			//	unsigned char *file_p = new unsigned char[file_size+1];
			//}
			////将整个文件读进内存
			//fread(file_p, 1, file_size, fin);

			int pos = 8;
			ch = fgetc(fin);
			while(1){
				--pos;
				if( ch & (1<<pos) ){
					curr = curr->right;
				}else{
					curr = curr->left;
				}
				if(curr && curr->left == NULL && curr->right == NULL){
					fputc(curr->weight.ch, fout);
					std::cout<<"write debug : "<<(int)curr->weight.ch<<std::endl;
					curr = root;
					if( --uchar_count == 0 ){
						break;
					}
				}
				if( pos <= 0 ){
					pos = 8;
					ch = fgetc(fin);
					continue;
				}
			}

			fclose(fin);
			fclose(fout);
			//delete[]file_p;
			return true;
		}

		~file_compress()
		{}
	private:
		uchar_info file_infos[256]; //对于我们的压缩，是按照8比特来进行处理的,所以最多有256种
};

