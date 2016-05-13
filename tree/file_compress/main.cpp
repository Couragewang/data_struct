#include "file_compress.hpp"

int main()
{
	long long _val=1234;
	std::string _res;

	std::string file_name="data_file";
	file_compress _fc;
	_fc.compress(file_name);
	_fc.uncompress(file_name);


//	long long _tmp=0;
//	std::string res="1234";
//	//type_to_string(_tmp, res);
//	//printf("%s\n", res.c_str());
//
//	string_to_type(res, _tmp);
//	printf("%lld\n", _tmp);
	return 0;
}
