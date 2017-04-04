//abc=xxx&aa[]=xxx&aa[]=xxx

#include "webc/webc.hpp"

using namespace webc::server;
using namespace std;


#define isarr(str) ((str[str.size()-1]==']') && (str[str.size()-2]=='['))



//构造函数
querystring::querystring(std::string str) {
	this->str = str;
}

//构造函数
querystring::querystring() {
	this->str = "";
}

//追加字符串
void querystring::append(std::string str) {
	this->str += str;
}

//转换
bool querystring::parse() {
	int ampp = 0;
	int eqp = 0;
	std::string key = "";
	std::string value = "";

	const char *_str = this->str.c_str();
	for (unsigned int i = 0; i < this->str.size(); i++) {
		if (_str[i] == '&') {
			ampp = i + 1;
		}
		else if (_str[i] == '=') {
			if (eqp != 0) {
				//不是第一个 = 符号，还需要计算出value
				value = string(_str + eqp, ampp - eqp - 1);
				this->add(key, value);
			}
			key = string(_str + ampp, i - ampp);
			eqp = i + 1;
		}
	}
	value = string(_str + eqp);
	this->add(key, value);
	return true;
}

//往map中添加元素
void querystring::add(std::string key, std::string value) {
	if (isarr(key)) {
		key = string(key.c_str(), key.size() - 2);
		vector<string> vec = (this->m_map[key].IsNull()) ? vector<string>() : this->m_map[key].cast<vector<string>>();
		vec.push_back(value);
		this->m_map[key] = vec;
	}
	else {
		this->m_map[key] = value;
	}
}