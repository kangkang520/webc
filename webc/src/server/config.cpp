#include "webc/webc.hpp"

using namespace std;
using namespace webc::server;
using namespace webc::utils;

json::Value value = NULL;

json::Value config::get_config(std::string filepath) {
	if (value != NULL)
		return value;
	//获取配置文件内容
	std::string json_str = fs::read_content(filepath);
	if (json_str == "") {
		std::cerr << "读取配置文件错误（无法读取，可能是文件不存在或被占用）" << endl;
		throw new exception("读取配置文件错误（无法读取，可能是文件不存在或被占用）");
		return NULL;
	}
	//解析jeson
	json::Reader reader;
	if (!reader.parse(json_str, value))  // reader将Json字符串解析到root，root将包含Json里所有子元素   
	{
		std::cerr << "读取配置文件错误(无法解析，可能是语法错误)" << endl;
		throw new exception("读取配置文件错误(无法解析，可能是语法错误)");
		return NULL;
	}
	std::clog << "配置已加载" << std::endl;
	//返回数据
	return value;
}