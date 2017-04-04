#include "webc/webc.hpp"
#include <stdio.h>
#include <fstream>
#include <vector>

#ifdef _WIN32
#include <direct.h>
#define mkdir_sys _mkdir
#else
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#define mkdir_sys(filename) mkdir(filename, 0766)
#endif // _WIN32



using namespace webc::utils;


//创建目录
bool fs::mkdir(std::string filename) {
	int ret = mkdir_sys(filename.c_str());
	return ret == 0;
}

//循环创建目录
bool fs::mkdir_c(std::string filename) {
	char buffer[5120] = { 0 };
	int bufferat = 0;
	std::vector<std::string> vec;
	//遍历字符串并按照分隔符分割
	for (unsigned int i = 0; i < filename.size(); i++) {
		if (filename[i] == '/' || filename[i] == '\\' || i == filename.size() - 1) {
			if (i == filename.size() - 1) {
				buffer[bufferat] = filename[i];
			}
			vec.push_back(buffer);
			bufferat = 0;
			memset(buffer, 0, 5120);
			continue;
		}
		buffer[bufferat] = filename[i];
		bufferat++;
	}
	//循环创建目录
	std::string path = "";
	for (unsigned int i = 0; i < vec.size(); i++) {
		path += vec[i] + "/";
		//如果不存在则创建
		if (!fs::exists(path)) {
			if (false == fs::mkdir(path))
				return false;
		}
	}
	return true;
}

//是不是目录
bool fs::isdir(std::string filename) {
	struct stat st;
	stat(filename.c_str(), &st);
	return ((st.st_mode & S_IFDIR) != 0);
}

//是不是文件
bool fs::isfile(std::string filename) {
	struct stat st;
	stat(filename.c_str(), &st);
	return (
		(st.st_mode == 0) &&
		((st.st_mode & S_IFDIR) == 0)
		);
}

//是否存在
bool fs::exists(std::string filename) {
	struct stat st;
	stat(filename.c_str(), &st);
	return st.st_mode != 0;
}

//写入文件（覆盖）
bool fs::write_content(std::string filename, std::string content) {
	std::ofstream fst(filename.c_str(), std::ios::out | std::ios::trunc);
	if (!fst) {
		fst.close();
		return false;
	}
	fst << content.c_str();
	fst.close();
	return true;
}

//追加写入
bool fs::append(std::string filename, std::string content) {
	std::ofstream fst(filename.c_str(), std::ios::app);
	if (!fst) {
		fst.close();
		return false;
	}
	fst << content.c_str();
	fst.close();
	return true;
}

//读取文件
std::string fs::read_content(std::string filename) {
	std::ifstream fst(filename.c_str());
	if (!fst) {
		fst.close();
		return "";
	}
	//获取文件大小
	fst.seekg(0, std::ios::end);
	int size = fst.tellg();
	fst.seekg(0, std::ios::beg);
	//读取
	char *buffer = new char[size + 1];
	if (!buffer) {
		fst.close();
		return "";
	}
	//删除数据
	memset(buffer, 0, size + 1);
	fst.read(buffer, size);
	fst.close();
	//返回数据
	std::string str(buffer);
	delete[] buffer;
	return str;
}